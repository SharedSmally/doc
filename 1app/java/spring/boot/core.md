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

The standard $\{name\} property-placeholder syntax can be used anywhere within a value. It can specify a default value using a : to separate the default value from the property name, for example $\{name:default\}.
```
app.name=MyApp
app.description=${app.name} is a Spring Boot application written by ${username:Unknown}
```
    
- Working with Multi-Document Files
    
The standard YAML multi-document syntax, **---**, is used for application.yml files, and  #--- for application.properties.

- Activation Properties    
Conditionally activate a properties document using **spring.config.activate.\* **.    
    
    - on-profile: A profile expression that must match for the document to be active.
    - on-cloud-platform: The CloudPlatform that must be detected for the document to be active.
```
myprop=always-set
#---
spring.config.activate.on-cloud-platform=kubernetes
spring.config.activate.on-profile=prod | staging
myotherprop=sometimes-set
```    

# Configuring Random Values

Inject random values for integers, longs, uuids, or strings:
```
my.secret=${random.value}
my.number=${random.int}
my.bignumber=${random.long}
my.uuid=${random.uuid}
my.number-less-than-ten=${random.int(10)}
my.number-in-range=${random.int[1024,65536]}
``` 
    
- Configuring System Environment Properties
    
Spring Boot supports setting a prefix for environment properties. The prefix for system environment properties can be set directly on SpringApplication.
For example, set the prefix to input, a property such as remote.timeout will also be resolved as input.remote.timeout in the system environment.   

- Type-safe Configuration Properties    

Use @ConfigurationProperties in stead of @Value:
```java
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.springframework.boot.context.properties.ConfigurationProperties;

@ConfigurationProperties("my.service")
public class MyProperties {
    private boolean enabled;
    private InetAddress remoteAddress;
    private final Security security = new Security();

    // getters / setters...
    public boolean isEnabled() {
        return this.enabled;
    }

    public void setEnabled(boolean enabled) {
        this.enabled = enabled;
    }

    public InetAddress getRemoteAddress() {
        return this.remoteAddress;
    }

    public void setRemoteAddress(InetAddress remoteAddress) {
        this.remoteAddress = remoteAddress;
    }

    public Security getSecurity() {
        return this.security;
    }

    public static class Security {
        private String username;
        private String password;
        private List<String> roles = new ArrayList<>(Collections.singleton("USER"));

        // getters / setters...
        public String getUsername() {
            return this.username;
        }
        public void setUsername(String username) {
            this.username = username;
        }
        public String getPassword() {
            return this.password;
        }
        public void setPassword(String password) {
            this.password = password;
        }
        public List<String> getRoles() {
            return this.roles;
        }
        public void setRoles(List<String> roles) {
            this.roles = roles;
        }
    }
}
```    
Use Constructor binding in an immutable fashion (getter):
```
import java.net.InetAddress;
import java.util.List;

import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.boot.context.properties.ConstructorBinding;
import org.springframework.boot.context.properties.bind.DefaultValue;

@ConstructorBinding
@ConfigurationProperties("my.service")
public class MyProperties {
    // fields...
    private final boolean enabled;
    private final InetAddress remoteAddress;
    private final Security security;

    public MyProperties(boolean enabled, InetAddress remoteAddress, Security security) {
        this.enabled = enabled;
        this.remoteAddress = remoteAddress;
        this.security = security;
    }

    // getters...
    public boolean isEnabled() {
        return this.enabled;
    }

    public InetAddress getRemoteAddress() {
        return this.remoteAddress;
    }

    public Security getSecurity() {
        return this.security;
    }

    public static class Security {
        // fields...
        private final String username;
        private final String password;
        private final List<String> roles;

        public Security(String username, String password, @DefaultValue("USER") List<String> roles) {
            this.username = username;
            this.password = password;
            this.roles = roles;
        }

        // getters...
        public String getUsername() {
            return this.username;
        }

        public String getPassword() {
            return this.password;
        }

        public List<String> getRoles() {
            return this.roles;
        }
    }
}
```  
The class must be enabled using @EnableConfigurationProperties or configuration property scanning for constructor binding. Spring Boot provides infrastructure to bind @ConfigurationProperties types and register them as beans:
```
import org.springframework.boot.context.properties.EnableConfigurationProperties;
import org.springframework.context.annotation.Configuration;

@Configuration(proxyBeanMethods = false)
@EnableConfigurationProperties(SomeProperties.class)
public class MyConfiguration {

}    
```   
    or
```
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.context.properties.ConfigurationPropertiesScan;

@SpringBootApplication
@ConfigurationPropertiesScan({ "com.example.app", "com.example.another" })
public class MyApplication {

}
```   
The @ConfigurationProperties beans can be injected in the same way as any other bean:    
```
import org.springframework.stereotype.Service;

@Service
public class MyService {
    private final SomeProperties properties;
    public MyService(SomeProperties properties) {
        this.properties = properties;
    }

    public void openConnection() {
        Server server = new Server(this.properties.getRemoteAddress());
        server.start();
        // ...
    }
    // ...
}
```    
- Third-party Configuration

