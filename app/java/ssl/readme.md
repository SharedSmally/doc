# Java SSL configurations
- [Certificate](https://en.wikipedia.org/wiki/X.509): public key, DNAME and Certificate fingerprints that are signed by Issuer's private key
- Key store:  private key and self-signed ca
- Trust store: trusted certificates

## Certificate filenames extensions
- .pem – (Privacy-enhanced Electronic Mail) Base64 encoded DER certificate, enclosed between "-----BEGIN CERTIFICATE-----" and "-----END CERTIFICATE-----"
- .cer, .crt, .der – usually in binary DER form, but Base64-encoded certificates are common too
- .p7b, .p7c – PKCS#7 SignedData structure without data, just certificate(s) or CRL(s)
- .p12 – PKCS#12, may contain certificate(s) (public) and private keys (password protected)
- .pfx – PFX, predecessor of PKCS#12 (usually contains data in PKCS#12 format, e.g., with PFX files generated in IIS)

## Distinguished Name (DNAME)
- CN: Common Name (the fully qualified domain name such as www.xxx.com, including * for subdomain)
- OU: Organizational Unit (division or department of company)
- O:  Organization (legal company name)
- ST: State (such as New York, California, or CA)
- L:  Locality/City
- C:  Country (2 character country code such as US)

## keytool
```
Key and Certificate Management Tool. Commands:
 -genkeypair         Generates a key pair
 -genseckey          Generates a secret key
 -gencert            Generates certificate from a certificate request
 -certreq            Generates a certificate request

 -exportcert         Exports certificate
 -importcert         Imports a certificate or a certificate chain
 -importkeystore     Imports one or all entries from another keystore
 
 -changealias        Changes an entry's alias
 -delete             Deletes an entry
 
 -importpass         Imports a password
 -keypasswd          Changes the key password of an entry
 -storepasswd        Changes the store password of a keystore
 
 -list               Lists entries in a keystore
 -printcert          Prints the content of a certificate
 -printcertreq       Prints the content of a certificate request
 -printcrl           Prints the content of a CRL file
```
- Generate a Keystore and key pair
```
keytool -genkey -keyalg RSA -alias mydomain -keystore keystore.jks -keysize 2048 -keypasswd  keypass  -storepasswd storepass
```    
- Generate a keystore and self-signed certificate 
```
keytool -genkey -keyalg RSA -alias selfsigned -keystore keystore.jks -keysize 2048 -keypasswd  keypass -storepass password -validity 360 -dname DN
```
- Generate a certificate signing request (CSR) from an existing Java keystore
```
keytool -certreq -alias mydomain -keystore keystore.jks -file mydomain.csr
```
- Import a root or intermediate CA certificate to an existing Java keystore
```
keytool -import -trustcacerts -alias root -file Thawte.crt -keystore keystore.jks
```
- Import a signed primary certificate to an existing Java keystore
```
keytool -import -trustcacerts -alias mydomain -file mydomain.crt -keystore keystore.jks
```
- Transform jks key store to PKCS12 format
```
	keytool -importkeystore \
	   -srckeystore server.jks -destkeystore server.p12 \
	   -srcstoretype jks -deststoretype pkcs12 \
	   -srcstorepass pass_keystore_server  -deststorepass pass_keystore_server \
	   -srcalias server -destalias server \
	   -srckeypass pass_key_server -destkeypass pass_keystore_server \
	   -noprompt
```
- Check CA
```
keytool -printcert -v -file mydomain.crt  # check CA
keytool -list -v -keystore keystore.jks   # check CA in keystore
keytool -list -v -keystore keystore.jks -alias mydomain  # check specific CA in keystore
keytool -list -v -keystore cacerts # list trusted CAs from trusted store

keytool -delete -alias mydomain -keystore keystore.jks
keytool -storepasswd -new new_storepass -keystore keystore.jks  #change keystore password
```
- Export/Import CA
```
keytool -export -alias mydomain -file mydomain.crt -keystore keystore.jks  # export CA from a keystore
keytool -import -trustcacerts -file ca.pem -alias CANAME -keystore cacerts # import CA to a Trusted Certs(Store)
```

## openssl
