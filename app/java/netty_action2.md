# Netty in Action

## SSL/TLS
Add SslHandler to the pipe as the first handler
```
public class SslChannelInitializer extends ChannelInitializer<Channel>{
   private final SslContext context;
   private final boolean startTls;
   
   public SslChannelInitializer(SslContext context,boolean startTls) {
      this.context = context;
      this.startTls = startTls;
   }
   
   @Override
   protected void initChannel(Channel ch) throws Exception {
      SSLEngine engine = context.newEngine(ch.alloc());
      ch.pipeline().addFirst("ssl", new SslHandler(engine, startTls));
   }
}
```

### HTTP/HTTPS

#### HTTP decoder, encoder, and codec
An HTTP request/response may consist of more than one data part, and it always 
terminates with a LastHttpContent part. The FullHttpRequest and FullHttpResponse 
messages are special subtypes that represent a complete request and response, 
respectively. All types of HTTP messages ( FullHttpRequest , LastHttpContent)
implement the HttpObject interface.

FullHttpRequest included HttpRequest (the first part of the HTTP request contains headers),
list of HttpContents(contains data and may be followed by one or more HttpContent parts), 
and LastHttpContent(marks the end of the HTTP request, and may contain trailing headers).


FullHttpResponse included HttpResponse (the first part of the HTTP response contains headers),
list of HttpContents(contains data and may be followed by one or more HttpContent parts), 
and LastHttpContent(marks the end of the HTTP response, and may contain trailing headers).

- HttpRequestEncoder: Encodes HttpRequest , HttpContent , and LastHttpContent messages to bytes.
- HttpResponseEncoder: Encodes HttpResponse , HttpContent , and LastHttpContent messages to bytes.
- HttpRequestDecoder: Decodes bytes into HttpRequest , HttpContent , and LastHttpContent messages.
- HttpResponseDecoder: Decodes bytes into HttpResponse, HttpContent , and LastHttpContent messages.

#### HttpPipelineInitializer
The class HttpPipelineInitializer simplifies the  HTTP support in application: 
merely add the correct ChannelHandlers to the ChannelPipeline.
```
public class HttpPipelineInitializer extends ChannelInitializer<Channel> {
   private final boolean client;
   public HttpPipelineInitializer(boolean client) {
      this.client = client;
   }
   @Override
   protected void initChannel(Channel ch) throws Exception {
      ChannelPipeline pipeline = ch.pipeline();
      if (client) {
        pipeline.addLast("decoder", new HttpResponseDecoder());
        pipeline.addLast("encoder", new HttpRequestEncoder());
      } else {
         pipeline.addLast("decoder", new HttpRequestDecoder());
         pipeline.addLast("encoder", new HttpResponseEncoder());
      }
   }
}
```

#### HTTP message aggregation

HTTP requests and responses are composed of many parts, each part is different 
HttpObject messages, it need to aggregate them to form complete messages. 
Netty provides an aggregator that merges message parts into FullHttpRequest 
and FullHttpResponse messages. There’s a slight cost to this operation because 
the message segments need to be buffered until complete messages can be forwarded 
to the next ChannelInboundHandler.
```
public class HttpAggregatorInitializer extends ChannelInitializer<Channel> {
   private final boolean isClient;
   public HttpAggregatorInitializer(boolean isClient) {
      this.isClient = isClient;
   }

   @Override
   protected void initChannel(Channel ch) throws Exception {
      ChannelPipeline pipeline = ch.pipeline();
      if (isClient) {
          pipeline.addLast("codec", new HttpClientCodec());
          //pipeline.addLast("decompressor",new HttpContentDecompressor());
          //clients to handle compressed content from the server
      } else {
          pipeline.addLast("codec", new HttpServerCodec());
          pipeline.addLast("compressor",new HttpContentCompressor());
          // server to compress the data if the client supports it. 
      }
      pipeline.addLast("aggregator",new HttpObjectAggregator(512 * 1024));
      // Add HttpObjectAggregator with a max message size of 512K
   }
}
```
#### HTTP compression

The client can indicate supported encryption modes by supplying the following header:
```
GET /encrypted-area HTTP/1.1
Host: www.example.com
Accept-Encoding: gzip, deflate
```

