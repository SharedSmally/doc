# [Actuator](https://docs.spring.io/spring-boot/docs/2.2.0.RELEASE/reference/html/production-ready-features.html)
## Dependency
```
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-actuator</artifactId>
		</dependency>
```

## Configurations
- [Reference](https://docs.spring.io/spring-boot/docs/2.2.0.RELEASE/reference/html/appendix-application-properties.html#actuator-properties)
- the Actuator Endpoints HTTP Port or Address
    - management.server.port: the application listening port
    - management.server.address: the network IP address that the server is able to bind.
    - management.server.ssl.xxx: SSL configurations
    - management.server.servlet.context-path: Management endpoint context-path (for instance, `/management`). Requires a custom management.server.port.
    
- Enable/Expose Endpoints
    - management.endpoint.xxx.cache.time-to-live: Maximum time that a response can be cached.
    - management.endpoint.xxx.enabled: Whether to enable the xxx endpoint.
    - management.health.xxx.enabled: Whether to enable xxx health check.
    - management.metrics.enable.*: Whether meter IDs starting-with the specified name should be enabled. The longest match wins, the key `all` can also be used to configure all meters.
    - management.endpoints.web.exposure.include: Endpoint IDs that should be included or '*' for all.
    - management.endpoints.web.exposure.exclude> Endpoint IDs that should be excluded or '*' for all.
    - management.metrics.export.xxx.enabled: Whether exporting of metrics to xxx is enabled.
    - management.metrics.export.xxx.yyy: Whether exporting of metrics to xxx is enabled.
    
## Add New Metrics
- Boot 2.0: [MicroMeter](https://www.baeldung.com/micrometer)
     - Add depdency for micrometer
```
	<dependency>
  		<groupId>io.micrometer</groupId>
  		<artifactId>micrometer-registry-prometheus</artifactId>
	</dependency>
```
     - Registe metric with MeterRegistry(Replacing CounterService)
```
@Autowired
private MeterRegistry registry;
private List<String> statusList;
 
@Override
public void increaseCount(final int status) {
    String counterName = "counter.status." + status;
    registry.counter(counterName).increment(1);
    if (!statusList.contains(counterName)) {
        statusList.add(counterName);
    }
}
```
or 
```
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import io.micrometer.core.instrument.Counter;
import io.micrometer.core.instrument.MeterRegistry;

@RestController
public class MyController {
    private final Counter myCounter;
    public MyController(MeterRegistry meterRegistry) {
        // Create the counter using the helper method on the builder
        myCounter = meterRegistry.counter("my.counter", "mytagname", "mytagvalue"); //name,tagname,tagvalue
    }

    @GetMapping("/")
    public String getSomething() {
    	myCounter.increment();
    	return "hello, world";
    }
}
```
     - Exporting Counts Using MeterRegistry
```
@Scheduled(fixedDelay = 60000)
private void exportMetrics() {
    ArrayList<Integer> statusCount = new ArrayList<Integer>();
    for (String status : statusList) {
         Search search = registry.find(status);
         if (search != null) {
              Counter counter = search.counter();
              statusCount.add(counter != null ? ((int) counter.count()) : 0);
              registry.remove(counter);
         } else {
              statusCount.add(0);
         }
    }
    statusMetricsByMinute.add(statusCount);
}
```
   - Publishing Metrics Using Meters
```
@Scheduled(fixedDelay = 60000)
private void exportMetrics() {
    ArrayList<Integer> lastMinuteStatuses = initializeStatuses(statusList.size()); 
    for (Meter counterMetric : publicMetrics.getMeters()) {
        updateMetrics(counterMetric, lastMinuteStatuses);
    }
    statusMetricsByMinute.add(lastMinuteStatuses);
}
 
private void updateMetrics(final Meter counterMetric, final ArrayList<Integer> statusCount) {
    String status = "";
    int index = -1;
    int oldCount = 0;
 
    if (counterMetric.getId().getName().contains("counter.status.")) {
        status = counterMetric.getId().getName().substring(15, 18); // example 404, 200
        appendStatusIfNotExist(status, statusCount);
        index = statusList.indexOf(status);
        oldCount = statusCount.get(index) == null ? 0 : statusCount.get(index);
        statusCount.set(index, (int)((Counter) counterMetric).count() + oldCount);
    }
}
```
- [REST Metrics](https://www.baeldung.com/spring-rest-api-metrics)
- [Spring Metrics](https://docs.spring.io/spring-metrics/docs/current/public/prometheus)

## Add New EndPoint
```
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import org.springframework.boot.actuate.endpoint.annotation.DeleteOperation;
import org.springframework.boot.actuate.endpoint.annotation.Endpoint;
import org.springframework.boot.actuate.endpoint.annotation.ReadOperation;
import org.springframework.boot.actuate.endpoint.annotation.Selector;
import org.springframework.boot.actuate.endpoint.annotation.WriteOperation;
import org.springframework.stereotype.Component;

@Component
@Endpoint(id = "features")
public class FeaturesEndpoint { 
    private Map<String, Feature> features = new ConcurrentHashMap<>();
 
    @ReadOperation
    public Map<String, Feature> features() {
        return features;
    }
 
    @ReadOperation
    public Feature feature(@Selector String name) {
        return features.get(name);
    }
 
    @WriteOperation
    public void configureFeature(@Selector String name, Feature feature) {
        features.put(name, feature);
    }
 
    @DeleteOperation
    public void deleteFeature(@Selector String name) {
        features.remove(name);
    }
 
    public static class Feature {
        private Boolean enabled;
         // [...] getters and setters 
    }
}
```
To get the endpoint, we need a bean. In our example, we're using @Component for this. Also, we need to decorate this bean with @Endpoint.

The path of our endpoint is determined by the id parameter of @Endpoint, in our case, it'll route requests to /actuator/features.

Once ready, we can start defining operations using:
- @ReadOperation – it'll map to HTTP GET
- @WriteOperation – it'll map to HTTP POST
- @DeleteOperation – it'll map to HTTP DELETE

## Extend existing EndPoint
We can easily extend the behavior of a predefined endpoint using the @EndpointExtension annotations, or its more concrete specializations @EndpointWebExtension or @EndpointJmxExtension:
```
@Component
@EndpointWebExtension(endpoint = InfoEndpoint.class)
public class InfoWebEndpointExtension {
     private InfoEndpoint delegate;
     // standard constructor
     @ReadOperation
    public WebEndpointResponse<Map> info() {
        Map<String, Object> info = this.delegate.info();
        Integer status = getStatus(info);
        return new WebEndpointResponse<>(info, status);
    } 
    private Integer getStatus(Map<String, Object> info) {
        // return 5xx if this is a snapshot
        return 200;
    }
}
```
## Enable All Endpoints
In order to access the actuator endpoints using HTTP, we need to both enable and expose them. 
By default, all endpoints but /shutdown are enabled.  Only the /health and /info endpoints are exposed by default.

- Expose all endpoints :
```
management.endpoints.web.exposure.include=*
```
- Explicitly enable a specific endpoint (for example /shutdown):
'''
management.endpoint.shutdown.enabled=true
```
- Expose all enabled endpoints except one (for example /loggers):
```
management.endpoints.web.exposure.include=*
management.endpoints.web.exposure.exclude=loggers
```
## [How To](https://docs.spring.io/spring-boot/docs/2.2.0.RELEASE/reference/html/howto.html#howto-actuator)
## [Samples](https://www.baeldung.com/spring-boot-actuators)
