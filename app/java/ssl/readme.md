# Java SSL configurations
- CA: public key, DNAME and Certificate fingerprints that are signed by Issuer's private key
- Key store:  private key and self-signed ca
- Trust store: trusted certificates

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
- Generate Keystore

- Generate Certificate Request

- Import certificate into truststore

## openssl
