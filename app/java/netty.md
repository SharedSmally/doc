# [Netty](https://netty.io/)

## mvn
```
<property>
    <netty.version>4.1.51.Final</netty.version>
</property>

<dependency>
    <groupId>io.netty</groupId>
    <artifactId>netty-all</artifactId>
    <version>${netty.version}</version>
</dependency>
```
## Bootstrap
- AbstractBootstrap<B,C>: : set group,channel,handler for creted channels
```
public abstract class AbstractBootstrap<B extends AbstractBootstrap<B,C>,C extends Channel>

abstract AbstractBootstrapConfig<B,C> 	config()

B 	channel(java.lang.Class<? extends C> channelClass)
B 	group(EventLoopGroup group)
B 	handler(ChannelHandler handler)

ChannelFuture 	bind(xxx)
```
- AbstractBootstrapConfig
```
public abstract class AbstractBootstrapConfig<B extends AbstractBootstrap<B,C>,C extends Channel>

java.util.Map<AttributeKey<?>,java.lang.Object> 	attrs()
ChannelFactory<? extends C> 	channelFactory()
EventLoopGroup 	group()
ChannelHandler 	handler()
java.net.SocketAddress 	localAddress()
java.util.Map<ChannelOption<?>,java.lang.Object> 	options()
```
- Bootstrap
```
public class Bootstrap extends AbstractBootstrap<Bootstrap,Channel>
BootstrapConfig config()
ChannelFuture connect(xxx);
Bootstrap remoteAddress(xxx);
```
- BootstrapConfig
```
public final class BootstrapConfig extends AbstractBootstrapConfig<Bootstrap,Channel>

java.net.SocketAddress 	remoteAddress()
AddressResolverGroup<?> 	resolver()
```
- ServerBootstrap: add group,channel,handler for child
```
public class ServerBootstrap extends AbstractBootstrap<ServerBootstrap,ServerChannel>

<T> ServerBootstrap 	childAttr(AttributeKey<T> childKey, T value)
ServerBootstrap 	childHandler(ChannelHandler childHandler)
<T> ServerBootstrap 	childOption(ChannelOption<T> childOption, T value)

ServerBootstrapConfig 	config()
```
- ServerBootstrapConfig:
```
public final class ServerBootstrapConfig extends AbstractBootstrapConfig<ServerBootstrap,ServerChannel>

java.util.Map<AttributeKey<?>,java.lang.Object> 	childAttrs()
EventLoopGroup 	childGroup()
ChannelHandler 	childHandler()
java.util.Map<ChannelOption<?>,java.lang.Object> 	childOptions()
```
## Concepts
- EventLoop: handle all the I/O operations for a Channel once registered
```
public interface EventLoop extends OrderedEventExecutor, EventLoopGroup
EventLoopGroup 	parent();
```
- EventLoopGroup: Allows registering Channels that get processed for later selection during the event loop.
```
public interface EventLoopGroup extends EventExecutorGroup
EventLoop 	next()
ChannelFuture 	register(Channel channel)
ChannelFuture 	register(ChannelPromise promise)
```
-  EventExecutorGroup: Provide the EventExecutor's to use via its next() method
```
public interface EventExecutorGroup extends java.util.concurrent.ScheduledExecutorService, java.lang.Iterable<EventExecutor>
```
- ChannelFuture: The result of an asynchronous Channel I/O operation
```
public interface ChannelFuture extends Future<java.lang.Void>
ChannelFuture 	addListener(GenericFutureListener<? extends Future<? super java.lang.Void>> listener)
ChannelFuture 	removeListener(GenericFutureListener<? extends Future<? super java.lang.Void>> listener)
ChannelFuture 	await()/awaitUninterruptibly()
ChannelFuture 	sync()/syncUninterruptibly()
```
- ChannelPromise: Special ChannelFuture which is writable.
```
public interface ChannelPromise extends ChannelFuture, Promise<java.lang.Void>
ChannelPromise 	setFailure(java.lang.Throwable cause)
ChannelPromise 	setSuccess() 
ChannelPromise 	setSuccess(java.lang.Void result)
```
- ChannelHandlerContext
Enables a ChannelHandler to interact with its ChannelPipeline and other handlers.
```
public interface ChannelHandlerContext extends AttributeMap, ChannelInboundInvoker, ChannelOutboundInvoker
ChannelHandlerContext 	fireChannelXxxx()
ChannelPipeline 	pipeline()
ChannelHandlerContext 	flush()/read()
Channel 	channel()
EventExecutor 	executor()
```
- ChannelPipeline
A list of ChannelHandlers which handles or intercepts inbound events and outbound operations of a Channel.
```
public interface ChannelPipeline extends ChannelInboundInvoker, ChannelOutboundInvoker, java.lang.Iterable<java.util.Map.Entry<java.lang.String,ChannelHandler>>
ChannelPipeline 	add/remove/replaceXxx(...,ChannelHandler handler)
ChannelPipeline 	fireXxx(...)
ChannelHandlerContext context()
```
- ChannelHandler

