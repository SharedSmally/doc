package com.jpw.app;

import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;

import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelFutureListener;

public class SuplHandler extends ChannelInboundHandlerAdapter 
{
  private ByteBuf tmp;

  @Override
  public void handlerAdded(ChannelHandlerContext ctx) {
      System.out.println("Handler added");
      tmp = ctx.alloc().buffer(4);
  }

  @Override
  public void handlerRemoved(ChannelHandlerContext ctx) {
      System.out.println("Handler removed");
      tmp.release();
      tmp = null;
  }

  @Override
  public void channelRead(ChannelHandlerContext ctx, Object msg) {
      ByteBuf m = (ByteBuf) msg;
      tmp.writeBytes(m);
      m.release();  //no inbound handler; or m.clear() if use ByteArrayEncoder()

      System.out.format("Received data: readable size=%d; capacity=%d",tmp.readableBytes(), tmp.capacity());
      System.out.println("; Content=\n"+Util.hex(tmp));

      byte[] data = Util.toByteArray(Util.SAMPLE_STR);
      System.out.println("Send data:"+data.length);

      ChannelFuture future = ctx.writeAndFlush(data);
      // Wait until all messages are flushed before closing the channel.
      if (future != null) {
          future.addListener(new ChannelFutureListener() {
              public void operationComplete(ChannelFuture channelFuture) {
                   System.out.println("Finish Sending data:");
                  // Perform post-closure operation ...
              }
          });
          
          try {
              future.sync();
          } catch (Exception ex) {}
      } else {
         System.out.println("Fails to write and flush data");
      }
  }
  
  @Override
  public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) { 
      // Close the connection when an exception is raised.
      cause.printStackTrace();
      //ctx.close();
  }
}
