# Netty in Action

## Concepts
- Channel (Socket): For incoming(inbound) and outgoing(outbound) data

Netty’s Channel implementations are thread-safe, so you can store a reference to a
Channel and use it whenever you need to write something to the remote peer, even
when many threads are in use.

- Events: triggerd by inbund data or an associated change of state, or the result of an operation

- ChannelHandler: Callback to handle events
     - @Sharable: can be safely shared by multiple channels

- ChannelFuture: Notify an application when an operation has completed, acts as a placeholder for the result of an async operation

- EventLoop:  An EventLoop is assigned to each Channel to handle all of the events. It is driven by only one thread that handles all of the I/O events for
one Channel and does not change during the lifetime of the EventLoop.
      - An EventLoopGroup contains one or more EventLoops.
      - An EventLoop is bound to a single Thread for its lifetime.
      - All I/O events processed by an EventLoop are handled on its dedicated Thread.
      - A Channel is registered for its lifetime with a single EventLoop.
      - A single EventLoop may be assigned to one or more Channels.

- ChannelPipeline: provides a container for a chain of ChannelHandlers and defines an API for propagating the flow of inbound and 
outbound events along the chain. When a Channel is created, it is automatically assigned its own ChannelPipeline.

- ChannelHandlerContext: 

When a ChannelHandler is added to a ChannelPipeline, it’s assigned a ChannelHandlerContext, which represents the binding 
between a ChannelHandler and the ChannelPipeline. Although this object can be used to obtain the underlying Channel,
it’s mostly utilized to write outbound data.

There are two ways of sending messages in Netty. You can write directly to the Channel or write to a ChannelHandlerContext object associated with a ChannelHandler. The former
approach causes the message to start from the tail of the ChannelPipeline, the latter causes the message to start from the next handler in the ChannelPipeline.

## Classes
- ChannelInitializer: a special class. When a new connection is accepted, a new child Channel will be created, and the Channel-
Initializer will add an instance of ChannelHandler to the Channel’s ChannelPipeline.

- ChannelInboundHandlerAdapter: server handler

      - channelRead()—Called for each incoming message
      - channelReadComplete()—Notifies the handler that the last call made to channel-Read() was the last message in the current batch
      - exceptionCaught()—Called if an exception is thrown during the read operation

- SimpleChannelInboundHandler<ByteBuf>: client handler to process the data
     
      - channelActive()—Called after the connection to the server is established
      - channelRead0()—Called when a message is received from the server
      - exceptionCaught()—Called if an exception is raised during processing


## Channel:

Implementations are thread-safe, can be stored and used to write data to the remote peer whenever needed

- eventLoop: return the EventLoop that is assigned to the Channel
- pipeline: return the ChannelPipeline (list of ChannelHandlers) that is assigned to the Channel
- isActive: return true if the Channel is active: TcpSocket is active if connected to the remote peer, and DatagramSocket is open
- localAddress: return the local SocketAddress
- remoteAddress: return the remote SocketAddress
- write: writes data to the remote peer. The data is passed to ChannelPipeline and queued until it is flushed
- flush: Flush the previously written data to the underlying transport, such as a Socket
- writeAndFlush: calling write followed by flush().  

wite/flush return ChannelFuture that can set the listener (ChannelFutureListener) to be called when the operation completed.

Channel transport Types
- NIO: io.netty.channel.socket.nio: Selector-based: TCP/UDP/SCTP/UDT: NioSocketChannel/NioServerSocketChannel/NioEventLoopGroup
- OIO: io.netty.channel.socket.oio: blocking stream: TCP/UDP/SCTP/UDT: OioSocketChannel/OioServerSocketChannel/OioEventLoopGroup
- EPoll: io.netty.channel.epoll: JNI for epoll() and non-blocking io: TCP/UDP: EpollSocketChannel/EpollServerSocketChannel/EpollEventLoopGroup
- Local: io.netty.channel.local: communication in the same VM via pipe
- Embedded: io.netty.channel.embedded: without a true network-based transport. Used for testing ChannelHandler

