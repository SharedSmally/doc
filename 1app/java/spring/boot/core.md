# Spring Boot 

## [Core Features](https://docs.spring.io/spring-boot/docs/current/reference/html/features.html)

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
Property values can be injected directly into beans by using the **@Value** annotation, accessed through Spring’s Environment abstraction, or be bound to structured objects through **@ConfigurationProperties**.

- Default properties (specified by setting SpringApplication.setDefaultProperties).
- @PropertySource annotations on the @Configuration classes. 
- Config data (such as application.properties files).
- A RandomValuePropertySource that has properties only in random.*.
- OS environment variables.
- Java System properties (System.getProperties()).
- JNDI attributes from java:comp/env.
- ServletContext init parameters.
- ServletConfig init parameters.
- Properties from SPRING_APPLICATION_JSON (inline JSON embedded in an environment variable or system property).
- Command line arguments.
- properties attribute on the tests. Available on @SpringBootTest and the test annotations for testing a particular slice of the application.
- @TestPropertySource annotations on the tests.
- Devtools global settings properties in the $HOME/.config/spring-boot directory when devtools is active.

Config data files are considered in the following order:
- Application properties packaged inside the jar (application.properties and YAML variants).
- Profile-specific application properties packaged the your jar (application-{profile}.properties and YAML variants).
- Application properties outside of the packaged jar (application.properties and YAML variants).
- Profile-specific application properties outside of the packaged jar (application-{profile}.properties and YAML variants).

```java
@Component
public class MyBean {
    @Value("${name}")
    private String name;
    // ...
}
```
In application.properties file:
```
name=Spring
```
or 
```
$ java -jar app.jar --name="Spring"
```
- Accessing Command Line Properties

By default, SpringApplication converts any command line option arguments (arguments starting with --, such as --server.port=9000) to a property and adds them to the Spring Environment. It can be disabled by using **SpringApplication.setAddCommandLineProperties(false)**.

- JSON Application Properties

When the application starts, any **spring.application.json** or **SPRING_APPLICATION_JSON** properties will be parsed and added to the Environment.
```
$ SPRING_APPLICATION_JSON='{"my":{"name":"test"}}' java -jar myapp.jar
$ java -Dspring.application.json='{"my":{"name":"test"}}' -jar myapp.jar
$ java -jar myapp.jar --spring.application.json='{"my":{"name":"test"}}'
```
Use a JNDI variable named java:comp/env/spring.application.json if deployed to a classic Application Server.

- External Application Properties:   
Spring Boot will automatically find and load **application.properties** and **application.yaml** files from the following locations:
     - From the classpath
          - The classpath root
          - The classpath /config package
     - From the current directory
          - The current directory
          - The /config subdirectory in the current directory
          - Immediate child directories of the /config subdirectory

The configuration file name can be specified by **spring.config.name**, and location by **spring.config.location** (replace), **spring.config.additional-location**(add additional locations). The optional: means not mind if not exist. They must be defined as an environment property (typically an OS environment variable, a system property, or a command-line argument):
```
$ java -jar myproject.jar --spring.config.name=myproject
$ java -jar myproject.jar 
    --spring.config.location=\
    optional:classpath:/default.properties,\
    optional:classpath:/override.properties,\
    optional:file:./custom-config/
```
Use the **spring.config.on-not-found=ignore** to ignore all ConfigDataLocationNotFoundExceptions and continue to start the application, either using SpringApplication.setDefaultProperties() or with a system/environment variable.

Wildcard location, a config file location includes the * character for the last path segment, is expanded when the config is loaded so that immediate subdirectories are also checked. By default, Spring Boot includes **config/\*/** in the default search locations.

A wildcard location must contain only one * and end with \*/ for search locations that are directories or \*/<filename> for search locations that are files.

- Profile Specific Files
    
Spring Boot loads profile-specific files using the naming convention *application-{profile}*.

- Importing Additional Data

Application properties may import further config data from other locations using the *spring.config.import* property. Several locations can be specified under a single spring.config.import key.

```
    spring.config.import=optional:file:./dev.properties
```
When using k8s ConfigMaps and Secrets, uultiple files are written to a directory tree, with the filename becoming the ‘key’ and the contents becoming the ‘value’.
```
etc/
  config/
    myapp/
      username
      password
    
    spring.config.import=optional:configtree:/etc/config/   # inject myapp.username and myapp.password properties
    spring.config.import=optional:configtree:/etc/config/*/ # import multiple config trees  
```
    
- Property Placeholders in property files

The standard ${name} property-placeholder syntax can be used anywhere within a value. It can specify a default value using a : to separate the default value from the property name, for example ${name:default}.
```
app.name=MyApp
app.description=${app.name} is a Spring Boot application written by ${username:Unknown}
```
    
- Working with Multi-Document Files
    
The standard YAML multi-document syntax, **---**, is used for application.yml files, and  #--- for application.properties.

- Activation Properties
    
Conditionally activate a properties document using **spring.config.activate.\* **.    
    
    
### Profiles

### Logging
