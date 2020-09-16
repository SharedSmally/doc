# Spring Framework
- [Java API](https://docs.spring.io/spring/docs/current/javadoc-api/overview-summary.html)
- [Document](https://docs.spring.io/spring-framework/docs/current/spring-framework-reference/)

## Spring Framework Components
- Core: IoC Container, Events, Resources, i18n, Validation, Data Binding, Type Conversion, SpEL, AOP.
     - aop: aspectj, framework
     - beans: factory
     - context
     - core: codec,convert,env,io,buffer,log,serializer,style,task, type
     - expression: SpEL
     - validation
     - format: datetime, number
     - ui
     - util
- Testing	: Mock Objects, TestContext Framework, Spring MVC Test, WebTestClient.
     - mock    
     - test: context, web
- Data Access: Transactions, DAO Support, JDBC, O/R Mapping, XML Marshalling.
     - dao
     - jdbc: datasource
     - orm: hibernate, jpa
     - transaction: jta, reactive
     - oxm: jaxb, jibx,mime,xstream
- Web Servlet: Spring MVC, WebSocket, SockJS, STOMP Messaging.
     - http
         - server: reactive
         - client: reactive
         - codec: xml,json,protobuf,cbor,multipart
         - converter: xml,json,protobuf,cbor,feed,smile    
     - web:
     - web.server
     - web.servlet: 
         - view: xml, json, xslt, document, freemaker, feed, groovy, script, titles3
    
- Web Reactive: Spring WebFlux, WebClient, WebSocket.
     - web.socket: 
          - client: jetty, standard
          - server: jetty, standard
          - sockjs: 
     - web.reactive:
- Integration:  Remoting, JMS, JCA, JMX, Email, Tasks, Scheduling, Caching.
     - cache: ehcache, jcache, caffeine, concurrent
     - ejb
     - jca: cci
     - jms
     - jmx
     - jndi
     - mail  
     - messaging: handler, rsocket, simp, tcp
     - remoting: caucho, httpinvoker, jaxws, rmi, soap     
     - scheduling: aspectj, commonj, concurrent, quartz
- Languages: Kotlin, Groovy, Dynamic Languages.
     - scripting: bsh,groovy









