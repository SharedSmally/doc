# Http/2 PUSH

HTTP/2 Push is a mechanism that allows the server to send multiple resources to the client for a single client request. 
This will reduce the amount of round-trips necessary to retrieve all the resources that make up a web page and can 
significantly improve the page load time. HTTP/2 Push can be automated by configuring a PushCacheFilter in the [web.xml](https://www.eclipse.org/jetty/documentation/current/http2-configuring-push.html)

The [PushBuilder APIs](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/server/PushBuilder.html) can setup a resource to push, and to push it.
```
PushBuilder	path(java.lang.String path)	
void	push()	
```
The path(java.lang.String) method must be called on the PushBuilder instance before the call to push().

```
        Server server = new Server();

        // HTTP Port
        HttpConfiguration httpConfig = new HttpConfiguration();
        httpConfig.setSecureScheme("https"); // needed on non-ssl connector for secure redirect
        httpConfig.setSecurePort(SSL_PORT); // needed on non-ssl connector for secure redirect
        httpConfig.setSendXPoweredBy(false);
        httpConfig.setSendServerVersion(false);

        HttpConnectionFactory httpConnectionFactory = new HttpConnectionFactory();
        ServerConnector httpConnector = new ServerConnector(server, httpConnectionFactory);
        httpConnector.setPort(8080);
        server.addConnector(httpConnector);

        // TLS (SSL) Port
        HttpConfiguration httpsConfig = new HttpConfiguration(httpConfig); // extends from non-ssl
        httpsConfig.addCustomizer(new SecureRequestCustomizer()); // only valid on SSL/TLS connector

        HTTP2ServerConnectionFactory http2ConnectionFactory = new HTTP2ServerConnectionFactory(httpsConfig);
        ALPNServerConnectionFactory alpnConnectionFactory = new ALPNServerConnectionFactory();
        alpnConnectionFactory.setDefaultProtocol(httpConnectionFactory.getProtocol());
        SslContextFactory sslContextFactory = new SslContextFactory();
        sslContextFactory.setKeyStorePath(GzipHttp2PushFilterExample.class.getResource("/keystore").toExternalForm());
        sslContextFactory.setCipherComparator(HTTP2Cipher.COMPARATOR);
        sslContextFactory.setKeyStorePassword("changeit");
        sslContextFactory.setUseCipherSuitesOrder(true);
        SslConnectionFactory sslConnectionFactory = new SslConnectionFactory(sslContextFactory, alpnConnectionFactory.getProtocol());
        ServerConnector httpsConnector = new ServerConnector(server, sslConnectionFactory, http2ConnectionFactory,  httpConnectionFactory);

        server.addConnector(httpsConnector);

        // Non Handler Configuration
        server.setRequestLog(new AsyncNCSARequestLog());

        // Servlet ROOT Context
        ServletContextHandler context = new ServletContextHandler();
        context.setContextPath("/");
        context.setWelcomeFiles(new String[]{"index.html"});
        context.setBaseResource(new PathResource(Paths.get("some","path", "somewhere")));

        // Push Cache Filter
        FilterHolder pushFilter = context.addFilter(PushCacheFilter.class, "/*", EnumSet.of(DispatcherType.REQUEST));
        pushFilter.setInitParameter("maxAssociations", "" + 32);
        pushFilter.setInitParameter("ports", "" + SSL_PORT);

        // customized servlet
        context.addServlet(AdapterServlet.class, "/*"); // won't serve static files if use this url-pattern!

        // what serves static files from a ServletContext, always added last
        ServletHolder defHolder = new ServletHolder("default", DefaultServlet.class); // always named "default"
        defHolder.setInitParameter("dirAllowed", "false");
        context.addServlet(defHolder, "/"); // always at url-pattern "/"

        // Handler Tree
        HandlerList handlers = new HandlerList();
        handlers.addHandler(new SecuredRedirectHandler()); // no need for Constraints / Constraint Mappings
        handlers.addHandler(new GzipHandler()); // wrapping / nesting is optional
        handlers.addHandler(context);
        handlers.addHandler(new DefaultHandler()); // always last in handler tree, to help with errors and configuration mistakes

        server.setHandler(handlers);

```

