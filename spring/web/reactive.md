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

