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
