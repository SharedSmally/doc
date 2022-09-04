# Spring Boot
## [Spring Boot Actuator](https://docs.spring.io/spring-boot/docs/2.7.3/reference/html/actuator.html)

## Enabling Production-ready Features
The spring-boot-actuator module provides all of Spring Boot’s production-ready features
```
<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-actuator</artifactId>
    </dependency>
</dependencies>
```
## Endpoints: [Actuator Web API](https://docs.spring.io/spring-boot/docs/2.7.3/actuator-api/htmlsingle/)
Spring Boot includes a number of built-in endpoints and can add applicaion ones. Can enable or disable each 
individual endpoint and expose them (make them remotely accessible) over HTTP or JMX. 


| ID | 	Description |
|----|--------------|
| auditevents | Exposes audit events information for the current application. Requires an AuditEventRepository bean.
| beans | Displays a complete list of all the Spring beans in your application.|
| caches | Exposes available caches.|
| conditions | Shows the conditions that were evaluated on configuration and auto-configuration classes and the reasons why they did or did not match.|
| configprops | Displays a collated list of all @ConfigurationProperties.|
|env|Exposes properties from Spring’s ConfigurableEnvironment.|
|flyway|Shows any Flyway database migrations that have been applied. Requires one or more Flyway beans.|
|health|Shows application health information.|
|httptrace|Displays HTTP trace information (by default, the last 100 HTTP request-response exchanges). Requires an HttpTraceRepository bean.|
|info|Displays arbitrary application info.|
|integrationgraph|Shows the Spring Integration graph. Requires a dependency on spring-integration-core.|
|loggers|Shows and modifies the configuration of loggers in the application.|
|liquibase| Shows any Liquibase database migrations that have been applied. Requires one or more Liquibase beans.|
|metrics|Shows “metrics” information for the current application.|
|mappings|Displays a collated list of all @RequestMapping paths.|
|quartz | Shows information about Quartz Scheduler jobs.| 
| scheduledtasks| Displays the scheduled tasks in your application.| 
| sessions| Allows retrieval and deletion of user sessions from a Spring Session-backed session store. Requires a servlet-based web application that uses Spring Session.| 
| shutdown| Lets the application be gracefully shutdown. Disabled by default.| 
| startup| Shows the startup steps data collected by the ApplicationStartup. Requires the SpringApplication to be configured with a BufferingApplicationStartup.| 
| threaddump| Performs a thread dump.| 

For web application (Spring MVC, Spring WebFlux, or Jersey):
| ID | 	Description| 
|----|-------------|
|heapdump| Returns a heap dump file. On a HotSpot JVM, an HPROF-format file is returned. On an OpenJ9 JVM, a PHD-format file is returned.| 
| jolokia| Exposes JMX beans over HTTP when Jolokia is on the classpath (not available for WebFlux). Requires a dependency on jolokia-core.| 
| logfile| Returns the contents of the logfile (if the logging.file.name or the logging.file.path property has been set). Supports the use of the HTTP Range header to retrieve part of the log file’s content.| 
| prometheus| Exposes metrics in a format that can be scraped by a Prometheus server. Requires a dependency on micrometer-registry-prometheus.| 

By default, all endpoints except for shutdown are enabled. To configure the enablement of an endpoint, use its
**management.endpoint.\<id\>.enabled** property, or **management.endpoints.[jmx|web].exposure.[exclude|include]**. 

### Implementing Custom Endpoints
- If adding a @Bean annotated with @Endpoint, any methods annotated with @ReadOperation(GET), @WriteOperation(POST), or
@DeleteOperation(DELETE) are automatically exposed over JMX and, in a web application, over HTTP as well.
- @JmxEndpoint or @WebEndpoint: technology-specific endpoints
- @EndpointWebExtension and @EndpointJmxExtension: provide technology-specific operations to augment an existing endpoint.
- @ControllerEndpoint and @RestControllerEndpoint to implement an endpoint that is exposed only by Spring MVC or Spring WebFlux. 