## ByteBuf
NIO uses ByteBuffer as byte container; while Nettys use ByteBuf. ByteBuf has both reader and write indices, while NIO ByteByffer has only one, so need to call mark()/flip() to switch between read and write modes.

BufferBuf could be in different modes:

- Heap buffer mode

Stores the data in the heap space of JVM ( via a backing array, memory allocated fromJVM heap):
```
ByteBuf heapBuf = ...;
if (heapBuf.hasArray()) {
   byte[] array = heapBuf.array();
   int offset = heapBuf.arrayOffset() + heapBuf.readIndex(); // offset of first byte
   int length = heapBuf.readableBytes(); // number of readable bytes
   handleArray(array, offset, length);
}
```
- Direct buffer mode

Memory is allocated via native calls, the contents resides outside of the normal garbage-collected heap, it can avoid copying the buffer contents before/after each invocation of a native IO operation. When data is in a heap-allocated buffer, JVM needs to copy the buffer data to a direct buffer internally before sending it through the socket. 

It is more expensive to allocate and release the direct buffer that the heap-based buffers, and may need to make a copy for the data is not in the heap:
```
ByteBuf directBuf = ...;
if (!directBuf.hasArray()) {
   int length = directBuf.readableBytes(); // number of readable bytes
   byte[] array = new byte[length];
   directBuf.getBytes(directBuf.readIndex(),array); // copy data into the array
   handleArray(array, 0, length);
}
```

- Composite node

Present an aggregated view of multiple ByteBufs, may include  both direct and notredict allocations
```
CompositeByteBuf msgBuf = Unpooled.compositeBuffer();
ByteBuf headerBuf = ...; // direct or nondirect
ByteBuf bodyBuf = ...; // direct or nondirect
messageBuf.addComponents(headerBuf,bodyBuf);
//messageBuf.removeComponents(0); //remove first component, headerBuf
for (ByteBuf buf : messageBuf) {
   System.out.println(buf.toString());
}
```
CompositeByteBuf resembles the direct buffer pattern to access the data:
```
CompositeByteBuf compBuf = Unpooled.compositeBuffer();
int length = compBuf.readableBytes(); // number of readable bytes
byte[] array = new byte[length];
compBuf.getBytes(compBuf.readIndex(),array); // copy data into the array
handleArray(array, 0, length);
```

### ByteBuf operations
- Drrived buffers
    - duplicate()
    - slice()/slice(int,int)
    - Unpooled.unmodifiableBuffer(...)
    - order(ByteOrder)
    - readSlice(int)
Each returns a new ByteBuf instance with its own reader,writer and marker indices, but the internal storage is shared.
The derived buffer is inexpensive to create, but when modify its contents, the source instance contents are modified.
If need a true copy of an existing buffer, use copy()/copy(int,int) to return an independent copy of the data.

- Read/write operations
    - get()/set(): start at a given index and leave it unchanged
    - read()/write(): start at a given index and adjust it by the number of bytes accessed
    
- ByteBufHolder
Interface to handle common use case for using ByteBuffer. It provides methods to access the underlying data and reference counting.

- ByteBuf allocation
    - on-demand: interface ByteBufAllocator with pooling to reduce the overhead of allocation and deallocating memory. ByteBufAllocator can be obtained from Channel( each have a distinct instance) or the ChannelHandlerContext that is bound to a ChannelHandler.
```
Channel channel = ...;
ByteBufAllocator alloc = channel.alloc();

ChannelHandlerContext ctx = ...;
ByteBufAllocator alloc = ctx.alloc();
```

   Netty provided 2 implementations of ByteBufAllocator: PooledByteBufAllocator and UnpolledByteBufAllocator. The former improves the performance and minimuzes memory fragmentation.
   
   Netty provides a utility class, Unpooled, to provide static helper methods to create unpooled ByteBuf instance when don't have a reference to a ByteBufAllocator. 
   
   ByteBufUtil provides static helper methods for manipulating a ByteBuf. hexdump() prints a hexdec representation of the content. boolean equals(NyteNuf, ByteBuf).
   
