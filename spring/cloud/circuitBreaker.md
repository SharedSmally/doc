# Circuit Breaker
- [Project](https://spring.io/projects/spring-cloud-circuitbreaker)
- [Resilience4J Reference](https://docs.spring.io/spring-cloud-circuitbreaker/docs/1.0.4.RELEASE/reference/html/)
- [Tutorial](https://www.baeldung.com/spring-cloud-netflix-hystrix)
- [Sample](https://spring.io/guides/gs/circuit-breaker/)

## Core Concepts
- Circuit Breakers In non-Reactive Code
```
@Service
public static class DemoControllerService {
	private RestTemplate rest;
	private CircuitBreakerFactory cbFactory;

	public DemoControllerService(RestTemplate rest, CircuitBreakerFactory cbFactory) {
		this.rest = rest;
		this.cbFactory = cbFactory;
	}

	public String slow() {
		return cbFactory.create("slow").run(() -> rest.getForObject("/slow", String.class),
		          throwable -> "fallback");
	}
}
```
The CircuitBreakerFactory.create API will create an instance of a class called CircuitBreaker. The run method takes a Supplier and a Function. The Supplier is the code that you are going to wrap in a circuit breaker. The Function is the fallback that will be executed if the circuit breaker is tripped. The function will be passed the Throwable that caused the fallback to be triggered. You can optionally exclude the fallback if you do not want to provide one.

- Circuit Breakers In Reactive Code
```
@Service
public static class DemoControllerService {
	private ReactiveCircuitBreakerFactory cbFactory;
	private WebClient webClient;

	public DemoControllerService(WebClient webClient, ReactiveCircuitBreakerFactory cbFactory) {
		this.webClient = webClient;
		this.cbFactory = cbFactory;
	}

	public Mono<String> slow() {
		return webClient.get().uri("/slow").retrieve().bodyToMono(String.class).transform(
		     it -> cbFactory.create("slow").run(it, throwable -> return Mono.just("fallback")));
	}
}
```
The ReactiveCircuitBreakerFactory.create API will create an instance of a class called ReactiveCircuitBreaker. The run method takes with a Mono or Flux and wraps it in a circuit breaker. You can optionally profile a fallback Function which will be called if the circuit breaker is tripped and will be passed the Throwable that caused the failure.


## Netfix Hystrix
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

##

## [Concept](https://martinfowler.com/bliki/CircuitBreaker.html)
- Pattern: 

![pattern](https://martinfowler.com/bliki/images/circuitBreaker/sketch.png)

The basic idea behind the circuit breaker is very simple. You wrap a protected function call in a circuit breaker object, 
which monitors for failures. Once the failures reach a certain threshold, the circuit breaker trips, and all further calls
to the circuit breaker return with an error, without the protected call being made at all. 

- State:

![state](https://martinfowler.com/bliki/images/circuitBreaker/state.png)

Calling the circuit breaker will call the underlying block if the circuit is closed, but return an error if it's open.