#### Use HTTPS
```
public class HttpsCodecInitializer extends ChannelInitializer<Channel> {
   private final SslContext context;
   private final boolean isClient;
   public HttpsCodecInitializer(SslContext context, boolean isClient) {
      this.context = context;
      this.isClient = isClient;
   }
   @Override
   protected void initChannel(Channel ch) throws Exception {
      ChannelPipeline pipeline = ch.pipeline();
      SSLEngine engine = context.newEngine(ch.alloc());
      pipeline.addFirst("ssl", new SslHandler(engine));
      
      if (isClient) {
         pipeline.addLast("codec", new HttpClientCodec());
      } else {
         pipeline.addLast("codec", new HttpServerCodec());
      }
   }
}
```

## WebSocket
A WebSocket provides “a single TCP connection for traffic in both directions.
Combined with the WebSocket API, it provides an alternative to HTTP polling 
for two-way communication from a web page to a remote server. WebSockets 
provide a true bidirectional exchange of data between client and server.
The communication starts as plain HTTP and upgrades to bidirectional WebSocket.

To add WebSocket support, need to include the appropriate client-side or 
server-side WebSocket ChannelHandler in the pipeline. This class will handle
the special message types defined by WebSocket, known as frames.

- BinaryWebSocketFrame: Data frame: binary data
- TextWebSocketFrame: Data frame: text data
- ContinuationWebSocketFrame: Data frame: text or binary data that belongs to a previous BinaryWebSocketFrame or TextWebSocketFrame
- CloseWebSocketFrame: Control frame: a CLOSE request, close status code, and a phrase
- PingWebSocketFrame: Control frame: requests a PongWebSocketFrame
- PongWebSocketFrame: Control frame: responds to a PingWebSocketFrame request

```
public class WebSocketServerInitializer extends ChannelInitializer<Channel>{
   @Override
   protected void initChannel(Channel ch) throws Exception {
      ch.pipeline().addLast(
         new HttpServerCodec(),
         new HttpObjectAggregator(65536),  //Provides aggregated HttpRequests for the handshake
         new WebSocketServerProtocolHandler("/websocket"),
         new TextFrameHandler(),     // handle TextWebSocketFrames
         new BinaryFrameHandler(),   // handle BinaryWebSocketFrames
         new ContinuationFrameHandler()); //handle ContinuationWebSocketFrames
   }
   public static final class TextFrameHandler extends SimpleChannelInboundHandler<TextWebSocketFrame> {
      @Override
      public void channelRead0(ChannelHandlerContext ctx,TextWebSocketFrame msg) throws Exception {
          // Handle text frame
      }
   }
   public static final class BinaryFrameHandler extends SimpleChannelInboundHandler<BinaryWebSocketFrame> {
      @Override
      public void channelRead0(ChannelHandlerContext ctx,BinaryWebSocketFrame msg) throws Exception {
          // Handle binary frame
      }
   }
   
   public static final class ContinuationFrameHandler extends SimpleChannelInboundHandler<ContinuationWebSocketFrame> {
      @Override
      public void channelRead0(ChannelHandlerContext ctx, ContinuationWebSocketFrame msg) throws Exception {
         // Handle continuation frame
      }
   }
}
```
To add security to WebSocket, simply insert the SslHandler as the first ChannelHandler in the pipeline.

### Idle connections and timeouts

Detecting idle connections and timeouts is essential to freeing resources in a timely manner. 
This is such a common task that Netty provides several ChannelHandler implementations for this purpose.

- IdleStateHandler 

Fires an IdleStateEvent if the connection idles too long. You can then handle the IdleStateEvent by overriding
userEventTriggered() in your ChannelInboundHandler .

- ReadTimeoutHandler

Throws a ReadTimeoutException and closes the Channel when no inbound data is received for a specified interval. The
ReadTimeoutException can be detected by overriding exceptionCaught() in your ChannelHandler.

- WriteTimeoutHandler