- Refernce counting

Both ByteBuf and ByteBufHolder implement interface ReferenceCounted, which is essential to pooling implementation. Trying to access a reference-counted object that’s been released will result in an IllegalReferenceCountException.

In ChannelHandler, it is responsible for explicitly releasing the memory associated with pooled ByteBuf instances. Prevent leaks in the implemement Channel-
InboundHandler.channelRead() and ChannelOutboundHandler.write().  Netty provides a utility method for this purpose, ReferenceCountUtil.release(msg). Netty provides class ResourceLeakDetector to diagnose potential problems. The detect levels are:

- DISABLED
- SIMPLE
- ADVANCED
- PARANOID

```
java -Dio.netty.leakDetectionLevel=ADVANCED
```
   
## Channel,ChannelHandler and ChannelPipeline
ChannelHandlers are chained together in a ChannelPipeline to organize processing logic.

### Channel Lifecycle
- ChannelUnregistered: The Channel was created, but isn’t registered to an EventLoop .
- ChannelRegistered: The Channel is registered to an EventLoop .
- ChannelActive:  The Channel is active (connected to its remote peer). It’s now possible to receive and send data.
- ChannelInactive: The Channel isn’t connected to the remote peer.

### ChannelHandler Lifecycle (with ChannelHandlerContext)
- handlerAdded: Called when a ChannelHandler is added to a ChannelPipeline
- handlerRemoved: Called when a ChannelHandler is removed from a ChannelPipeline
- exceptionCaught: Called if an error occurs in the ChannelPipeline during processing

### subinterfaces of ChannelHandler :
- ChannelInboundHandler: Processes inbound data and state changes of all kinds, Implemented classes: ChannelInboundHandlerAdapter, SimpleChannelInboundHandler(no need to release message)
    - channelRegistered: Invoked when a Channel is registered to its EventLoop and is able to handle I/O.
    - channelUnregistered: Invoked when a Channel is deregistered from its EventLoop and can’t handle any I/O.
    - channelActive: Invoked when a Channel is active; the Channel is connected/bound and ready.
    - channelInactive: Invoked when a Channel leaves active state and is no longer connected to its remote peer.
    
    - channelReadComplete: Invoked when a read operation on the Channel has completed.
    - channelRead: Invoked if data is read from the Channel .
    - channelWritabilityChanged: Invoked when the writability state of the Channel changes.
    - userEventTriggered: Invoked when ChannelnboundHandler.fireUserEventTriggered() is called  

- ChannelOutboundHandler —Processes outbound data and allows interception of all operations
    - bind(ChannelHandlerContext, SocketAddress,ChannelPromise): Invoked on request to bind the Channel to a local address
    - connect(ChannelHandlerContext, SocketAddress,SocketAddress,ChannelPromise): Invoked on request to connect the Channel to the remote peer
    - disconnect(ChannelHandlerContext,ChannelPromise): Invoked on request to disconnect the Channel from the remote peer
    - close(ChannelHandlerContext,ChannelPromise): Invoked on request to close the Channel    
    - deregister(ChannelHandlerContext,ChannelPromise): Invoked on request to deregister the Channel from its EventLoop
    
    - read(ChannelHandlerContext): Invoked on request to read more data from the Channel
    - flush(ChannelHandlerContext): Invoked on request to flush queued data to the remote peer through the Channel
    - write(ChannelHandlerContext,Object,ChannelPromise): Invoked on request to write data through the Channel to the remote peer
    
Most of the methods in ChannelOutboundHandler take a ChannelPromise argument to be notified when the operation completes. 
ChannelPromise is a subinterface of ChannelFuture that defines the writable methods, such as setSuccess() or setFailure( ), thus
making ChannelFuture immutable.    

