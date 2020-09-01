# jetty Https

## keytool

Key and Certificate Management Tool

```
keytool -command_name 
Commands:
 -certreq            Generates a certificate request
 -changealias        Changes an entry's alias
 -delete             Deletes an entry
 -exportcert         Exports certificate
 -genkeypair         Generates a key pair
 -genseckey          Generates a secret key
 -gencert            Generates certificate from a certificate request
 -importcert         Imports a certificate or a certificate chain
 -importpass         Imports a password
 -importkeystore     Imports one or all entries from another keystore
 -keypasswd          Changes the key password of an entry
 -list               Lists entries in a keystore
 -printcert          Prints the content of a certificate
 -printcertreq       Prints the content of a certificate request
 -printcrl           Prints the content of a CRL file
 -storepasswd        Changes the store password of a keystore

```
## [Config SSL/TLS](https://www.eclipse.org/jetty/documentation/current/configuring-ssl.html)
### Generating Key Pairs and Certificates with JDK’s keytool
- Generating Keys and Certificates 
```
$ keytool -genkey -keystore keystore    -alias jetty -keyalg RSA
$ keytool -genkey -keystore app.jks -alias app   -keyalg RSA -keysize 2048 \
        -validity 10000 -dname "CN=jetty.eclipse.org, OU=Jetty, O=TCS, L=Annapolis, ST=MD, C=US" \
        -storepass abcdef12 -keypass abcdef12
```
- Export the generated server certificate into the file:
```
$ keytool -export -alias app -storepass abcdef12  -keystore keystore -file jetty.cer
$ keytool -exportcert -rfc -alias jetty -storepass abcdef12  -keystore keystore -file jetty.pem
```
- Convert to PKCS12
```
$ keytool -importkeystore -srckeystore keystore -destkeystore keystore -deststoretype pkcs12  #migrate to PKCS12
$ openssl x509 -in cert.cer -out cert.pem  # convert CER to PEM
$ openssl x509 -in jetty.der -inform DER -outform PEM -out jetty.crt  #convert DER to PEM
```
- Requesting a Trusted Certificate
```
$ keytool -certreq -alias jetty -keystore keystore -file jetty.csr
```
- Loading Certificates (in PEM)
```
$ keytool -import -keystore keystore -alias jetty -file jetty.crt -trustcacerts
```

### [Generating Key Pairs and Certificates with openssl](https://www.sslshopper.com/article-most-common-openssl-commands.html)
- Generating Keys and Certificates
```
$ openssl genrsa -aes128 -out jetty.key
$ openssl req -new -x509 -newkey rsa:2048 -sha256 -key jetty.key -out jetty.crt
```
- Requesting a Trusted Certificate
```
$ openssl req -new -key jetty.key -out jetty.csr
```

### Configure Jetty SslContextFactory
The SslContextFactory is responsible for:
- Creating the Java SslEngine used by Jetty’s Connectors and Jetty’s Clients (HTTP/1, HTTP/2, and WebSocket).
- Managing Keystore Access
- Managing Truststore Access
- Managing Protocol selection via Excludes / Includes list
- Managing Cipher Suite selection via Excludes / Includes list
- Managing order of Ciphers offered (important for TLS/1.2 and HTTP/2 support)
- SSL Session Caching options
- Certificate Revocation Lists and Distribution Points (CRLDP)
- OCSP Support
- Client Authentication Support

For Jetty Connectors, the configured SslContextFactory.Server is injected into a specific ServerConnector SslConnectionFactory.

For Jetty Clients, the various constructors support using a configured SslContextFactory.Client.

```

```

### sample makefile:
```
NAME=app

#Common Name
CN=jetty.eclipse.org
#organizational unit
UNIT=Jetty
#organization
ORG=TCS
#City or Locality
CITY=Annapolis
#State
STATE=MD
#two-letter country code
COUNTRY=US

# keystore password
KEYSTORE_PASS=abcdef12
# private key password
KEY_PASS=abcdef12
# trusted store password

main: app.pem app.csr app.p12

app: app.jks

${NAME}.jks:
        keytool -genkey -keystore ${NAME}.jks -alias ${NAME}  -keyalg RSA -keysize 2048 \
        -validity 10000 -dname "CN=${CN}, OU=${UNIT}, O=${ORG}, L=${CITY}, ST=${STATE}, C=${COUNTRY}" \
        -storepass ${KEYSTORE_PASS} -keypass ${KEY_PASS}

%.pem:%.jks
        keytool -exportcert -rfc -alias ${NAME} -storepass ${KEYSTORE_PASS}  -keystore $< -file $@

%.csr:%.jks
        keytool -certreq -alias ${NAME} -storepass ${KEYSTORE_PASS} -keystore $< -file  $@

# convert jks to pkcs12
%.p12:%.jks
        keytool -importkeystore -srckeystore $< -destkeystore $@ -deststoretype pkcs12 \
        -srcstorepass ${KEYSTORE_PASS} -deststorepass ${KEYSTORE_PASS}

print:
        keytool -list -storepass ${KEYSTORE_PASS} -keystore ${NAME}.jks

printp12:
        keytool -list -storepass ${KEYSTORE_PASS} -keystore ${NAME}.p12

printcert:
        keytool -printcert -file app.pem

```
