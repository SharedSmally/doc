# Circuit Breaker
- [Reference]()
- [Sample](https://spring.io/guides/gs/circuit-breaker/)

##
- Dependencies: netflix-hystrix
- Set up a Server Microservice Application
```
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;

@RestController
@SpringBootApplication
public class CircuitBreakerBookstoreApplication {
  @RequestMapping(value = "/recommended")
  public String readingList(){
    return "Spring rest service";
  }

  public static void main(String[] args) {
     SpringApplication.run(CircuitBreakerBookstoreApplication.class, args);
  }
}
```
src/main/resources/application.properties:
```
server.port=8090
```
- Set up a Client Microservice Application
```
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.client.RestTemplateBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cloud.client.circuitbreaker.EnableCircuitBreaker;
import org.springframework.web.client.RestTemplate;

@EnableCircuitBreaker
@RestController
@SpringBootApplication
public class CircuitBreakerReadingApplication {
  @Autowired
  private BookService bookService;

  @Bean
  public RestTemplate rest(RestTemplateBuilder builder) {
    return builder.build();
  }

  @RequestMapping("/to-read")
  public String toRead() {
    return bookService.readingList();
  }

  public static void main(String[] args) {
    SpringApplication.run(CircuitBreakerReadingApplication.class, args);
  }
}
```
Should add annotation, @EnableCircuitBreaker. It tells Spring Cloud that the application uses circuit breakers and to enable their monitoring, opening, and closing (behavior supplied by Hystrix).

src/main/resources/application.properties:
```
server.port=8080
```

- Apply the Circuit Breaker Pattern
```
import com.netflix.hystrix.contrib.javanica.annotation.HystrixCommand;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

import java.net.URI;

@Service
public class BookService {
  private final RestTemplate restTemplate;

  public BookService(RestTemplate rest) {
     this.restTemplate = rest;
  }

  @HystrixCommand(fallbackMethod = "reliable")
  public String readingList() {
     URI uri = URI.create("http://localhost:8090/recommended");// service
     return this.restTemplate.getForObject(uri, String.class);
  }

  public String reliable() {
     return "Cloud Native Java";
  }
}
```
Apply @HystrixCommand to the original readingList() method, and a new method: reliable(). The @HystrixCommand annotation has reliable as its fallbackMethod. If, for some reason, Hystrix opens the circuit on readingList(), there is an excellent (short) placeholder reading list ready for your users.


## [Concept](https://martinfowler.com/bliki/CircuitBreaker.html)
- Pattern: 

![pattern](https://martinfowler.com/bliki/images/circuitBreaker/sketch.png)

The basic idea behind the circuit breaker is very simple. You wrap a protected function call in a circuit breaker object, 
which monitors for failures. Once the failures reach a certain threshold, the circuit breaker trips, and all further calls
to the circuit breaker return with an error, without the protected call being made at all. 

- State:

![state](https://martinfowler.com/bliki/images/circuitBreaker/state.png)

Calling the circuit breaker will call the underlying block if the circuit is closed, but return an error if it's open.