Because consuming inbound data and releasing it is such a common task, Netty provides a special ChannelInboundHandler implementation called SimpleChannelInboundHandler . This implementation will automatically release a message once it’s consumed by channelRead0().

### ChannelPipeline
Every new Channel that’s created is assigned a new ChannelPipeline . This association is permanent; the Channel can neither attach another ChannelPipeline nor
detach the current one. This is a fixed operation in Netty’s component lifecycle and requires no action on the part of the developer. If an inbound event is triggered, it’s passed from the beginning to the end of the ChannelPipeline

A ChannelHandlerContext enables a ChannelHandler to interact with its ChannelPipeline and with other handlers. A handler can notify the next ChannelHandler
in the ChannelPipeline and even dynamically modify the ChannelPipeline it belongs to.

### ChannelHandlerContext
A ChannelHandlerContext represents an association between a ChannelHandler and
a ChannelPipeline and is created whenever a ChannelHandler is added to a ChannelPipeline.
The primary function of a ChannelHandlerContext is to manage the interaction of its 
associated ChannelHandler with others in the same ChannelPipeline .

If you invoke these methods on a Channel or ChannelPipeline instance, they propagate
through the entire pipeline. The same methods called on a ChannelHandlerContext
will start at the current associated ChannelHandler and propagate only to the next
ChannelHandler in the pipeline that is capable of handling the event.

The ChannelHandlerContext associated with a ChannelHandler never changes,
so it’s safe to cache a reference to it.
```
public class WriteHandler extends ChannelHandlerAdapter {
   private ChannelHandlerContext ctx;
   @Override
   public void handlerAdded(ChannelHandlerContext ctx) {
      this.ctx = ctx;
   }
   public void send(String msg) {
      ctx.writeAndFlush(msg);
   }
}
```
Because a ChannelHandler can belong to more than one ChannelPipeline , it can be
bound to multiple ChannelHandlerContext instances. A ChannelHandler intended
for this use must be annotated with @Sharable ; otherwise, attempting to add it to
more than one ChannelPipeline will trigger an exception. Clearly, to be safe for use
with multiple concurrent channels (that is, connections), such a ChannelHandler
must be thread-safe.
```
@Sharable
public class SharableHandler extends ChannelInboundHandlerAdapter {
   @Override
   public void channelRead(ChannelHandlerContext ctx, Object msg) {
      System.out.println("Channel read message: " + msg);
      ctx.fireChannelRead(msg);   //forwards to next Handler
   }
}
```
use @Sharable only if it is certain that ChannelHandler is thread-safe.

### Handling inbound exceptions

If an exception is thrown during processing of an inbound event, it will start to flow
through the ChannelPipeline starting at the point in the ChannelInboundHandler
where it was triggered. To handle such an inbound exception, you need to override
the following method in your ChannelInboundHandler implementation.
```
public class InboundExceptionHandler extends ChannelInboundHandlerAdapter {
   @Override
   public void exceptionCaught(ChannelHandlerContext ctx,Throwable cause) {
       cause.printStackTrace();
       ctx.close();
   }
}
```
Because the exception will continue to flow in the inbound direction (just as with all
inbound events), the ChannelInboundHandler that implements the preceding logic is
usually placed last in the ChannelPipeline . This ensures that all inbound exceptions
are always handled, wherever in the ChannelPipeline they may occur.

### Handling outbound exceptions
- Every outbound operation returns a ChannelFuture . The ChannelFutureListeners 
registered with a ChannelFuture are notified of success or error when the operation completes.
- Almost all methods of ChannelOutboundHandler are passed an instance of ChannelPromise.
As a subclass of ChannelFuture , ChannelPromise can also be assigned listeners for asynchronous notification.
```
ChannelPromise setSuccess();
ChannelPromise setFailure(Throwable cause);
```
Option 1: invoke addListener() on the ChannelFuture that is returned
by an outbound operation (for example write() )
```
ChannelFuture future = channel.write(someMessage);
future.addListener(new ChannelFutureListener() {
   @Override
   public void operationComplete(ChannelFuture f) {
      if (!f.isSuccess()) {
         f.cause().printStackTrace();
         f.channel().close();
      }
    }
});
```