### Auto-configured HealthIndicators
- management.endpoint.health.show-details/management.endpoint.health.show-components: never/always/when-authorized

Health information is collected from the content of a **HealthContributorRegistry** (by default, all HealthContributor instances 
defined in ApplicationContext). Spring Boot includes a number of auto-configured HealthContributors.

A **HealthContributor** can be either a **HealthIndicator** or a **CompositeHealthContributor**. A HealthIndicator provides actual 
health information, including a Status. A CompositeHealthContributor provides a composite of other HealthContributors. 

Can use the HealthContributorRegistry to register and unregister health indicators at runtime.

- Custom HealthIndicators
```
import org.springframework.boot.actuate.health.Health;
import org.springframework.boot.actuate.health.HealthIndicator;
import org.springframework.stereotype.Component;

@Component
public class MyHealthIndicator implements HealthIndicator {

    @Override
    public Health health() {
        int errorCode = check();
        if (errorCode != 0) { return Health.down().withDetail("Error Code", errorCode).build(); }
        return Health.up().build();
    }
    private int check() {
        // perform some specific health check
        return ...
    }
}
```
- Custom Reactive HealthIndicators
```
@Component
public class MyReactiveHealthIndicator implements ReactiveHealthIndicator {
    @Override
    public Mono<Health> health() {
        return doHealthCheck().onErrorResume((exception) ->
            Mono.just(new Health.Builder().down(exception).build()));
    }

    private Mono<Health> doHealthCheck() {
        // perform some specific health check
        return ...
    }
}
```
Health indicators can be grouped using **management.endpoint.health.group.\<name\>** property, and specify a list of health indicator IDs to include or exclude. 


### Kubernetes Probes

Actuator gathers the “Liveness” and “Readiness” information from the ApplicationAvailability interface and uses that information in 
dedicated health indicators: LivenessStateHealthIndicator and ReadinessStateHealthIndicator. These indicators are shown on the 
global health endpoint ("/actuator/health"). They are also exposed as separate HTTP Probes by using health groups:
"/actuator/health/liveness" and "/actuator/health/readiness".

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

### Custom Application Information
When the env contributor is enabled, you can customize the data exposed by the info endpoint by setting info.* Spring properties.
All Environment properties under the info key are automatically exposed.
- Applicaion Info
- Git Info
- Build Info
- Java Info
- OS Info
- Custom InfoContributors
```
@Component
public class MyInfoContributor implements InfoContributor {
    @Override
    public void contribute(Info.Builder builder) {
        builder.withDetail("example", Collections.singletonMap("key", "value"));
    }
}
```
##  Monitoring and Management over HTTP
```
server.port=8443
server.ssl.enabled=true
server.ssl.key-store=classpath:store.jks
server.ssl.key-password=secret

management.endpoints.web.base-path=/manage
management.endpoints.web.path-mapping.health=healthcheck
management.server.port=8081   # -1 to disable it
management.server.address=127.0.0.1
management.server.ssl.enabled=true  # false
management.server.ssl.key-store=classpath:management.jks
management.server.ssl.key-password=secret
```

## Monitoring and Management over JMX
Spring Boot exposes the most suitable MBeanServer as a bean with an ID of mbeanServer. Any of beans that are annotated with Spring JMX annotations 
(@ManagedResource, @ManagedAttribute, or @ManagedOperation) are exposed to it.

```
spring.jmx.enabled=true
spring.jmx.unique-names=true
management.endpoints.jmx.domain=com.example.myapp
management.endpoints.jmx.exposure.exclude=* # disable JMX Endpoints
```
### Using Jolokia for JMX over HTTP
Jolokia is a JMX-HTTP bridge that provides an alternative method of accessing JMX beans using HTTP. 
```
<dependency>
    <groupId>org.jolokia</groupId>
    <artifactId>jolokia-core</artifactId>
</dependency>
```

## Loggers level:
- TRACE
- DEBUG
- INFO
- WARN
- ERROR
- FATAL
- OFF
- null

