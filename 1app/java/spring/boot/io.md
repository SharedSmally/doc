# Spring Boot for IO

## [IO](https://docs.spring.io/spring-boot/docs/current/reference/html/io.html)

## Caching (@EnableCaching/spring-boot-starter-cache)
Apply caching to methods
```
@Component
public class MyMathService {
    @Cacheable("piDecimals")
    public int computePiDecimal(int precision) {
        ...
    }
}
```
Supported Cache Providers(the CacheManager is auto-configured by Spring Boot):
- Generic: the context defines at least one org.springframework.cache.Cache bean.
- JCache (JSR-107) (EhCache 3, Hazelcast, Infinispan, and others): JCacheCacheManager with spring.cache.jcache.* properties
- EhCache 2.x: EhCacheCacheManager with spring.cache.ehcache.* properties
- Hazelcast: a HazelcastInstance with spring.hazelcast.* properties(spring.hazelcast.config/hazelcast.client.config/hazelcast-client.yaml)
- Infinispan: with spring.cache.infinispan.* properties
- Couchbase: spring.cache.infinispan with spring.cache.couchbase.* properties
- Redis: RedisCacheManager with spring.cache.redis.* properties
- Caffeine: CaffeineCacheManager with spring.cache.caffeine.* properties
- Cache2k: SpringCache2kCacheManager with spring.cache.cache-names property
- Simple: a ConcurrentHashMap as the cache store is configured.
```
spring.cache.type=none  # disable cacheing, or use other type
spring.cache.cache-names=cache1,cache2
```


## Quartz: spring-boot-starter-quartz/spring.quartz.properties.*
A **Scheduler** is auto-configured through the SchedulerFactoryBean, and the following are automatically picked up and associated with the Scheduler:
- JobDetail: defines a particular Job. JobDetail instances can be built with the JobBuilder API.
- Calendar.
- Trigger: defines when a particular job is triggered.

By default, an in-memory JobStore is used, but can be cofigured via JDBC-based store using DataSource:
```
spring.quartz.job-store-type=jdbc
spring.quartz.jdbc.initialize-schema=always

```
To have Quartz use a DataSource other than the application’s main DataSource, declare a DataSource bean, annotating its @Bean method with @QuartzDataSource. 

To have Quartz use a TransactionManager other than the application’s main TransactionManager declare a TransactionManager bean, annotating its @Bean method with @QuartzTransactionManager.

## Mail: spring-boot-starter-mail(spring.mail.*/properties*)
 Sending email by using the **JavaMailSender** auto-configured beans,
 
## Validation
This lets bean methods be annotated with javax.validation constraints on their parameters and/or on their return value. Target classes with such annotated methods need to be annotated with the @Validated annotation at the type level for their methods to be searched for inline constraint annotations.
```
@Service
@Validated
public class MyBean {
    public Archive findByCodeAndAuthor(@Size(min = 8, max = 10) String code, Author author) {
        return ...
    }
}
```
## REST Clients: Calling REST Services with RestTemplate and WebClient
### RestTemplate
**RestTemplate** instances often need to be customized before being used, Spring Boot does not provide any single auto-configured RestTemplate bean. It does auto-configure a **RestTemplateBuilder** to create RestTemplate instances when needed:

```
import org.springframework.boot.web.client.RestTemplateBuilder;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

@Service
public class MyService {
    private final RestTemplate restTemplate;

    public MyService(RestTemplateBuilder restTemplateBuilder) {
        this.restTemplate = restTemplateBuilder.build();
    }

    public Details someRestCall(String name) {
        return this.restTemplate.getForObject("/{name}/details", Details.class, name);
    }
}
```
- Inject the auto-configured **RestTemplateBuilder**, and then call its methods as required.
- Make an application-wide, additive customization: use a **RestTemplateCustomizer** bean. All such beans are automatically registered with the auto-configured RestTemplateBuilder and are applied to any templates that are built with it.
- Define custom **RestTemplateBuilder** bean

### WebClient for WebFlux
Spring Boot creates and pre-configures a **WebClient.Builder**:
```
@Service
public class MyService {
    private final WebClient webClient;
    public MyService(WebClient.Builder webClientBuilder) {
        this.webClient = webClientBuilder.baseUrl("https://example.org").build();
    }
    public Mono<Details> someRestCall(String name) {
        return this.webClient.get().uri("/{name}/details", name).retrieve().bodyToMono(Details.class);
    }
}
```
Spring Boot will auto-detect which ClientHttpConnector to use to drive WebClient on Reactor Netty, Jetty RS client and Apache HttpClient.
- Inject the auto-configured **WebClient.Builder**(stateful) and then call its methods as required
- Make an application-wide, additive customization:  declare WebClientCustomizer beans and change the WebClient.Builder locally at the point of injection.
- Use WebClientCustomizer

## Webservices: spring-boot-starter-webservices
**SimpleWsdl11Definition** and **SimpleXsdSchema** beans are automatically created for WSDLs and XSDs respectively:
```
spring.webservices.wsdl-locations=classpath:/wsdl
```
Use **WebServiceTemplate** class to call remote Web services. WebServiceTemplate often need to be customized before being used, Spring Boot auto-configure a WebServiceTemplateBuilder to create WebServiceTemplate instances when needed:
```
import org.springframework.boot.webservices.client.WebServiceTemplateBuilder;
import org.springframework.stereotype.Service;
import org.springframework.ws.client.core.WebServiceTemplate;
import org.springframework.ws.soap.client.core.SoapActionCallback;

@Service
public class MyService {
    private final WebServiceTemplate webServiceTemplate;
    public MyService(WebServiceTemplateBuilder webServiceTemplateBuilder) {
        this.webServiceTemplate = webServiceTemplateBuilder.build();
    }

    public SomeResponse someWsCall(SomeRequest detailsReq) {
        return (SomeResponse) this.webServiceTemplate.marshalSendAndReceive(detailsReq,
                new SoapActionCallback("https://ws.example.com/action"));
    }
}
```
The WebServiceTemplate can be customized:
```
@Configuration(proxyBeanMethods = false)
public class MyWebServiceTemplateConfiguration {
    @Bean
    public WebServiceTemplate webServiceTemplate(WebServiceTemplateBuilder builder) {
        WebServiceMessageSender sender = new HttpWebServiceMessageSenderBuilder()
                .setConnectTimeout(Duration.ofSeconds(5))
                .setReadTimeout(Duration.ofSeconds(2))
                .build();
        return builder.messageSenders(sender).build();
    }
}
```

## JTA: Distributed Transactions with JTA
Distributed JTA transactions across multiple XA resources by using an **Atomikos** embedded transaction manager, or Java EE Application Server.
Use standard Spring idioms, such as **@Transactional**, to participate in a distributed transaction. 

- Atomikos Transaction Manager: spring-boot-starter-jta-atomikos
- 