Option 2: add a ChannelFutureListener to the ChannelPromise that is
passed as an argument to the ChannelOutboundHandler methods
```
public class OutboundExceptionHandler extends ChannelOutboundHandlerAdapter {
   @Override
   public void write(ChannelHandlerContext ctx, Object msg, ChannelPromise promise) {
      promise.addListener(new ChannelFutureListener() {
         @Override
         public void operationComplete(ChannelFuture f) {
             if (!f.isSuccess()) {
                f.cause().printStackTrace();
                f.channel().close();
              }
          }
     });
   }
}
```

## Eventloop
An EventLoop is powered by exactly one Thread that never changes,
and tasks ( Runnable or Callable ) can be submitted directly to EventLoop implementations 
for immediate or scheduled execution. Depending on the configuration and
the available cores, multiple EventLoop s may be created in order to optimize resource
use, and a single EventLoop may be assigned to service multiple Channels.

Netty’s EventLoop extends ScheduledExecutorService, defines parent() that returns a reference 
to the EventLoopGroup to which the current EventLoop instance belongs.
```
public interface EventLoop extends EventExecutor, EventLoopGroup {
    @Override
    EventLoopGroup parent();
}
```
All I/O operations and events are handled by the same Thread that has been assigned to the EventLoop, 

If the calling Thread is that of the EventLoop , the code block is executed. Otherwise, 
the EventLoop schedules a task for later execution and puts it in an internal queue. 
When the EventLoop next processes its events, it will execute those in the queue. 
Each EventLoop has its own task queue, independent of that of any other EventLoop.

Never put a long-running task in the execution queue, because it will block any other task from executing on the same thread.

The EventLoop s that service I/O and events for Channel s are contained in an EventLoopGroup.
Asynchronous implementations use only a few EventLoops (and associated Threads), and they
may be shared among Channels. This allows many Channels to be served by the smallest 
possible number of Threads, rather than assigning a Thread per Channel. Once a Channel 
has been assigned an EventLoop , it will use this EventLoop/Thread throughout its lifetime.

For OIO, one EventLoop/Thread is assigned to each Channel. It is guaranteed that the I/O events of 
each Channel will be handled by only one Thread.

## Bootstrap
Bootstrapping an application is the process of configuring it to run. A server application
devotes a parent channel to accepting connections from clients and
creating child channels for conversing with them, whereas a client will most likely
require only a single, non-parent channel for all network interactions.