Throws a WriteTimeoutException and closes the Channel when no inbound data is received for a specified interval. The
WriteTimeoutException can be detected by overriding exceptionCaught() in your ChannelHandler .
```
public class IdleStateHandlerInitializer extends ChannelInitializer<Channel> {
   @Override
   protected void initChannel(Channel ch) throws Exception {
       ChannelPipeline pipeline = ch.pipeline();
          // sends an IdleStateEvent when triggered
       pipeline.addLast( new IdleStateHandler(0, 0, 60, TimeUnit.SECONDS));       
       pipeline.addLast(new HeartbeatHandler());
   }

   // Implements userEvent-Triggered() to send the heartbeat
   public static final class HeartbeatHandler extends ChannelStateHandlerAdapter {
       //The heartbeat to send to the remote peer
       private static final ByteBuf HEARTBEAT_SEQUENCE = Unpooled.unreleasableBuffer(Unpooled.copiedBuffer("HEARTBEAT", CharsetUtil.ISO_8859_1));

       @Override
       public void userEventTriggered(ChannelHandlerContext ctx, Object evt) throws Exception {
          if (evt instanceof IdleStateEvent) {
             ctx.writeAndFlush(HEARTBEAT_SEQUENCE.duplicate())
                .addListener(ChannelFutureListener.CLOSE_ON_FAILURE); //Sends the heartbeat and closes the connection if the send fails
          } else {
             super.userEventTriggered(ctx, evt); // Not an IdleStateEvent, so pass it to the next Chandler
          }
      }
   }
}
```

### Delimited protocols

Delimited message protocols use defined characters to mark the beginning or end of a message or message segment, often called a frame,
such as SMTP , POP3 , IMAP , and Telnet.
- DelimiterBasedFrameDecoder A generic decoder that extracts frames using any user-provided delimiter.
- LineBasedFrameDecoder A decoder that extracts frames delimited by the line-endings \n or \ r\n . This decoder is faster than DelimiterBasedFrameDecoder.
```
public class LineBasedHandlerInitializer extends ChannelInitializer<Channel> {
   @Override
   protected void initChannel(Channel ch) throws Exception {
      ChannelPipeline pipeline = ch.pipeline();
      pipeline.addLast(new LineBasedFrameDecoder(64 * 1024));
          //The LineBasedFrameDecoder forwards extracted frames to the next handler
      pipeline.addLast(new FrameHandler());  // Adds the FrameHandler to receive the frames
   }

   public static final class FrameHandler extends SimpleChannelInboundHandler<ByteBuf> {
      @Override
      // Passes in the contents of a single frame
      public void channelRead0(ChannelHandlerContext ctx, ByteBuf msg) throws Exception {
          // Do something with the data extracted from the frame
      }
   }
}
```

### Length-based protocols

A length-based protocol defines a frame by encoding its length in a header segment of
the frame, rather than by marking its end with a special delimiter.
- FixedLengthFrameDecoder: Extracts frames of a fixed size, specified when the constructor is called.
- LengthFieldBasedFrameDecoder: Extracts frames based on a length value encoded in a field in the frame header; the offset and length of the field are specified in the constructor.
```
public class LengthBasedInitializer extends ChannelInitializer<Channel> {
   @Override
   protected void initChannel(Channel ch) throws Exception {
      ChannelPipeline pipeline = ch.pipeline();
      pipeline.addLast(new LengthFieldBasedFrameDecoder(64 * 1024, 0, 8));
      pipeline.addLast(new FrameHandler());
   }

   public static final class FrameHandler extends SimpleChannelInboundHandler<ByteBuf> {
      @Override
      public void channelRead0(ChannelHandlerContext ctx, ByteBuf msg) throws Exception {
        // Do something with the frame
      }
   }
}
```
 ### Writing big data
Use an implementation of interface FileRegion a region of a file that is sent via a Channel that supports zero-copy file transfer.

```
FileInputStream in = new FileInputStream(file);   //Creates a FileInputStream
FileRegion region = new DefaultFileRegion(in.getChannel(), 0, file.length());
     //Creates a new DefaultFileRegion for the full length of the file
channel.writeAndFlush(region).addListener( //Sends the DefaultFileRegion and registers a ChannelFutureListener
    new ChannelFutureListener() {
       @Override
       public void operationComplete(ChannelFuture future) throws Exception {
           if (!future.isSuccess()) {
              Throwable cause = future.cause();
               // Do something
            }
        }
});
```

In cases where need to copy the data from the file system into user memory, use ChunkedWriteHandler, 
which provides support for writing a large data stream asynchronously without incurring high
memory consumption. The key is interface ChunkedInput<B> , where the parameter B is the type returned
by the method readChunk(). Four implementations of this interface are provided.  Each one represents 
a data stream of indefinite length to be consumed by a ChunkedWriteHandler:

- ChunkedFile: Fetches data from a file chunk by chunk, for use when your platform doesn’t
      support zero-copy or you need to transform the data. 
- ChunkedNioFile: Similar to ChunkedFile except that it uses FileChannel
- ChunkedStream: Transfers content chunk by chunk from an InputStream
- ChunkedNioStream: Transfers content chunk by chunk from a ReadableByteChannel

