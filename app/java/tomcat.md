# Create Http Server on Tomcat
See [example](https://devcenter.heroku.com/articles/create-a-java-web-application-using-embedded-tomcat) and [embedded tomcat](http://zetcode.com/web/embeddedtomcat/)
- Add dependencies in pom.xml: Only embed-core is required
```
  <properties>
    <tomcat.version>8.5.23</tomcat.version>
  </properties>
  <dependencies>
    <dependency>
        <groupId>org.apache.tomcat.embed</groupId>
        <artifactId>tomcat-embed-core</artifactId>
        <version>${tomcat.version}</version>
    </dependency>
    <dependency>
        <groupId>org.apache.tomcat.embed</groupId>
        <artifactId>tomcat-embed-jasper</artifactId>
        <version>${tomcat.version}</version>
    </dependency>
    <dependency>
        <groupId>org.apache.tomcat</groupId>
        <artifactId>tomcat-jasper</artifactId>
        <version>${tomcat.version}</version>
    </dependency>
    <dependency>
        <groupId>org.apache.tomcat</groupId>
        <artifactId>tomcat-jasper-el</artifactId>
        <version>${tomcat.version}</version>
    </dependency>
    <dependency>
        <groupId>org.apache.tomcat</groupId>
        <artifactId>tomcat-jsp-api</artifactId>
        <version>${tomcat.version}</version>
    </dependency>
  </dependencies>
```
- Start Tomcat: Main.java
```
package launch;
import java.io.File;

import org.apache.catalina.WebResourceRoot;
import org.apache.catalina.core.StandardContext;
import org.apache.catalina.startup.Tomcat;
import org.apache.catalina.webresources.DirResourceSet;
import org.apache.catalina.webresources.StandardRoot;

public class Main {
    public static void main(String[] args) throws Exception {
        String webappDirLocation = "src/main/webapp/";
        Tomcat tomcat = new Tomcat();

        //The port that we should run on can be set into an environment variable
        //Look for that variable and default to 8080 if it isn't there.
        String webPort = System.getenv("PORT");
        if(webPort == null || webPort.isEmpty()) {
            webPort = "8080";
        }
        tomcat.setPort(Integer.valueOf(webPort));

        StandardContext ctx = (StandardContext) tomcat.addWebapp("/", new File(webappDirLocation).getAbsolutePath());
        System.out.println("configuring app with basedir: " + new File("./" + webappDirLocation).getAbsolutePath());

        // Declare an alternative location for your "WEB-INF/classes" dir:  Servlet 3.0 annotation will work
        File additionWebInfClasses = new File("target/classes");
        WebResourceRoot resources = new StandardRoot(ctx);
        resources.addPreResources(new DirResourceSet(resources, "/WEB-INF/classes", additionWebInfClasses.getAbsolutePath(), "/"));
        ctx.setResources(resources);

        tomcat.start();
        tomcat.getServer().await();
    }
}
```
- Add Servlet: HelloServlet.java
```
package servlet;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "MyServlet", urlPatterns = {"/hello"})
public class HelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        ServletOutputStream out = resp.getOutputStream();
        out.write("hello heroku".getBytes());
        out.flush();
        out.close();
    }
}
```
- Example supports http/2 and TLS
```
import org.apache.catalina.Context;
import org.apache.catalina.startup.Tomcat;
import org.apache.catalina.LifecycleException;
import org.apache.catalina.connector.Connector;
import org.apache.coyote.http2.Http2Protocol;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;

    private volatile boolean mutualAuthentication;
    private volatile String cipherSuites;
    private volatile String tlsVersions;
    private volatile String trustStore;
    private volatile String trustStorePassword;
    
    void setupTomcat() {  
                Tomcat tomcat = new Tomcat();
                tomcat.setBaseDir("temp");
                tomcat.setPort(Integer.parseInt(port));

                String contextPath = "";
                String docBase = new File(".").getAbsolutePath();

                Context context = tomcat.addContext(contextPath, docBase);

                HttpServlet servlet = new HttpCustomerServlet(this);
                String servletName = "HttpCustomerServlet";
                String urlPattern = "/*";

                tomcat.addServlet(contextPath, servletName, servlet);
                context.addServletMappingDecoded(urlPattern, servletName);

                Connector connector = tomcat.getConnector();
                connector.addUpgradeProtocol(new Http2Protocol());

                if (Boolean.parseBoolean(secure)) {
                    // set up ssl params
                    connector.setSecure(true);
                    connector.setScheme("https");
                    connector.setAttribute("SSLEnabled", true);
                    connector.setAttribute("clientAuth", mutualAuthentication);
                    connector.setAttribute("sslProtocol", "TLS");
                    //need keypass and keystore
                    if (trustStorePassword != null)
                        connector.setAttribute("keystorePass", trustStorePassword);
                    if (trustStore != null)
                        connector.setAttribute("keystoreFile", trustStore);
                    if (tlsVersions != null)
                        connector.setAttribute("sslEnabledProtocols", tlsVersions);
                    if (cipherSuites != null)
                        connector.setAttribute("ciphers", cipherSuites);
                }
            } catch (LifecycleException err) {
                return false;
            }
       }

import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HttpCustomerServlet extends HttpServlet {
    @Override
    protected void service(HttpServletRequest req, HttpServletResponse resp)
           throws ServletException, IOException {
           String body=req.getReader().lines().collect(Collectors.joining(System.lineSeparator()));

            resp.setContentType(contenttype);
            resp.setContentLength(responseData.length());
                
            PrintWriter writer = resp.getWriter();
            writer.println(responseData);
            writer.flush();
    }
}
```


