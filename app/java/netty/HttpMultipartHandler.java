//https://gist.github.com/breznik/6215834
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

import static io.netty.buffer.Unpooled.copiedBuffer;
import static io.netty.handler.codec.http.HttpHeaders.isKeepAlive;
import static io.netty.handler.codec.http.HttpHeaders.Names.CONTENT_TYPE;
import static io.netty.handler.codec.http.HttpResponseStatus.BAD_REQUEST;
import static io.netty.handler.codec.http.HttpResponseStatus.OK;
import static io.netty.handler.codec.http.HttpVersion.HTTP_1_1;
import io.netty.buffer.ByteBuf;
import io.netty.buffer.ByteBufOutputStream;
import io.netty.buffer.Unpooled;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelFutureListener;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import io.netty.handler.codec.http.DefaultFullHttpResponse;
import io.netty.handler.codec.http.FullHttpRequest;
import io.netty.handler.codec.http.FullHttpResponse;
import io.netty.handler.codec.http.HttpContent;
import io.netty.handler.codec.http.HttpHeaders;
import io.netty.handler.codec.http.HttpObject;
import io.netty.handler.codec.http.HttpRequest;
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
import io.netty.util.CharsetUtil;

import java.io.IOException;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

// curl -F 'data=./odbc.ini' -F upload=@odbc.ini http://127.0.0.1:9999/upload
// Receive atribute:data=./odbc.ini
// Receive fileload:content-disposition: form-data; name="upload"; filename="odbc.ini"
//
//public class MyHttpHandler extends SimpleChannelInboundHandler<HttpObject> {
public class MyHttpHandler extends SimpleChannelInboundHandler<FullHttpRequest> {
    private static final Logger LOGGER = LoggerFactory.getLogger(MyHttpHandler.class);
    
    private static final String CONTENT_TYPE_JSON = "application/json";
    
    /** Factory for creating data objects used in decoding of Multipart POSTs */
    private final HttpDataFactory dataFactory;
    
    /** Decoder used for Multipart POST requests */
    private HttpPostRequestDecoder decoder;
    
    /** The request used for decoding of Multipart POST requests */
    private FullHttpRequest fullHttpRequest;
    
    private String readData;
    
    static {
        DiskFileUpload.deleteOnExitTemporaryFile = true;    // delete file on exit (normal exit)
        DiskFileUpload.baseDirectory = null;                // system temp directory
        DiskAttribute.deleteOnExitTemporaryFile = true;     // delete file on exit (normal exit)
        DiskAttribute.baseDirectory = null;                 // system temp directory
    }
    
    MyHttpHandler() {//final HttpDataFactory dataFactory) {
        //this.dataFactory = dataFactory;
        this.dataFactory = new DefaultHttpDataFactory(DefaultHttpDataFactory.MINSIZE);
    }
    
    @Override
    public void channelUnregistered(ChannelHandlerContext ctx) throws Exception {
        if (decoder != null) {
            decoder.cleanFiles();
        }
    }
    