## Metrics
Spring Boot Actuator provides dependency management and auto-configuration for Micrometer, an application metrics facade that supports many monitoring systems.
It auto-configures a composite **MeterRegistry** and adds a registry to the composite for each of the supported implementations found on the classpath. 
Need to have a dependency on micrometer-registry-{system} in the runtime classpath to configure the registry.
### Monitor Systems
- Elastic
- Graphite 
- Influx
- Prometheus
- Simple (in-memory)

### Supported Metrics and Meters
- @Timed Annotation Support
```
import java.util.List;

import io.micrometer.core.annotation.Timed;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@Timed
public class MyController {
    @GetMapping("/api/addresses")
    public List<Address> listAddress() {
        return ...
    }

    @GetMapping("/api/people")
    @Timed(extraTags = { "region", "us-east-1" })
    @Timed(value = "all.people", longTask = true)
    public List<Person> listPeople() {
        return ...
    }\
}
```
### Register Cusomize Metrics
```
import io.micrometer.core.instrument.MeterRegistry;
import io.micrometer.core.instrument.Tags;

import org.springframework.stereotype.Component;

@Component
public class MyBean {
    private final Dictionary dictionary;
    public MyBean(MeterRegistry registry) {
        this.dictionary = Dictionary.load();
        registry.gauge("dictionary.size", Tags.empty(), this.dictionary.getWords().size());
    }

}
```
If metrics depend on other beans, use a MeterBinder to register them:
```
import io.micrometer.core.instrument.Gauge;
import io.micrometer.core.instrument.binder.MeterBinder;
import org.springframework.context.annotation.Bean;

public class MyMeterBinderConfiguration {
    @Bean
    public MeterBinder queueSize(Queue queue) {
        return (registry) -> Gauge.builder("queueSize", queue::size).register(registry);
    }
}
```

### Cusomize Metrics
Use the io.micrometer.core.instrument.config.MeterFilter interface to custom a specific Meter instances:
```
@Configuration(proxyBeanMethods = false)
public class MyMetricsFilterConfiguration {
    @Bean
    public MeterFilter renameRegionTagMeterFilter() {
        return MeterFilter.renameTag("com.example", "mytag.region", "mytag.area");
    }
}
```

## Auditing
Once Spring Security is in play, Spring Boot Actuator has a flexible audit framework that publishes events (by default,
“authentication success”, “failure” and “access denied” exceptions).

To enable auditing, provide a bean of type AuditEventRepository in the application’s configuration, such as InMemoryAuditEventRepository. 

To customize published security events, provide custom implementations of AbstractAuthenticationAuditListener and AbstractAuthorizationAuditListener.

Can use the audit services for application business events, either inject the AuditEventRepository bean into components and use that directly or publish an AuditApplicationEvent with the Spring ApplicationEventPublisher (by implementing ApplicationEventPublisherAware).

## HTTP Tracing
Enable HTTP Tracing by providing a bean of type HttpTraceRepository in the application’s configuration, such as InMemoryHttpTraceRepository, or Zipkin or Spring Cloud Sleuth 
for puoduction, or create customized HttpTraceRepository.

## Process Monitoring

Two classes to create files for process monitoring:
- ApplicationPidFileWriter creates a file that contains the application PID (by default, in the application directory with a file name of application.pid).
- WebServerPortFileWriter creates a file (or files) that contain the ports of the running web server (by default, in the application directory with a file name of application.port).
```
org.springframework.context.ApplicationListener=\
   org.springframework.boot.context.ApplicationPidFileWriter,\
   org.springframework.boot.web.context.WebServerPortFileWriter
```

## Cloud Foundry Support
The /cloudfoundryapplication path provides an alternative secured route to all @Endpoint beans.
```
server.servlet.context-path=/app   #Cloud Foundry endpoints: /app/cloudfoundryapplication/*
management.cloudfoundry.enabled=false
management.cloudfoundry.skip-ssl-validation=true

```
