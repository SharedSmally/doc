# [HTTP/2](https://en.wikipedia.org/wiki/HTTP/2) using jetty

## Http/2 Server:

[Protocols](https://http2.github.io/http2-spec/) using ServerConnector:
- h2: http/2: SSL, (ssl, alpn, h2) {0.0.0.0:8443}

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

## Http/2 Client

## WebSocket (Server Push)
