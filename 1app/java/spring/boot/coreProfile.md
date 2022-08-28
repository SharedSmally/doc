# Spring Boot

## Core Features
    
### Profiles
Any @Component, @Configuration or @ConfigurationProperties can be marked with @Profile to limit when it is loaded,

```
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Profile;

@Configuration(proxyBeanMethods = false)
@Profile("production")
public class ProductionConfiguration {
    // ...
}
```

The **spring.profiles.active** Environment property is used to specify which profiles are active:
```
spring.profiles.active=dev,hsqldb   # in application.properties
spring.profiles.default=none        # If no profile is active, a default profile is enabled. 
                                    # The name of the default profile is default
--spring.profiles.active=dev,hsqldb # on the command line
```

The **spring.profiles.include** property can be used to add active profiles on top of those activated by the **spring.profiles.active** property:
```
spring.profiles.include[0]=common
spring.profiles.include[1]=local
```
**spring.profiles.active**, **spring.profiles.default** and **spring.profiles.include** can only be used in non-profile specific documents. They cannot be included in profile specific files or documents activated by **spring.config.activate.on-profile**.

A profile group define a logical name for a related group of profiles.
```
spring.profiles.group.production[0]=proddb
spring.profiles.group.production[1]=prodmq
```
Use *--spring.profiles.active=production* to active the *production*, *proddb* and *prodmq* profiles in one hit.

The active profiles can be set by calling SpringApplication.setAdditionalProfiles() before the application runs, or Spring’s ConfigurableEnvironment interface.

### Logging

By default Logback is used for logging when using the Starters. 

- spring.output.ansi.enabled: support ANSI, color output
- logging.file.name or logging.file.path: for logging File Output
- logging.logback.rollingpolicy.\*: for File Rotation. Use the corresponding config files for other logging framework.
- logging.level.<logger-name>=<level>: for Log Level: ERROR, WARN, INFO, DEBUG, or TRACE.
- logging.group.xxx: for logging group, the group can be set using logging.level.xxx=<level>
- logging.register-shutdown-hook=false/true: trigger log system cleanup when the JVM exits is provided.
- logging.\*: Custom Log Configuration    
- logback.xml or logback-spring.xml to config Logback configuration
     - <springProfile>: include or exclude sections of configuration based on the active Spring profiles.
     - <springProperty>: expose properties from the Spring Environment for use within Logback.

### Internationalization
    
