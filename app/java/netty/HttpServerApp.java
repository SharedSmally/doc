package com.jpw.app;

import java.nio.charset.StandardCharsets;

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
import io.netty.channel.ChannelPipeline;

import io.netty.bootstrap.ServerBootstrap;

import io.netty.buffer.ByteBuf;

import io.netty.handler.ssl.SslHandler;

import io.netty.handler.logging.LogLevel;
import io.netty.handler.logging.LoggingHandler;

import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;

import io.netty.handler.codec.DecoderResult;

import io.netty.handler.codec.http.HttpHeaders;
import io.netty.handler.codec.http.HttpHeaderNames;
import io.netty.handler.codec.http.HttpHeaderValues;
import io.netty.handler.codec.http.HttpMessage;
import io.netty.handler.codec.http.FullHttpMessage;
import io.netty.handler.codec.http.FullHttpRequest;
import io.netty.handler.codec.http.HttpUtil;

import io.netty.handler.codec.http.HttpServerCodec;
import io.netty.handler.codec.http.HttpRequestDecoder;
import io.netty.handler.codec.http.HttpResponseEncoder;
import io.netty.handler.codec.http.HttpObjectAggregator;

import io.netty.handler.codec.http.HttpVersion;
import io.netty.handler.codec.http.HttpResponseStatus;
import io.netty.handler.codec.http.HttpResponse;
import io.netty.handler.codec.http.DefaultHttpResponse;

import io.netty.buffer.Unpooled;
import io.netty.handler.codec.http.FullHttpResponse;
import io.netty.handler.codec.http.DefaultLastHttpContent;
import io.netty.handler.codec.http.DefaultFullHttpResponse;

// test:
// curl --url http://127.0.0.1:9999/test
// curl http://127.0.0.1:9999/upload --upload-file makefile

public class HttpServerApp 
{
    public ServerApp()
    {
        executor = Executors.newFixedThreadPool(10);
        queue = new LinkedBlockingQueue();
    }
    static final int MAX_HTTP_CONTENT_LENGTH = 1024*64; // 64K
    
    public void run(int port) throws Exception {
        EventLoopGroup bossGroup = new NioEventLoopGroup();
        EventLoopGroup workerGroup = new NioEventLoopGroup();
        
        // Load the certificates and initiate the SSL Context
        //SSLHandlerProvider.initSSLContext();
        //sslHandler = SSLHandlerProvider.getSSLHandler();
        
        try {
            ServerBootstrap b = new ServerBootstrap();
            b.group(bossGroup, workerGroup)
              .channel(NioServerSocketChannel.class)
              .handler(new LoggingHandler(LogLevel.DEBUG))
              .childHandler(new ChannelInitializer<SocketChannel>() {
                @Override
                public void initChannel(SocketChannel ch) 
                  throws Exception {
                    ChannelPipeline p = ch.pipeline();
                    //p.addLast("logging", new LoggingHandler(this.getClass(), LogLevel.DEBUG));
                    //p.remove(LOGGING_HANDLER_NAME);
                    //p.addLast("ssl", sslHandler);

                    // Provides support for http objects:
                    p.addLast("codec", new HttpServerCodec()); // HttpMessage
                    // Deals with fragmentation in http traffic: 
                    p.addLast("aggregator", new HttpObjectAggregator(MAX_HTTP_CONTENT_LENGTH)); //FullHttpRequest
                    // Deals with optional compression of responses:
                    // p.addLast("aggregator", new HttpContentCompressor());

                    /*
                    p.addLast("customer", new SimpleChannelInboundHandler<HttpMessage>() {
                            @Override
                            protected void channelRead0(ChannelHandlerContext ctx, HttpMessage msg) throws Exception {
                                System.out.println("Http Version: " + msg.protocolVersion() + " ");
                                for (java.util.Map.Entry<String,String> entry : msg.headers().entries() ) {
                                    System.out.format("header: %s=%s\n", entry.getKey(), entry.getValue());
                                }
                            }
                        }
                    */
                    p.addLast("customer", new SimpleChannelInboundHandler<FullHttpRequest>() {
                            @Override
                            protected void channelRead0(ChannelHandlerContext ctx, FullHttpRequest request) throws Exception {
                                // If this handler is hit then no upgrade has been attempted and the client is just talking HTTP.
                                System.out.format("Http Request: %s\n\n", request.toString());

                                // Check for invalid http data:
                                if(request.getDecoderResult() != DecoderResult.SUCCESS ) {
                                    ctx.close();
                                    return;
                                }

                                //Http Request: version=HTTP/1.1, method: GET; uri=/test
                                System.out.format("Http Request: version=%s, method: %s; uri=%s\n",
                                        request.protocolVersion(), request.getMethod(), request.getUri());
                                /*
                                for (java.util.Map.Entry<String,String> entry : request.headers().entries() ) {
                                    System.out.format("header: %s=%s\n", entry.getKey(), entry.getValue());
                                }
                                */

                                ByteBuf data = request.content();
                                System.out.format("POST/PUT length: %d\n", data.readableBytes());
                                System.out.format("POST/PUT as string: %s\n", data.toString(StandardCharsets.UTF_8)); 

                                // Send response back
                                ByteBuf responseBytes = ctx.alloc().buffer();
                                responseBytes.writeBytes("Hello World".getBytes());
                                // ByteBuf responseBytes = Unpooled.copiedBuffer("My Netty".getBytes());
                                
                                HttpResponseStatus responseStatus = HttpResponseStatus.OK;
                                FullHttpResponse response = new DefaultFullHttpResponse(HttpVersion.HTTP_1_1, 
                                     responseStatus, responseBytes);
                                response.headers().add(request.headers());
                                response.headers().set(HttpHeaderNames.CONTENT_LENGTH, response.content().readableBytes());
                                
                                if (HttpUtil.isKeepAlive(request)) {
                                    response.headers().set(HttpHeaderNames.CONNECTION, HttpHeaderValues.KEEP_ALIVE);
                                }
                                if (HttpUtil.is100ContinueExpected(request)) {
                                    ctx.write(new DefaultFullHttpResponse(HttpVersion.HTTP_1_1, HttpResponseStatus.CONTINUE));
                                }
                                ctx.writeAndFlush(response);
                                System.out.format("write response: %s\n", response.toString());
                            }

                            public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
                                cause.printStackTrace();
                                ctx.close();
                            }
                        } 
                    );
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
    protected SslHandler sslHandler;
}