    @Override
    // HttpObject when using 
    //     pipeline.addLast(new HttpRequestDecoder());
    //     pipeline.addLast(new HttpResponseEncoder());
    //protected void channelRead0(ChannelHandlerContext ctx, HttpObject msg) throws Exception {
    //
    // FullHttpRequest when using
    //     pipeline.addLast("codec", new HttpServerCodec()); // HttpMessage
    //     pipeline.addLast("aggregator", new HttpObjectAggregator(Short.MAX_VALUE)); 
    //     pipeline.addLast("customer", new MyHttpHandler() );  //FullHttpRequest
    //
    protected void channelRead0(ChannelHandlerContext ctx, FullHttpRequest request) throws Exception {
        LOGGER.info("http request:"+request.toString()+"\n");
        //System.out.format("Http Request: %s\n\n", request.toString());
        
        if (request.method().name().equalsIgnoreCase("GET")) {
            return;
        }
        
        String contentType = request.headers().get("Content-Type");
            
        if (contentType == null) {
            String content = request.content().toString(Charset.forName("UTF-8"));
            LOGGER.info("content:\n"+content+"\n");

            sendResponse(ctx, HttpResponseStatus.OK, "content");
            return;
        }
            
        if(contentType.contains(";")) {
              contentType = contentType.split(";")[0];
        }
        switch (contentType.toLowerCase()) {
            case "application/json":
            case "application/json;charset=utf-8":
            case "text/xml":
                String content = request.content().toString(Charset.forName("UTF-8"));
                LOGGER.info("content:"+content+"\n");
                break;

            case "multipart/form-data":
                HttpPostRequestDecoder decoder = null; 
                try {
                    decoder = new HttpPostRequestDecoder(new io.netty.handler.codec.http.multipart.DefaultHttpDataFactory(false), request);
                    int cnt = decoder.getBodyHttpDatas().size();
                    for(int i=0; i< cnt; i++) {
                         InterfaceHttpData data = decoder.next();
                         if(data.getHttpDataType() == HttpDataType.FileUpload) {
                         /*
                            FileUpload fileUpload = (FileUpload) data;
                            if(fileUpload.isCompleted()) {
                                MultipartFile file = new MultipartFile();
                                file.setFileName(fileUpload.getFilename());
                                file.setFileType(fileUpload.getContentType());
                                file.setFileData(fileUpload.get());
                                //requestInfo.getFiles().add(file);
                           }*/
                             System.out.format("Receive fileload:%s\n",data.toString());
                         } else if(data.getHttpDataType() == HttpDataType.Attribute) {
                                Attribute attribute = (Attribute) data;
                                System.out.format("Receive atribute:%s\n",data.toString());
                                //requestInfo.getFormData().put(attribute.getName(), attribute.getValue());
                         } else {

                         }
                         decoder.removeHttpDataFromClean(data);
                         data.release();
                    }
                } finally {
                    if(decoder != null) {
                         decoder.destroy();
                         decoder = null;
                    }
                }
        }

        sendResponse(ctx, HttpResponseStatus.OK, "multipart");
        //}
        
        /*
            try {
                decoder = new HttpPostRequestDecoder(dataFactory, request);
                decoder.setDiscardThreshold(0);
            } catch (NotEnoughDataDecoderException e) {
                // No body to decode
                handleInvalidRequest(ctx, request, BAD_REQUEST, copiedBuffer(e.getMessage(), CharsetUtil.UTF_8));
                return;
            } catch (ErrorDataDecoderException e) {
                // Bad default charset or other issues such as a missing boundary
                handleInvalidRequest(ctx, request, BAD_REQUEST, copiedBuffer(e.getMessage(), CharsetUtil.UTF_8));
                return;
            }
        //}
        
        if (decoder != null) {
            //if (msg instanceof HttpContent) {
               // HttpContent chunk = (HttpContent) msg;
        if (request instanceof HttpContent) {
                HttpContent chunk = (HttpContent) request;
            
                try {
                    decoder.offer(chunk);
                } catch (ErrorDataDecoderException e) {
                    LOGGER.warn("Unable to add chunk to decoder", e);
                    handleInvalidRequest(ctx, fullHttpRequest, BAD_REQUEST, copiedBuffer(e.getMessage(), CharsetUtil.UTF_8));
                    return;
                } catch (Exception e) {
                    LOGGER.warn("Unable to add chunk to decoder", e);
                    handleInvalidRequest(ctx, fullHttpRequest, BAD_REQUEST, copiedBuffer(e.getMessage(), CharsetUtil.UTF_8));
                    return;
                }
                
                // Read data as it becomes available, chunk by chunk.
                readChunkByChunk(ctx);
                
                if (chunk instanceof LastHttpContent) {
                    readChunkByChunk(ctx);
                    sendResponse(ctx);
                    resetPostRequestDecoder();
                }
            }
        }
        */
    }
    
    /**
     * Reads each HTTP chunk into an {@link InterfaceHttpData} for processing
     * @param ctx
     */
    private void readChunkByChunk(ChannelHandlerContext ctx) {
        try {
            while (decoder.hasNext()) {
                InterfaceHttpData data = decoder.next();
                if (data != null) {
                    try {
                        processChunk(ctx, data);
                    } finally {
                        data.release();
                    }
                }
            }
        } catch (EndOfDataDecoderException e) {
            // No more data to decode, that's fine
        }
    }
    
    /**
     * Processes an individual HTTP Data chunk
     * @param ctx
     * @param data
     */
    private void processChunk(ChannelHandlerContext ctx, InterfaceHttpData data) {
        LOGGER.debug("HTTP Data Name: {}, Type: {}", data.getName(), data.getHttpDataType());
        
        switch(data.getHttpDataType()) {
            case Attribute:
                Attribute attrib = (Attribute) data;
                if (!"json".equals(attrib.getName())) {
                    LOGGER.debug("Received unknown attribute: {}", attrib.getName());
                    handleInvalidRequest(ctx, fullHttpRequest, BAD_REQUEST, copiedBuffer("Unknown Part Name: " + attrib.getName(), CharsetUtil.UTF_8));
                    return;
                }
                
                try {
                    readData = attrib.getByteBuf().toString(CharsetUtil.UTF_8);
                    LOGGER.debug("Content Size: {}, Content: {}", attrib.getByteBuf().readableBytes(), readData);
                } catch (IOException e) {
                    LOGGER.error("Unable to read attribute content", e);
                }
                
                break;
            case FileUpload:
                FileUpload fileUpload = (FileUpload) data;
                // handle upload
                break;
            default:
                LOGGER.warn("Received unknown attribute type. Skipping.");
                break;
        }
    }
    