```
public class ChunkedWriteHandlerInitializer extends ChannelInitializer<Channel> {
   private final File file;
   private final SslContext sslCtx;
   public ChunkedWriteHandlerInitializer(File file, SslContext sslCtx) {
      this.file = file;
      this.sslCtx = sslCtx;
   }

   @Override
   protected void initChannel(Channel ch) throws Exception {
      ChannelPipeline pipeline = ch.pipeline();
      pipeline.addLast(new SslHandler(sslCtx.createEngine());
      pipeline.addLast(new ChunkedWriteHandler()); //Adds a ChunkedWriteHandler to handle data passed in as ChunkedInput
      pipeline.addLast(new WriteStreamHandler());  //WriteStreamHandler starts to write the file data once the connection is established.
   }
   public final class WriteStreamHandler extends ChannelInboundHandlerAdapter {
      //writes the file data using ChunkedInput when the connection is established.
      @Override
      public void channelActive(ChannelHandlerContext ctx) throws Exception {
         super.channelActive(ctx);
         ctx.writeAndFlush(new ChunkedStream(new FileInputStream(file)));
   }
}
```
To use your own ChunkedInput implementation install a ChunkedWriteHandler in the pipeline.

### Serializing data
JDK provides ObjectOutputStream and ObjectInputStream for serializing and
deserializing primitive data types and graphs of POJO s over the network.
It can be applied to any object that implements java.io.Serializable.

- CompatibleObjectDecoder:
Decoder for interoperating with non-Netty peers that use JDK serialization
- CompatibleObjectEncoder:
Encoder for interoperating with non-Netty peers that use JDK serialization
- ObjectDecoder:
Decoder that uses custom serialization for decoding on top of JDK serialization
- ObjectEncoder:
Encoder that uses custom serialization for encoding on top of JDK serialization

JBoss Marshalling is much faster than JDK serialization:

- CompatibleMarshallingDecoder/CompatibleMarshallingEncoder: 
For compatibility with peers that use JDK serialization.
- MarshallingDecoder/MarshallingEncoder:
For use with peers that use JBoss Marshalling. These classes must be used together.

```
public class MarshallingInitializer extends ChannelInitializer<Channel> {
   private final MarshallerProvider marshallerProvider;
   private final UnmarshallerProvider unmarshallerProvider;
   
   public MarshallingInitializer(UnmarshallerProvider unmarshallerProvider,MarshallerProvider marshallerProvider) {
      this.marshallerProvider = marshallerProvider;
      this.unmarshallerProvider = unmarshallerProvider;
   }

   @Override
   protected void initChannel(Channel channel) throws Exception {
      ChannelPipeline pipeline = channel.pipeline();
         pipeline.addLast(new MarshallingDecoder(unmarshallerProvider));  //Adds a MarshallingEncoder to convert POJOs to ByteBufs
         pipeline.addLast(new MarshallingEncoder(marshallerProvider));   //Adds a MarshallingDecoder to convert ByteBufs to POJOs
         pipeline.addLast(new ObjectHandler());   //Adds an ObjectHandler for normal POJOs that implement Serializable
   }

   public static final class ObjectHandler extends SimpleChannelInboundHandler<Serializable> {
      @Override
      public void channelRead0( ChannelHandlerContext channelHandlerContext, Serializable serializable) throws Exception {
          // Do something
      }
   }
}

```

Serialization via Protocol Buffers
The ChannelHandler implementations Netty supplies for protobuf support:

- ProtobufDecoder:
Decodes a message using protobuf
- ProtobufEncoder:
Encodes a message using protobuf
- ProtobufVarint32FrameDecoder:
Splits received ByteBuf s dynamically by the value of the Google Protocol “Base 128 Varints” a integer length field in the message
```
public class ProtoBufInitializer extends ChannelInitializer<Channel> {
   private final MessageLite lite;
   public ProtoBufInitializer(MessageLite lite) {
       this.lite = lite;
   }
   
   @Override
   protected void initChannel(Channel ch) throws Exception {
      ChannelPipeline pipeline = ch.pipeline();
      pipeline.addLast(new ProtobufVarint32FrameDecoder()); //Adds ProtobufVarint32FrameDecoder to break down frames
      pipeline.addLast(new ProtobufEncoder()); // Adds ProtobufEncoder to handle encoding of messages
      pipeline.addLast(new ProtobufDecoder(lite)); //Adds ProtobufDecoder to decode messages
      pipeline.addLast(new ObjectHandler());  Adds ObjectHandler to handle the decoded messages
   }
   public static final class ObjectHandler extends SimpleChannelInboundHandler<Object> {
      @Override
      public void channelRead0(ChannelHandlerContext ctx, Object msg) throws Exception {
         // Do something with the object
      }
   }
}
```

