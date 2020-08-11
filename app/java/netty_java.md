# [netty java API](https://netty.io/4.0/api/index.html?overview-summary.html)

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
ChannelPipeline	addAfter/Before(EventExecutorGroup group, java.lang.String baseName, java.lang.String name, ChannelHandler handler)
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
void	connect(ChannelHandlerContext ctx, java.net.SocketAddress remoteAddress, java.net.SocketAddress localAddress, ChannelPromise promise)

void	close(ChannelHandlerContext ctx, ChannelPromise promise)
void	disconnect(ChannelHandlerContext ctx, ChannelPromise promise)
void	deregister(ChannelHandlerContext ctx, ChannelPromise promise)

void	flush(ChannelHandlerContext ctx)
void	read(ChannelHandlerContext ctx)
void	write(ChannelHandlerContext ctx, java.lang.Object msg, ChannelPromise promise)
```
