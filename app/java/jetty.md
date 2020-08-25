# Embedded Jetty 
- [jetty document](https://www.eclipse.org/jetty/documentation/current/index.html)
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
## Handlers

## Connectors

## WebSocket


