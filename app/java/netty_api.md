# [Netty API javadoc](https://netty.io/4.1/api/index.html)

## [Bootstrap](https://netty.io/4.1/api/io/netty/bootstrap/Bootstrap.html)
- [AbstractBootstrap](https://netty.io/4.1/api/io/netty/bootstrap/AbstractBootstrap.html)
```
public abstract class AbstractBootstrap<B extends AbstractBootstrap<B,C>,C extends Channel>

<T> B 	attr(AttributeKey<T> key, T value)
B 	channel(java.lang.Class<? extends C> channelClass)
B 	channelFactory(ChannelFactory<? extends C> channelFactory)
B 	group(EventLoopGroup group)
B 	handler(ChannelHandler handler)
B 	localAddress(InetAddress host, int port)/localAddress(int port)/localAddress(SocketAddress localAddr)/localAddress(String host, int port) 
<T> B option(ChannelOption<T> option, T value)

abstract AbstractBootstrapConfig<B,C> 	config()

ChannelFuture 	bind()/bind(InetAddress host, int port)/bind(int port)/bind(SocketAddress localAddr)/bind(String host, int port)

ChannelFuture 	register()
abstract B 	clone()
B 	validate()
```
- [AbstractBootstrapConfig](https://netty.io/4.1/api/io/netty/bootstrap/AbstractBootstrapConfig.html)
```
java.util.Map<AttributeKey<?>,java.lang.Object>  attrs()
ChannelFactory<? extends C> 	channelFactory()
EventLoopGroup 	group()
ChannelHandler 	handler()
java.net.SocketAddress 	localAddress()
java.util.Map<ChannelOption<?>,java.lang.Object> 	options()
```

- [Bootstrap](https://netty.io/4.1/api/io/netty/bootstrap/Bootstrap.html)
```
public class Bootstrap extends AbstractBootstrap<Bootstrap,Channel>

Bootstrap remoteAddress(InetAddress host, int port)/remoteAddress(SocketAddress remoteAddr)/remoteAddress(java.lang.String host, int port) 
Bootstrap resolver(AddressResolverGroup<?> resolver)

BootstrapConfig 	config()
Bootstrap 	clone()/clone(EventLoopGroup group)
Bootstrap 	validate()

ChannelFuture 	connect()/connect(InetAddress host, int port)/connect(SocketAddress remoteAddr)/connect(SocketAddress remoteAddr, SocketAddress localAddr)/connect(java.lang.String host, int port)
```

- [BootstrapConfig](https://netty.io/4.1/api/io/netty/bootstrap/BootstrapConfig.html)
```
public final class BootstrapConfig extends AbstractBootstrapConfig<Bootstrap,Channel>

java.net.SocketAddress 	remoteAddress()
AddressResolverGroup<?> 	resolver()
```

- [ServerBootstrap](https://netty.io/4.1/api/io/netty/bootstrap/ServerBootstrap.html)
```
public class ServerBootstrap extends AbstractBootstrap<ServerBootstrap,ServerChannel>

ServerBootstrap 	group(EventLoopGroup group)
ServerBootstrap 	group(EventLoopGroup parentGroup, EventLoopGroup childGroup)

<T> ServerBootstrap 	childAttr(AttributeKey<T> childKey, T value)
ServerBootstrap 	childHandler(ChannelHandler childHandler)
<T> ServerBootstrap 	childOption(ChannelOption<T> childOption, T value)

ServerBootstrapConfig 	config()
ServerBootstrap 	clone()
ServerBootstrap 	validate()
```

- [ServerBootstrapConfig](https://netty.io/4.1/api/io/netty/bootstrap/ServerBootstrapConfig.html)
```
public final class ServerBootstrapConfig extends AbstractBootstrapConfig<ServerBootstrap,ServerChannel>

EventLoopGroup 	childGroup()
ChannelHandler 	childHandler()

Map<AttributeKey<?>,Object> 	childAttrs()
Map<ChannelOption<?>,Object> 	childOptions()
```

## [EventLoopGroup](https://netty.io/4.1/api/io/netty/channel/EventLoopGroup.html)
- EventExecutorGroup
```
public interface EventExecutorGroup extends ScheduledExecutorService, Iterable<EventExecutor>

EventExecutor 	next()
Future<?> 	submit(Runnable task)
ScheduledFuture<?> 	schedule(Runnable command, long delay,TimeUnit unit) 
Future<?> 	shutdownGracefully()
Future<?> 	terminationFuture()
```

- EventLoopGroup:

Implementing Classes:
   - AbstractEventLoopGroup, EpollEventLoopGroup, NioEventLoopGroup, OioEventLoopGroup, KQueueEventLoopGroup, LocalEventLoopGroup
   - DefaultEventLoopGroup, MultithreadEventLoopGroup, ThreadPerChannelEventLoopGroup
   - AbstractEventLoop, DefaultEventLoop, NioEventLoop, SingleThreadEventLoop, ThreadPerChannelEventLoop,  (implementing classes of EventGroup)
     
```
public interface EventLoopGroup extends EventExecutorGroup

EventLoop 	next()
ChannelFuture 	register(Channel channel)
ChannelFuture 	register(ChannelPromise promise)
```

- EventExecutor
```
public interface EventExecutor extends EventExecutorGroup

boolean 	inEventLoop()/inEventLoop(java.lang.Thread thread)

<V> Promise<V> 	newPromise()
<V> ProgressivePromise<V> newProgressivePromise()

<V> Future<V> 	newSucceededFuture(V result)
<V> Future<V> 	newFailedFuture(java.lang.Throwable cause)
```

- EventLoop:
```
public interface EventLoop extends OrderedEventExecutor, EventLoopGroup

EventLoopGroup 	parent()
```

## Channels
- [Channel](https://netty.io/4.1/api/io/netty/channel/Channel.html)

All Known Subinterfaces:
   - SctpChannel, DomainSocketChannel, SocketChannel, UdtChannel,  
   - ServerChannel: SctpServerChannel, ServerDomainSocketChannel, ServerSocketChannel, UdtServerChannel
   - DatagramChannel,  DuplexChannel, Http2StreamChannel, UnixChannel    

All Known Implementing Classes:
   - AbstractChannel
       - AbstractEpollServerChannel
           - EpollServerDomainSocketChannel
           - EpollServerSocketChannel
       - AbstractEpollStreamChannel
           - EpollDomainSocketChannel
           - EpollSocketChannel
       - AbstractKQueueServerChannel
           - KQueueServerDomainSocketChannel
           - KQueueServerSocketChannel
       - AbstractKQueueStreamChannel
           - KQueueDomainSocketChannel
           - KQueueSocketChannel
       - AbstractNioChannel
           - AbstractNioByteChannel
               - NioSocketChannel
               - NioUdtByteConnectorChannel
                   - NioUdtByteRendezvousChannel
           - AbstractNioMessageChannel
               - NioDatagramChannel
               - NioSctpChannel-
               - NioSctpServerChannel
               - NioServerSocketChannel
               - NioUdtAcceptorChannel
                   - NioUdtByteAcceptorChannel
                   - NioUdtMessageAcceptorChannel
               - NioUdtMessageConnectorChannel
                   - NioUdtMessageRendezvousChannel
       - AbstractOioChannel
           - AbstractOioByteChannel
               - OioByteStreamChannel
                   - OioSocketChannel
                   - RxtxChannel
           - AbstractOioMessageChannel
               - OioDatagramChannel
               - OioSctpChannel
               - OioSctpServerChannel
               - OioServerSocketChannel
       - AbstractServerChannel
           - LocalServerChannel
       - EmbeddedChannel
       - EpollDatagramChannel 
       - KQueueDatagramChannel
       - LocalChannel
```
public interface Channel extends AttributeMap, ChannelOutboundInvoker, java.lang.Comparable<Channel>

ByteBufAllocator 	alloc()
ChannelConfig 	config()
EventLoop 	eventLoop()
ChannelMetadata 	metadata()
Channel 	parent()
ChannelPipeline 	pipeline()
Channel.Unsafe 	unsafe()

java.net.SocketAddress 	localAddress()
java.net.SocketAddress 	remoteAddress()

long 	bytesBeforeUnwritable()
long 	bytesBeforeWritable()

ChannelFuture 	closeFuture()
Channel 	flush()
Channel 	read()

ChannelId 	id()
boolean 	isActive()
boolean 	isOpen()
boolean 	isRegistered()
boolean 	isWritable()
```

## Channel Options
- [ChannelOption<T>](https://netty.io/4.1/api/io/netty/channel/ChannelOption.html)
   Known Subclasses: NioChannelOption, RxtxChannelOption, SctpChannelOption, UdtChannelOption, UnixChannelOption
```
public class ChannelOption<T> extends AbstractConstant<ChannelOption<T>>

static ChannelOption<ByteBufAllocator> 	ALLOCATOR 
static ChannelOption<MessageSizeEstimator> 	MESSAGE_SIZE_ESTIMATOR 
static ChannelOption<RecvByteBufAllocator> 	RCVBUF_ALLOCATOR 

static ChannelOption<java.net.InetAddress> 	IP_MULTICAST_ADDR 
static ChannelOption<java.net.NetworkInterface> 	IP_MULTICAST_IF 

static ChannelOption<java.lang.Boolean> 	ALLOW_HALF_CLOSURE 
static ChannelOption<java.lang.Boolean> 	AUTO_CLOSE
static ChannelOption<java.lang.Boolean> 	AUTO_READ 
static ChannelOption<java.lang.Integer> 	CONNECT_TIMEOUT_MILLIS 
static ChannelOption<java.lang.Boolean> 	IP_MULTICAST_LOOP_DISABLED 
static ChannelOption<java.lang.Integer> 	IP_MULTICAST_TTL 
static ChannelOption<java.lang.Integer> 	IP_TOS 
static ChannelOption<java.lang.Boolean> 	SINGLE_EVENTEXECUTOR_PER_GROUP 
static ChannelOption<java.lang.Integer> 	SO_BACKLOG 
static ChannelOption<java.lang.Boolean> 	SO_BROADCAST 
static ChannelOption<java.lang.Boolean> 	SO_KEEPALIVE 
static ChannelOption<java.lang.Integer> 	SO_LINGER 
static ChannelOption<java.lang.Integer> 	SO_RCVBUF 
static ChannelOption<java.lang.Boolean> 	SO_REUSEADDR 
static ChannelOption<java.lang.Integer> 	SO_SNDBUF 
static ChannelOption<java.lang.Integer> 	SO_TIMEOUT 
static ChannelOption<java.lang.Boolean> 	TCP_NODELAY 
static ChannelOption<WriteBufferWaterMark> 	WRITE_BUFFER_WATER_MARK 
static ChannelOption<java.lang.Integer> 	WRITE_SPIN_COUNT  
```

- [NioChannelOption]()
```
public final class NioChannelOption<T> extends ChannelOption<T>

static <T> ChannelOption<T> 	of(java.net.SocketOption<T> option)
```
- [RxtxChannelOption](https://netty.io/4.1/api/io/netty/channel/rxtx/RxtxChannelOption.html): Deprecated. 

- [SctpChannelOption]()
```
public final class SctpChannelOption<T> extends ChannelOption<T>

static ChannelOption<java.lang.Boolean> 	SCTP_DISABLE_FRAGMENTS 
static ChannelOption<java.lang.Boolean> 	SCTP_EXPLICIT_COMPLETE 
static ChannelOption<java.lang.Integer> 	SCTP_FRAGMENT_INTERLEAVE 
static ChannelOption<com.sun.nio.sctp.SctpStandardSocketOptions.InitMaxStreams> 	SCTP_INIT_MAXSTREAMS 
static ChannelOption<java.lang.Boolean> 	SCTP_NODELAY 
static ChannelOption<java.net.SocketAddress> 	SCTP_PRIMARY_ADDR 
static ChannelOption<java.net.SocketAddress> 	SCTP_SET_PEER_PRIMARY_ADDR 
```

- [UdtChannelOption](https://netty.io/4.1/api/io/netty/channel/udt/UdtChannelOption.html): Deprecated. 

- [UnixChannelOption]()
```
public class UnixChannelOption<T> extends ChannelOption<T>

static ChannelOption<DomainSocketReadMode> 	DOMAIN_SOCKET_READ_MODE 
static ChannelOption<java.lang.Boolean> 	SO_REUSEPORT 
```

## ChannelFuture
- [ChannelFuture](https://netty.io/4.1/api/io/netty/channel/ChannelFuture.html)
```
public interface ChannelFuture extends Future<java.lang.Void>

ChannelFuture 	addListener(GenericFutureListener<? extends Future<? super java.lang.Void>> listener)
ChannelFuture 	addListeners(GenericFutureListener<? extends Future<? super java.lang.Void>>... listeners)
ChannelFuture 	removeListener(GenericFutureListener<? extends Future<? super java.lang.Void>> listener)
ChannelFuture 	removeListeners(GenericFutureListener<? extends Future<? super java.lang.Void>>... listeners)

ChannelFuture 	await()
ChannelFuture 	awaitUninterruptibly()
ChannelFuture 	sync()
ChannelFuture 	syncUninterruptibly()

Channel 	channel()
boolean 	isVoid()
```
- [ChannelPromise](https://netty.io/4.1/api/io/netty/channel/ChannelPromise.html)
```
public interface ChannelPromise extends ChannelFuture, Promise<java.lang.Void>

ChannelPromise 	addListener(GenericFutureListener<? extends Future<? super java.lang.Void>> listener)
ChannelPromise 	addListeners(GenericFutureListener<? extends Future<? super java.lang.Void>>... listeners)
ChannelPromise 	removeListener(GenericFutureListener<? extends Future<? super java.lang.Void>> listener)
ChannelPromise 	removeListeners(GenericFutureListener<? extends Future<? super java.lang.Void>>... listeners)

ChannelPromise 	await()
ChannelPromise 	awaitUninterruptibly()
ChannelPromise 	sync()
ChannelPromise 	syncUninterruptibly()

Channel 	channel()

ChannelPromise 	setFailure(java.lang.Throwable cause)
ChannelPromise 	setSuccess() 
ChannelPromise 	setSuccess(java.lang.Void result)
boolean 	trySuccess() 
ChannelPromise 	unvoid()
```
- [GenericFutureListener](https://netty.io/4.1/api/io/netty/util/concurrent/GenericFutureListener.html)
```
public interface GenericFutureListener<F extends Future<?>> extends java.util.EventListener

void 	operationComplete(F future)
```

## ChannelHandler
- [ChannelHandler](https://netty.io/4.1/api/io/netty/channel/ChannelHandler.html)
```
void 	handlerAdded(ChannelHandlerContext ctx)
void 	handlerRemoved(ChannelHandlerContext ctx)
```
- [ChannelInboundHandler](https://netty.io/4.1/api/io/netty/channel/ChannelInboundHandler.html)
```
public interface ChannelInboundHandler extends ChannelHandler

void 	channelActive(ChannelHandlerContext ctx)
void 	channelInactive(ChannelHandlerContext ctx)

void 	channelRegistered(ChannelHandlerContext ctx)
void 	channelUnregistered(ChannelHandlerContext ctx)

void 	exceptionCaught(ChannelHandlerContext ctx, java.lang.Throwable cause)

void 	channelRead(ChannelHandlerContext ctx, java.lang.Object msg)
void 	channelReadComplete(ChannelHandlerContext ctx)

void 	channelWritabilityChanged(ChannelHandlerContext ctx)

void 	userEventTriggered(ChannelHandlerContext ctx, java.lang.Object evt)
```
- [ChannelOutboundHandler]()
```
void 	bind(ChannelHandlerContext ctx, java.net.SocketAddress localAddress, ChannelPromise promise)
void 	close(ChannelHandlerContext ctx, ChannelPromise promise)
void 	connect(ChannelHandlerContext ctx, SocketAddress remoteAddr, SocketAddress localAddr, ChannelPromise promise)

void 	deregister(ChannelHandlerContext ctx, ChannelPromise promise)
void 	disconnect(ChannelHandlerContext ctx, ChannelPromise promise)

void 	flush(ChannelHandlerContext ctx)
void 	read(ChannelHandlerContext ctx)
void 	write(ChannelHandlerContext ctx, java.lang.Object msg, ChannelPromise promise)
```
- [ChannelHandlerContext](https://netty.io/4.1/api/io/netty/channel/ChannelHandlerContext.html)
```
public interface ChannelHandlerContext extends AttributeMap, ChannelInboundInvoker, ChannelOutboundInvoker

ByteBufAllocator 	alloc()
<T> Attribute<T> 	attr(AttributeKey<T> key)

Channel 	channel()
ChannelPipeline 	pipeline()

EventExecutor 	executor()
ChannelHandler 	handler()

<T> boolean 	hasAttr(AttributeKey<T> key)
boolean 	isRemoved()
java.lang.String 	name()

ChannelHandlerContext 	fireChannelActive()
ChannelHandlerContext 	fireChannelInactive()
ChannelHandlerContext 	fireChannelRead(java.lang.Object msg)
ChannelHandlerContext 	fireChannelReadComplete()
ChannelHandlerContext 	fireChannelRegistered()
ChannelHandlerContext 	fireChannelUnregistered()
ChannelHandlerContext 	fireChannelWritabilityChanged()
ChannelHandlerContext 	fireExceptionCaught(java.lang.Throwable cause)
ChannelHandlerContext 	fireUserEventTriggered(java.lang.Object evt)

ChannelHandlerContext 	flush()
ChannelHandlerContext 	read()
From ChannelOutboundInvoker fro writexxx.
```
- [ChannelOutboundInvoker](https://netty.io/4.1/api/io/netty/channel/ChannelOutboundInvoker.html)
```
ChannelFuture 	bind(java.net.SocketAddress localAddress)
ChannelFuture 	bind(java.net.SocketAddress localAddress, ChannelPromise promise)

ChannelFuture 	close()
ChannelFuture 	close(ChannelPromise promise)

ChannelFuture 	connect(java.net.SocketAddress remoteAddress)
ChannelFuture 	connect(java.net.SocketAddress remoteAddress, ChannelPromise promise)
ChannelFuture 	connect(java.net.SocketAddress remoteAddress, java.net.SocketAddress localAddress)
ChannelFuture 	connect(java.net.SocketAddress remoteAddress, java.net.SocketAddress localAddress, ChannelPromise promise)

ChannelFuture 	disconnect()
ChannelFuture 	disconnect(ChannelPromise promise)

ChannelFuture 	deregister()
ChannelFuture 	deregister(ChannelPromise promise)

ChannelFuture 	newFailedFuture(java.lang.Throwable cause)
ChannelProgressivePromise 	newProgressivePromise()
ChannelPromise 	newPromise()
ChannelFuture 	newSucceededFuture()
ChannelPromise 	voidPromise()

ChannelOutboundInvoker 	read()
ChannelOutboundInvoker 	flush()
ChannelFuture 	write(java.lang.Object msg)
ChannelFuture 	write(java.lang.Object msg, ChannelPromise promise)
ChannelFuture 	writeAndFlush(java.lang.Object msg)
ChannelFuture 	writeAndFlush(java.lang.Object msg, ChannelPromise promise)
```

- [ChannelPipeline](https://netty.io/4.1/api/io/netty/channel/ChannelPipeline.html)
```
public interface ChannelPipeline extends ChannelInboundInvoker, ChannelOutboundInvoker, Iterable<Map.Entry<String,ChannelHandler>>

ChannelPipeline 	addAfter(EventExecutorGroup group, java.lang.String baseName, java.lang.String name, ChannelHandler handler)
ChannelPipeline 	addAfter(java.lang.String baseName, java.lang.String name, ChannelHandler handler)

ChannelPipeline 	addBefore(EventExecutorGroup group, java.lang.String baseName, java.lang.String name, ChannelHandler handler)
ChannelPipeline 	addBefore(java.lang.String baseName, java.lang.String name, ChannelHandler handler)

ChannelPipeline 	addFirst(ChannelHandler... handlers)
ChannelPipeline 	addFirst(EventExecutorGroup group, ChannelHandler... handlers)
ChannelPipeline 	addFirst(EventExecutorGroup group, java.lang.String name, ChannelHandler handler)
ChannelPipeline 	addFirst(java.lang.String name, ChannelHandler handler)

ChannelPipeline 	addLast(ChannelHandler... handlers)
ChannelPipeline 	addLast(EventExecutorGroup group, ChannelHandler... handlers)
ChannelPipeline 	addLast(EventExecutorGroup group, java.lang.String name, ChannelHandler handler)
ChannelPipeline 	addLast(java.lang.String name, ChannelHandler handler)

ChannelPipeline 	remove(ChannelHandler handler)
<T extends ChannelHandler> T 	remove(java.lang.Class<T> handlerType)
ChannelHandler 	remove(java.lang.String name)
ChannelHandler 	removeFirst()
ChannelHandler 	removeLast()

ChannelPipeline 	replace(ChannelHandler oldHandler, java.lang.String newName, ChannelHandler newHandler)
<T extends ChannelHandler> T 	replace(java.lang.Class<T> oldHandlerType, java.lang.String newName, ChannelHandler newHandler)
ChannelHandler 	replace(java.lang.String oldName, java.lang.String newName, ChannelHandler newHandler)

Channel 	channel()
java.util.List<String> 	names()
java.util.Map<String,ChannelHandler> 	toMap()

ChannelHandlerContext 	context(ChannelHandler handler)
ChannelHandlerContext 	context(java.lang.Class<? extends ChannelHandler> handlerType)
ChannelHandlerContext 	context(java.lang.String name)

ChannelPipeline 	fireChannelActive()
ChannelPipeline 	fireChannelInactive()
ChannelPipeline 	fireChannelRead(java.lang.Object msg)
ChannelPipeline 	fireChannelReadComplete()
ChannelPipeline 	fireChannelRegistered()
ChannelPipeline 	fireChannelUnregistered()
ChannelPipeline 	fireChannelWritabilityChanged()
ChannelPipeline 	fireExceptionCaught(java.lang.Throwable cause)
ChannelPipeline 	fireUserEventTriggered(java.lang.Object event)

ChannelHandler 	first()
ChannelHandlerContext 	firstContext()
ChannelHandler 	last()
ChannelHandlerContext 	lastContext()
<T extends ChannelHandler> T 	get(java.lang.Class<T> handlerType)
ChannelHandler 	get(java.lang.String name)

ChannelPipeline 	flush()
Methods from ChannelOutboundInvoker for read,write,bind,connect,etc/
```
- [ChannelInitializer](https://netty.io/4.1/api/io/netty/channel/ChannelInitializer.html)
```
@ChannelHandler.Sharable
public abstract class ChannelInitializer<C extends Channel> extends ChannelInboundHandlerAdapter

void 	channelRegistered(ChannelHandlerContext ctx)
void 	exceptionCaught(ChannelHandlerContext ctx, Throwable cause)
void 	handlerAdded(ChannelHandlerContext ctx)
void 	handlerRemoved(ChannelHandlerContext ctx)

protected abstract void 	initChannel(C ch)
```

- [SimpleChannelInboundHandler](https://netty.io/4.1/api/io/netty/channel/SimpleChannelInboundHandler.html)
```
public abstract class SimpleChannelInboundHandler<I> extends ChannelInboundHandlerAdapter

protected 	SimpleChannelInboundHandler()
protected 	SimpleChannelInboundHandler(boolean autoRelease)
protected 	SimpleChannelInboundHandler(java.lang.Class<? extends I> inboundMessageType)
protected 	SimpleChannelInboundHandler(java.lang.Class<? extends I> inboundMessageType, boolean autoRelease)

boolean 	acceptInboundMessage(java.lang.Object msg)
void 	channelRead(ChannelHandlerContext ctx, java.lang.Object msg)
protected abstract void 	channelRead0(ChannelHandlerContext ctx, I msg)
```
- [ByteToMessageCodec](https://netty.io/4.1/api/io/netty/handler/codec/ByteToMessageCodec.html)
```
public abstract class ByteToMessageCodec<I> extends ChannelDuplexHandler 

boolean 	acceptOutboundMessage(java.lang.Object msg)

void 	channelInactive(ChannelHandlerContext ctx)
void 	channelRead(ChannelHandlerContext ctx, java.lang.Object msg)
void 	channelReadComplete(ChannelHandlerContext ctx)

void 	handlerAdded(ChannelHandlerContext ctx)
void 	handlerRemoved(ChannelHandlerContext ctx)
void 	write(ChannelHandlerContext ctx, java.lang.Object msg, ChannelPromise promise)

protected abstract void 	decode(ChannelHandlerContext ctx, ByteBuf in, List<Object> out) 
protected void 	decodeLast(ChannelHandlerContext ctx, ByteBuf in, List<Object> out) 
protected abstract void 	encode(ChannelHandlerContext ctx, I msg, ByteBuf out)
```


- [ByteToMessageDecoder](https://netty.io/4.1/api/io/netty/handler/codec/ByteToMessageDecoder.html)
```
public abstract class ByteToMessageDecoder extends ChannelInboundHandlerAdapter
protected int 	actualReadableBytes()
protected void 	callDecode(ChannelHandlerContext ctx, ByteBuf in, java.util.List<java.lang.Object> out)

void 	channelInactive(ChannelHandlerContext ctx)
void 	channelRead(ChannelHandlerContext ctx, java.lang.Object msg)
void 	channelReadComplete(ChannelHandlerContext ctx)

protected abstract void 	decode(ChannelHandlerContext ctx, ByteBuf in, List<Object> out)

protected void 	decodeLast(ChannelHandlerContext ctx, ByteBuf in, java.util.List<java.lang.Object> out)
protected void 	discardSomeReadBytes() 
void 	handlerRemoved(ChannelHandlerContext ctx)
protected void 	handlerRemoved0(ChannelHandlerContext ctx)
protected ByteBuf 	internalBuffer()
boolean 	isSingleDecode()
void 	setCumulator(ByteToMessageDecoder.Cumulator cumulator)
void 	setDiscardAfterReads(int discardAfterReads)
void 	setSingleDecode(boolean singleDecode)
void 	userEventTriggered(ChannelHandlerContext ctx, java.lang.Object evt)
```
- [MessageToByteEncoder](https://netty.io/4.1/api/io/netty/handler/codec/MessageToByteEncoder.html)
```
public abstract class MessageToByteEncoder<I> extends ChannelOutboundHandlerAdapter

boolean 	acceptOutboundMessage(java.lang.Object msg)
protected ByteBuf 	allocateBuffer(ChannelHandlerContext ctx, I msg, boolean preferDirect)
protected abstract void 	encode(ChannelHandlerContext ctx, I msg, ByteBuf out)
protected boolean 	isPreferDirect() 

void 	write(ChannelHandlerContext ctx, java.lang.Object msg, ChannelPromise promise)
```
- [MessageToMessageCodec](https://netty.io/4.1/api/io/netty/handler/codec/MessageToMessageCodec.html)
```
boolean 	acceptInboundMessage(java.lang.Object msg)
boolean 	acceptOutboundMessage(java.lang.Object msg)
void 	channelRead(ChannelHandlerContext ctx, java.lang.Object msg)

protected abstract void 	decode(ChannelHandlerContext ctx, INBOUND_IN msg, java.util.List<java.lang.Object> out) 
protected abstract void 	encode(ChannelHandlerContext ctx, OUTBOUND_IN msg, java.util.List<java.lang.Object> out) 

void 	write(ChannelHandlerContext ctx, java.lang.Object msg, ChannelPromise promise)
```

- [MessageToMessageDecoder](https://netty.io/4.1/api/io/netty/handler/codec/MessageToMessageDecoder.html)
```
public abstract class MessageToMessageDecoder<I> extends ChannelInboundHandlerAdapter

boolean 	acceptInboundMessage(java.lang.Object msg)
void 	channelRead(ChannelHandlerContext ctx, java.lang.Object msg)

protected abstract void 	decode(ChannelHandlerContext ctx, I msg, List<Object> out)
```

- [MessageToMessageEncoder](https://netty.io/4.1/api/io/netty/handler/codec/MessageToMessageEncoder.html)
```
public abstract class MessageToMessageEncoder<I> extends ChannelOutboundHandlerAdapter

boolean 	acceptOutboundMessage(java.lang.Object msg)
protected abstract void 	encode(ChannelHandlerContext ctx, I msg, List<Object> out)
void 	write(ChannelHandlerContext ctx, java.lang.Object msg, ChannelPromise promise)
```
