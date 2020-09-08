make: server client ca

server: server.crt server.key
client: client.crt client.key
ca: server_ca.jks client_ca.jks 

# generate server keystroe with private key and self-signed CA 
#-genkey is old now rather use -genkeypair althought both works equally.
server.jks:
	keytool -genkey -alias server -keystore server.jks \
	-keyalg RSA -keysize 2048 \
	-validity 10000 -dname "CN=localhost, OU=test, O=jpw, L=Annapolis, ST=MD, C=US" \
	-keypass pass_key_server -storepass pass_keystore_server 

# convert keystore from jks to pkcs12
server.p12: server.jks 
	keytool -importkeystore \
	        -srcalias  server -srcstoretype  jks    -srckeystore ./server.jks  \
	        -srckeypass pass_key_server -srcstorepass pass_keystore_server   \
	        -destalias server -deststoretype pkcs12 -destkeystore ./server.p12 \
	        -destkeypass pass_p12_server -deststorepass pass_p12_server -noprompt
# Different store and key passwords not supported for PKCS12 KeyStores
# for pkcs12, keypass should be the same as storepass

server.crt: server.p12
	openssl pkcs12 -in server.p12 -nokeys -out server.crt -passin pass:pass_p12_server 

server.key:	
	openssl pkcs12 -in server.p12 -nocerts -nodes -out server.key -passin pass:pass_p12_server

###############################################################################
# CN=localhost works without mutual authen. using 127.0.0.1; hostname
# use -ext san=dns:computerName for SAN(subject alternative names)
client.jks:
	keytool -genkey -alias client -keystore client.jks \
	-keyalg RSA -keysize 2048 \
	-validity 10000 -dname "CN=127.0.0.1, OU=test, O=jpw, L=Annapolis, ST=MD, C=US" \
	-keypass pass_key_client -storepass pass_keystore_client 

# convert keystore from jks to pkcs12
client.p12: client.jks 
	keytool -importkeystore \
	        -srcalias  client -srcstoretype  jks    -srckeystore ./client.jks  \
	        -srckeypass pass_key_client -srcstorepass pass_keystore_client   \
	        -destalias client -deststoretype pkcs12 -destkeystore ./client.p12 \
	        -destkeypass pass_p12_client -deststorepass pass_p12_client -noprompt
# Different store and key passwords not supported for PKCS12 KeyStores
# for pkcs12, keypass should be the same as storepass

client.crt: client.p12
	openssl pkcs12 -in client.p12 -nokeys -out client.crt -passin pass:pass_p12_client 

client.key:
	openssl pkcs12 -in client.p12 -nocerts -nodes -out client.key -passin pass:pass_p12_client

###############################################################################
# import client.crt to server truststore
server_ca.jks:
	keytool -import -alias client -file client.crt -storetype jks \
	-keystore server_ca.jks -storepass pass_turststore_server -noprompt
	
# import server.crt to client truststore
client_ca.jks:
	keytool -import -alias server -file server.crt -storetype jks \
	-keystore client_ca.jks -storepass pass_turststore_client -noprompt
	
###############################################################################
passwd_svr:
	mvn -f ../pom.xml exec:java -Dexec.mainClass="org.eclipse.jetty.util.security.Password" \
	-Dexec.classpathScope=runtime -Dexec.args="wchen pass_keystore_server"
	mvn -f ../pom.xml  exec:java -Dexec.mainClass="org.eclipse.jetty.util.security.Password" \
	-Dexec.classpathScope=runtime -Dexec.args="wchen pass_key_server"
	mvn -f ../pom.xml exec:java -Dexec.mainClass="org.eclipse.jetty.util.security.Password" \
	-Dexec.classpathScope=runtime -Dexec.args="wchen pass_turststore_server"

passwd_client:
	mvn -f ../pom.xml exec:java -Dexec.mainClass="org.eclipse.jetty.util.security.Password" \
	-Dexec.classpathScope=runtime -Dexec.args="wchen pass_keystore_client"
	mvn -f ../pom.xml  exec:java -Dexec.mainClass="org.eclipse.jetty.util.security.Password" \
	-Dexec.classpathScope=runtime -Dexec.args="wchen pass_key_client"
	mvn -f ../pom.xml exec:java -Dexec.mainClass="org.eclipse.jetty.util.security.Password" \
	-Dexec.classpathScope=runtime -Dexec.args="wchen pass_turststore_client"

###############################################################################
print:
	keytool -list -storetype pkcs12 -keystore server.p12 -storepass pass_p12_server
	keytool -list -storetype pkcs12 -keystore client.p12 -storepass pass_p12_client


print_jks:
	keytool -list -v -storetype jks -keystore server.jks -storepass pass_keystore_server
	keytool -list -v -storetype jks -keystore client.jks -storepass pass_keystore_client

print_ca:
	keytool -list -v -storetype jks -keystore server_ca.jks -storepass pass_turststore_server
	keytool -list -v -storetype jks -keystore client_ca.jks -storepass pass_turststore_client
		
copy:
	cp *.jks ../src/main/resources/
	cp *.p12 ../src/main/resources/
	
clean:
	${RM} *.jks *.cer *.p12 *.crt *.key
	${RM} ../src/main/resources/*

test:
	curl -v https://localhost:9998 --cert ./server.crt --key ./client.key

dummy:
	#curl -v -k https://localhost:9998 --cert ./server.crt --key ./client.key
	#curl -k https://localhost:9998 --cert ./server.crt --key ./client.key	
	#Pcert-type: PEM, DER, ENG and P12
	#keytool -list -keystore client.jks -storepass pass_keystore_client
	#openssl pkcs12 -info -in client.p12 -noout
