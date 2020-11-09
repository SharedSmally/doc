# Spring Service Registration and Discovery 
- [Reference]()
- [Eureka](https://cloud.spring.io/spring-cloud-netflix/multi/multi__service_discovery_eureka_clients.html)
- [Sample](https://spring.io/guides/gs/service-registration-and-discovery/)

## Implementations
- Eureka Discovery Server/Client: Eureka is the Netflix Service Discovery Server and Client
- Apache Zookeeper Discovery
- Cloud Foundary Discovery
- Consul Discovery

## Server:
- Dependencies: netflix-eureka-server
```
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.netflix.eureka.server.EnableEurekaServer;

@EnableEurekaServer
@SpringBootApplication
public class ServiceRegistrationAndDiscoveryServiceApplication {

	public static void main(String[] args) {
		SpringApplication.run(ServiceRegistrationAndDiscoveryServiceApplication.class, args);
	}
}
```
use the spring-cloud-starter-netflix-eureka-server dependency and @EnableEurekaServer to run own server.

- src/main/resources/application.properties
```
server.port=8761

eureka.client.register-with-eureka=false
eureka.client.fetch-registry=false

logging.level.com.netflix.eureka=OFF
logging.level.com.netflix.discovery=OFF
```
## Client
- Dependencies: netflix-eureka-client and server; actuator and web
```
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.ServiceInstance;
import org.springframework.cloud.client.discovery.DiscoveryClient;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@EnableDiscoveryClient
@RestController
@SpringBootApplication
public class ServiceRegistrationAndDiscoveryClientApplication {

	public static void main(String[] args) {
		SpringApplication.run(ServiceRegistrationAndDiscoveryClientApplication.class, args);
	}
  
	@Autowired
	private DiscoveryClient discoveryClient;

	@RequestMapping("/service-instances/{applicationName}")
	public List<ServiceInstance> serviceInstancesByApplicationName(
			@PathVariable String applicationName) {
		return this.discoveryClient.getInstances(applicationName);
	}
}
```
The Spring Boot application with @EnableEurekaClient will try to contact a Eureka server on http://localhost:8761 (the default value of eureka.client.serviceUrl.defaultZone).

- In src/main/resources/bootstrap.properties:
```
spring.application.name=a-bootiful-client
```
When a client registers with Eureka, it provides meta-data about itself — such as host, port, health indicator URL, home page, and other details. Eureka receives heartbeat messages from each instance belonging to a service. If the heartbeat fails over a configurable timetable, the instance is normally removed from the registry.

Having spring-cloud-starter-netflix-eureka-client on the classpath makes the app into both a Eureka “instance” (it registers itself) and a “client” (it can query the registry to locate other services). The instance behaviour is driven by eureka.instance.* configuration keys, but the defaults are fine if you ensure that your application has a value for spring.application.name (this is the default for the Eureka service ID or VIP).

- In application.properties:
```
eureka.client.serviceUrl.defaultZone = http://localhost:8761/eureka
```
eureka.client.serviceUrl.defaultZone indicates the location of the Eureka server.

## Consumer
- Use Feign to import interface service
- Use Ribbon via @LoadBalanced and RestTemplate to access the service. [Sample](https://stackabuse.com/spring-cloud-service-discovery-with-eureka/)
### End Service Setup (Movie Service):
```
@SpringBootApplication
@EnableEurekaClient
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
}

@RestController
public class MovieController {

    private static List<Movie> movieList = new ArrayList<>();
    static {
        movieList.add(new Movie(1, "movie-1", "summary-1"));
        movieList.add(new Movie(2, "movie-2", "summary-2"));
        movieList.add(new Movie(3, "movie-3", "summary-3"));
    }

    @GetMapping("/movies")
    public ResponseEntity<?> getMovies() {
        return ResponseEntity.ok(movieList);
    }
}

In application.properties:
server.port = 8060
spring.application.name = movie-service
eureka.client.serviceUrl.defaultZone = http://localhost:8761/eureka/
```
Along with specifying the URL of the server, we need to specify the application name. It will be this name that other service use for making REST calls.

With that, we've registered our service to the server, and any other registered service can call it using spring.application.name.

### Client Service Setup:Recommendation Service

Build our client service that will call movie-service
```
@RestController
public class RecommendationController {
    @Autowired
    RestTemplate restTemplate;

    @RequestMapping(value = "/recommendations", method = RequestMethod.GET)
    @ResponseBody
    public Movie[] recommendations() {
        Movie[] result = restTemplate.getForObject("http://movie-service/movies", Movie[].class);
        return result;
    }
}

@SpringBootApplication
@EnableEurekaClient
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
    
    @LoadBalanced  # use client-side load balancing by Ribbon
    @Bean
    RestTemplate restTemplate() {   
        return new RestTemplate();
    }
}

In application.properties:
server.port = 8050
spring.application.name = recommendation-service
eureka.client.serviceUrl.defaultZone = http://localhost:8761/eureka/

```
@Autowired the Ribbon-enabled RestTemplate and use it to call the movie-service. Do not have to specify the hostname or the port anywhere.

What Spring internally does here is because it's registered with the Eureka server, it stores the list of all the services and its running instances locally. When we made a REST call to the movie-service like this (instead of providing a hostname and port), it substitutes the actual endpoint URLs from the previously stored list and then makes the REST call.
