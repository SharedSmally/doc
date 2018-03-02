# netty IO:

## Tutorial
- (Timer Server/Client sample) [ http://shengwangi.blogspot.com/2016/03/netty-tutorial-hello-world-example.html]

## SSL Setup
### Server Side Keystore
- Create a Keystore:
```
keytool -keysize 2048 -genkey -alias tomcat -keyalg RSA -keystore tomcat.keystore
```
- Create a Certificate Signing Request (CSR)
```
keytool -certreq -keyalg RSA -alias tomcat -file yourdomain.csr -keystore tomcat.keystore
```
- Create a Certificate (Using 3rd Party or self Certificate)
- Installing the Certificates into your Keystore
   - Install root certificate
```
keytool -import -alias root -keystore tomcat.keystore -trustcacerts –file root.crt
```
   - Install the intermediary certificates:
```
keytool -import -alias intermed -keystore tomcat.keystore -trustcacerts –file intermediate.crt
```
   - Install the certificate for the server:
```
keytool -import -alias tomcat -keystore tomcat.keystore -trustcacerts –file yourdomain.com
```
   - Check all Installed Certificates
```
keytool –list –keystore tomcat.keystore
```
### netty ssl
- Create server/client side SslContext:
- Use SslContext to create SslEngine
- Use SslEngine to create SslHandler
- For netty, use SslContextBuilder to build SslContext, and use SslContext to create SslHandler directly

      - SslContextBuilder:
      
```
static SslContextBuilder forClient()
static SslContextBuilder forServer(File keyCertChainFile, File keyFile) ...
SslContextBuilder setXXX(xxx)
SslContext	build()
```

      - SslContext:
      
```
abstract javax.net.ssl.SSLEngine	newEngine(ByteBufAllocator alloc)
abstract javax.net.ssl.SSLEngine	newEngine(ByteBufAllocator alloc, java.lang.String peerHost, int peerPort)
SslHandler	newHandler(ByteBufAllocator alloc)
SslHandler	newHandler(ByteBufAllocator alloc, java.lang.String peerHost, int peerPort)
```

### Server Side 
-  Convert your keystore into a String using Base64Coder and the OneUtils.
```
final File original = new File(pathtoyourkeystore);
System.out.println(Base64Coder.encode(OneUtilsJre.toByteArray(new FileInputStream(original))));
```
- Copy the String and place it into a static variable, for instance:
```
class MyKeystore {
    public static data = "[generated base 64 data]";
}
```
 - Create an SSLContext from the data of your keystore.
```
SSLContext serverContext = SSLContext.getInstance("TLS");
 
final KeyStore ks = KeyStore.getInstance("JKS");
 
ks.load(new ByteArrayInputStream(Base64Coder.decode(MyKeystore.data)),"yourkeystorepassword".toCharArray());
final KeyManagerFactory kmf = KeyManagerFactory.getInstance(algorithm);
 kmf.init(ks, "yourkeystorepassword".toCharArray());
 serverContext.init(kmf.getKeyManagers(), null, null);
 ```
- Create a Netty SSLHandler from the created context,  and add it to the netty pipe (must be the first handler):
 ```
final SslHandler sslHandler = new SslHandler(serverContext);
pipeline.addLast("ssl", sslHandler);
```
### Client Side
