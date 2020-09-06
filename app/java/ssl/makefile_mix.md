DIR=../src/main/resources/

#https://www.eclipse.org/jetty/documentation/current/configuring-ssl.html
#https://www.sslshopper.com/article-most-common-java-keytool-keystore-commands.html
# keystore/; truststore
main: server client

################################################################################
#*.jks: jks key store
#*.p12: pkcs12 key store

#*.ca.jks: jks trust store
#*.ca.p12: pkcs12 trust store

#*.cer: certificate in CER
#*.der: certificate in DER
#*.pem: certificate in PEM
#*.crt: certificate

################################################################################
#server: keystore; truststore(server root ca, client cert); certificate for client
# CN is DNS for server
server: server_jks server_p12 server_p12 server_ca server_p12ca server_p12key

# generate jks keystore
server_jks:
	keytool -genkey -alias server -keystore server.jks \
	-keyalg RSA -keysize 2048 \
	-validity 10000 -dname "CN=localhost, OU=test, O=jpw, L=Annapolis, ST=MD, C=US" \
	-keypass pass_key_server -storepass pass_keystore_server

# convert jks keystore to pkcs12 keystore
# Different store and key passwords not supported for PKCS12 KeyStores
# -deststorepass and -destkeypass must be the same
server_p12: 
	keytool -importkeystore \
	-srckeystore server.jks -destkeystore server.p12 \
	-srcstoretype jks -deststoretype pkcs12 \
	-srcstorepass pass_keystore_server  -deststorepass pass_keystore_server \
	-srcalias server -destalias server \
	-srckeypass pass_key_server -destkeypass pass_keystore_server \
	-noprompt
	 
# generate server ca and key in pem 
server_ca:
	keytool -export -alias server -storepass pass_keystore_server -storetype jks \
	-keystore server.jks -file server.cer 
	keytool -export -alias server -storepass pass_keystore_server -storetype jks \
	-keystore server.jks -rfc -file server.pem  

# using p12. same as server_ca
server_p12ca:
	keytool -export -alias server -storepass pass_keystore_server -storetype pkcs12 \
	-keystore server.p12 -file server.p12.cer 
	keytool -export -alias server -storepass pass_keystore_server -storetype pkcs12 \
	-keystore server.p12 -rfc -file server.p12.pem 

#export private key and public key from pkcs12 keystore
server_p12key:
	openssl pkcs12 -password pass:pass_keystore_server -nodes -nocerts \
	-in server.p12 -out server.key.pem 
	openssl pkcs12 -password pass:pass_keystore_server -nokeys \
	-in server.p12 -out server.pub.pem 
################################################################################

################################################################################
openssl_server:
	openssl genrsa -aes128 -out jetty.key
	openssl req -new -x509 -newkey rsa:2048 -sha256 -key jetty.key -out jetty.crt
	openssl req -new -key jetty.key -out jetty.csr
	openssl x509 -in jetty.der -inform DER -outform PEM -out jetty.crt
	openssl pkcs12 -inkey jetty.key -in jetty.crt -export -out jetty.pkcs12
################################################################################

################################################################################
#client: keystore; truststore(client root ca, certs from server); certificate for server
client: client_jks client_p12 client_p12 client_ca client_p12ca client_p12key

# CN is DNS for client
# generate jks keystore
client_jks:
	keytool -genkey -alias client -keystore client.jks \
	-keyalg RSA -keysize 2048 \
	-validity 10000 -dname "CN=localhost, OU=test, O=jpw, L=Annapolis, ST=MD, C=US" \
	-keypass pass_key_client -storepass pass_keystore_client

# convert jks keystore to pkcs12 keystore
# Different store and key passwords not supported for PKCS12 KeyStores
# -deststorepass and -destkeypass must be the same
client_p12: 
	keytool -importkeystore \
	-srcstoretype jks -deststoretype pkcs12 \
	-srcstorepass pass_keystore_client  -deststorepass pass_keystore_client \
	-srcalias client -destalias client \
	-srckeypass pass_key_client -destkeypass pass_keystore_client \
	-noprompt \
	-srckeystore client.jks -destkeystore client.p12 \
	 
# generate server ca and key in pem 
client_ca:
	keytool -export -alias client -storepass pass_keystore_client -storetype jks \
	-keystore client.jks -file client.cer 
	keytool -export -alias client -storepass pass_keystore_client -storetype jks \
	-keystore client.jks -rfc -file client.pem  

# using p12. same as client_ca
client_p12ca:
	keytool -export -alias client -storepass pass_keystore_client -storetype pkcs12 \
	-keystore client.p12 -file client.p12.cer 
	keytool -export -alias client -storepass pass_keystore_client -storetype pkcs12 \
	-keystore client.p12 -rfc -file client.p12.pem 

#export private key and public key from pkcs12 keystore
client_p12key:
	openssl pkcs12 -password pass:pass_keystore_client -nodes -nocerts \
	-in client.p12 -out client.key.pem 
	openssl pkcs12 -password pass:pass_keystore_client -nokeys \
	-in client.p12 -out client.pub.pem 
################################################################################

#import client ca to server truststore and server ca to client truststore
#–trustcacerts: import this as a trusted certificate 
truststore cas:
	keytool -importcert -trustcacerts -storetype JKS \
	-storepass pass_keystore_client -noprompt \
	-alias server -file server.pem -keystore client.truststore 

	keytool -importcert -trustcacerts -storetype JKS \
	-storepass pass_keystore_server -noprompt \
	-alias server -file client.pem -keystore server.truststore 

################################################################################

#Generate a certificate signing request (CSR) for an existing Java keystore
server_csr:
	keytool -certreq -keypass pass_key_server -storepass pass_keystore_server \
	-alias server -keystore server.p12 -file server.csr

server_jks_csr:
	keytool -certreq -keypass pass_key_server -storepass pass_keystore_server \
	-alias server -keystore server.jks -file server.csr



copy:
	cp *.jks ../src/main/resources/

print_key:
	#keytool -list -keystore server.jks -storetype jks -storepass pass_keystore_server -v
	keytool -list -keystore server.p12 -storetype pkcs12 -storepass pass_keystore_server -v
	keytool -list -keystore client.p12 -storetype pkcs12 -storepass pass_keystore_client -v

print_cas:
	keytool -list -v -keystore client.truststore -storepass pass_keystore_client
	keytool -list -v -keystore server.truststore -storepass pass_keystore_server

print_crt:
	keytool -printcert -v -file client.crt
	keytool -printcert -v -file client.pem
	
clean:
	${RM} *.jks *.cer *.p12	
