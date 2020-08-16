# [Netty API javadoc](https://netty.io/4.1/api/index.html)

## EventLoopGroup related classes:
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

EventExecutor
```
public interface EventExecutor extends EventExecutorGroup

boolean 	inEventLoop()/inEventLoop(java.lang.Thread thread)

<V> Promise<V> 	newPromise()
<V> ProgressivePromise<V> newProgressivePromise()

<V> Future<V> 	newSucceededFuture(V result)
<V> Future<V> 	newFailedFuture(java.lang.Throwable cause)
```

EventLoop:
```
public interface EventLoop extends OrderedEventExecutor, EventLoopGroup

EventLoopGroup 	parent()
```


