# [Reactive](https://projectreactor.io/)
- [API](https://projectreactor.io/docs/core/release/api/)
- [Reference](https://projectreactor.io/docs/core/release/reference/)
- [Flux](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/Flux.html)
- [Mono](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/Mono.html)
- [Sink](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/Sinks.html)

## Dependency
```
<dependencyManagement> 
    <dependencies>
        <dependency>
            <groupId>io.projectreactor</groupId>
            <artifactId>reactor-bom</artifactId>
            <version>2020.0.13</version>
            <type>pom</type>
            <scope>import</scope>
        </dependency>
    </dependencies>
</dependencyManagement>

<dependencies>
    <dependency>
        <groupId>io.projectreactor</groupId>
        <artifactId>reactor-core</artifactId>         
    </dependency>
    <dependency>
        <groupId>io.projectreactor</groupId>
        <artifactId>reactor-test</artifactId> 
        <scope>test</scope>
    </dependency>
</dependencies>
```

## Flux<T>/Mono<T>: implement Publisher
- Flux object represents a reactive sequence of 0..N items, 
![Flux](https://projectreactor.io/docs/core/release/reference/images/flux.svg)    
- Mono object represents a single-value-or-empty (0..1) result.
![Mono](https://projectreactor.io/docs/core/release/reference/images/mono.svg)    

### Create     

### Sinks
| Method | Description |
|--------|-------------|
| Flux<T> 	asFlux() | Return a Flux view of this sink.|
|int 	currentSubscriberCount() |Get how many Subscribers are currently subscribed to the sink.|
|void 	emitComplete(Sinks.EmitFailureHandler failureHandler)| A simplified attempt at completing via the tryEmitComplete() API, generating an onComplete signal.|
|void 	emitError(Throwable error, Sinks.EmitFailureHandler failureHandler)|A simplified attempt at failing the sequence via the tryEmitError(Throwable) API, generating an onError signal.|
|void 	emitNext(T t, Sinks.EmitFailureHandler failureHandler)| A simplified attempt at emitting a non-null element via the tryEmitNext(Object) API, generating an onNext signal.|
|Sinks.EmitResult 	tryEmitComplete()| Try to terminate the sequence successfully, generating an onComplete signal.|
|Sinks.EmitResult 	tryEmitError(Throwable error)|Try to fail the sequence, generating an onError signal.|
|Sinks.EmitResult 	tryEmitNext(T t)|Try emitting a non-null element, generating an onNext signal.|
    
    