It may need to create multiple channels that have similar or identical settings. 
To support this pattern without requiring a new bootstrap instance to be created
and configured for each channel, AbstractBootstrap has been marked Cloneable.
Calling clone() on an already configured bootstrap will return another bootstrap
instance that’s immediately usable. This creates only a shallow copy of the 
bootstrap’s EventLoopGroup, so the latter will be shared among all of the cloned channels.
```
public abstract class AbstractBootstrap <B extends AbstractBootstrap<B,C>,C extends Channel>

public class Bootstrap extends AbstractBootstrap<Bootstrap,Channel>: client or connectionless app

public class ServerBootstrap extends AbstractBootstrap<ServerBootstrap,ServerChannel>: server app
```
Client Application:
```
EventLoopGroup group = new NioEventLoopGroup();
Bootstrap bootstrap = new Bootstrap();
bootstrap.group(group)
  .channel(NioSocketChannel.class)
  .handler(new SimpleChannelInboundHandler<ByteBuf>() {
     @Override
     protected void channeRead0(ChannelHandlerContext ctx, ByteBuf byteBuf) throws Exception {
        System.out.println("Received data");
     }
  } );
ChannelFuture future = bootstrap.connect( new InetSocketAddress("www.manning.com", 80));
future.addListener(new ChannelFutureListener() {
    @Override
    public void operationComplete(ChannelFuture channelFuture) throws Exception {
        if (channelFuture.isSuccess()) {
           System.out.println("Connection established");
        } else {
           System.err.println("Connection attempt failed");
           channelFuture.cause().printStackTrace();
        }
    }
} );
```
Server Application:
```
NioEventLoopGroup group = new NioEventLoopGroup();
ServerBootstrap bootstrap = new ServerBootstrap();
bootstrap.group(group)
  .channel(NioServerSocketChannel.class)
  .childHandler(new SimpleChannelInboundHandler<ByteBuf>() {
     @Override
     protected void channelRead0(ChannelHandlerContext ctx, ByteBuf byteBuf) throws Exception {
         System.out.println("Received data");
     }
   });
ChannelFuture future = bootstrap.bind(new InetSocketAddress(8080));
future.addListener(new ChannelFutureListener() {
   @Override
   public void operationComplete(ChannelFuture channelFuture) throws Exception {
      if (channelFuture.isSuccess()) {
         System.out.println("Server bound");
      } else {
         System.err.println("Bound attempt failed");
         channelFuture.cause().printStackTrace();
      }
   }
});   
```
The EventLoop can be shared. 

To add multiple ChannelHandlers during a bootstrap use ChannelInitializer:

```
public abstract class ChannelInitializer<C extends Channel> extends ChannelInboundHandlerAdapter
{
    protected abstract void initChannel(C ch) throws Exception;
}

bootstrap.group(new NioEventLoopGroup(), new NioEventLoopGroup())
  .channel(NioServerSocketChannel.class)
  .childHandler(new ChannelInitializerImpl());

final class ChannelInitializerImpl extends ChannelInitializer<Channel> {
  @Override
  protected void initChannel(Channel ch) throws Exception {
    ChannelPipeline pipeline = ch.pipeline();
    pipeline.addLast(new HttpClientCodec());
    pipeline.addLast(new HttpObjectAggregator(Integer.MAX_VALUE));
  }
}
```

Use ChannelOption s to configure a Channel and an attribute to store properties and data.
Netty offers the AttributeMap abstraction, a collection provided by the channel and bootstrap 
classes, and AttributeKey<T> , a generic class for inserting and retrieving attribute values. 
With these tools, you can safely associate any kind of data item with both client and server Channel s.
```
final AttributeKey<Integer> id = new AttributeKey<Integer>("ID");
Bootstrap bootstrap = new Bootstrap();
bootstrap.handler(
    new SimpleChannelInboundHandler<ByteBuf>() {    
      @Override
      public void channelRegistered(ChannelHandlerContext ctx) throws Exception {
         Integer idValue = ctx.channel().attr(id).get();
         // do something with the idValue attribute with the AttributeKey and its value
      }
    }); 
     ...
bootstrap.     
bootstrap.attr(id, 123456);     
```
Bootstrapping DatagramChannels: use Bootstrap, don't need to call connect() but only bind().  
```
Bootstrap bootstrap = new Bootstrap();
bootstrap.group(new OioEventLoopGroup()).channel(OioDatagramChannel.class).handler(
   new SimpleChannelInboundHandler<DatagramPacket>(){
      @Override
      public void channelRead0(ChannelHandlerContext ctx, DatagramPacket msg) throws Exception {
         // Do something with the packet
      }
   }
);
ChannelFuture future = bootstrap.bind(new InetSocketAddress(0));
future.addListener(new ChannelFutureListener() { 
   @Override
   public void operationComplete(ChannelFuture channelFuture) throws Exception {
      if (channelFuture.isSuccess()) {
         System.out.println("Channel bound");
      } else {
         System.err.println("Bind attempt failed");     
         channelFuture.cause().printStackTrace();
      }
   }
});     
```

