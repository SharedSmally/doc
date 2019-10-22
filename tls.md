## TLS connection
![TLS Connection](https://ldapwiki.com/attach/How%20SSL-TLS%20Works/tls-handshake.png)
- Client sends ClientHello to Server, with TLS version, RNc, list of Cipher suites
- Server sends ServerHello to Client, with TLS version, RNg, list of Cipher suites
- Server sends Public-key certificate (server.cert) to client
- Client autherticate the server's CA based on its trusted CAs
- *Client sends Public-key certificate (client.cert) to client
- *Server autherticate the client's CA based on its trusted CAs
- Key/Cipher Exchanges
- Exchange encrypted data

