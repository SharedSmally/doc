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

### Profiles

### Logging