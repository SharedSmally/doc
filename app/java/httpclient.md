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
    
For H2_PRIOR_KNOWLEDGE, Network is unreachable to http://www.google.com/.





