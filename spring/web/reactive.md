# Java Reactive
- Interfaces: Publisher, Subscriber, Subscription, SubmitPPublisher
- Implementations:
    - Reactor: Mono<T>; Flux<T>
    - RxJava: Single<T>, Observerable<T>

## Spring Web:
- Architecture ![arch](https://docs.spring.io/spring-framework/docs/5.0.0.M1/spring-framework-reference/html/images/web-reactive-overview.png)
- MVC WebClient: RestTemplate
- Reactive Web Client: WebClient
```
ClientHttpConnector httpConnector = new ReactorClientHttpConnector();
WebClient webClient = new WebClient(httpConnector);

Mono<Account> response = webClient    #Reactor
		.perform(get("http://example.com/accounts/1").accept(APPLICATION_JSON))
		.extract(body(Account.class));

Single<Account> response = webClient  #RxJava
		.perform(get("http://example.com/accounts/1").accept(APPLICATION_JSON))
		.extract(body(Account.class));
```

### Reactive Client
- [org.springframework.web.reactive.function.client](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/reactive/function/client/package-summary.html)
```
ClientRequest	        Represents a typed, immutable, client-side HTTP request, as executed by the ExchangeFunction.
ClientRequest.Builder	Defines a builder for a request.
ClientResponse	        Represents an HTTP response, as returned by WebClient and also ExchangeFunction.
ClientResponse.Builder	Defines a builder for a response.
ClientResponse.Headers	Represents the headers of the HTTP response.

ExchangeFilterFunction	Represents a function that filters an exchange function.
ExchangeFunction	Represents a function that exchanges a request for a (delayed) ClientResponse.
ExchangeStrategies	Provides strategies for use in an ExchangeFunction.
ExchangeStrategies.Builder	A mutable builder for an ExchangeStrategies.

WebClient	        Non-blocking, reactive client to perform HTTP requests, exposing a fluent, reactive API over underlying HTTP client libraries such as Reactor Netty.
WebClient.Builder	A mutable builder for creating a WebClient.
WebClient.RequestBodySpec	Contract for specifying request headers and body leading up to the exchange.
WebClient.RequestBodyUriSpec	Contract for specifying request headers, body and URI for a request.
WebClient.RequestHeadersSpec<S extends WebClient.RequestHeadersSpec<S>>		Contract for specifying request headers leading up to the exchange.
WebClient.RequestHeadersUriSpec<S extends WebClient.RequestHeadersSpec<S>>	Contract for specifying request headers and URI for a request.
WebClient.ResponseSpec		Contract for specifying response operations following the exchange.
WebClient.UriSpec<S extends WebClient.RequestHeadersSpec<?>>			Contract for specifying the URI for a request.
```

### WebClient
- [API doc](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/reactive/function/client/WebClient.html)
```
static WebClient.Builder builder()
static WebClient create()
static WebClient create(String baseUrl)

WebClient.Builder	mutate()
WebClient.RequestHeadersUriSpec<?> delete()
WebClient.RequestHeadersUriSpec<?> get()
WebClient.RequestHeadersUriSpec<?> head()
WebClient.RequestHeadersUriSpec<?> options()
WebClient.RequestBodyUriSpec	patch()
WebClient.RequestBodyUriSpec	post()
WebClient.RequestBodyUriSpec	put()
WebClient.RequestBodyUriSpec method(HttpMethod method)
```
- [UriSpec](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/reactive/function/client/WebClient.UriSpec.html)
```
S uri(Function<UriBuilder,URI> uriFunction)
S uri(String uri, Function<UriBuilder,URI> uriFunction)
S uri(String uri, Map<String,?> uriVariables)
S uri(String uri, Object... uriVariables)
S uri(URI uri)
```
- [RequestHeadersSpec](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/reactive/function/client/WebClient.RequestHeadersSpec.html)
```
Interface WebClient.RequestHeadersSpec<S extends WebClient.RequestHeadersSpec<S>> {
    WebClient.ResponseSpec retrieve()
    <V> reactor.core.publisher.Flux<V>	exchangeToFlux(Function<ClientResponse,? extends reactor.core.publisher.Flux<V>> responseHandler)
    <V> reactor.core.publisher.Mono<V>	exchangeToMono(Function<ClientResponse,? extends reactor.core.publisher.Mono<V>> responseHandler)
}
```
- [RequestBodySpec](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/reactive/function/client/WebClient.RequestBodySpec.html)
```
public static interface WebClient.RequestBodySpec extends WebClient.RequestHeadersSpec<WebClient.RequestBodySpec> {
   WebClient.RequestHeadersSpec<?>	body(BodyInserter<?,? super ClientHttpRequest> inserter)
   WebClient.RequestHeadersSpec<?>	body(Object producer, Class<?> elementClass)
   WebClient.RequestHeadersSpec<?>	body(Object producer, ParameterizedTypeReference<?> elementTypeRef)
   <T,P extends org.reactivestreams.Publisher<T>> WebClient.RequestHeadersSpec<?>	body(P publisher, Class<T> elementClass)
   <T,P extends org.reactivestreams.Publisher<T>> WebClient.RequestHeadersSpec<?>	body(P publisher, ParameterizedTypeReference<T> elementTypeRef)
   WebClient.RequestHeadersSpec<?>	bodyValue(Object body)
   WebClient.RequestBodySpec	contentLength(long contentLength)
   WebClient.RequestBodySpec	contentType(MediaType contentType)
}
```
- [RequestHeadersUriSpec](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/reactive/function/client/WebClient.RequestHeadersUriSpec.html)
```
public static interface WebClient.RequestHeadersUriSpec<S extends WebClient.RequestHeadersSpec<S>>
   extends WebClient.UriSpec<S>, WebClient.RequestHeadersSpec<S>
```
- [RequestBodyUriSpec](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/reactive/function/client/WebClient.RequestBodyUriSpec.html)
```
public static interface WebClient.RequestBodyUriSpec 
   extends WebClient.RequestBodySpec, WebClient.RequestHeadersUriSpec<WebClient.RequestBodySpec>
```

- [ResponseSpec](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/reactive/function/client/WebClient.ResponseSpec.html)
```
<T> reactor.core.publisher.Flux<T>	bodyToFlux(Class<T> elementClass)
<T> reactor.core.publisher.Flux<T>	bodyToFlux(ParameterizedTypeReference<T> elementTypeRef)
<T> reactor.core.publisher.Mono<T>	bodyToMono(Class<T> elementClass)
<T> reactor.core.publisher.Mono<T>	bodyToMono(ParameterizedTypeReference<T> elementTypeRef)

WebClient.ResponseSpec	onRawStatus(IntPredicate statusCodePredicate, Function<ClientResponse,reactor.core.publisher.Mono<? extends Throwable>> exceptionFunction)
WebClient.ResponseSpec	onStatus(Predicate<HttpStatus> statusPredicate, Function<ClientResponse,reactor.core.publisher.Mono<? extends Throwable>> exceptionFunction)

reactor.core.publisher.Mono<ResponseEntity<Void>>	toBodilessEntity()
<T> reactor.core.publisher.Mono<ResponseEntity<T>>	toEntity(Class<T> bodyClass)
<T> reactor.core.publisher.Mono<ResponseEntity<T>>	toEntity(ParameterizedTypeReference<T> bodyTypeReference)
<T> reactor.core.publisher.Mono<ResponseEntity<List<T>>>	toEntityList(Class<T> elementClass)
<T> reactor.core.publisher.Mono<ResponseEntity<List<T>>>	toEntityList(ParameterizedTypeReference<T> elementTypeRef)
```
- Sample
```
 Mono<Object> entityMono = client.get()
     .uri("/persons/1")
     .accept(MediaType.APPLICATION_JSON)
     .exchangeToMono(response -> {
         if (response.statusCode().equals(HttpStatus.OK)) {
             return response.bodyToMono(Person.class);
         }
         else if (response.statusCode().is4xxClientError()) {
             return response.bodyToMono(ErrorContainer.class);
         }
         else {
             return Mono.error(response.createException());
         }
     });
```


### R2DBC
R2DBC stands for Reactive Relational Database Connectivity, an incubator to integrate relational databases using a reactive driver. Spring Data R2DBC provides familiar Spring abstractions and repository support for R2DBC. It helps Spring-powered applications to perform database operations in a reactive way. At this moment, only PostGres, MSSQL, and H2 support R2DBC drivers.
- [Sample](https://medium.com/@dassum/building-a-reactive-restful-web-service-using-spring-boot-and-postgres-c8e157dbc81d)
```
@Data
@AllArgsConstructor
@NoArgsConstructor
@Table("users")
public class User {

    @Id
    private Integer id;
    private String name;
    private int age;
    private double salary;
}

@Data
@AllArgsConstructor
@NoArgsConstructor
@Table("department")
public class Department {
    @Id
    private Integer id;
    private String name;
    @Column("user_id")
    private Integer userId;
    private String loc;
}
public interface UserRepository extends ReactiveCrudRepository<User,Long> {
    @Query("select * from users where age >= $1")
    Flux<User> findByAge(int age);
}

public interface DepartmentRepository extends ReactiveCrudRepository<Department,Integer> {
    Mono<Department> findByUserId(Integer userId);
}

import com.reactive.examples.dto.UserDepartmentDTO;
import com.reactive.examples.model.User;
import com.reactive.examples.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

import java.util.List;

@RestController
@RequestMapping("/users")
public class UserController {
@Autowired
private UserService userService;

    @PostMapping
    @ResponseStatus(HttpStatus.CREATED)
    public Mono<User> create(@RequestBody User user){
        return userService.createUser(user);
    }

    @GetMapping
    public Flux<User> getAllUsers(){
        return userService.getAllUsers();
    }

    @GetMapping("/{userId}")
    public Mono<ResponseEntity<User>> getUserById(@PathVariable Integer userId){
        Mono<User> user = userService.findById(userId);
        return user.map( u -> ResponseEntity.ok(u))
                .defaultIfEmpty(ResponseEntity.notFound().build());
    }

    @PutMapping("/{userId}")
    public Mono<ResponseEntity<User>> updateUserById(@PathVariable Integer userId, @RequestBody User user){
        return userService.updateUser(userId,user)
                .map(updatedUser -> ResponseEntity.ok(updatedUser))
                .defaultIfEmpty(ResponseEntity.badRequest().build());
    }

    @DeleteMapping("/{userId}")
    public Mono<ResponseEntity<Void>> deleteUserById(@PathVariable Integer userId){
        return userService.deleteUser(userId)
                .map( r -> ResponseEntity.ok().<Void>build())
                .defaultIfEmpty(ResponseEntity.notFound().build());
    }

    @GetMapping("/age/{age}")
    public Flux<User> getUsersByAge(@PathVariable int age) {
        return userService.findUsersByAge(age);
    }

    @PostMapping("/search/id")
    public Flux<User> fetchUsersByIds(@RequestBody List<Integer> ids) {
        return userService.fetchUsers(ids);
    }

    @GetMapping("/{userId}/department")
    public Mono<UserDepartmentDTO> fetchUserAndDepartment(@PathVariable Integer userId){
        return userService.fetchUserAndDepartment(userId);
    }
}
```
### Other Reactive Sources
- Reactive Redis
- Reactive Kafka
- Reactive mongodb
- [Reactive Streams](https://docs.spring.io/spring-integration/reference/html/reactive-streams.html)