## Testing: EmbeddedChannel
Write inbound or outbound data into an EmbeddedChannel and then check whether anything 
reached the end of the ChannelPipeline to determine whether messages were encoded or 
decoded and whether any ChannelHandler actions were triggered.
```
writeInbound( Object... msgs) Writes an inbound message to the EmbeddedChannel . Returns
            true if data can be read from the EmbeddedChannel via readInbound() .
readInbound() Reads an inbound message from the EmbeddedChannel . Anything
            returned traversed the entire ChannelPipeline . Returns null if nothing is ready to read.
writeOutbound(Object... msgs) Writes an outbound message to the EmbeddedChannel . Returns
            true if something can now be read from the EmbeddedChannel via readOutbound() .
readOutbound() Reads an outbound message from the EmbeddedChannel . Anything
            returned traversed the entire ChannelPipeline . Returns null if nothing is ready to read.
finish() Marks the EmbeddedChannel as complete and returns true if either inbound or outbound data can be read. 
            This will also call close() on the EmbeddedChannel .
```
Inbound data is processed by ChannelInboundHandler s and represents data read from
the remote peer. Outbound data is processed by ChannelOutboundHandler s and repre-
sents data to be written to the remote peer. Use the \*Inbound() or \*Outbound() pairs of methods to test the ChannelHandlers.
```
@Test
public void testFramesDecoded2() {
  ByteBuf buf = Unpooled.buffer();
  for (int i = 0; i < 9; i++) {
     buf.writeByte(i);
  }
  
  ByteBuf input = buf.duplicate();
  EmbeddedChannel channel = new EmbeddedChannel(new FixedLengthFrameDecoder(3));
  assertFalse(channel.writeInbound(input.readBytes(2)));
  assertTrue(channel.writeInbound(input.readBytes(7)));
  assertTrue(channel.finish());

  ByteBuf read = (ByteBuf) channel.readInbound();
  assertEquals(buf.readSlice(3), read);
  read.release();
  read = (ByteBuf) channel.readInbound();
  assertEquals(buf.readSlice(3), read);
  read.release();

  read = (ByteBuf) channel.readInbound();
  assertEquals(buf.readSlice(3), read);
  read.release();
  assertNull(channel.readInbound());
  buf.release();
  
  EmbeddedChannel channel = new EmbeddedChannel(new AbsIntegerEncoder());
  assertTrue(channel.writeOutbound(buf));
  assertTrue(channel.finish());
  // read bytes
  for (int i = 1; i < 10; i++) {
    assertEquals(i, channel.readOutbound());
  }
  assertNull(channel.readOutbound());
}
```
## Codecs (encoder/decoder)
### Decoders
- Decoding bytes to messages: ByteToMessageDecoder and ReplayingDecoder
- Decoding one message type to another: MessageToMessageDecoder

Decoders are responsible for transforming inbound data from one format to
another, they implement ChannelInboundHandler.

#### ByteToMessageDecoder
Not know whether the remote peer will send a complete message all at once, this
class buffers inbound data until it’s ready for processing.
```
decode(ChannelHandlerContext ctx, ByteBuf in, List<Object> out);
   // This call is repeated until it is determined that no new items have been 
   // added to the List or no more bytes are readable in the ByteBuf
   // if the List is not empty, its contents are passed to the next handler in the pipeline
decodeLast(ChannelHandlerContext ctx,ByteBuf in,List<Object> out)
   // The default implementation provided by Netty simply calls decode(). 
   // This method is called once, when the Channel goes inactive. 
   // Override the method to provide special handling.
```
Sample
```
public class ToIntegerDecoder extends ByteToMessageDecoder {
  @Override
  public void decode(ChannelHandlerContext ctx, ByteBuf in, List<Object> out) throws Exception {
    if (in.readableBytes() >= 4) { // need to verify that the input ByteBuf has enough data
       out.add(in.readInt());
    }
  }
}
```
In the case of encoders and decoders, the reference counting procedure is quite simple:
once a message has been encoded or decoded, it will automatically be released by a call to
ReferenceCountUtil.release(message). If need to keep a reference for later use,
call ReferenceCountUtil.retain(message). This increments the reference count, 
preventing the message from being released.