    private void resetPostRequestDecoder() {
        fullHttpRequest = null;
        readData = null;

        // clean previous FileUpload if Any
        decoder.destroy();
        decoder = null;
    }

    private static void sendResponse(ChannelHandlerContext ctx, HttpResponseStatus status, String message) {
        final FullHttpResponse response;
        String msgDesc = message;
        if (message == null) {
          msgDesc = "Failure: " + status;
        }
        msgDesc += " \r\n";

        final ByteBuf buffer = Unpooled.copiedBuffer(msgDesc, CharsetUtil.UTF_8);
        if (status.code() >= HttpResponseStatus.BAD_REQUEST.code()) {
          response = new DefaultFullHttpResponse(HTTP_1_1, status, buffer);
        } else {
          response = new DefaultFullHttpResponse(HTTP_1_1, status, buffer);
        }
        response.headers().set(HttpHeaderNames.CONTENT_TYPE, "text/plain; charset=UTF-8");

        // Close the connection as soon as the response is sent.
        ctx.writeAndFlush(response).addListener(ChannelFutureListener.CLOSE);
      }
    
    private void sendResponse(ChannelHandlerContext ctx) {
        // Serialize Response
        ByteBuf outputContent = Unpooled.buffer();
        ByteBufOutputStream bbos = new ByteBufOutputStream(outputContent);
        try {
            bbos.writeBytes(readData);
        } catch (IOException e) {
            LOGGER.error("Unable to serialize response", e);
        }
        
        // Create HTTP Response
        FullHttpResponse response = new DefaultFullHttpResponse(HTTP_1_1, OK, outputContent);
        response.headers().set(CONTENT_TYPE, CONTENT_TYPE_JSON);
        setContentLength(response, outputContent.readableBytes());
        
        // Send HTTP Response
        sendHttpResponse(ctx, fullHttpRequest, response);
    }
    
    private void handleInvalidRequest(ChannelHandlerContext ctx, HttpRequest request, HttpResponseStatus responseStatus, ByteBuf errorMessage) {
        sendHttpResponse(ctx, request, new DefaultFullHttpResponse(HTTP_1_1, responseStatus, errorMessage));
        return;
    }
    
    private void sendHttpResponse(ChannelHandlerContext ctx, HttpRequest request, FullHttpResponse response) {
        if (!response.headers().contains(HttpHeaders.Names.CONTENT_LENGTH)) {
            setContentLength(response, response.content().readableBytes());
        }

        // Send the response and close the connection if necessary.
        ChannelFuture f = ctx.channel().writeAndFlush(response);
        if (!isKeepAlive(request) || response.getStatus().code() != OK.code()) {
            f.addListener(ChannelFutureListener.CLOSE);
        }
    }
    
    private static void setContentLength(FullHttpResponse response, int length) {
        response.headers().add(HttpHeaders.Names.CONTENT_LENGTH, length);
    }
    
    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws Exception {
        LOGGER.warn("Exception:", cause);
        ctx.close();
    }
    
    /*
    public void testMultipart() throws Exception {
        HttpRequest request = new DefaultFullHttpRequest(HttpVersion.HTTP_1_1, HttpMethod.POST, "/");
        HttpPostRequestEncoder encoder = new HttpPostRequestEncoder(dataFactory, request, true);
        
        request.headers().add(HttpHeaders.Names.CONTENT_TYPE, HttpHeaders.Values.MULTIPART_FORM_DATA);
        encoder.addBodyHttpData(createJSONAttribute(request, dataFactory));
        encoder.addBodyHttpData(createFileUpload(request, dataFactory));
        request = encoder.finalizeRequest();
        
        sendMultipartRequest(request, encoder);
     }
     
    private void sendMultipartRequest(HttpRequest request, HttpPostRequestEncoder encoder) throws Exception {
        channel.writeInbound(request);
        
        if (!channel.isOpen()) {
            // Channel was closed early due to a bad request being written, so don't bother to write the chunks
            encoder.cleanFiles();
            return;
        }
        
        HttpContent content;
        while (!encoder.isEndOfInput()) {
            content = encoder.readChunk(null);
            channel.writeInbound(content);
        }
        channel.flush();
        
        encoder.cleanFiles();
    }

    private InterfaceHttpData createJSONAttribute(HttpRequest request, HttpDataFactory factory) throws IOException {
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
     */
}
