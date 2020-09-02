# Jetty Certificates
- [Generate CA, Server, Client certificates](https://gist.github.com/jankronquist/6412839) 
- [Enable mutual authentication in Jetty server](https://imlc.me/how-to-enable-mutual-authentication-in-jetty-server)
- [Add Certificate in jetty](https://stackoverflow.com/questions/20056304/in-the-jetty-server-how-can-i-obtain-the-client-certificate-used-when-client-aut)

##  Generate Certificates
In src/main/resources:

- Generate server keystore(used by server), and export its certificate into truststore (used by client).
```
keytool -genkey -alias server -keyalg RSA -keypass changeit -storepass changeit -keystore server.jks

keytool -export -alias server -storepass changeit -keystore server.jks -file server.cer 
keytool -import -file ./server.cer -alias server -keystore client_truststore.jks
```

- Generate client keystore(used by client), and export its certificate into truststore (used by server)
```
keytool -genkey -alias client -keyalg RSA -keypass changeit -storepass changeit -keystore client.jks

keytool -export -alias client -storepass changeit -keystore client.jks -file client.cer 
keytool -import -file ./client.cer -alias client -keystore server_truststore.jks
```

- Convert between different formats
```
keytool -importkeystore -srckeystore client.jks -destkeystore client.p12 -srcalias client -srcstoretype jks -deststoretype pkcs12
openssl pkcs12 -in client.p12 -nokeys -out client.crt
openssl pkcs12 -in client.p12 -nocerts -nodes -out client.key
```

##  Config jetty server
Set the KeyStore and KeyStore password, and the TrustStore and TrustStore password via SslContextFactory:
```
SslContextFactory.Server sslContextFactory = new SslContextFactory.Server();
sslContextFactory.setKeyStorePath(this.getClass().getResource("/server.jks").toExternalForm());
sslContextFactory.setKeyStorePassword("changeit");

sslContextFactory.setTrustStorePath(this.getClass().getResource("/server_truststore.jks").toExternalForm());
sslContextFactory.setTrustStorePassword("changeit");
sslContextFactory.setNeedClientAuth(true);
```

## Config jetty client
```
        SslContextFactory sslContextFactory = new SslContextFactory.Client();
        sslContextFactory.setKeyStorePath(this.getClass().getResource("/client.jks").toExternalForm());
        sslContextFactory.setKeyStorePassword("changeit");
        
        sslContextFactory.setTrustAll(true);
        
        sslContextFactory.setTrustStorePath(this.getClass().getResource("/client_truststore.jks").toExternalForm());
        sslContextFactory.setTrustStorePassword("changeit");
        
        HttpClient httpClient = new HttpClient(sslContextFactory);      
        httpClient.start();
        
        ContentResponse response = httpClient.newRequest("https://localhost:8443").send();       
        httpClient.stop();
```

## Verify using curl
- Convert KeyStore to pkcs12 format
```
keytool -importkeystore -srckeystore client.jks -destkeystore client.p12 -srcalias client -srcstoretype jks -deststoretype pkcs12
```
- Convert private key and certificate in PEM format
```
openssl pkcs12 -in client.p12 -nokeys -out client.crt
openssl pkcs12 -in client.p12 -nocerts -nodes -out client.key
```
- Test
```
curl -v -k https://localhost:8443 --cert ./client.crt --key ./client.key
curl -v -k --cert-type P12 --cert ./client.p12 https://localhost:8443
```

