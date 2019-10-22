## [TLS connection](https://ldapwiki.com/wiki/How%20SSL-TLS%20Works)
![TLS Connection](https://www.acunetix.com/wp-content/uploads/2017/01/image34.png)
- Client sends ClientHello to Server, with TLS version, RNc, list of Cipher suites
- Server sends ServerHello to Client, with TLS version, RNg, list of Cipher suites
- Server sends Public-key certificate (server.cert) to client
- Client autherticate the server's CA based on its trusted CAs
- *Client sends Public-key certificate (client.cert) to client
- *Server autherticate the client's CA based on its trusted CAs
- Key/Cipher Exchanges
- Exchange encrypted data

## Verify a certificate chain:
The cerficate chain:
'''
Root Certificate - Intermediate Certificate - User Certificate
'''
Root Cert is a self signed certificate, Intermediate Certificate is signed by Root and User by Intermediate.

To verify the entire chain in a single command:
```
openssl verify -CAfile RootCert.pem -untrusted Intermediate.pem UserCert.pem
```

## Create a certificate:
- List content of a certificate
```
$ openssl x509 -in acs.qacafe.com.pem -text
$ openssl x509 -in MYCERT.der -inform der -text  # for DER
```
- Generate a new private key and Certificate Signing Request
```
openssl req -out CSR.csr -new -newkey rsa:2048 -nodes -keyout privateKey.key
```
- Generate a self-signed certificate
```
openssl req -x509 -sha256 -nodes -days 365 -newkey rsa:2048 -keyout privateKey.key -out certificate.crt
```
- Generate a certificate signing request (CSR) for an existing private key
```
openssl req -out CSR.csr -key privateKey.key -new
```
- Generate a certificate signing request based on an existing certificate
```
openssl x509 -x509toreq -in certificate.crt -out CSR.csr -signkey privateKey.key
```
- Remove a passphrase from a private key
```
openssl rsa -in privateKey.pem -out newPrivateKey.pem
```
- Check a Certificate Signing Request (CSR)
```
openssl req -text -noout -verify -in CSR.csr
```
- Check a private key
```
openssl rsa -in privateKey.key -check
```
 - Check a certificate
 ```
openssl x509 -in certificate.crt -text -noout
```
- Check a PKCS#12 file (.pfx or .p12)
```
openssl pkcs12 -info -in keyStore.p12
```

 