#### ReplayingDecoder

ReplayingDecoder extends ByteToMessageDecoder, a special decode that frees us from having to call
readableBytes(). It wraps the incoming ByteBuf with a custom ByteBuf implementation, 
ReplayingDecoderBuffer , that executes the call internally.
```
public abstract class ReplayingDecoder<S> extends ByteToMessageDecoder

The parameter S specifies the type to be used for state management, where Void 
indicates that none is to be performed.

public class ToIntegerDecoder2 extends ReplayingDecoder<Void> {
  @Override
  public void decode(ChannelHandlerContext ctx, ByteBuf in, List<Object> out) throws Exception {
    out.add(in.readInt());
  }
}
```
ints extracted from the ByteBuf are added to the List. If insufficient bytes
are available, this implementation of readInt() throws an Error that will be caught
and handled in the base class. The decode() method will be called again when more
data is ready for reading.

Not all ByteBuf operations are supported. If an unsupported method is called,
an UnsupportedOperationException will be thrown.

#### MessageToMessageDecoder<I>
The parameter I specifies the type of the input msg argument to decode().
```
public abstract class MessageToMessageDecoder<I> extends ChannelInboundHandlerAdapter

decode(ChannelHandlerContext ctx, I msg, List<Object> out)
```
     
Netty provides a TooLongFrameException , which is intended to be thrown by decoders if a
frame exceeds a specified size limit.


### Encoders

an encoder implements ChannelOutboundHandler and transforms outbound data from one format to another.

#### MessageToByteEncoder
```
 encode(ChannelHandlerContext ctx, I msg, ByteBuf out)
    // called with the outbound message (of type I ) that this class will encode to a ByteBuf.
    // The ByteBuf is then forwarded to the next ChannelOutboundHandler in the pipeline.
public class ShortToByteEncoder extends MessageToByteEncoder<Short> {
  @Override
  public void encode(ChannelHandlerContext ctx, Short msg, ByteBuf out) throws Exception {
     out.writeShort(msg);
  }
}
```

#### MessageToMessageEncoder
```
encode(ChannelHandlerContext ctx, I msg, List<Object> out)

public class IntegerToStringEncoder extends MessageToMessageEncoder<Integer> {
  @Override
  public void encode(ChannelHandlerContext ctx, Integer msg, List<Object> out) throws Exception {
    out.add(String.valueOf(msg));
  }
}
```
### codec classes
Manage transformations of both inbound and outbound data and messages in one class. 
These classes implement both ChannelInboundHandler and ChannelOutboundHandler.

#### ByteToMessageCodec
```
decode(ChannelHandlerContext ctx, ByteBuf in, List<Object>) 
decodeLast(ChannelHandlerContext ctx,ByteBuf in,List<Object> out)
encode(ChannelHandlerContext ctx,I msg,ByteBuf out)
```
#### MessageToMessageCodec
```
public abstract class MessageToMessageCodec<INBOUND_IN,OUTBOUND_IN>

protected abstract decode(ChannelHandlerContext ctx, INBOUND_IN msg, List<Object> out)
protected abstract encode(ChannelHandlerContext ctx,OUTBOUND_IN msg,List<Object> out)
```

#### CombinedChannelDuplexHandler

Deploy a decoder and an encoder as a single unit, acts as a container for a ChannelInboundHandler and a ChannelOutbound-
Handler.

```
public class CombinedChannelDuplexHandler <I extends ChannelInboundHandler, O extends ChannelOutboundHandler>

public class CombinedByteCharCodec extends CombinedChannelDuplexHandler<ByteToCharDecoder, CharToByteEncoder> {
   public CombinedByteCharCodec() {
      super(new ByteToCharDecoder(), new CharToByteEncoder());
   }
}
```
