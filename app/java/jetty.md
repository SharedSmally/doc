# Embedded Jetty 
- [jetty document](https://www.eclipse.org/jetty/documentation/current/index.html)
    - [jetty embedding](https://www.eclipse.org/jetty/documentation/current/embedding-jetty.html)
    - [embedding examples](https://www.eclipse.org/jetty/documentation/current/embedded-examples.html)
- [java API doc](https://www.eclipse.org/jetty/javadoc/)
- [Tutorial](https://wiki.eclipse.org/Jetty/Tutorial/Embedding_Jetty)

## Maven

## Jetty Server
- [Maven](https://mvnrepository.com/artifact/org.eclipse.jetty): need jetty-server and jetty-servlet libraries:
```
<dependency>
    <groupId>org.eclipse.jetty</groupId>
    <artifactId>jetty-server</artifactId>
    <version>9.4.31.v20200723</version>
</dependency>
<dependency>
    <groupId>org.eclipse.jetty</groupId>
    <artifactId>jetty-servlet</artifactId>
    <version>9.4.31.v20200723</version>
</dependency>
```
Additional libraries include WebSocket, WebApp, Security, Http2, HttpClient, ...

or use jetty-all.jar
```
<dependency>
    <groupId>org.eclipse.jetty.aggregate</groupId>
    <artifactId>jetty-all</artifactId>
    <version>9.4.31.v20200723</version>
    <type>pom</type>
    <scope>test</scope>
</dependency>
```
- Handler
```
public class HelloHandler extends AbstractHandler{
    public void handle(String target,Request baseRequest,HttpServletRequest request,
              HttpServletResponse response) throws IOException, ServletException {
        response.setContentType("text/html;charset=utf-8");
        response.setStatus(HttpServletResponse.SC_OK);
        baseRequest.setHandled(true);
        response.getWriter().println("<h1>Hello World</h1>");
    }
}
```
- Server Application
```
public static void main(String[] args) throws Exception{
    Server server = new Server(8080);
    server.setHandler(new HelloHandler());
     server.start();
    server.join();
}
```
## [Handler](https://www.eclipse.org/jetty/javadoc/9.4.31.v20200723/org/eclipse/jetty/server/Handler.html)
To produce a response to a request:
- Examine/modify the HTTP request.
- Generate the complete HTTP response.
- Call another Handler (HandlerWrapper).
- Select one or many Handlers to call (HandlerCollection).
```
void handle(java.lang.String target, Request baseRequest, javax.servlet.http.HttpServletRequest request, 
            javax.servlet.http.HttpServletResponse response)
            throws java.io.IOException, javax.servlet.ServletException
```
Application:
```
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.HttpConnectionFactory;
public class App {
    public static void main( String[] args ) {
        try {
            App app = new App();
            app.start();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
    public void start() throws Exception {
        Server server = new Server(9999);
        try {
            server.getConnectors()[0].getConnectionFactory(HttpConnectionFactory.class);
            server.setHandler(new HelloHttpRequestHandler());
            server.start();
            server.join();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```
Customized Handler:
```
import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.handler.AbstractHandler;

public class HelloHttpRequestHandler extends AbstractHandler {
    public HelloHttpRequestHandler() {
        this("Hello World");
    }
    public HelloHttpRequestHandler( String greeting){
        this(greeting, null);
    }   
    public HelloHttpRequestHandler( String greeting, String body ) {
        this.greeting = greeting;
        this.body = body;
    }

    @Override
    public void handle( String target, Request baseRequest,  HttpServletRequest request,
                       HttpServletResponse response ) throws IOException, ServletException {
        response.setContentType("text/html; charset=utf-8");
        response.setStatus(HttpServletResponse.SC_OK);

        PrintWriter out = response.getWriter();

        out.println("<h1>" + greeting + "</h1>");
        if (body != null) {
            out.println(body);
        }

        baseRequest.setHandled(true);
    }

    final String greeting;
    final String body;
}
```

### Handler Collections
Complex request handling is typically built from multiple Handlers to be combined:
- HandlerCollection

Holds a collection of other handlers and calls each handler in order, such as for combining statistics and logging handlers with the handler that generates the response.
- HandlerList

A Handler Collection that calls each handler in turn until either an exception is thrown, the response is committed or the request.isHandled() returns true, such as combining handlers that conditionally handle a request, such as calling multiple contexts until one matches a virtual host.

- HandlerWrapper

A Handler base class to daisy chain handlers together in the style of aspect-oriented programming, such as a standard web application implemented by a chain of a context, session, security and servlet handlers.

- ContextHandlerCollection

A specialized HandlerCollection that uses the longest prefix of the request URI (the contextPath) to select a contained ContextHandler to handle the request.

### Handlers
- ResourceHandler:  serve static content/resource from the specific path
- ServletHandler: handles HTTP requests based on servlets logic.
- ContextHandler: type of ScopedHandler that responds only to requests that a URI prefix matches the configured context path
- ServletContextHandler: specialized ContextHandler that supports for standard sessions and Servlets
- WebAppContext: extension of ServletContextHandler that uses the standard layout and web.xml to configure the servlets, filters and other features from a web.xml and/or annotations.


## Connectors
When the Server instance is passed a port number, it internally creates a default instance of a Connector(ServerConnector) that listens for requests on that port. It is desirable to explicitly instantiate and configure one or more Connectors for a Server instance.


## WebSocket


## [HttpClient](https://www.eclipse.org/jetty/documentation/current/http-client-api.html)
- Blocking API
- Non-Blocking API

- [Content Handling](https://www.eclipse.org/jetty/documentation/current/http-client-api.html#http-client-content)
```
import static org.junit.Assert.assertTrue;

import org.junit.Test;

import java.util.concurrent.TimeUnit;
import java.nio.charset.StandardCharsets;

import org.eclipse.jetty.client.HttpClient;
import org.eclipse.jetty.client.api.ContentResponse;
import org.eclipse.jetty.client.api.Response;//.CompleteListener
import org.eclipse.jetty.client.api.Result;
import org.eclipse.jetty.client.util.BufferingResponseListener;

public class AppTest {
    @Test
    public void testHelloHttpServer() {
       try {  //https://www.eclipse.org/jetty/documentation/current/http-client-api.html
        HttpClient httpClient = new HttpClient();
        httpClient.start();
        testGet(httpClient);
        testPost(httpClient);
        testPostAsync(httpClient);
        Thread.sleep(5000);       
        httpClient.stop();
       } catch (Exception ex)       {
          ex.printStackTrace();
       }
    }
    
    protected void testGet(HttpClient client) throws Exception {
        ContentResponse response = client
            .GET("http://localhost:9999");

        System.out.format("Http GET response:\n  version=%s; status=%d; reason=%s\n",
                response.getVersion(), response.getStatus(), response.getReason());
        System.out.format("  type=%s; encoding=%s;\n  content:\n%s\n",
              response.getMediaType(), response.getEncoding(), response.getContentAsString());
    }
    
    protected void testPost(HttpClient client) throws Exception {
        ContentResponse response = client
          .POST("http://localhost:9999/entity/1")
          .param("p", "value")
          .timeout(5, TimeUnit.SECONDS)
          .send();

        System.out.format("Http POST response:\n  version=%s; status=%d; reason=%s\n",
                response.getVersion(), response.getStatus(), response.getReason());
        System.out.format("  type=%s; encoding=%s;\n  content:\n%s\n",
              response.getMediaType(), response.getEncoding(), response.getContentAsString());
    }

    protected void testPostAsync(HttpClient client) throws Exception {
        client
          .POST("http://localhost:9999/entity/1")
          .param("p", "value")
          .timeout(5, TimeUnit.SECONDS)
          .onResponseContent(new Response.ContentListener() {
              @Override
              public void onContent(Response response, java.nio.ByteBuffer content) {
                   System.out.println("POST request content");
                   System.out.format("Http Async POST response content:\n  version=%s; status=%d; reason=%s\n",
                           response.getVersion(), response.getStatus(), response.getReason());
                   //System.out.format("  content:\n%s\n", content.toString()); //not work
              }
          })
          .send(/* new Response.CompleteListener() {
              @Override
              public void onComplete(Result result) {  //1.7
              result -> { //1.8
                  if (result.isSucceeded()) {
                      System.out.println("POST request completed: success");
                      Response response = result.getResponse();
                      System.out.format("Http Async POST response:\n  version=%s; status=%d; reason=%s\n",
                              response.getVersion(), response.getStatus(), response.getReason());
                  } else if (result.isFailed()) {
                     System.out.println("POST request completed: failed");
                     java.lang.Throwable failure =  result.getFailure();
                     if (failure != null) {
                         failure.printStackTrace();
                     }
                  } else {
                     System.out.println("POST request completed: none success/failure");  
                  }
              //} */
              //https://www.eclipse.org/jetty/documentation/current/http-client-api.html#http-client-content
              new BufferingResponseListener(8 * 1024) {
                    @Override
                    public void onComplete(Result result) {
                        System.out.println("POST request completed: success");
                        if (!result.isFailed()) {
                            byte[] content = getContent();
                            System.out.println("  Content:"+new String(content, StandardCharsets.UTF_8));
                        }
                    }
          });
    }
}
```

