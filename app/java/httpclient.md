# HttpClients
- [Http2 understanding](https://dzone.com/articles/understanding-http2)

- The [HTTP Client](https://openjdk.java.net/groups/net/httpclient/intro.html) was added in Java 11. It can be used to request HTTP resources over the network. 
It supports HTTP/1.1 and HTTP/2. See [tutorial](https://blog.codefx.org/java/http-2-api-tutorial/) and [client-api](https://dzone.com/articles/http2-server-push-via-http-client-api) for 3 components: HttpClient; HttpRequest; HttpResponse.

JDK 11 comes up with the HTTP Client API as a reinvention of HttpUrlConnection(only for Http/1.1). The HTTP Client API is easy to use and supports HTTP/2 (default) and HTTP/1.1. For backward compatibility, the HTTP Client API will automatically downgrade from HTTP/2 to HTTP 1.1 when the server doesn't support HTTP/2.

- [Jetty client](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/http2/client/HTTP2Client.html) supports the HTTP/2 protocol for both client and server implementations
- [Netty client](https://netty.io/)

- [Apache HttpComponents](https://hc.apache.org/news.html): Core; Client; AsyncClient
- [OkHttp3](https://square.github.io/okhttp/): OkHttp depends on Okio for high-performance I/O and the Kotlin standard library. An HTTP+HTTP/2 client for Android and Java applications.







