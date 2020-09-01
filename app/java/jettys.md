# jetty Https

The JSSE makes use of files called KeyStores and TrustStores. The KeyStore is used by the adapter for client authentication, while the TrustStore is used to authenticate a server in SSL authentication.

- A KeyStore consists of a database containing a private key and an associated certificate, or an associated certificate chain. The certificate chain consists of the client certificate and one or more certification authority (CA) certificates.

- A TrustStore contains only the certificates trusted by the client (a “trust” store). These certificates are CA root certificates, that is, self-signed certificates.

## [Secure Password Obfuscation](https://www.eclipse.org/jetty/documentation/current/configuring-security-secure-passwords.html)
Passwords can be stored in clear text, obfuscated, checksummed or encrypted in order of increasing security. The class org.eclipse.jetty.util.security.Password can be used to generate all varieties of passwords.

```
$ java -cp ../lib/jetty-util-9.4.31.v20200723.jar org.eclipse.jetty.util.security.Password username password
2017-12-13 11:19:27.928:INFO::main: Logging initialized @95ms to org.eclipse.jetty.util.log.StdErrLog
password
OBF:1v2j1uum1xtv1zej1zer1xtn1uvk1v1v
MD5:5f4dcc3b5aa765d61d8327deb882cf99
CRYPT:usjRS48E8ZADM

//Using the `-n` option to exclude a new line from being added.
$ echo -n password | md5sum
5f4dcc3b5aa765d61d8327deb882cf99 *-
```

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
$ openssl x509 -inform PEM -in ssl/app.pem -text -out certdata.pem
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
#organizational unit?
UNIT=Jetty
#organization?
ORG=TCS
#City or Locality?
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

main: app.pem app.csr app.p12 appCA.jks


app: app.jks

${NAME}.jks:
        keytool -genkey -keystore ${NAME}.jks -alias ${NAME}  -keyalg RSA -keysize 2048 \
        -validity 10000 -dname "CN=${CN}, OU=${UNIT}, O=${ORG}, L=${CITY}, ST=${STATE}, C=${COUNTRY}" \
        -storepass ${KEYSTORE_PASS} -keypass ${KEY_PASS}

# create trustedstore
%CA.jks:%.pem
        keytool -import -file $< -alias ${NAME} -keystore $@ -storepass ${KEYSTORE_PASS}

%.pem:%.jks
        keytool -exportcert -rfc -alias ${NAME} -storepass ${KEYSTORE_PASS}  -keystore $< -file $@

%.csr:%.jks
        keytool -certreq -alias ${NAME} -storepass ${KEYSTORE_PASS} -keystore $< -file  $@

# convert jks to pkcs12
%.p12:%.jks
        keytool -importkeystore -srckeystore $< -destkeystore $@ -deststoretype pkcs12 \
        -srcstorepass ${KEYSTORE_PASS} -deststorepass ${KEYSTORE_PASS}

passwd:
        $ java -cp ~/.m2/repository/org/eclipse/jetty/jetty-util/9.4.31.v20200723/jetty-util-9.4.31.v20200723.jar \
                org.eclipse.jetty.util.security.Password ${NAME} ${KEY_PASS}
        $ java -cp ~/.m2/repository/org/eclipse/jetty/jetty-util/9.4.31.v20200723/jetty-util-9.4.31.v20200723.jar \
                org.eclipse.jetty.util.security.Password ${NAME} ${KEYSTORE_PASS}

print:
        keytool -list -storepass ${KEYSTORE_PASS} -keystore ${NAME}.jks
        keytool -list -storepass ${KEYSTORE_PASS} -keystore ${NAME}CA.jks

printp12:
        keytool -list -storepass ${KEYSTORE_PASS} -keystore ${NAME}.p12

printcert:
        keytool -printcert -file app.pem
```