Handles an I/O event or intercepts an I/O operation, and forwards it to its next handler in its ChannelPipeline. Implement one of its subtypes:
    - ChannelInboundHandler to handle inbound I/O events, and
    - ChannelOutboundHandler to handle outbound I/O operations.
or the following adapter classes:
    - ChannelInboundHandlerAdapter to handle inbound I/O events,
    - ChannelOutboundHandlerAdapter to handle outbound I/O operations
    - ChannelDuplexHandler to handle both inbound and outbound events

A ChannelHandler is provided with a ChannelHandlerContext object. A ChannelHandler is supposed to interact with the ChannelPipeline it belongs to via a context object. Using the context object, the ChannelHandler can pass events upstream or downstream, modify the pipeline dynamically, or store the information (using AttributeKeys) which is specific to the handler.

```
public interface ChannelHandler

public interface ChannelInboundHandler extends ChannelHandler
void channelRead(ChannelHandlerContext ctx, java.lang.Object msg)
void channelXxx(ChannelHandlerContext ctx)
......

public interface ChannelOutboundHandler extends ChannelHandler
void write(ChannelHandlerContext ctx, java.lang.Object msg, ChannelPromise promise)
......
```

## Channels (socket,sctp for NIO, OIO-deprecated)
- ChannelGroup / ChannelPool
- TCP/IP: 
    - io.netty.channel.socket interfaces
        - DatagramChannel/DatagramChannelConfig : DatagramPacket
        - SocketChannel/SocketChannelConfig
        - ServerSocketChannel / ServerSocketChannelConfig
    - io.netty.channel.socket.nio classes:
         - NioDatagramChannel
         - NioSocketChannel
         - NioServerSocketChannel
    - io.netty.channel.socket.oio classes: deprecated
         - OioDatagramChannel
         - OioSocketChannel
         - OioServerSocketChannel
- SCTP/IP:
    - io.netty.channel.sctp interfaces
         - SctpChannel / SctpChannelConfig
         - SctpServerChannel / SctpServerChannelConfig : SctpMessage
    - io.netty.channel.sctp.nio classes:
         - NioSctpChannel
         - NioSctpServerChannel
    - io.netty.channel.sctp.oio classes: deprecated
         - OioSctpChannel
         - OioSctpServerChannel
- unix
    - DatagramSocketAddress / DomainSocketAddress
    - UnixChannel / ServerDomainSocketChannel
    - DomainSocketChannel / DomainSocketChannelConfig
- local
    - LocalEventLoopGroup / LocalAddress
    - LocalChannel / LocalServerChannel
- rxtx
    - RxtxDeviceAddress / RxtxChannelOption<T> / RxtxChannelConfig
    - RxtxChannel

## Transprots
- OIO: old blocking IO: n<1000; OioEventLoopGroup (deprecated)
- NIO : NIO based nonblocking: n>1000: 
      - NioEventLoop; NioEventLoopGroup
- epoll: 
    - EpollEventLoopGroup / Epoll / EpollTcpInfo / EpollMode	 
    - EpollChannelConfig / / EpollServerChannelConfig / EpollChannelOption<T>	
    - EpollDatagramChannel / EpollDatagramChannelConfig 	 
    - EpollDomainSocketChannel / EpollDomainSocketChannelConfig  
    - EpollServerDomainSocketChannel / EpollServerChannelConfig  
    - EpollServerSocketChannel / EpollServerSocketChannelConfig       
    - EpollSocketChannel / EpollSocketChannelConfig        
- kqueue

- ndt: Deprecated 

## Codecs:  io.netty.handler.codec
- base64
- bytes
- compression
- dns
- haproxy
- http / http2
- json / xml/protobuf
- ssl
- ......