Use @ConfigurationProperties to annotate a class on public @Bean methods:
```
@Configuration(proxyBeanMethods = false)
public class ThirdPartyConfiguration {
    @Bean
    @ConfigurationProperties(prefix = "another")
    public AnotherComponent anotherComponent() {
        return new AnotherComponent();
    }
}
```
Any JavaBean property defined with the another prefix is mapped onto that AnotherComponent bean

- Relaxed Binding    

@ConfigurationProperties(prefix = "my.main-project.person") can be mapped to

| Property |	Note |
|----------|---------|
|my.main-project.person.first-name|Kebab case, which is recommended for use in .properties and .yml files.|
|my.main-project.person.firstName|Standard camel case syntax.|
|my.main-project.person.first_name|Underscore notation, which is an alternative format for use in .properties and .yml files.|
|MY_MAINPROJECT_PERSON_FIRSTNAME|Upper case format, which is recommended when using system environment variables.|

When binding to Map properties, need to use a special bracket notation so that the original key value is preserved. If the key is not surrounded by [], any characters that are not alpha-numeric, - or . are removed.
```
my.map.[/key1]=value1
my.map.[/key2]=value2
my.map./key3=value3    
```    
    
To convert a property name in the canonical-form to an environment variable name:
     - Replace dots (.) with underscores (_).
     - Remove any dashes (-).
     - Convert to uppercase.

To bind to a List, the element number should be surrounded with underscores in the variable name. For example, the configuration property my.service[0].other would use an environment variable named MY_SERVICE_0_OTHER.

- Duration for java.time.Duration

Use the following formats:
    - A regular long representation (using milliseconds as the default unit unless a @DurationUnit has been specified)
    - The standard ISO-8601 format used by java.time.Duration
    - A more readable format where the value and the unit are coupled (10s means 10 seconds, ns,us,ms,s,m,h,d)
```
import java.time.Duration;
import java.time.temporal.ChronoUnit;

import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.boot.context.properties.ConstructorBinding;
import org.springframework.boot.context.properties.bind.DefaultValue;
import org.springframework.boot.convert.DurationUnit;

@ConfigurationProperties("my")
@ConstructorBinding
public class MyProperties {
    // fields...
    private final Duration sessionTimeout;
    private final Duration readTimeout;

    public MyProperties(@DurationUnit(ChronoUnit.SECONDS) @DefaultValue("30s") Duration sessionTimeout,
            @DefaultValue("1000ms") Duration readTimeout) {
        this.sessionTimeout = sessionTimeout;
        this.readTimeout = readTimeout;
    }

    // getters...
    public Duration getSessionTimeout() {
        return this.sessionTimeout;
    }

    public Duration getReadTimeout() {
        return this.readTimeout;
    }
}
```
    
- Period for java.time.Period   

Use the following formats:    
     - An regular int representation (using days as the default unit unless a @PeriodUnit has been specified)
     - The standard ISO-8601 format used by java.time.Period
     - A simpler format where the value and the unit pairs are coupled (1y3d means 1 year and 3 days; y,w,m,d)

- Data Sizes for DataSize

Use the following formats:    
     - A regular long representation (using bytes as the default unit unless a @DataSizeUnit has been specified)
     - A more readable format where the value and the unit are coupled (10MB means 10 megabytes; B,KB,MB,GB,TB)
```
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.boot.context.properties.ConstructorBinding;
import org.springframework.boot.context.properties.bind.DefaultValue;
import org.springframework.boot.convert.DataSizeUnit;
import org.springframework.util.unit.DataSize;
import org.springframework.util.unit.DataUnit;

@ConfigurationProperties("my")
@ConstructorBinding
public class MyProperties {
    // fields...
    private final DataSize bufferSize;
    private final DataSize sizeThreshold;
    public MyProperties(@DataSizeUnit(DataUnit.MEGABYTES) @DefaultValue("2MB") DataSize bufferSize,
            @DefaultValue("512B") DataSize sizeThreshold) {
        this.bufferSize = bufferSize;
        this.sizeThreshold = sizeThreshold;
    }

    // getters...
    public DataSize getBufferSize() {
        return this.bufferSize;
    }
    public DataSize getSizeThreshold() {
        return this.sizeThreshold;
    }
}
```    

- @ConfigurationProperties Validation    

Spring Boot attempts to validate @ConfigurationProperties classes whenever they are annotated with Spring’s @Validated annotation. 

```
@ConfigurationProperties("my.service")
@Validated
public class MyProperties {
    @NotNull
    private InetAddress remoteAddress;

    @Valid
    private final Security security = new Security();

    // getters/setters...
    public InetAddress getRemoteAddress() {
        return this.remoteAddress;
    }

    public void setRemoteAddress(InetAddress remoteAddress) {
        this.remoteAddress = remoteAddress;
    }

    public Security getSecurity() {
        return this.security;
    }

    public static class Security {
        @NotEmpty
        private String username;

        // getters/setters...
        public String getUsername() {
            return this.username;
        }
        public void setUsername(String username) {
            this.username = username;
        }
    }
}    
```    
