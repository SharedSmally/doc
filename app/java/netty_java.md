# [netty java API](https://netty.io/4.0/api/index.html?overview-summary.html)
- [Netty-in action](https://livebook.manning.com/book/netty-in-action/chapter-5/)

## Issues
- Decode called [multiple times](https://stackoverflow.com/questions/26531134/netty-decoder-method-called-multiple-times)

Simple solution: call clear() method.
The decoding mechanism is explained more in the Netty User Guide - Dealing with a Stream-based Transport. Multiple calls are made to ensure the full message bytes are received.

- [netty writeandflush not working] (https://stackoverflow.com/questions/28934777/netty-writeandflush-method-doesnt-work),
    - [second issue](https://stackoverflow.com/questions/43909348/netty-writeandflush-incomplete)
    - [third issue](https://stackoverflow.com/questions/22794326/not-able-to-send-byte-to-server-with-netty)

Solution: all writeandflush statements must end with "\r\n" in order to flush. With out that they dont flush. I don't understand why that is but whatever.

- netty cannot send byte[]

Solution: Need to add io.netty.handler.codec.bytes.ByteArrayEncoder and ByteArrayDecoder to do the transformation between byte[] and ByteBuf. The Netty socket only works directly with ByteBuf. 

- [execute handler in a separate thread](https://stackoverflow.com/questions/44398509/how-to-execute-business-logic-handler-in-a-separate-thread-pool-using-netty)

The handler will be always attached to the same thread of EventExecutorGroup. In order to execute blocking operation in parallel as soon as it arrives, need to use a separate ThreadPoolExecutor:
```
ch.pipeline().addLast(new ServerHandler(blockingThreadPool));
```
where blockingThreadPool is regular ThreadPoolExecutor.
```
ExecutorService blockingThreadPool = Executors.newFixedThreadPool(10)
```

Not working using the following:
```
ch.pipeline().addLast(new DefaultEventExecutorGroup(10), new ServerHandler());
```

- [Netty ChannelHandlerContext writing from different thread](https://stackoverflow.com/questions/44782682/netty-channelhandlercontext-writing-from-different-thread)

ChannelHandlerContext.write method checks what thread you are in. If ctx.write method is called from the outside thread (not the event executor thread) than the ctx.write operation will be submitted to the thread that belongs to your context. What actually happens could simply described like this:
```
gameLogicPool.send(new Runnable() {
         //your logic here
         ctx.write(response);
         //ctx.write actually does this when executed from another thread:
         ctx.executor().execute(new Runnable() {
             //write happens here when you are in event executor already
             }
         );
    }
);
```

- [write difference for channelhandlercontext and channel](https://stackoverflow.com/questions/32514803/netty-what-are-the-differences-between-channelhandlercontext-channel-write)

Channel#write and ChannelPipeline#write write response from the tail handler context in pipeline.
```
// DefaultChannelPipeline # write
public ChannelFuture write(Object msg) {
    return tail.write(msg);
}
```

ChannelHandlerContext#write writes response from the next handler context.
```
// AbstractChannelHandlerContext # write
next.invoker().invokeWrite(next, msg, promise);
```

- [Pipeline](https://programmer.group/netty-pipeline-depth-analysis.html)

ChannelPepiline is a component added by netty to the native channel. Annotations on the Channel Pipeline interface illustrate the role of channel Pipeline. This channel Pipeline is the implementation of advanced filters. netty directs the data in channel Pipeline and gives users 100% control over the data in channel. In addition, the channelPipeline data structure is a two-way linked list. Each node is ChannelContext. ChannelContext maintains the reference of the corresponding handler and pipeline. To sum up, through channelPipeline, users can easily write data to Channel and read data from Channel.

- http Server:
```
public class ServerInitializer extends ChannelInitializer<Channel> {   
    @Override  
    protected void initChannel(Channel ch) {  
        ChannelPipeline pipeline = ch.pipeline();  
        pipeline.addLast(new HttpServerCodec());  
        pipeline.addLast(new HttpObjectAggregator(Integer.MAX_VALUE));  
        pipeline.addLast(new ServerHandler());  
    }        
}
public class ServerHandler extends SimpleChannelInboundHandler<FullHttpRequest> {       
    @Override  
    protected void channelRead0(ChannelHandlerContext ctx, FullHttpRequest msg) {  
        ByteBuf content = Unpooled.copiedBuffer("Hello World!", CharsetUtil.UTF_8);  
        FullHttpResponse response = new DefaultFullHttpResponse(HttpVersion.HTTP_1_1, HttpResponseStatus.OK, content);  
        response.headers().set(HttpHeaderNames.CONTENT_TYPE, "text/html");  
        response.headers().set(HttpHeaderNames.CONTENT_LENGTH, content.readableBytes());  
        ctx.write(response);  
        ctx.flush();  
    }       
}
```

## Concepts
- Events
Netty is event-driven application, so the pipeline of the data processing is a chain of events going through handlers. Events and handlers are related to the inbound and outbound data flow. 

Inbound events:
- Channel activation and deactivation
- Read operation events
- Exception events
- User events

Outbound events are related to opening/closing a connection and writing/flushing data.

- Channel Handler
The base interfaces for the channel event handlers are ChannelHandler and its ancestors ChannelOutboundHandler and ChannelInboundHandler. The empty implementations are ChannelInboundHandlerAdapter and ChannelOutboundHandlerAdapter. These adapters can be extended when need to process only a subset of all events. The implementations for HTTP are HttpRequestDecoder, HttpResponseEncoder, HttpObjectAggregator. 

- Encoders and Decoders: convert the message from byte sequence (for socket read/write) to Java object and vice versa.
    - Decoders: special extensions of the ChannelInboundHandler to decode incoming data. The base class of most decoders is ByteToMessageDecoder.
    - Encoder: special extensions of the ChannelOutboundHandler to encode outgoing data. The base for most encoders is MessageToByteEncoder. We can 

- Channels
    - EpollSocket (Uses JNI for epoll() and non-blocking IO: EpollEventLoopGroup, NioServerSocketChannel, EpollServerSocketChannel; only for TCP and UDP in Linux)
    - EmbeddedChannel (testing ChannelHandlers)
    - LocalServerChannel (Local transport—asynchronous communications within a JVM)
    - NioDatagramChannel
    - NioSctpChannel  
    - NioSocketChannel (NIO—asynchronous transport: TCP, UDP, SCTP, UDT)
    - OioSocketChannel (OIO—blocking transport: TCP, UDP, SCTP, UDT))

- Threads for a channel:
     - Regardless of its transport and type, all its upstream (i.e. inbound) events must be fired from the thread that performs I/O for the channel (i.e. I/O thread).
     - All downstream (i.e. outbound) events can be triggered from any thread including the I/O thread and non-I/O threads. However, any upstream events triggered as a side effect of the downstream event must be fired from the I/O thread. (e.g. If Channel.close() triggers channelDisconnected, channelUnbound, and channelClosed, they must be fired by the I/O thread.

- [Reference Counted Objects](https://netty.io/wiki/reference-counted-objects.html)
[ByteBuf](https://netty.io/4.0/api/index.html?io/netty/buffer/ByteBuf.html) is the most notable type which takes advantage of reference counting to improve the allocation and deallocation performance


## [Channel](https://netty.io/4.0/api/io/netty/channel/Channel.html)

public interface Channel extends AttributeMap
```
ByteBufAllocator	alloc()
ChannelConfig	config()
EventLoop	eventLoop()
ChannelPipeline	pipeline()

ChannelFuture	bind(java.net.SocketAddress localAddress[,ChannelPromise promise])
ChannelFuture	connect(java.net.SocketAddress remoteAddress[,ChannelPromise promise])
ChannelFuture	disconnect([ChannelPromise promise])
ChannelFuture	close([ChannelPromise promise])

ChannelFuture	deregister([ChannelPromise promise])
Channel	flush()
Channel	read()
ChannelFuture	write(java.lang.Object msg[,ChannelPromise promise])
ChannelFuture	writeAndFlush(java.lang.Object msg [,ChannelPromise promise])
```

## [ChannelPipeline](https://netty.io/4.0/api/io/netty/channel/ChannelPipeline.html)
public interface ChannelPipeline extends java.lang.Iterable<java.util.Map.Entry<java.lang.String,ChannelHandler>>
```
ChannelPipeline	addAfter/Before(EventExecutorGroup group, String baseName, java.lang.String name, ChannelHandler handler)
ChannelPipeline	addAfter/Before(java.lang.String baseName, java.lang.String name, ChannelHandler handler)

ChannelPipeline	addFirst/Last(ChannelHandler... handlers)
ChannelPipeline	addFirst/Last(EventExecutorGroup group, ChannelHandler... handlers)
ChannelPipeline	addFirst/Last(EventExecutorGroup group, java.lang.String name, ChannelHandler handler)
ChannelPipeline	addFirst/Last(java.lang.String name, ChannelHandler handler)

ChannelPipeline	remove(ChannelHandler handler)
<T extends ChannelHandler> T	remove(java.lang.Class<T> handlerType)
ChannelHandler	remove(java.lang.String name)/removeFirst()/removeLast()

ChannelPipeline	replace(ChannelHandler oldHandler, java.lang.String newName, ChannelHandler newHandler)
<T extends ChannelHandler> T	replace(java.lang.Class<T> oldHandlerType, java.lang.String newName, ChannelHandler newHandler)
ChannelHandler	replace(java.lang.String oldName, java.lang.String newName, ChannelHandler newHandler)

ChannelHandlerContext	context(ChannelHandler handler)
ChannelHandlerContext	context(java.lang.Class<? extends ChannelHandler> handlerType)
ChannelHandlerContext	context(java.lang.String name)

ChannelHandler	first()/last()
ChannelHandlerContext	firstContext()/lastContext()

<T extends ChannelHandler> T	get(java.lang.Class<T> handlerType)
ChannelHandler	get(java.lang.String name)

ChannelFuture	bind(java.net.SocketAddress localAddress)/bind(java.net.SocketAddress localAddress, ChannelPromise promise)
ChannelFuture	connect(java.net.SocketAddress remoteAddress)
ChannelFuture	connect(java.net.SocketAddress remoteAddress, ChannelPromise promise)
ChannelFuture	connect(java.net.SocketAddress remoteAddress, java.net.SocketAddress localAddress)
ChannelFuture	connect(java.net.SocketAddress remoteAddress, java.net.SocketAddress localAddress, ChannelPromise promise)

ChannelFuture	close()/close(ChannelPromise promise)
ChannelFuture	disconnect()/disconnect(ChannelPromise promise)
ChannelFuture	deregister()/deregister(ChannelPromise promise)

ChannelPipeline	fireChannelActive()/fireChannelInactive()
ChannelPipeline	fireChannelRead(java.lang.Object msg)/fireChannelReadComplete()
ChannelPipeline	fireChannelRegistered()/fireChannelUnregistered()
ChannelPipeline	fireChannelWritabilityChanged()
ChannelPipeline	fireExceptionCaught(java.lang.Throwable cause)
ChannelPipeline	fireUserEventTriggered(java.lang.Object event)

Channel	channel()
java.util.List<java.lang.String>	names()
java.util.Map<java.lang.String,ChannelHandler>	toMap()

ChannelPipeline	read()
ChannelPipeline	flush()
ChannelFuture	write(java.lang.Object msg[, ChannelPromise promise])
ChannelFuture	writeAndFlush(java.lang.Object msg[, ChannelPromise promise])
```

## [ChannelPromise](https://netty.io/4.0/api/io/netty/channel/ChannelPromise.html)

public interface ChannelPromise extends ChannelFuture, Promise<java.lang.Void>

```
ChannelPromise	addListener(GenericFutureListener<? extends Future<? super java.lang.Void>> listener)
ChannelPromise	addListeners(GenericFutureListener<? extends Future<? super java.lang.Void>>... listeners)
ChannelPromise	removeListener(GenericFutureListener<? extends Future<? super java.lang.Void>> listener)
ChannelPromise	removeListeners(GenericFutureListener<? extends Future<? super java.lang.Void>>... listeners)

ChannelPromise	await()/awaitUninterruptibly()
ChannelPromise	sync()/syncUninterruptibly()

Channel	channel()
boolean	trySuccess() 

ChannelPromise	setFailure(java.lang.Throwable cause)/setSuccess()/setSuccess(java.lang.Void result)
```

## [ChannelFuture](https://netty.io/4.0/api/io/netty/channel/ChannelFuture.html)

public interface ChannelFuture extends Future<java.lang.Void>

```
ChannelFuture	addListener(GenericFutureListener<? extends Future<? super java.lang.Void>> listener)
ChannelFuture	addListeners(GenericFutureListener<? extends Future<? super java.lang.Void>>... listeners)
ChannelFuture	removeListener(GenericFutureListener<? extends Future<? super java.lang.Void>> listener)
ChannelFuture	removeListeners(GenericFutureListener<? extends Future<? super java.lang.Void>>... listeners)

ChannelFuture	await()/awaitUninterruptibly()
ChannelFuture	sync()/ChannelFuture	syncUninterruptibly()

Channel	channel()
```

## [ChannelHandler](https://netty.io/4.0/api/io/netty/channel/ChannelHandler.html)
```
void	handlerAdded(ChannelHandlerContext ctx)
void	handlerRemoved(ChannelHandlerContext ctx)
```

## [ChannelHandlerContext](https://netty.io/4.0/api/io/netty/channel/ChannelHandlerContext.html)
public interface ChannelHandlerContext extends AttributeMap
```
ByteBufAllocator	alloc()
Channel	channel()
EventExecutor	executor()
ChannelHandler	handler()
ChannelPipeline	pipeline()
boolean	isRemoved()
java.lang.String	name()

ChannelFuture	bind(java.net.SocketAddress localAddress[, ChannelPromise promise])
ChannelFuture	connect(java.net.SocketAddress remoteAddress)
ChannelFuture	connect(java.net.SocketAddress remoteAddress, ChannelPromise promise)
ChannelFuture	connect(java.net.SocketAddress remoteAddress, java.net.SocketAddress localAddress)
ChannelFuture	connect(java.net.SocketAddress remoteAddress, java.net.SocketAddress localAddress, ChannelPromise promise)
ChannelFuture	deregister([ChannelPromise promise])
ChannelFuture	disconnect([ChannelPromise promise])
ChannelFuture	close([ChannelPromise promise])

ChannelHandlerContext	fireChannelActive()/fireChannelInactive()
ChannelHandlerContext	fireChannelRead(java.lang.Object msg)/fireChannelReadComplete()
ChannelHandlerContext	fireChannelRegistered()/fireChannelUnregistered()
ChannelHandlerContext	fireChannelWritabilityChanged()
ChannelHandlerContext	fireExceptionCaught(java.lang.Throwable cause)
ChannelHandlerContext	fireUserEventTriggered(java.lang.Object evt)

ChannelFuture	newFailedFuture(java.lang.Throwable cause)/newSucceededFuture()
ChannelProgressivePromise	newProgressivePromise()
ChannelPromise	newPromise()/voidPromise()

ChannelHandlerContext	flush()
ChannelHandlerContext	read()

ChannelFuture	write(java.lang.Object msg[, ChannelPromise promise])
ChannelFuture	writeAndFlush(java.lang.Object msg[, ChannelPromise promise])
```

## [ChannelInboundHandler](https://netty.io/4.0/api/io/netty/channel/ChannelInboundHandler.html)
public interface ChannelInboundHandler extends ChannelHandler
```
void	channelActive(ChannelHandlerContext ctx)/channelInactive(ChannelHandlerContext ctx)
void	channelRegistered(ChannelHandlerContext ctx)/channelUnregistered(ChannelHandlerContext ctx)

void	channelRead(ChannelHandlerContext ctx, java.lang.Object msg)
void	channelReadComplete(ChannelHandlerContext ctx)/channelWritabilityChanged(ChannelHandlerContext ctx)

void	exceptionCaught(ChannelHandlerContext ctx, java.lang.Throwable cause)
void	userEventTriggered(ChannelHandlerContext ctx, java.lang.Object evt)
```

## [ChannelOutboundHandler](https://netty.io/4.0/api/io/netty/channel/ChannelOutboundHandler.html)
public interface ChannelOutboundHandler extends ChannelHandler
```
void	bind(ChannelHandlerContext ctx, java.net.SocketAddress localAddress, ChannelPromise promise)
void	connect(ChannelHandlerContext ctx, SocketAddress remoteAddr, SocketAddress localAddr, ChannelPromise promise)

void	close(ChannelHandlerContext ctx, ChannelPromise promise)
void	disconnect(ChannelHandlerContext ctx, ChannelPromise promise)
void	deregister(ChannelHandlerContext ctx, ChannelPromise promise)

void	flush(ChannelHandlerContext ctx)
void	read(ChannelHandlerContext ctx)
void	write(ChannelHandlerContext ctx, java.lang.Object msg, ChannelPromise promise)
```
