# [HTTP/2](https://en.wikipedia.org/wiki/HTTP/2) using jetty

## Http/2 Server:

[Protocols](https://http2.github.io/http2-spec/) using ServerConnector:
- h2: http/2: SSL, (ssl, alpn, h2) {0.0.0.0:8443} [jetty-alpn-server-${jetty.version}.jar;jetty-alpn-client-${jetty.version}.jar]
h2 identifies the protocol where HTTP/2 uses Transport Layer Security (TLS). 
It is used in the TLS application-layer protocol negotiation (ALPN) extension
field and in any place where HTTP/2 over TLS is identified.

- h2c: http2c: HTTP/1.1, (http/1.1, h2c) {0.0.0.0:8080}  
h2c identifies the protocol where HTTP/2 is run over cleartext TCP. It is used in 
the HTTP/1.1 Upgrade header field and in any place where HTTP/2 over TCP is identified.

Uses the HTTP Upgrade mechanism for http request Without prior knowledge about support for HTTP/2.

Request for http/2 upgrade:
```
GET / HTTP/1.1
Host: server.example.com
Connection: Upgrade, HTTP2-Settings
Upgrade: h2c
HTTP2-Settings: <base64url encoding of HTTP/2 SETTINGS payload>
```

Response not supporting Http/2
```
HTTP/1.1 200 OK
Content-Length: 243
Content-Type: text/html
...
```

Response supporting Http/2
```
HTTP/1.1 101 Switching Protocols
Connection: Upgrade
Upgrade: h2c

[ HTTP/2 connection ...
```

```
org.eclipse.jetty.server.ServerConnector
org.eclipse.jetty.server.ConnectionFactory:
   org.eclipse.jetty.server.SslConnectionFactory
   org.eclipse.jetty.alpn.server.ALPNServerConnectionFactory
   org.eclipse.jetty.http2.server.HTTP2ServerConnectionFactory
   
-Xbootclasspath/p:
   ${settings.localRepository}/org/mortbay/jetty/alpn/alpn-boot/8.1.11.v20170118/alpn-boot-8.1.11.v20170118.jar
```

### Start jetty Http/2 server
```
$ java -jar $JETTY_HOME/start.jar --add-to-startd=http2,http2c
```

HTTP/2 Configuration

| Properties |	Configuration File | Description |
| ----------- | ----------- | ----------- |
| start.d 	| $JETTY_HOME/etc 	| |
| ssl.ini |	jetty-ssl.xml |	Connector configuration (eg port) common to HTTPS and HTTP/2|
| ssl.ini |	jetty-ssl-context.xml |	Keystore  configuration common to HTTPS and HTTP/2 |
| https.ini |	jetty-https.xml |	HTTPS Protocol configuraton |
| http2.ini |	jetty-http2.xml |	HTTP/2 Protocol configuration |


## Http/2 Client

## WebSocket (Server Push)
