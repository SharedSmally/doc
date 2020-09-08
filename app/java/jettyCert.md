# Jetty Certificates

When the server certificate is having Subject Alternative Names (SAN), the requesting home name must match with one of the SANs.
If the server’s SSL certificate does not have SANs, then the requesting home name must match with the Common Name (CN) of
the certificate.

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

## makefile:
```
make: server client

server:
	keytool -genkey -alias server -keystore server.jks \
	-keyalg RSA -keysize 2048 \
	-validity 10000 -dname "CN=localhost, OU=test, O=jpw, L=Annapolis, ST=MD, C=US" \
	-keypass pass_key_server -storepass pass_keystore_server 
	keytool -export -alias server -storepass pass_keystore_server -keystore server.jks -file server.cer 
	keytool -import -file ./server.cer -alias server -storepass pass_turststore_server -keystore client_truststore.jks -noprompt
	
client:
	keytool -genkey -alias client -keystore client.jks \
	-keyalg RSA -keysize 2048  \
	-validity 10000 -dname "CN=localhost, OU=test, O=jpw, L=Annapolis, ST=MD, C=US" \
	-keypass pass_key_client -storepass pass_keystore_client  
	keytool -export -alias client -storepass pass_keystore_client -keystore client.jks -file client.cer 
	keytool -import -file ./client.cer -alias client -storepass pass_keystore_client -keystore server_truststore.jks -noprompt

p12:
	keytool -importkeystore \
	        -srcalias  client -srcstoretype  jks    -srckeystore ./client.jks  \
	        -srckeypass pass_key_client -srcstorepass pass_keystore_client   \
	        -destalias client -deststoretype pkcs12 -destkeystore ./client.p12 \
	        -destkeypass pass_key_client -deststorepass pass_key_client -noprompt
#for pkcs12, keypass should be the same as storepass

p12_ext:
	openssl pkcs12 -in client.p12 -nokeys -out client.crt -passin pass:pass_key_client -password pass:pass_key_client
	openssl pkcs12 -in client.p12 -nocerts -nodes -out client.key
	openssl pkcs12 -in client.p12 -out client.pem

# Different store and key passwords not supported for PKCS12 KeyStores
#-genkey is old now rather use -genkeypair althought both works equally.

print:
	#keytool -list -keystore client.jks -storepass pass_keystore_client
	keytool -list -storetype pkcs12 -keystore client.p12 -storepass pass_key_client
	#openssl pkcs12 -info -in client.p12 -noout 
	 
copy:
	cp *.jks ../src/main/resources/
	
clean:
	${RM} *.jks *.cer *.p12

test:
	curl -v -k https://localhost:9998 --cert ./client.crt --key ./client.key
	curl -v -k --cert-type P12 --cert ./client.p12 https://localhost:9998
	
	#Pcert-type: PEM, DER, ENG and P12
```
