# Netty in Action

## Concepts
- Channel (Socket): For incoming(inbound) and outgoing(outbound) data

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
