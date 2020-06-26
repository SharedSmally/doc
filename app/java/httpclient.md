# HttpClients
- [Http2 understanding](https://dzone.com/articles/understanding-http2)

- The [HTTP Client](https://openjdk.java.net/groups/net/httpclient/intro.html) was added in Java 11. It can be used to request HTTP resources over the network. 
It supports HTTP/1.1 and HTTP/2. See [tutorial](https://blog.codefx.org/java/http-2-api-tutorial/) and [client-api](https://dzone.com/articles/http2-server-push-via-http-client-api) for 3 components: HttpClient; HttpRequest; HttpResponse.

JDK 11 comes up with the HTTP Client API as a reinvention of HttpUrlConnection(only for Http/1.1). The HTTP Client API is easy to use and supports HTTP/2 (default) and HTTP/1.1. For backward compatibility, the HTTP Client API will automatically downgrade from HTTP/2 to HTTP 1.1 when the server doesn't support HTTP/2.

- [Jetty client](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/http2/client/HTTP2Client.html) supports the HTTP/2 protocol for both client and server implementations
- [Netty client](https://netty.io/)

- [Apache HttpComponents](https://hc.apache.org/news.html): Core; Client; AsyncClient
- [OkHttp](https://square.github.io/okhttp/): OkHttp depends on Okio for high-performance I/O and the Kotlin standard library. An HTTP+HTTP/2 client for Android and Java applications.


## okhttp
### Protocols:
- H2_PRIOR_KNOWLEDGE: Cleartext HTTP/2 with no upgrade round trip.
- HTTP_1_0: An obsolete plaintext framing that does not use persistent sockets by default.
- HTTP_1_1: A plaintext framing that includes persistent connections.
- HTTP_2: The IETF's binary-framed protocol that includes header compression, multiplexing multiple requests on the same socket, and server-push.
- QUIC: QUIC (Quick UDP Internet Connection) is a new multiplexed and secure transport atop UDP, designed from the ground up and optimized for HTTP/2 semantics.

protocols must contain h2_prior_knowledge(cannot with other protocols) or http/1.1.
```
builder.protocols(Arrays.asList(Protocol.H2_PRIOR_KNOWLEDGE));
builder.connectionSpecs(Arrays.asList(ConnectionSpec.MODERN_TLS, ConnectionSpec.COMPATIBLE_TLS));
```

### ConnectionSpec
- CLEARTEXT: Unencrypted, unauthenticated connections for http: URLs. The CLEARTEXT message is due to requesting an http URL, either directly or via a server-side redirect (e.g., starts with https, then redirects to http).
-	COMPATIBLE_TLS: A backwards-compatible fallback configuration that works on obsolete client platforms and can connect to obsolete servers.
- MODERN_TLS: A modern TLS configuration that works on most client platforms and can connect to most servers.
- RESTRICTED_TLS: A secure TLS connection that requires a recent client platform and a recent server.
```
builder.connectionSpecs(Arrays.asList(ConnectionSpec.CLEARTEXT));
builder.protocols(Arrays.asList(Protocol.HTTP_2, Protocol.HTTP_1_1));
```






