# [Spring Cloud Netflix](https://spring.io/projects/spring-cloud-netflix)
- [Reference](https://docs.spring.io/spring-cloud-netflix/docs/2.2.5.RELEASE/reference/html/)

## Netflix OSS components
- Service Discovery/Registry: Eureka 
- Circuit Breaker: Hystrix clients and dashboard
- Declarative REST Client: Feign 
- Client Side Load Balancer: Ribbon
- External Configuration: Archaius
- Router and Filter: Zuul

## Eureka
- [Tutorial](https://medium.com/swlh/spring-cloud-service-discovery-with-eureka-16f32068e5c7): 
![Architecture](https://miro.medium.com/max/700/1*ITGONeSNR8GBm-UznTNODA.png)
- [Tutorial](https://www.baeldung.com/spring-cloud-netflix-eureka)
- Inter-Microservice Communication via Eureka
![imc](https://miro.medium.com/max/700/1*_twIuTE0ll6IB9C0TT0bfg.png)

Client-side service discovery allows services to find and communicate with each other without hard-coding hostname and port. The only ‘fixed point' in such an architecture consists of a service registry with which each service has to register.

Three microservices:
- a service registry (Eureka Server),
- a REST service which registers itself at the registry (Eureka Client) and
- a web application, which is consuming the REST service as a registry-aware client (Spring Cloud Netflix Feign Client).
    
## Eureka Client Server Communication
- Register: Eureka client registers the information about the running instance to the Eureka server.
- Renew: Eureka client needs to renew the lease by sending heartbeats every 30 seconds. The renewal informs the Eureka server that the instance is still alive.
- Special Note: Eureka server doesn’t poll service instances (client) to find out their availability. Instead, clients send a heartbeat to Eureka server to inform their availability.
- Fetch Registry: Eureka clients fetches the registry information from the server and caches it locally. After that, the clients use that information to find other services.
- Cancel: Eureka client sends a cancel request to Eureka server on shutdown. This removes the instance from the server’s instance registry thereby effectively taking the instance out of traffic.


## Feign Client
Feign is discovery-aware Spring RestTemplate using interfaces to communicate with endpoints. This interfaces will be automatically implemented at runtime and instead of service-urls, it is using service-names.

Without Feign we would have to autowire an instance of EurekaClient into our controller with which we could receive a service-information by service-name as an Application object. We would use this Application to get a list of all instances of this service, pick a suitable one and use this InstanceInfo to get hostname and port. 
```
@Autowired
private EurekaClient eurekaClient;
	 
public void doRequest() {
	    Application application = eurekaClient.getApplication("spring-cloud-eureka-client");
	    InstanceInfo instanceInfo = application.getInstances().get(0);
	    String hostname = instanceInfo.getHostName();
	    int port = instanceInfo.getPort();
      // A RestTemplate can also be used to access Eureka client-services by name,
	    // ...
	}
```
To enable it, need to annotate a @Configuration with @EnableFeignClients. 
To use it, we simply annotate an interface with @FeignClient(“service-name”) and auto-wire it into a controller.

- The interface shared between server and client:
```
@FeignClient("spring-cloud-eureka-client")
public interface GreetingClient {
	    @RequestMapping("/greeting")
	    String greeting();
}
```

- The consumer
```
@SpringBootApplication
@EnableFeignClients
@Controller
public class FeignClientApplication {
	    @Autowired
	    private GreetingClient greetingClient;
	 
	    public static void main(String[] args) {
	        SpringApplication.run(FeignClientApplication.class, args);
	    }
	 
	    @RequestMapping("/get-greeting")
	    public String greeting(Model model) {
	        model.addAttribute("greeting", greetingClient.greeting());
	        return "greeting-view";
	    }
	}
```
- The provider, EurekaClient implements the service:
```
@SpringBootApplication
@RestController
public class EurekaClientApplication implements GreetingController { 
	    @Autowired
	    @Lazy
	    private EurekaClient eurekaClient;
	 
	    @Value("${spring.application.name}")
	    private String appName;
	 
	    public static void main(String[] args) {
	        SpringApplication.run(EurekaClientApplication.class, args);
	    }
	 
	    @Override
	    public String greeting() {
	        return String.format(
	          "Hello from '%s'!", eurekaClient.getApplication(appName).getName());
	    }
	}
```
Config the client to locate the registry: in application.yml with a configured Spring application name to uniquely identify our client in the list of registered applications.
```
	spring:
	  application:
	    name: spring-cloud-eureka-client  # match with FeignClient annotation
	server:
	  port: 0
	eureka:
	  client:
	    serviceUrl:
	      defaultZone: ${EUREKA_URI:http://localhost:8761/eureka}
	  instance:
	    preferIpAddress: true
```




    
