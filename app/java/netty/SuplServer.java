package com.jpw.app;

import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioServerSocketChannel;

import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelOption;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.socket.SocketChannel;

import io.netty.bootstrap.ServerBootstrap;

import io.netty.handler.codec.LengthFieldBasedFrameDecoder;
import io.netty.handler.codec.bytes.ByteArrayEncoder;
import io.netty.handler.codec.bytes.ByteArrayDecoder;

public class SuplServer 
{
    public SuplServer()
    {
        executor = Executors.newFixedThreadPool(10);
        queue = new LinkedBlockingQueue();
    }

    public void run(int port) throws Exception {
        EventLoopGroup bossGroup = new NioEventLoopGroup();
        EventLoopGroup workerGroup = new NioEventLoopGroup();

        
        try {
            
            ServerBootstrap b = new ServerBootstrap();
            b.group(bossGroup, workerGroup)
              .channel(NioServerSocketChannel.class)
              .childHandler(new ChannelInitializer<SocketChannel>() {
                @Override
                public void initChannel(SocketChannel ch) 
                  throws Exception {
                    ch.pipeline().addLast(
                       //new ByteArrayEncoder(), new SuplHandler()); // raw message
                       //lengthFieldOffset = 0;  lengthFieldLength   = 2
                       //lengthAdjustment  = -2 (whole length);   initialBytesToStrip = 0
                       new LengthFieldBasedFrameDecoder(SuplDecoder.MAX_SUPL_LENGTH,0,2,-2,0),
                       new ByteArrayEncoder(), new ByteArrayDecoder(), new SuplDecoder(executor));
                       //new ByteArrayEncoder(), new ByteArrayDecoder(), new SuplDecoder(queue));  
                }
            }).option(ChannelOption.SO_BACKLOG, 128)
              .childOption(ChannelOption.SO_KEEPALIVE, true);
 
            ChannelFuture f = b.bind(port).sync();
            f.channel().closeFuture().sync();
        } finally {
            workerGroup.shutdownGracefully();
            bossGroup.shutdownGracefully();
        }
    }

    protected BlockingQueue<byte[]> queue;
    protected ExecutorService executor;
}
