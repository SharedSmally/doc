# jetty

## 
The basic class is [Server](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/server/Server.html). 
It aggregates [Connectors](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/server/Connector.html) (HTTP request receivers) and request Handlers. 

### [ServerConnector](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/server/ServerConnector.html)
subclass of Connector for the Jetty server over TCP/IP. By the use of various ConnectionFactory instances it is 
able to accept connections for HTTP, HTTP/2 and WebSocket, either directly or over SSL.
```
ServerConnector(Server server)
ServerConnector(Server server, ConnectionFactory... factories)	
ServerConnector(Server server, SslContextFactory sslContextFactory)	
ServerConnector(Server server, SslContextFactory sslContextFactory, ConnectionFactory... factories)
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

