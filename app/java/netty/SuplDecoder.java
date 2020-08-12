package com.jpw.app;

import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;

import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelFutureListener;
import io.netty.channel.ChannelHandlerContext;

import io.netty.handler.codec.MessageToMessageDecoder;

public class SuplDecoder extends MessageToMessageDecoder<byte[]> 
{
  public static final int MAX_SUPL_LENGTH = 4096;

  /*
  public SuplDecoder(BlockingQueue<byte[]> queue)
  {
      this.queue = queue; //may the channel
  }*/

  public SuplDecoder(ExecutorService executor) {
      this.executor = executor;
  }


  @Override
  public void decode(ChannelHandlerContext ctx, byte[] in, List<Object> out) {

      //boolean ret = queue.offer(in);
      //Future<?>	task = executor.submit( new SuplTask () );
      executor.submit( new SuplTask (ctx.channel(), in) );

      //System.out.format("SuplDecoder Received data: lengthe=%d; queue_size=%d\n",in.length,queue.size());
      System.out.format("SuplDecoder Received data: length=%d",in.length);
      System.out.println("content:"+Util.toHexString(in));

      //in.clear(); // use ByteArrayEncoder() only
      //in.release(); // not use LengthFieldBasedFrameDecoder
  }
  
  @Override
  public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) { 
      // Close the connection when an exception is raised.
      cause.printStackTrace();
      //ctx.close();
  }
  
  //final BlockingQueue<byte[]> queue;
  final ExecutorService executor;
}