## WebSocket
A mechanism known as the upgrade handshake 3 is used to switch from standard HTTP
or HTTPS protocol to WebSocket. Thus, an application that uses WebSocket will
always start with HTTP/S and then perform the upgrade.


## UDP
Interface AddressedEnvelope and its default implementation:
```
interface AddressedEnvelope <M, A extends SocketAddress> extends ReferenceCounted
class DefaultAddressedEnvelope <M, A extends SocketAddress> implements AddressedEnvelope<M,A>
```
Defines a message that wraps another message with sender and recipient addresses. M is the message type; A is the address type

DatagramPacket: Extends DefaultAddressedEnvelope to use ByteBuf as the message data container.

```
class DatagramPacket extendsDefaultAddressedEnvelope <ByteBuf, InetSocketAddress> implements ByteBufHolder
```

Netty’s DatagramPacket is a simple message container used by DatagramChannel implementations to communicate with remote peers.
It carries the address of the recipient (and optionally, the sender) as well as the message payload itself.
Extend Netty’s MessageToMessageEncoder to convert customized messages to DatagramPacket.

All data to be transmitted is encapsulated in LogEvent messages.
The LogEventBroadcaster writes these to the channel, sending them through the
ChannelPipeline where they’re converted (encoded) into DatagramPacket messages.
Finally, they are broadcast via UDP and picked up by remote peers (monitors).

```
// LogEventEncoder creates DatagramPacket messages to be sent to the specified InetSocketAddress
public class LogEventEncoder extends MessageToMessageEncoder<LogEvent> {
   private final InetSocketAddress remoteAddress;
   public LogEventEncoder(InetSocketAddress remoteAddress) {
      this.remoteAddress = remoteAddress;
   }

   @Override
   protected void encode(ChannelHandlerContext channelHandlerContext, LogEvent logEvent, List<Object> out) throws Exception {
      byte[] file = logEvent.getLogfile().getBytes(CharsetUtil.UTF_8);
      byte[] msg = logEvent.getMsg().getBytes(CharsetUtil.UTF_8);
      ByteBuf buf = channelHandlerContext.alloc()
             .buffer(file.length + msg.length + 1); //Writes the filename to the ByteBuf
      buf.writeBytes(file);
      buf.writeByte(LogEvent.SEPARATOR); //Adds a SEPARATOR
      buf.writeBytes(msg); //Writes the log message to the ByteBuf
      out.add(new DatagramPacket(buf, remoteAddress));   //Adds a new DatagramPacket with the data and destination address to the list of outbound messages
   }
}
```
The main class, LogEventBroadcaster:
```
public class LogEventBroadcaster {
   private final EventLoopGroup group;
   private final Bootstrap bootstrap;
   private final File file;
   
   public LogEventBroadcaster(InetSocketAddress address, File file) {
      group = new NioEventLoopGroup();
      bootstrap = new Bootstrap();
      // Bootstraps the NioDatagram-Channel (connectionless)
      bootstrap.group(group).channel(NioDatagramChannel.class) 
        .option(ChannelOption.SO_BROADCAST, true)  //set SO_BROADCAST socket option
        .handler(new LogEventEncoder(address));
     this.file = file;
   }

   public void run() throws Exception {
      Channel ch = bootstrap.bind(0).sync().channel(); //Binds the channel
      long pointer = 0;
      for (;;) { // Starts the main processing loop
        long len = file.length();
        if (len < pointer) {  // file was reset
           pointer = len;  // If necessary, sets the file pointer to the last byte of the file
        } else if (len > pointer) {
           // Content was added
           RandomAccessFile raf = new RandomAccessFile(file, "r");
           raf.seek(pointer);  //Sets the current file pointer so nothing old is sent
           
           String line;
           while ((line = raf.readLine()) != null) {
               // For each log entry, writes a LogEvent to the channel
               ch.writeAndFlush(new LogEvent(null, -1, file.getAbsolutePath(), line));
           }
           pointer = raf.getFilePointer(); //Stores the current position within the file
           raf.close();
       }
       try {
           Thread.sleep(1000); //Sleeps for 1 second. 
       } catch (InterruptedException e) {
           Thread.interrupted();  //if interrupted, exits the loop; else restarts it.
           break; 
       }
     }
   }
   public void stop() {
      group.shutdownGracefully();
   }
   public static void main(String[] args) throws Exception {
      if (args.length != 2) {
          throw new IllegalArgumentException();
      }

      LogEventBroadcaster broadcaster = new LogEventBroadcaster(
          new InetSocketAddress("255.255.255.255",
          Integer.parseInt(args[0])), new File(args[1]));
      try {
          broadcaster.run();  // Creates and starts a new LogEventBroadcaster instance
      }
      finally {
          broadcaster.stop();
      }
   }
}
```
netcat is perfect for basic testing of this application; it just listens on a specified
port and prints all data received to standard output. Set it to listen for UDP data on
port 9999 as follows:
```
$ nc -l -u 9999
```

