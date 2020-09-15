# jetty
- [Jetty](https://www.eclipse.org/jetty/)
- [Document](https://www.eclipse.org/jetty/documentation/current/)
- [Java Doc](https://www.eclipse.org/jetty/javadoc/current/)
- [Official cookbook](https://github.com/jetty-project/embedded-jetty-cookbook)

## jetty Server
The basic class is [Server](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/server/Server.html). 
It aggregates [Connectors](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/server/Connector.html) (HTTP request receivers) and request Handlers. 

### [ServerConnector](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/server/ServerConnector.html)
subclass of Connector for the Jetty server over TCP/IP. By the use of various ConnectionFactory instances it is 
able to accept connections for HTTP, HTTP/2 and WebSocket, either directly or over SSL.
```
java.lang.Object
   org.eclipse.jetty.util.component.AbstractLifeCycle
      org.eclipse.jetty.util.component.ContainerLifeCycle
         org.eclipse.jetty.server.handler.AbstractHandler
            org.eclipse.jetty.server.handler.AbstractHandlerContainer
               org.eclipse.jetty.server.handler.HandlerWrapper
                  org.eclipse.jetty.server.Server

ServerConnector(Server server)
ServerConnector(Server server, ConnectionFactory... factories)	
ServerConnector(Server server, SslContextFactory sslContextFactory)	
ServerConnector(Server server, SslContextFactory sslContextFactory, ConnectionFactory... factories)

void	addConnector(Connector connector)/removeConnector(Connector connector)

Methods inherited from class org.eclipse.jetty.server.handler.HandlerWrapper
   destroy, expandChildren, getHandler, getHandlers, handle, insertHandler, setHandler
public void setHandler(Handler handler)
```

### [ConnectionFactory](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/server/ConnectionFactory.html)
A Connection factory is responsible for instantiating and configuring a Connection instance to handle an EndPoint accepted by a Connector.
- http

Creates an HTTP connection that can handle multiple versions of HTTP from 0.9 to 1.1
- h2

Creates an HTTP/2 connection that handles the HTTP/2 protocol
- SSL-XYZ

Create an SSL connection chained to a connection obtained from a connection factory with a protocol "XYZ".
- SSL-http

Create an SSL connection chained to an HTTP connection (aka https)
- SSL-ALPN

Create an SSL connection chained to a ALPN connection, that uses a negotiation with the client to determine the next protocol.

All Known Implementing Classes:
- AbstractConnectionFactory, AbstractHTTP2ServerConnectionFactory, ALPNServerConnectionFactory, DetectorConnectionFactory, 
HTTP2CServerConnectionFactory, HTTP2ServerConnectionFactory, HttpConnectionFactory, NegotiatingServerConnectionFactory, 
OptionalSslConnectionFactory, ProxyConnectionFactory, RawHTTP2ServerConnectionFactory, ServerFCGIConnectionFactory, SslConnectionFactory

### [Handler](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/server/Handler.html)
Handle incoming HTTP requests:
- Completely generate the HTTP Response
- Examine/modify the request and call another Handler: [HandlerWrapper](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/server/handler/HandlerWrapper.html)
- Pass the request to one or more other Handlers:[HandlerCollection](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/server/handler/HandlerCollection.html)
```
Server	getServer()	 
void	setServer(Server server)
void	handle(java.lang.String target, Request baseRequest, javax.servlet.http.HttpServletRequest request,
             javax.servlet.http.HttpServletResponse response)	
```

## jetty WebSocket

## jetty Client

