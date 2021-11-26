
# Feign

The Feign is a declarative web service (HTTP client) developed by Netflix. Its aim is to simplify the HTTP API clients. 
It is a Java to HTTP client binder. Create an interface, and annotate it if need to use Feign,. 
It provides pluggable annotation support, including Feign annotations and JAX-RS annotations.

It is a library for creating REST API clients. It makes web service clients easier. The developers can use declarative 
annotations to call the REST services instead of writing representative boilerplate code.

Spring Cloud OpenFeign provides OpenFeign integrations for Spring Boot apps through auto-configuration and binding to 
the Spring Environment. Without Feign, in Spring Boot application, we use RestTemplate to call the User service. 
To use the Feign, we need to add spring-cloud-starter-openfeign dependency in the pom.xml file.

The other additional thing that Feign provides is:  it integrates with the Ribbon (client-side load balancing framework).

- Add Feign dependency:
```
    <dependency>  
    <groupId>org.springframework.cloud</groupId>    
    <artifactId>spring-cloud-starter-feign</artifactId>  
    </dependency>  
```
-  Enable the Feign to scan the clients by adding the annotation @EnableFeignClients in the Application file.
```
import org.springframework.cloud.openfeign.EnableFeignClients;  

@EnableFeignClients("com.xxx.service")  
```
- Create a Feign proxy to talk to external microservices: Add an annotation @FeignClient. Pass the attributes name and URL.

```
// check REST Service: http://localhost:8000/currency-exchange/from/USD/to/INR
@FeignClient(name="currency-exchange", url="localhost:8000")  

```

## Client-Side Load Balancing with Ribbon
