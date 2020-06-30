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
- H2_PRIOR_KNOWLEDGE: Cleartext HTTP/2 with no upgrade round trip. Cannot be with other protocol.
- HTTP_1_0: An obsolete plaintext framing that does not use persistent sockets by default.
- HTTP_1_1: A plaintext framing that includes persistent connections.
- HTTP_2: The IETF's binary-framed protocol that includes header compression, multiplexing multiple requests on the same socket, and server-push.
- QUIC: QUIC (Quick UDP Internet Connection) is a new multiplexed and secure transport atop UDP, designed from the ground up and optimized for HTTP/2 semantics.

protocols must contain h2_prior_knowledge(only itself) or http/1.1.
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

### For http/2
Needs to use [ALPN](https://www.eclipse.org/jetty/documentation/current/alpn-chapter.html) for application Negotiation before JDK 8.0. 
ALPN includes 3 components:
- boot: for boot JVM
- client: for client application
- server: for server application

Browsers only support HTTP/2 over TLS by negotiating the HTTP/2 protocol via ALPN. You need to configure the server to support TLS and ALPN if you want browsers to use the HTTP/2 protocol, otherwise they will default to HTTP/1.1.

```
GetExample.java

import java.io.IOException;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class GetExample {
  OkHttpClient client = new OkHttpClient();

  String run(String url) throws IOException {
    Request request = new Request.Builder()
        .url(url)
        .build();

    try (Response response = client.newCall(request).execute()) {
      return response.body().string()+"; protocol="+response.protocol();
    }
  }

  public static void main(String[] args) throws IOException {
    GetExample example = new GetExample();
    String response = example.run("https://www.cloudflare.com/");
    String response = example.run("https://www.google.com/"); //protocol=h2
    String response = example.run("http://www.google.com/");  //protocol=http/1.1
    System.out.println(response);
  }
}
```
Run command:
```
javac GetExample.java
java -cp ./:${CLASSPATH} -Xbootclasspath/p:./lib/alpn-boot-8.1.13.v20181017.jar:./lib/jetty-alpn-client-9.4.30.v20200611.jar GetExample

protocol=h2

Without alpn-boot and alpn-client, always go to http/1.1.
```
GetExampleH2.java
```
import java.io.IOException;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

import okhttp3.ConnectionSpec;
import okhttp3.Protocol;
import java.util.Arrays;

public class GetExampleH2 {
  OkHttpClient client = new OkHttpClient.Builder()
          //.connectionSpecs(Arrays.asList(ConnectionSpec.CLEARTEXT)) //fails if only CLEARTEXT
          //.protocols(Arrays.asList(Protocol.H2_PRIOR_KNOWLEDGE))
          .protocols(Arrays.asList(Protocol.HTTP_2, Protocol.HTTP_1_1))
          .connectionSpecs(Arrays.asList(ConnectionSpec.CLEARTEXT, ConnectionSpec.MODERN_TLS, ConnectionSpec.COMPATIBLE_TLS))
          .build();

  String run(String url) throws IOException {
    Request request = new Request.Builder()
        .url(url)
        .build();

    try (Response response = client.newCall(request).execute()) {
      return response.body().string()+"; protocol="+response.protocol();
    }
  }

  public static void main(String[] args) throws IOException {
    GetExampleH2 example = new GetExampleH2();
    String response = example.run("https://www.google.com/");
    //String response = example.run("http://www.google.com/");
    System.out.println(response);
  }
}
```

- https: 
    - with ALPN; protocol=h2
    - without ALPN; protocol=http/1.0
- http: 
    - with/without ALPN; protocol=http/1.0
    
For H2_PRIOR_KNOWLEDGE without setting ConnectionSpecs, Network is unreachable to http://www.google.com/. It uses http/2 requests for http://website with returning protocol=h2_prior_knowledge. 


### Protocols
- h2 protocol/encrypted mode: HTTP/2 uses Transport Layer Security (TLS) [TLS12]. It is used in the TLS application-layer protocol negotiation (ALPN) extension [TLS-ALPN] field and in any place where HTTP/2 over TLS is identified. The "h2" string is serialized into an ALPN protocol identifier as the two-octet sequence: 0x68, 0x32.
- h2c protocol/unencrypted variant: HTTP/2 is run over cleartext TCP. This identifier is used in the HTTP/1.1 Upgrade header field and in any place where HTTP/2 over TCP is identified. The "h2c" string is reserved from the ALPN identifier space but describes a protocol that does not use TLS. It either requires a HTTP upgrade or to have prior knowledge about HTTP/2. HTTP/2 can be negotiated over unencrypted channels (known as h2c) using Upgrade header.

HTTP/2 can be negotiated over unencrypted channels (known as h2c) but it's more complicated as how does the client know whether the server will understand the relatively new HTTP/2 protocol? Additionally proxy servers often have problems handling new protocols like this when sent unencrypted but handle them fine when sent encrypted (because they cannot see its using a new protocol in this case).

For encrypted connections, HTTP/2 (known as h2 when encrypted) is negotiated as part of HTTPS negotiation using the ALPN extension (or the older NPN extension it has replaced) before the first HTTP request is sent.

For unencrypted connections, where there is no HTTPS negotiation, there are two options:
- Assume the server speaks HTTP/2 and just start talking HTTP/2 immediately. This is a bit presumptious but in theory would work if you fell back to HTTP/1 if that failed. In many ways it's similar to the discussion on making HTTPS default and falling back to HTTP - it needs critical mass to make this worthwhile.

- Send the initial request as a HTTP/1 request and with an upgrade: h2c HTTP Header (and a base 64 HTTP/2 settings frame as another HTTP header). This asks the server if we can switch to HTTP/2 for the next request. The server should send the HTTP/1 response with a similar upgrade header at which point the next request can be sent as a HTTP/2 request. This process is detailed in the HTTP/2 spec in section 3.2.

So the cases could be:
- h1_1: h1_1 only
- h2: h2 for TLS and h2_prior knowledge for non-tls (http/2 directly)
- h2c: h2 for TLS (version negiotiation) and h2c for non-tls (via h2c upgrade: first http/1.1 with header: Upgrade: h2c, then continues with http/2.0





