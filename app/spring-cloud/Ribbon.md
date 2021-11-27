# Ribbon

Netflix Ribbon is a Part of Netflix OSS. It is a cloud library that provides the client-side load balancing for HTTP and TCP client. 
It automatically interacts with Netflix Service Discovery (Eureka) because it is a member of the Netflix family.

## Features
- Load balancing
- Fault tolerance
- Multiple protocol support in Asynchronous model
- Caching and batching

## Modules
- ribbon: API to integrate load balancing, fault-tolerance, caching, and
- ribbon-loadbalancer: Load balancer API that is independently or with other modules.
- ribbon eureka: Uses Eureka client that provides a dynamic server list for the Spring Cloud.
- ribbon-transport: Transport client that supports HTTP, TCP, and UDP These protocols use RxNetty with load balancing capability.
- ribbon-httpclient: REST client built on top of Apache HttpClient integrated with load balancers.
- ribbon-core: The Client Configuration API.

## Add Ribbon
- Add Ribbon starter
```
		<dependency>
			<groupId>org.springframework.cloud</groupId>
			<artifactId>spring-cloud-starter-netflix-ribbon</artifactId>
			<version>2.2.10.RELEASE</version>
		</dependency>
```
- Enable Ribbon

Add an annotation @RibbonClient and specify the name of the service to talk to. 
Ribbon client provide the declarative configuration for a client. 
Remove the attribute URL in the annotation @FeignClient 
```
//Enabling feign for REST Service using Proxy 
//@FeignClient(name="myservice", url="localhost:8000") //no LB 
@FeignClient(name="myservice")  
//enabling ribbon for LB 
@RibbonClient(name="myservice")  
public interface MyServiceProxy   
{  
   @GetMapping("/currency-exchange/from/{from}/to/{to}")       //where {from} and {to} are path variable  
   public CurrencyConversionBean retrieveExchangeValue(
      @PathVariable("from") String from, @PathVariable("to") String to); 
} 
```

- Update application.properties to figure the list of servers for the service
``` 
    name-of-the-service.ribbon.listOfServers=URLs  
``` 
Example:
```
spring.application.name=custom-service  
server.port=8100  
myservice.ribbon.listOfServers=http://localhost:8000, http://localhost:8001 
```
