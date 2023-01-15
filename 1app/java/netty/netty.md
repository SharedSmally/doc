# Netty
## Reference
- [netty java api](https://netty.io/4.1/api/index.html)
- [Handle Thousands of Connections](https://dzone.com/articles/thousands-of-socket-connections-in-java-practical)
        - default (# of CPUs * 2 threads/event-loops) for workerEventLoopGroup, and one thread for accepting new connections. 
        - SNDBUF: 1k*1K; RECVBUF: 32K
- [ByteBuf explaination](https://segmentfault.com/a/1190000040451565/en)


## ByteBuf (ByteBufAllocator)
```
public abstract class ByteBuf implements ReferenceCounted, Comparable<ByteBuf> 
```
2 Types of ByteBuf:
- HeapByteBuffer (byte arrays allocated on heap by JVM, cheaper)
- DirectByteBuffer (off-heap memory, can be directly passed to native OS functions for performing I/O, expensive)

Netty's ByteBuf can be created in two versions: pooled and unpooled, and the release of native memory (or putting 
the buffer back to pool) is based on a reference counting mechanism. 

When a ReferenceCounted is instantiated, its reference count=1, every time the retain() method is called, the count 
is increased, and the release() method is called to decrease the count. When the count is reduced to 0, the object 
will be released. An access exception will be reported if try to access the released object.

- Create a buff, using io.netty.buffer.Unpooled 
```
   import static io.netty.buffer.Unpooled.*;
  
   ByteBuf heapBuffer    = buffer(128);
   ByteBuf directBuffer  = directBuffer(256);
   ByteBuf wrappedBuffer = wrappedBuffer(new byte[128], new byte[256]);
   ByteBuf copiedBuffer  = copiedBuffer(ByteBuffer.allocate(128));
```

## Channel
- Channel extends AttributeMap, ChannelOutboundInvoker
    - SocketChannel/ServerSocketChannel (TCP: Epoll,KQueue,Nio,Oio)
    - DatagramChannel (UDP: Epoll,KQueue,Nio,Oio)
    - SctpChannel/SctpServerChannel (SCTP: Nio, Oio)
    - DomainSocketChannel/ServerDomainSocketChannel (Unix-TCP: Epoll, KQueue)     
    - DomainDatagramChannel (Unix-UDP: Epoll, KQueue) 
    - UdtChannel/UdtServerChannel (UDT: Byte, Message)
- ServerChannel    
    - SctpServerChannel, ServerDomainSocketChannel, ServerSocketChannel, UdtServerChannel
- DuplexChannel
    - DomainSocketChannel, SocketChannel
- UnixChannel    
    - DomainDatagramChannel, DomainSocketChannel, ServerDomainSocketChannel
- Misc
    - LocalChannel, LocalServerChannel, RxtxChannel
Each Channel has its own Channelpipeline, which contains a list of ChannelHandler, and is assigned (registered to) a 
EventLoop(io Thread) in the  EventLoopGroup.

## ChannelFuture
All Channel operations are asyn, and return immediately with the ChannelFuture, which can register the listeners:
```
Future<V> addListeners(GenericFutureListener<? extends Future<? super V>>... listeners);
```

## Channelpipeline
Created when Channel is created, to manage the list of ChannelHandlers to handle the IO events:
```
   static final EventExecutorGroup group = new DefaultEventExecutorGroup(16);
   ChannelPipeline p = ...;
   p.addLast("1", new InboundHandlerA());
   p.addLast("2", new InboundHandlerB());
   p.addLast("3", new OutboundHandlerA());
   p.addLast("4", new OutboundHandlerB());
   p.addLast("5", new InboundOutboundHandlerX());
   
   p.addLast(group，"MyHandler3", new MyHandler3());  // run this handler in the specific Executor
   // use UnorderedThreadPoolEventExecutor if don't need the handlers called by the order.
```
- For inbound event, channel.read() using ByteBuf -> 1, 2, 5 (Object Message)
- For outbound event, 5(Object Message) -> 4 -> 3 (ByteBuf) -> channel.write()
 
## ChannelHandlerContext
For ChannelHandle to work with ChannelPipeline or the other handlers:
```
public interface ChannelHandlerContext extends AttributeMap, ChannelInboundInvoker, ChannelOutboundInvoker {
   Channel channel();  //return pipeline.channel();
   ChannelHandler handler();
   ChannelPipeline pipeline();
   EventExecutor executor();  // return executor==null?channel().eventLoop():executor;
}
```

### Inbound events
```
ChannelHandlerContext.fireChannelRegistered()
ChannelHandlerContext.fireChannelActive()
ChannelHandlerContext.fireChannelRead(Object)
ChannelHandlerContext.fireChannelReadComplete()
ChannelHandlerContext.fireExceptionCaught(Throwable)
ChannelHandlerContext.fireUserEventTriggered(Object)
ChannelHandlerContext.fireChannelWritabilityChanged()
ChannelHandlerContext.fireChannelInactive()
ChannelHandlerContext.fireChannelUnregistered()
```
### Outbound
```
ChannelHandlerContext.bind(SocketAddress, ChannelPromise)
ChannelHandlerContext.connect(SocketAddress, SocketAddress, ChannelPromise)
ChannelHandlerContext.write(Object, ChannelPromise)
ChannelHandlerContext.flush()
ChannelHandlerContext.read()
ChannelHandlerContext.disconnect(ChannelPromise)
ChannelHandlerContext.close(ChannelPromise)
ChannelHandlerContext.deregister(ChannelPromise)
```

```
   public class MyInboundHandler extends ChannelInboundHandlerAdapter {
       @Override
       public void channelActive(ChannelHandlerContext ctx) {
           System.out.println("Connected!");
           ctx.fireChannelActive();  //pass to the next InboundHandler (comming)
       }
   }
  
   public class MyOutboundHandler extends ChannelOutboundHandlerAdapter {
       @Override
       public void close(ChannelHandlerContext ctx, ChannelPromise promise) {
           System.out.println("Closing ..");
           ctx.close(promise); //pass to the next OutboundHandler(outgoing)
       }
   }
```

## ChannelHandler
Handle IO event: handle, intercept, or pass to the next handler in the Pipeline 
- ChannelHandler:
    - Encoder/Decoder: Codec (Encoder+Decoder)
```
void handlerAdded(ChannelHandlerContext ctx) throws Exception;
void handlerRemoved(ChannelHandlerContext ctx) throws Exception;
void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws Exception;
```
The Handler can be shared by multiple channels, if it doesn't have the shared parameters.
**Most InboundHandlers cannot be shared, for it needs to keep some states for the Channel.**

If needs to keep the states for the channel in the Handler, and share the Handler, using its AttributeKey property:
```
   public interface Message {......   }
  
    @Sharable
   public class DataServerHandler extends SimpleChannelInboundHandler<Message> {
       private final AttributeKey<Boolean> auth = AttributeKey.valueOf("auth");
       // instead of: private boolean loggedIn;
       
        @Override
       public void channelRead(ChannelHandlerContext ctx, Message message) {
           Attribute<Boolean> attr = ctx.attr(auth);  // each channel has its own attribute
           if (message instanceof LoginMessage) {
               authenticate((LoginMessage) o);
               attr.set(true);
           } else (message instanceof GetDataMessage) {
               if (Boolean.TRUE.equals(attr.get())) {
                   ctx.writeAndFlush(fetchSecret((GetDataMessage) o));
               } else {
                   fail();
               }
           }
       }
       ...
   }
```


## ChannelGroup
One Bootstrap handles one Channel. Use ChannelGroup if needs to handle multiple Channels:
```
ChannelGroup group = new DefaultChannelGroup(GlobalEventExecutor.INSTANCE);
group.add(channelA);
group.add(channelB);

group.write(Unpooled.copiedBuffer("message from ChannelGroup for all channels",CharsetUtil.UTF_8));
```
If a Channel is closed, it will be removed from ChannelGroup automatically.
The server has one server channel and multiple accepted channels. The accepted channels can be managed by ChannelGroup.
```
ChannelGroup allChannels =
           new DefaultChannelGroup(GlobalEventExecutor.INSTANCE);ChannelGroup allChannels =
           new DefaultChannelGroup(GlobalEventExecutor.INSTANCE);
   public class MyHandler extends ChannelInboundHandlerAdapter {
        @Override
       public void channelActive(ChannelHandlerContext ctx) {
           group.add(ctx.channel());
           super.channelActive(ctx);
       }
   }
```
