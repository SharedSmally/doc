```
package com.jpw.app;

/**
 * Hello world!
 *
 */

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.ServerConnector;
import org.eclipse.jetty.server.HttpConnectionFactory;
import org.eclipse.jetty.server.HttpConfiguration;
import org.eclipse.jetty.server.SecureRequestCustomizer;
import org.eclipse.jetty.server.SslConnectionFactory;
import org.eclipse.jetty.server.Connector;

import org.eclipse.jetty.util.ssl.SslContextFactory; //.Server;

public class App {
    public static void main( String[] args ) {
        try {
            App app = new App();
            //app.start();
            app.startSecure();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public void start() throws Exception {
        Server server = new Server(9999);
        try {
            server.getConnectors()[0].getConnectionFactory(HttpConnectionFactory.class);
            server.setHandler(new HelloHttpRequestHandler());
            server.start();
            server.join();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // https://gist.github.com/jankronquist/6412839
    // https://stackoverflow.com/questions/20056304/in-the-jetty-server-how-can-i-obtain-the-client-certificate-used-when-client-aut
    public void startSecure() throws Exception {
        Server server = new Server();
        
        ServerConnector connector = new ServerConnector(server);
        connector.setPort(9999);
        //server.setConnectors(new Connector[] { connector});

        HttpConfiguration https = new HttpConfiguration();
        // adds a critical SecureRequestCustomizer to the HttpConfiguration
        https.addCustomizer(new SecureRequestCustomizer());
        
        SslContextFactory sslContextFactory = new SslContextFactory(true); //trust all imported certs
        // works with server cert: curl -k https://localhost:9998 --cert ./server.crt --key ./client.key
        // but throw exception: java.nio.channels.ClosedChannelException: null
        // -k: --insecure  Allow insecure server connections when using SSL
        // For self-signed ca: curl https://localhost:9998 --cacert ./server.crt --key ./client.key
        sslContextFactory.setKeyStorePath(App.class.getResource("/server.jks").toExternalForm());
        //sslContextFactory.setKeyStorePassword("pass_keystore_server");
        //sslContextFactory.setKeyManagerPassword("pass_key_server");        
        sslContextFactory.setKeyStorePassword("OBF:1xtp1saj1z7g1yf41rw91x131rwl1x1v1yf41y101y0q1yf21x0r1rw91x1j1rwl1yf21z7m1sar1xtt");
        sslContextFactory.setKeyManagerPassword("OBF:1xtp1saj1z7g1yf41rw91x131rwl20zj1rw91x1j1rwl1yf21z7m1sar1xtt");
        
        // also works with p12
        /*
        sslContextFactory.setKeyStorePath(App.class.getResource("/server.p12").toExternalForm());
        sslContextFactory.setKeyStorePassword("pass_p12_server");
        sslContextFactory.setKeyManagerPassword("pass_p12_server");
        */
        //

        sslContextFactory.setTrustStorePath(App.class.getResource("/server_ca.jks").toExternalForm());
        //sslContextFactory.setTrustStorePassword("pass_turststore_server");
        sslContextFactory.setTrustStorePassword("OBF:1xtp1saj1z7g1yf41rw91ytc1v2t1vnw1yf41y101yta1ytc1y0q1yf21vn61v1l1yta1rwl1yf21z7m1sar1xtt");
        sslContextFactory.setNeedClientAuth(true);

        ServerConnector sslConnector = new ServerConnector(server,
              new SslConnectionFactory(sslContextFactory, "http/1.1"),
              new HttpConnectionFactory(https));
       sslConnector.setPort(9998);
       server.setConnectors(new Connector[] { sslConnector });
       //server.setConnectors(new Connector[] { connector, sslConnector });
       
       server.setHandler(new HelloHttpRequestHandler());

       server.start();
       server.join();
    }
}
```
