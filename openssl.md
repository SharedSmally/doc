## OpenSSL
- private key
- certificate: public key with the subject information and the signature. The signature is the hash(encrypt(information) using issuer's private key)
- [ openssl tool](https://www.digitalocean.com/community/tutorials/openssl-essentials-working-with-ssl-certificates-private-keys-and-csrs)
- [Openssl CA](https://jamielinux.com/docs/openssl-certificate-authority/create-the-root-pair.html)

### Private Key
- Create a Private Key: a password-protected, 2048-bit private key (domain.key):
```
openssl genrsa -des3 -out domain.key 2048
```
- Verify a Private Key
```
openssl rsa -check -in domain.key
```
- Verify a Private Key Matches a Certificate and CSR: verify a private key (domain.key) matches a certificate (domain.crt) and CSR (domain.csr):
```
openssl rsa -noout -modulus -in domain.key | openssl md5
openssl x509 -noout -modulus -in domain.crt | openssl md5
openssl req -noout -modulus -in domain.csr | openssl md5
```

- Encrypt a Private Key: unencrypted private key (unencrypted.key) and outputs an encrypted version of it (encrypted.key):
```
openssl rsa -des3 \
       -in unencrypted.key \
       -out encrypted.key
```

- Decrypt a Private Key: takes an encrypted private key (encrypted.key) and outputs a decrypted version of it (decrypted.key):
```
openssl rsa \
       -in encrypted.key \
       -out decrypted.key
```

### Certificate Signing Request (CSR)

-  Generate a CSR and the corresponding new private key: -newkey option to generate key
```    
openssl req \
     -newkey rsa:2048 -nodes \   #generate private key for specific key type and size
     -keyout domain.key      \
     -out domain.csr \
     -subj "/C=country name/ST=state name/L=city name(location)/O=organizatoin name/OU=organizatoin unit/CN=common name"   
```

-  Generate a CSR from an Existing Private Key
```
openssl req \
        -key domain.key \  #existing private key
        -new -out domain.csr  \
        -subj "/C=country name/ST=state name/L=city name(location)/O=organizatoin name/OU=organizatoin unit/CN=common name"   
```

-  Generate a CSR from an Existing Certificate and Private Key
```
openssl x509 \
       -in domain.crt \         #existing cert
       -signkey domain.key \    #existing key
       -x509toreq -out domain.csr
```

### Certificate
- Generate a self-signed certificate: issuer=subject: -x509 option tells req to create a self-signed cerificate.
```
openssl req -x509  \
       [-config openssl.cnf]   \   #config
       -newkey rsa:2048 -nodes \
       -keyout domain.key \
       -out domain.crt    \
       -days 365    \
       -subj "/C=country name/ST=state name/L=city name(location)/O=organizatoin name/OU=organizatoin unit/CN=common name"   
```

- Generate a Self-Signed Certificate from an Existing Private Key
```
openssl req \
       -key domain.key \
       -new -x509      \
       -days 365 \
       -out domain.crt
```

- Generate a Self-Signed Certificate from an Existing Private Key and CSR:
```
openssl x509 \
       -signkey domain.key \   #existing private key
       -in domain.csr      \   #existing CSR   
       -req -days 365      \
       -out domain.crt      #
```

### View Certificate
- View CSR Entries:
```
openssl req -text -noout -verify -in domain.csr
```

- View Certificate Entries
```
openssl x509 -text -noout -in domain.crt
```

- Verify a Certificate was Signed by a CA: verify a certificate (domain.crt) signed by a specific CA certificate (ca.crt):
```
openssl verify -verbose -CAFile ca.crt domain.crt
```

### Convert Certificate Formats: PEM can have multiple entries, DER only has one entry
- Convert PEM(base64 text; domain.crt) to DER(binary; domain.der):
```
openssl x509 \
       -in domain.crt \
       -outform der -out domain.der
```
- Convert DER to PEM
```
openssl x509 \
       -inform der -in domain.der \
       -out domain.crt
```
- Convert PEM to PKCS7 (text with multiple entries; also used for java keystore): add PEM certificates (domain.crt and ca-chain.crt) to a PKCS7 file (domain.p7b):
```
openssl crl2pkcs7 -nocrl \
       -certfile domain.crt \
       -certfile ca-chain.crt \
       -out domain.p7b
```
- Convert PKCS7 to PEM
```
openssl pkcs7 \
       -in domain.p7b \
       -print_certs -out domain.crt
```
- Convert PEM to PKCS12: take a private key (domain.key) and a certificate (domain.crt), and combine them into a PKCS12 file (domain.pfx)
```
openssl pkcs12 \
       -inkey domain.key \
       -in domain.crt \
       -export -out domain.pfx
```
- Convert PKCS12 to PEM
```
openssl pkcs12 \
       -in domain.pfx \
       -nodes -out domain.combined.crt
```

## Java Keystore & TrustStore 
- KeyStore: includes private keys and its related certificates refer by its alias name. Used by a SSL server to store private keys and certificate (itself certificate) sent to the SSL client
 and truststore is used by third party client to store public keys provided by server to access
- TrustedStore: containes certificates. Used by the SSL client as the trusted ones to compare with those from SSL server
- Both are handled by javatools

### KeyStore
- Generate keystore 
- Generate CSR
- Import Certificate: alias is the name of the private key. If the private key not exist, imported as the trusted certificate

### TrustStore
- Import Signed Certificates

## Generating a Certificate Authority (CA) Certificate for Self-Signing
### Create the root CA certificate:
```
openssl genrsa -des3 -out CA-key.pem 2048  # Generate a CA private key: CA-key.pem
openssl req -new -key CA-key.pem -x509 -days 1000 -out CA-cert.pem   #Generate the root CA certificate: CA-cert.pem
```
### Create a Signing Certificate using root key and certificate
```
openssl genrsa -des3 -out server-key.pem 2048  #Generate a new key
copy the openssl.cnf and modify some of the configuration settings
openssl req –new –config openssl.cnf –key server-key.pem –out signingReq.csr #Generate a certificate signing request
openssl x509 -req -days 365 -in signingReq.csr -CA CA-cert.pem -CAkey CA-key.pem -CAcreateserial -out server-cert.pem  #Self-sign the certificate using CA-cert.pem certificate and CA-key.pem private key
```

