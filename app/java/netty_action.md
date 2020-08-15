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


## Channel: implementations are thread-safe, can be stored and used to write data to the remote peer whenever needed
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
   
