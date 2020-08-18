package com.jpw.app;

import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioSocketChannel;

import io.netty.buffer.Unpooled;
import io.netty.buffer.ByteBuf;
import io.netty.buffer.ByteBufAllocator;
import io.netty.buffer.ByteBufOutputStream;

import io.netty.channel.Channel;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelOption;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.ChannelPipeline;
import io.netty.channel.SimpleChannelInboundHandler;

import io.netty.bootstrap.Bootstrap;

import io.netty.handler.ssl.SslHandler;

import io.netty.handler.codec.http.HttpClientCodec;
import io.netty.handler.codec.http.HttpRequestEncoder;
import io.netty.handler.codec.http.HttpResponseDecoder;
import io.netty.handler.codec.http.HttpObjectAggregator;

import io.netty.handler.codec.http.DefaultHttpRequest;
import io.netty.handler.codec.http.DefaultFullHttpRequest;
import io.netty.handler.codec.http.DefaultFullHttpResponse;
import io.netty.handler.codec.http.FullHttpRequest;
import io.netty.handler.codec.http.FullHttpResponse;
import io.netty.handler.codec.http.HttpContent;
import io.netty.handler.codec.http.HttpHeaders;
import io.netty.handler.codec.http.HttpObject;
import io.netty.handler.codec.http.HttpRequest;
import io.netty.handler.codec.http.HttpVersion;
import io.netty.handler.codec.http.HttpMethod;
import io.netty.handler.codec.http.HttpResponseStatus;
import io.netty.handler.codec.http.LastHttpContent;
import io.netty.handler.codec.http.HttpHeaderNames;

import io.netty.handler.codec.http.multipart.Attribute;
import io.netty.handler.codec.http.multipart.InterfaceHttpData.HttpDataType;
import io.netty.handler.codec.http.multipart.DiskAttribute;
import io.netty.handler.codec.http.multipart.DiskFileUpload;
import io.netty.handler.codec.http.multipart.FileUpload;
import io.netty.handler.codec.http.multipart.HttpDataFactory;
import io.netty.handler.codec.http.multipart.DefaultHttpDataFactory;
import io.netty.handler.codec.http.multipart.HttpPostRequestDecoder;
import io.netty.handler.codec.http.multipart.HttpPostRequestDecoder.EndOfDataDecoderException;
import io.netty.handler.codec.http.multipart.HttpPostRequestDecoder.ErrorDataDecoderException;
import io.netty.handler.codec.http.multipart.HttpPostRequestDecoder.NotEnoughDataDecoderException;
import io.netty.handler.codec.http.multipart.InterfaceHttpData;

import io.netty.handler.codec.http.multipart.HttpPostRequestEncoder;

import io.netty.util.CharsetUtil;

