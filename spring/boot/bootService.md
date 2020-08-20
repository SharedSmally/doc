# Spring Boot
- [Reference](https://docs.spring.io/spring-boot/docs/current/reference/html/)
- [API Doc](https://docs.spring.io/spring-boot/docs/current/api/)
- [QuickStart](https://spring.io/quickstart)

## Guide: [Spring](https://spring.io/guides)
-  Web    
    - [REST Service](https://spring.io/guides/gs/rest-service/)
    - [Web Socket](https://spring.io/guides/gs/messaging-stomp-websocket/)
    - [SOAP Web Service](https://spring.io/guides/gs/consuming-web-service/)
    - [SOAP Web Client](https://spring.io/guides/gs/producing-web-service/)
    - [RestDocs]()
- [JDBC]
- JPA: JPA + database impl(h2,postgresql.mysql,...)(model/repository=>service)    
    - [H2](https://spring.io/guides/gs/accessing-data-jpa/)
    - [MySQL](https://spring.io/guides/gs/accessing-data-mysql/)
    - [MongoDB](https://spring.io/guides/gs/accessing-data-mongodb/)
    - [GemFile](https://spring.io/guides/gs/accessing-data-gemfire/)
    - [Neo4j](https://spring.io/guides/gs/accessing-data-neo4j/)  
- Reactive data access
    - [R2DBC](https://spring.io/guides/gs/accessing-data-r2dbc/): Reactive DB
    - [Redis]()
- [LDAP](https://spring.io/guides/gs/authenticating-ldap/)
- [RabbitMQ](https://spring.io/guides/gs/messaging-rabbitmq/)
- Redis: [Spring](https://spring.io/guides/gs/messaging-redis/),[DZone](https://dzone.com/articles/intro-to-redis-with-spring-boot#:~:text=Redis%20supports%20data%20structures%20such,abstraction%20to%20the%20data%20store.)
- Cloud
    - Service Registrion and Discovery
    - Centralized Configuration
    - Routing and Filtering
    - LoadBalancer
    - Circuit Breaker
    - Gateway
    - Vault
    - Cloud Stream
    - Cloud Data Flow
    - Cloud Task
- Deployment
    - [Kubernetes](https://spring.io/guides/gs/spring-boot-kubernetes/)
    - [Docker](https://spring.io/guides/gs/spring-boot-docker/)
    - [Azure]

## [Application Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-external-config): @ConfigurationProperties

- [Core properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#core-properties)
- [Cache properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#cache-properties)
- [Mail properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#mail-properties)
- [JSON properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#json-properties)
- [Data properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#data-properties)
- [Transaction properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#transaction-properties)
- [Data migration properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#data-migration-properties)
- [Integration properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#integration-properties)
- [Web properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#web-properties)
- [Templating properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#templating-properties)
- [Server properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#server-properties)
- [Security properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#security-properties)
- [RSocket properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#rsocket-properties)
- [Actuator properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#actuator-properties)
- [Devtools properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#devtools-properties)
- [Testing properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#testing-properties)

## Beans

## Components:
- @Compoenent
- @Controller
- @Service
- @Repository

## Packages
- org.springframework.boot.xxx
- org.springframework.boot.web.xxx
- org.springframework.boot.autoconfigure.xxx:  *AutoConfiguration
- org.springframework.boot.autoconfigure.metrics.xxx:  *MetricsAutoConfiguration
- org.springframework.boot.actuate.xxx
- org.springframework.boot.actuate.metrics.xxx
- org.springframework.boot.actuate.autoconfigure.xxx

- org.springframework.boot.cli.xxx
- org.springframework.boot.test.xxx
- org.springframework.boot.devtools.xxx
- org.springframework.boot.buildpack.xxx

## [org.springframework.boot.autoconfigure.condition](https://docs.spring.io/spring-boot/docs/current/api/org/springframework/boot/autoconfigure/condition/package-summary.html)
```
```
@ConfigurationProperties("app.system")
public class AppSystemProperties {
    @DurationUnit(ChronoUnit.SECONDS)
    private Duration sessionTimeout = Duration.ofSeconds(30);
    private Duration readTimeout = Duration.ofMillis(1000);

    public Duration getSessionTimeout() { return this.sessionTimeout; }
    public void setSessionTimeout(Duration sessionTimeout) { this.sessionTimeout = sessionTimeout; }
    
    public Duration getReadTimeout() { return this.readTimeout; }
    public void setReadTimeout(Duration readTimeout) { this.readTimeout = readTimeout;  }
}
```

 @Configuration
 public class MyAutoConfiguration {
 
     @ConditionalOnBean
     @Bean
     public MyService myService() {
         ...
     }
 }
```
- ConditionalOnBean: @Conditional that only matches when beans meeting all the specified requirements are already contained in the BeanFactory.
- ConditionalOnClass: @Conditional that only matches when the specified classes are on the classpath.
- ConditionalOnCloudPlatform: @Conditional that matches when the specified cloud platform is active.
- ConditionalOnExpression: Configuration annotation for a conditional element that depends on the value of a SpEL expression.
- ConditionalOnJava: @Conditional that matches based on the JVM version the application is running on.
- ConditionalOnJndi: @Conditional that matches based on the availability of a JNDI InitialContext and the ability to lookup specific locations.
- ConditionalOnMissingBean: @Conditional that only matches when no beans meeting the specified requirements are already contained in the BeanFactory.
- ConditionalOnMissingClass: @Conditional that only matches when the specified classes are not on the classpath.
- ConditionalOnNotWebApplication: @Conditional that only matches when the application context is a not a web application context.
- ConditionalOnProperty: @Conditional that checks if the specified properties have a specific value.
- ConditionalOnResource: @Conditional that only matches when the specified resources are on the classpath.
- ConditionalOnSingleCandidate: @Conditional that only matches when a bean of the specified class is already contained in the BeanFactory and a single candidate can be determined.
- ConditionalOnWarDeployment: @Conditional that matches when the application is a traditional WAR deployment.
- ConditionalOnWebApplication: @Conditional that matches when the application is a web application.
