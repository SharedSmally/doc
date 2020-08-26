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
void handle(java.lang.String target, Request baseRequest, javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws java.io.IOException, javax.servlet.ServletException
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


## Connectors

## WebSocket


