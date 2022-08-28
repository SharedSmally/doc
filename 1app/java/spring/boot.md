# Spring Boot
Auto Configuration based on Dependencies

## Reference
- [Site](https://spring.io/projects/spring-boot/)
- [Quick Start](https://spring.io/quickstart)
- [User Guide](https://docs.spring.io/spring-boot/docs/current/reference/html/)
- [API Javadoc](https://docs.spring.io/spring-boot/docs/current/api/)
- [Starters](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.build-systems.starters): spring-boot-starter-\*, a set of convenient dependency descriptors that can be included in the application. 
- [AutoConfig Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/application-properties.html#appendix.application-properties):
Core,Cache,Mail,JSON,Data,Transaction,Data,Integration,Web,Templating,Server,Security,RSocket,Actuator,Devtools and Testing.
- [Auto-configuration Classes](https://docs.spring.io/spring-boot/docs/current/reference/html/auto-configuration-classes.html#appendix.auto-configuration-classes)
- [Test Auto Configuration Annotations](https://docs.spring.io/spring-boot/docs/current/reference/html/test-auto-configuration.html#appendix.test-auto-configuration):
@DataCassandraTest,@DataCouchbaseTest,@DataElasticsearchTest,@DataJdbcTest,@DataJpaTest,@DataLdapTest,@DataMongoTest,@DataNeo4jTest,@DataR2dbcTest,@DataRedisTest,@GraphQlTest,@JdbcTest,@JooqTest,@JsonTest,@RestClientTest,@WebFluxTest,@WebMvcTest,@WebServiceClientTest,@WebServiceServerTest
- [Dependency Versions](https://docs.spring.io/spring-boot/docs/current/reference/html/dependency-versions.html#appendix.dependency-versions)

## Tutorial


## Developing
- Install Build systems: Maven/Gradle
- Install the Spring Boot CLI(*spring-boot-cli*), use the command: **spring grab|help|jar|run|test|version**
- Create pom.xml:
```xml
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.7.3</version>
    </parent>

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
    </dependencies>
```
- Application.java
```java
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;

import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;

@RestController
@EnableAutoConfiguration
//disable AutoConfiguration using exclude or excludeName 
//@SpringBootApplication(exclude = { DataSourceAutoConfiguration.class })
public class MyApplication {
    @RequestMapping("/")
    String home() {  return "Hello World!"; }
    public static void main(String[] args) {
        SpringApplication.run(MyApplication.class, args);
    }
}
```
**@EnableAutoConfiguration** tells Spring Boot to guess how to configure Spring based on the jar dependencies added. 
**@SpringBootApplication** does more than @EnableAutoConfiguration does, it is a combination: and **@SpringBootConfiguration**(enable registration of extra beans in the context or the import of additional configuration classes) from **@Configuration**(for Java-based configuration on Spring framework), **@ComponentScan**(enable component scanning of components like @Controller in current and sub-packages), and **@EnableAutoConfgiuration**(allow for auto-configuration in Spring Boot application).

- Run the application
```shell
    $ mvn spring-boot:run
    $ export MAVEN_OPTS=-Xmx1024m
```
or
```shell
    $ gradle bootRun
    $ export JAVA_OPTS=-Xmx1024m
```
or
```shell
    $ spring run
```
- Creating an Executable Jar
```xml
    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>
```
```shell
    $ mvn package
    $ java -jar target/myproject-0.0.1-SNAPSHOT.jar
    $ java -jar target/myproject-0.0.1-SNAPSHOT.jar --debug   #  enable debug
```
Open a web browser to localhost:8080

- Configuration Classes (@Depends)
     - **@Configuration**: build beans for the application. The class defining the main method is a good candidate as the primary @Configuration.
     - **@Import**: import additional configuration classes.
     - **@ImportResource**: load XML configuration files 
     - **@ComponentScan**: automatically pick up all Spring components, including @Configuration classes. All the application components (@Component, @Service, @Repository, @Controller, and others) are automatically registered as Spring Beans.
     - **@EnableAutoConfiguration/@SpringBootApplication**:attempts to automatically configure the Spring application based on the jar dependencies

- Add Developer Tools, can be configured by *spring-boot-devtools.properties/yaml/yml*.
     - Cache: can improve performance, the [cache options](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.property-defaults) are configured by settings in *application.properties* file.
     - [Automatic Restart](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.restart):Triggered by the updating of the classpath, can be disabled, and set/exclude the trigger files/resources. 
     - [Live Reload](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.livereload)
     - [Remote Application](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.remote-applications)
```xml
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-devtools</artifactId>
        <optional>true</optional>
    </dependency>
```

    
## [Boot](https://docs.spring.io/spring-boot/docs/current/reference/html/features.html)
### Spring Application
- Enable debug: *--debug*
- Lazy Initialization: 
    - *spring.main.lazy-initialization=true*
    - *SpringApplicationBuilder.lazyInitialization/SpringApplication.setLazyInitialization* 
    - *@Lazy(false)* for specific beans
- Customize the Banner:
    - A *banner.txt* and *banner.gif/jpg/png* in classpath or in *spring.banner.location*
    - SpringApplication.setBanner() for org.springframework.boot.Banner
- Customize SpringApplication
```java
import org.springframework.boot.Banner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class MyApplication {
    public static void main(String[] args) {
        SpringApplication application = new SpringApplication(MyApplication.class);
        application.setBannerMode(Banner.Mode.OFF);
        application.run(args);
    }
```
The constructor arguments passed to SpringApplication are configuration sources for Spring beans. 
- Fluent Builder
Use the SpringApplicationBuilder to build an ApplicationContext hierarchy (multiple contexts with a parent/child relationship) or others:
```java
new SpringApplicationBuilder()
        .sources(Parent.class)
        .child(Application.class)
        .bannerMode(Banner.Mode.OFF)
        .run(args);
```
- Application Availability for k8s
    - Liveness State: The internal state of Spring Boot applications is mostly represented by the Spring ApplicationContext. If the application context has started successfully, Spring Boot assumes that the application is in a valid state. An application is considered live as soon as the context has been refreshed.
    - Readiness State: An application is considered ready as soon as application and command-line runners have been called.
    - Spring Boot *actuator* health endpoint groups
```
livenessProbe:
  httpGet:
    path: "/actuator/health/liveness"
    port: <actuator-port>
  failureThreshold: ...
  periodSeconds: ...

readinessProbe:
  httpGet:
    path: "/actuator/health/readiness"
    port: <actuator-port>
  failureThreshold: ...
  periodSeconds: ...
```
    - Injecting the *ApplicationAvailability*

Export the "Readiness" state of the application to a file so that a Kubernetes "exec Probe" can look at this file:
```java
import org.springframework.boot.availability.AvailabilityChangeEvent;
import org.springframework.boot.availability.ReadinessState;
import org.springframework.context.event.EventListener;
import org.springframework.stereotype.Component;

@Component
public class MyReadinessStateExporter {
    @EventListener
    public void onStateChange(AvailabilityChangeEvent<ReadinessState> event) {
        switch (event.getState()) {
            case ACCEPTING_TRAFFIC:
                // create file /tmp/healthy
                break;
            case REFUSING_TRAFFIC:
                // remove file /tmp/healthy
                break;
        }
    }
}
```
 Update the state of the application, when the application breaks and cannot recover:
 ```java
import org.springframework.boot.availability.AvailabilityChangeEvent;
import org.springframework.boot.availability.LivenessState;
import org.springframework.context.ApplicationEventPublisher;
import org.springframework.stereotype.Component;

@Component
public class MyLocalCacheVerifier {
    private final ApplicationEventPublisher eventPublisher;

    public MyLocalCacheVerifier(ApplicationEventPublisher eventPublisher) {
        this.eventPublisher = eventPublisher;
    }
    public void checkLocalCache() {
        try {
            // ...
        }
        catch (CacheCompletelyBrokenException ex) {
            AvailabilityChangeEvent.publish(this.eventPublisher, ex, LivenessState.BROKEN);
        }
    }
}
 ```
- [Application Events and Listeners](https://docs.spring.io/spring-boot/docs/current/reference/html/features.html#features.spring-application.application-events-and-listeners)

In addition to the usual Spring Framework events, such as ContextRefreshedEvent, a SpringApplication sends some additional application events. Some events are triggered before the ApplicationContext is created, the listener cannot be registered as a @Bean, but can register them with the SpringApplication.addListeners() method or the SpringApplicationBuilder.listeners() method.

- Accessing Application Arguments

Inject a org.springframework.boot.ApplicationArguments bean to access the application arguments that were passed to SpringApplication.run(). It can access  both the raw String[] arguments as well as parsed option and non-option arguments.
```java
import java.util.List;

import org.springframework.boot.ApplicationArguments;
import org.springframework.stereotype.Component;

@Component
public class MyBean {
    public MyBean(ApplicationArguments args) {
        boolean debug = args.containsOption("debug");
        List<String> files = args.getNonOptionArgs();
        if (debug) {
            System.out.println(files);
        }
        // if run with "--debug logfile.txt" prints ["logfile.txt"]
    }
}
```

- Use the ApplicationRunner or CommandLineRunner

Implement the **ApplicationRunner**(as ApplicationArguments) or **CommandLineRunner**( a string array) interfaces to run some specific code once the SpringApplication has started, their run() method is called just before SpringApplication.run() completes.
```java
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

@Component
public class MyCommandLineRunner implements CommandLineRunner {
    @Override
    public void run(String... args) {
        // Do something...
    }
}
```
If must be called in a specific order, implement the *org.springframework.core.Ordered* interface or use the *org.springframework.core.annotation.Order* annotation.

- Application Exit

Each SpringApplication registers a shutdown hook with the JVM to ensure that the ApplicationContext closes gracefully on exit. All the standard Spring lifecycle callbacks (such as the DisposableBean interface or the @PreDestroy annotation) can be used.

Beans may implement the org.springframework.boot.ExitCodeGenerator interface to return a specific exit code when SpringApplication.exit() is called.
```java
@SpringBootApplication
public class MyApplication {
    @Bean
    public ExitCodeGenerator exitCodeGenerator() {
        return () -> 42;
    }

    public static void main(String[] args) {
        System.exit(SpringApplication.exit(SpringApplication.run(MyApplication.class, args)));
    }
}
```

- Admin Features

Enable admin-related features to exposes the SpringApplicationAdminMXBean on the platform MBeanServer
```
spring.application.admin.enabled=true
```

- Application Startup tracking using ApplicationStartup (StartFlightRecording or BufferingApplicationStartup)

```java
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.context.metrics.buffering.BufferingApplicationStartup;

@SpringBootApplication
public class MyApplication {
    public static void main(String[] args) {
        SpringApplication application = new SpringApplication(MyApplication.class);
        application.setApplicationStartup(new BufferingApplicationStartup(2048));
        application.run(args);
    }
}
```

### External Configuration

### Profiles

### Logging

## [Web](https://docs.spring.io/spring-boot/docs/current/reference/html/web.html)


    Servlet Web Applications: Spring MVC, Jersey, Embedded Servlet Containers

    Reactive Web Applications: Spring Webflux, Embedded Servlet Containers

    Graceful Shutdown: Graceful Shutdown

    Spring Security: Default Security Configuration, Auto-configuration for OAuth2, SAML

    Spring Session: Auto-configuration for Spring Session

    Spring HATEOAS: Auto-configuration for Spring HATEOAS


## [Data](https://docs.spring.io/spring-boot/docs/current/reference/html/data.html)


    SQL: Configuring a SQL Datastore, Embedded Database support, Connection pools, and more.

    NOSQL: Auto-configuration for NOSQL stores such as Redis, MongoDB, Neo4j, and others.


## [Messaging](https://docs.spring.io/spring-boot/docs/current/reference/html/messaging.html)


    JMS: Auto-configuration for ActiveMQ and Artemis, Sending and Receiving messages through JMS

    AMQP: Auto-configuration for RabbitMQ

    Kafka: Auto-configuration for Spring Kafka

    RSocket: Auto-configuration for Spring Framework’s RSocket Support

    Spring Integration: Auto-configuration for Spring Integration


## [IO](https://docs.spring.io/spring-boot/docs/current/reference/html/io.html)


    Caching: Caching support EhCache, Hazelcast, Infinispan and more

    Quartz: Quartz Scheduling

    Mail: Sending Email

    Validation: JSR-303 Validation

    REST Clients: Calling REST Services with RestTemplate and WebClient

    Webservices: Auto-configuration for Spring Web Services

    JTA: Distributed Transactions with JTA


## [Container Images](https://docs.spring.io/spring-boot/docs/current/reference/html/container-images.html)

## Misc
### [Production-ready Features](https://docs.spring.io/spring-boot/docs/current/reference/html/actuator.html)

### [Deploying Spring Boot Applications](https://docs.spring.io/spring-boot/docs/current/reference/html/deployment.html)

### [Spring Boot CLI](https://docs.spring.io/spring-boot/docs/current/reference/html/cli.html)

### [Build Tool Plugins](https://docs.spring.io/spring-boot/docs/current/reference/html/build-tool-plugins.html)

### [How-to Guides](https://docs.spring.io/spring-boot/docs/current/reference/html/howto.html)




## [Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/configuration-metadata.html#appendix.configuration-metadata) sample
```java
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.boot.context.properties.DeprecatedConfigurationProperty;

@ConfigurationProperties("my.app")
public class MyProperties {
    private String name;
    public String getName() {
        return this.name;
    }
    public void setName(String name) {
        this.name = name;
    }
    @Deprecated
    @DeprecatedConfigurationProperty(replacement = "my.app.name")
    public String getTarget() {
        return this.name;
    }
    @Deprecated
    public void setTarget(String target) {
        this.name = target;
    }
}
```
## Auto Configuration
