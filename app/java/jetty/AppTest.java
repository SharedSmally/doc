```
package com.jpw.app;

import static org.junit.Assert.assertTrue;

import org.junit.Test;

import java.util.concurrent.TimeUnit;
import java.nio.charset.StandardCharsets;

import org.eclipse.jetty.client.HttpClient;
import org.eclipse.jetty.client.api.ContentResponse;
import org.eclipse.jetty.client.api.Response;//.CompleteListener
import org.eclipse.jetty.client.api.Result;
import org.eclipse.jetty.client.util.BufferingResponseListener;
import org.eclipse.jetty.util.ssl.SslContextFactory;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLEngine;
import javax.net.ssl.TrustManager;
//import javax.net.ssl.TrustAllX509TrustManager;
import java.security.SecureRandom;

public class AppTest 
{
    @Test
    public void testHelloHttpServer()
    {
        //assertTrue( true );
       //org.eclipse.jetty.util.log.Log.setLog(new NoLogging());
       // turn off jetty debug
       System.setProperty("org.eclipse.jetty.util.log.class", "org.eclipse.jetty.util.log.StdErrLog");
       System.setProperty("org.eclipse.jetty.LEVEL", "OFF");

       try {  //https://www.eclipse.org/jetty/documentation/current/http-client-api.html
        // Get a Client
        SslContextFactory sslContextFactory = new SslContextFactory(true);
        // needed for mutual auth.
        sslContextFactory.setKeyStorePath(App.class.getResource("/client.jks").toExternalForm());
        sslContextFactory.setKeyStorePassword("pass_keystore_client");
        sslContextFactory.setKeyManagerPassword("pass_key_client");
        sslContextFactory.setNeedClientAuth(true);
        sslContextFactory.setEndpointIdentificationAlgorithm("HTTPS");

        // only need truststore if not need mutual authen.
        sslContextFactory.setTrustStorePath(App.class.getResource("/client_ca.jks").toExternalForm());
        sslContextFactory.setTrustStorePassword("pass_turststore_client");
/*
        SSLContext context = SSLContext.getInstance("TLS"); 
        context.init(null, new TrustManager[] { new TrustAllX509TrustManager() }, new SecureRandom()); 
        SSLEngine engine = context.createSSLEngine(); 
        engine.setNeedClientAuth(sslContextFactory.getNeedClientAuth()); 
        engine.setEnabledCipherSuites(engine.getSupportedCipherSuites()); 
        engine.setEnabledProtocols(engine.getSupportedProtocols()); 
*/
        HttpClient httpClient = new HttpClient(sslContextFactory);

        //HttpClient httpClient = new HttpClient(); // for Http
        // Start server
        httpClient.start();

        /*
        SslContextFactory sslContextFactory = new SslContextFactory(); 
        sslContextFactory.setKeyStorePath(<store path>); 
        sslContextFactory.setNeedClientAuth(true); 
        sslContextFactory.setKeyStorePassword(<password>); 
        sslContextFactory.setCertAlias(<client alias>); 
        sslContextFactory.setEndpointIdentificationAlgorithm("HTTPS"); 

        SSLContext context = SSLContext.getInstance("TLS"); 
        context.init(null, new TrustManager[] { new TrustAllX509TrustManager() }, new SecureRandom()); 
        SSLEngine engine = context.createSSLEngine(); 
        engine.setNeedClientAuth(sslContextFactory.getNeedClientAuth()); 
        engine.setEnabledCipherSuites(engine.getSupportedCipherSuites()); 
        engine.setEnabledProtocols(engine.getSupportedProtocols()); 

        sslContextFactory.setSslContext(context); 
        sslContextFactory.setEndpointIdentificationAlgorithm(null); 

        HttpClient httpClient = new HttpClient(sslContextFactory); 
        httpClient.setMaxConnectionsPerDestination(2); 
        httpClient.setMaxRequestsQueuedPerDestination(2); 
        httpClient.setIdleTimeout(180000); 
        httpClient.start(); 
         */

        /*
        testGet(httpClient);
        testPost(httpClient);
        testPostAsync(httpClient);
        Thread.sleep(5000);
        */
        testSslGet(httpClient);
        
        httpClient.stop();
       }
       catch (Exception ex)
       {
          ex.printStackTrace();
       }
    }

    protected void testSslGet(HttpClient client) throws Exception {
        ContentResponse response = client
            .GET("https://localhost:9998");

        System.out.format("Https GET response:\n  version=%s; status=%d; reason=%s\n",
                response.getVersion(), response.getStatus(), response.getReason());
        System.out.format("  type=%s; encoding=%s;\n  content:\n%s\n",
              response.getMediaType(), response.getEncoding(), response.getContentAsString());
    }
    
    protected void testGet(HttpClient client) throws Exception {
        ContentResponse response = client
            .GET("http://localhost:9999");

        System.out.format("Http GET response:\n  version=%s; status=%d; reason=%s\n",
                response.getVersion(), response.getStatus(), response.getReason());
        System.out.format("  type=%s; encoding=%s;\n  content:\n%s\n",
              response.getMediaType(), response.getEncoding(), response.getContentAsString());
    }
    
    protected void testPost(HttpClient client) throws Exception {
        ContentResponse response = client
          .POST("http://localhost:9999/entity/1")
          .param("p", "value")
          .timeout(5, TimeUnit.SECONDS)
          .send();

        System.out.format("Http POST response:\n  version=%s; status=%d; reason=%s\n",
                response.getVersion(), response.getStatus(), response.getReason());
        System.out.format("  type=%s; encoding=%s;\n  content:\n%s\n",
              response.getMediaType(), response.getEncoding(), response.getContentAsString());
    }

    protected void testPostAsync(HttpClient client) throws Exception {
        client
          .POST("http://localhost:9999/entity/1")
          .param("p", "value")
          .timeout(5, TimeUnit.SECONDS)
          .onResponseContent(new Response.ContentListener() {
              @Override
              public void onContent(Response response, java.nio.ByteBuffer content) {
                   System.out.println("POST request content");
                   System.out.format("Http Async POST response content:\n  version=%s; status=%d; reason=%s\n",
                           response.getVersion(), response.getStatus(), response.getReason());
                   //System.out.format("  content:\n%s\n", content.toString()); //not work
              }
          })
          .send(/* new Response.CompleteListener() {
              @Override
              public void onComplete(Result result) {  //1.7
              result -> { //1.8
                  if (result.isSucceeded()) {
                      System.out.println("POST request completed: success");
                      Response response = result.getResponse();
                      System.out.format("Http Async POST response:\n  version=%s; status=%d; reason=%s\n",
                              response.getVersion(), response.getStatus(), response.getReason());
                  } else if (result.isFailed()) {
                     System.out.println("POST request completed: failed");
                     java.lang.Throwable failure =  result.getFailure();
                     if (failure != null) {
                         failure.printStackTrace();
                     }
                  } else {
                     System.out.println("POST request completed: none success/failure");  
                  }
              //} */
              //https://www.eclipse.org/jetty/documentation/current/http-client-api.html#http-client-content
              new BufferingResponseListener(8 * 1024) {
                    @Override
                    public void onComplete(Result result) {
                        System.out.println("POST request completed: success");
                        if (!result.isFailed()) {
                            byte[] content = getContent();
                            System.out.println("  Content:"+new String(content, StandardCharsets.UTF_8));
                        }
                    }
          });
    }
}
```