For the monitor:

- Receive UDP DatagramPacket s broadcast by the LogEventBroadcaster
- Decode them to LogEvent messages
- Write the LogEvent messages to System.out

public class LogEventDecoder extends MessageToMessageDecoder<DatagramPacket> {
   @Override
   protected void decode(ChannelHandlerContext ctx, DatagramPacket datagramPacket, List<Object> out) throws Exception {
      ByteBuf data = datagramPacket.data();  //Gets a reference to the data in the DatagramPacket
      int idx = data.indexOf(0, data.readableBytes(), LogEvent.SEPARATOR); //Gets the index of the SEPARATOR
      String filename = data.slice(0, idx).toString(CharsetUtil.UTF_8);
      String logMsg = data.slice(idx + 1,data.readableBytes()).toString(CharsetUtil.UTF_8); //Extracts the log message
      //Constructs a new LogEvent object and adds it to the list
      LogEvent event = new LogEvent(datagramPacket.remoteAddress(), System.currentTimeMillis(), filename, logMsg);
      out.add(event);
   }
}

//Extends SimpleChannelInboundHandler to handle LogEvent messages
public class LogEventHandler extends SimpleChannelInboundHandler<LogEvent> {
   // On exception, prints the stack trace and closes the channel
   @Override
   public void exceptionCaught(ChannelHandlerContext ctx,Throwable cause) throws Exception {
      cause.printStackTrace();
      ctx.close();
   }
   
   @Override
   public void channelRead0(ChannelHandlerContext ctx, LogEvent event) throws Exception {
      StringBuilder builder = new StringBuilder();
      builder.append(event.getReceivedTimestamp());
      builder.append(" [");
      builder.append(event.getSource().toString());
      builder.append("] [");
      builder.append(event.getLogfile());
      builder.append("] : ");
      builder.append(event.getMsg());
      System.out.println(builder.toString());
   }
}   
```

```
public class LogEventMonitor {
   private final EventLoopGroup group;
   private final Bootstrap bootstrap;
   
   public LogEventMonitor(InetSocketAddress address) {
     group = new NioEventLoopGroup();

     bootstrap = new Bootstrap();
     bootstrap.group(group)
        .channel(NioDatagramChannel.class) //Bootstraps the NioDatagramChannel
        .option(ChannelOption.SO_BROADCAST, true) //Sets the SO_BROADCAST socket option
        .handler( new ChannelInitializer<Channel>() {
          @Override
          protected void initChannel(Channel channel) throws Exception {
             ChannelPipeline pipeline = channel.pipeline();
             //Adds the ChannelHandlers 
             pipeline.addLast(new LogEventDecoder());
             pipeline.addLast(new LogEventHandler());
         }
       } )
      .localAddress(address);
   }

   public Channel bind() {
      return bootstrap.bind().sync().channel();
   }
   public void stop() {
      group.shutdownGracefully();
   }

   public static void main(String[] main) throws Exception {
      if (args.length != 1) {
        throw new IllegalArgumentException("Usage: LogEventMonitor <port>");
      }
      LogEventMonitor monitor = new LogEventMonitor(new InetSocketAddress(args[0]));
      try {
        Channel channel = monitor.bind();
        System.out.println("LogEventMonitor running");
        channel.closeFuture().sync();
      } finally {
        monitor.stop();
      }
   }
}
```
Run it:
```
mvn exec:exec -PLogEventBroadcaster
```