import java.io.File;
import java.io.IOException;
import java.io.BufferedWriter;
import java.io.FileWriter;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ClientApp 
{
	
    public static void main(String[] args) throws Exception {
        String host = "127.0.0.1";
        int port = 9999;
        
        ClientApp app = new ClientApp();
        app.run(host,port);
    }
    
    public ClientApp()
    {
        executor = Executors.newFixedThreadPool(10);
        queue = new LinkedBlockingQueue();
        this.dataFactory = new DefaultHttpDataFactory(DefaultHttpDataFactory.MINSIZE);
    }

    public void run(String host, int port) throws Exception {
        EventLoopGroup workerGroup = new NioEventLoopGroup();
        
        // Load the certificates and initiate the SSL Context
        //SSLHandlerProvider.initSSLContext();
        //sslHandler = SSLHandlerProvider.getSSLHandler();
        
        try {
            
            Bootstrap b = new Bootstrap();
            b.group(workerGroup)
              .channel(NioSocketChannel.class)
              .handler(new ChannelInitializer<SocketChannel>() {
                @Override
                public void initChannel(SocketChannel ch) throws Exception {
                    //ch.pipeline().addLast( //sslHandler, );
                    ChannelPipeline p = ch.pipeline();
                    p.addLast("codec", new HttpClientCodec()); // HttpMessage
                    // Deals with fragmentation in http traffic: 
                    p.addLast("aggregator", new HttpObjectAggregator(Short.MAX_VALUE)); //FullHttpRequest
                    
                    p.addLast("customer", new SimpleChannelInboundHandler<FullHttpResponse>() {
                        @Override
                        public void channelRead0(ChannelHandlerContext ctx, FullHttpResponse response) throws Exception {

                                System.out.format("STATUS: %s ; VERSION: %s\n\n", response.getStatus(),  response.getProtocolVersion());

                                if (!response.headers().isEmpty()) {
                                    for (java.util.Map.Entry<String,String> entry : response.headers().entries() ) {
                                        System.out.format("HEADER: %s=%s\n", entry.getKey(), entry.getValue());
                                    }
                                    System.out.println();
                                }

                                if (HttpHeaders.isTransferEncodingChunked(response)) {
                                    System.out.println("CHUNKED CONTENT {");
                                } else {
                                    System.out.println("CONTENT");
                                }
                        }

                        @Override
                        public void exceptionCaught( ChannelHandlerContext ctx, Throwable cause) throws Exception {
                            cause.printStackTrace();
                            ctx.close();
                        }
                    }
                    );
                }
            });
 
            ChannelFuture f = b.connect(host,port).sync();
            
            HttpRequest request = getSimpleHttpRequest(host);
            
            // Send the HTTP request.
            Channel ch = f.channel();
            
            testMultipart(ch);
            
            //ch.writeAndFlush(request);

            // Wait for the server to close the connection.
            ch.closeFuture().sync();
        } finally {
            workerGroup.shutdownGracefully();
        }
    }
    
    protected HttpRequest getSimpleHttpRequest(String host)
    {
        // Prepare the HTTP request.
        HttpRequest request = new DefaultHttpRequest(
                HttpVersion.HTTP_1_1, HttpMethod.GET, "/");
        request.headers().set(HttpHeaders.Names.HOST, host);
        request.headers().set(HttpHeaders.Names.CONNECTION, HttpHeaders.Values.CLOSE);
        //request.headers().set(HttpHeaders.Names.ACCEPT_ENCODING, HttpHeaders.Values.GZIP);

        /*
        // Set some example cookies.
        request.headers().set(
                HttpHeaders.Names.COOKIE,
                ClientCookieEncoder.encode(
                        new DefaultCookie("my-cookie", "foo"),
                        new DefaultCookie("another-cookie", "bar")));
        */
        return request;
    }

    
    public void testMultipart(Channel channel) throws Exception {
        HttpRequest request = new DefaultFullHttpRequest(HttpVersion.HTTP_1_1, HttpMethod.POST, "/");
        HttpPostRequestEncoder encoder = new HttpPostRequestEncoder(dataFactory, request, true);
        
        request.headers().add(HttpHeaders.Names.CONTENT_TYPE, HttpHeaders.Values.MULTIPART_FORM_DATA);
        encoder.addBodyHttpData(createJSONAttribute(request, dataFactory));
        encoder.addBodyHttpData(createFileUpload(request, dataFactory));
        request = encoder.finalizeRequest();
        
        sendMultipartRequest(channel, request, encoder);
     }
     
    private void sendMultipartRequest(Channel channel, HttpRequest request, HttpPostRequestEncoder encoder) throws Exception {
        channel.write(request);
        
        if (!channel.isOpen()) {
            // Channel was closed early due to a bad request being written, so don't bother to write the chunks
            encoder.cleanFiles();
            return;
        }
        
        HttpContent content;
        while (!encoder.isEndOfInput()) {
            content = encoder.readChunk((ByteBufAllocator)null);
            channel.write(content);
        }
        channel.flush();
        
        encoder.cleanFiles();
    }

    private InterfaceHttpData createJSONAttribute(HttpRequest request, HttpDataFactory factory) throws IOException {
        String jsonContent="{ \"name\":\"John\" }";
        ByteBuf content = Unpooled.buffer();
        ByteBufOutputStream bbos = new ByteBufOutputStream(content);
        bbos.writeBytes(jsonContent);
        return factory.createAttribute(request, "json", content.toString(CharsetUtil.UTF_8));
    }
    
    private InterfaceHttpData createFileUpload(HttpRequest request, HttpDataFactory factory) throws IOException {
        File file = File.createTempFile("upload", ".txt");
        file.deleteOnExit();
        
        BufferedWriter bw = new BufferedWriter(new FileWriter(file));
        bw.write("Example file to be posted");
        bw.close();
        
        FileUpload fileUpload = factory.createFileUpload(request, "file", file.getName(), "plain/text", "7bit", null, file.length());
        fileUpload.setContent(file);
        
        return fileUpload;
    }
    
    protected BlockingQueue<byte[]> queue;
    protected ExecutorService executor;
    protected SslHandler sslHandler;
    private final HttpDataFactory dataFactory;
}
