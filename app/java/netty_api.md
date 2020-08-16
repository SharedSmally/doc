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

## ChannelHandler

