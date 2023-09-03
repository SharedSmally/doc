# Reactive
Reactive Streams Implementation 
- [Reactor](https://projectreactor.io/)
- [JavaRx](https://github.com/ReactiveX/RxJava)

## Reactive Streams Specification
![Java Reactive](https://miro.medium.com/v2/resize:fit:640/format:webp/0*Boh8h9YJ79LdXOl5.jpeg)
### Publisher (Flux;Mono)
This is a single method interface that will be used to register the subscriber to the publisher. The subscribe method of this interface accepts the subscriber object and registers it.

![Publisher](https://miro.medium.com/v2/resize:fit:640/format:webp/0*DksX5DKVJgqmgbyo.png)

### Subscriber

This is an interface that has four methods
- onSubscribe method will be called by the publisher when subscribing to the Subscribe object.
- onNext method will be called when the next data will be published to the subscriber
- onError method will be called when exceptions arise while publishing data to the subscriber
- onComplete method will be called after the successful completion of data publishing to the subscriber

![Subscriber](https://miro.medium.com/v2/resize:fit:640/format:webp/0*p1n-O-3mg8GAsCWy.png)

### Subscription

This is an interface with two methods. The subscription object will be created when the user subscribes to the publisher in the publisher object as discussed earlier. The subscription object will be passed to the subscriber object via onSubscribe method
- request method will be called when the subscriber needs to request data from the publisher
- cancel method will be called when the subscriber needs to cancel and close the subscription

![Subscription](https://miro.medium.com/v2/resize:fit:640/format:webp/0*LGXjQPVwOv0nP4bM.png)

### Processor (Operator)

This is an interface that is extended by both publisher and subscriber interfaces. This interface is not very common but will be used to process the logic of the subscribing and publishing workflow

![Processor](https://miro.medium.com/v2/resize:fit:720/format:webp/0*y0vILBzlmLThhI9D.png)

## Project Reactor
- Reactor core
- Reactor Test;Extra;Adaptor;Pool
- Reactor Netty
- Reactor Kafka
- Reactor RabbitMQ
  
### Flux

Flux represents an Asynchronous Sequence of 0-N Items. This is like a stream of 0 to N items, and we can do various transformations to this stream, including transforming it to an entirely different type of 0-N item stream.

![Flux](https://miro.medium.com/v2/resize:fit:640/format:webp/0*dahFWzPbgq5EXwoE.png)

### Mono

Mono represents only one value stream of items. We can do various transformations to this, including transforming it entirely.

![Mono](https://miro.medium.com/v2/resize:fit:720/0*YbFa5e6k_DO4zsEn)

### Sink

Sinks are constructs through which Reactive Streams signals can be programmatically pushed, with Flux or Mono semantics. These standalone sinks expose tryEmit methods that return an Sinks.EmitResult enum, allowing to atomically fail in case the attempted signal is inconsistent with the spec and/or the state of the sink. 

- Sinks.EmissionException:  An exception representing a failed Sinks.EmitResult.
- Sinks.EmitFailureHandler: A handler supporting the emit API (eg.
- Sinks.EmitResult: Represents the immediate result of an emit attempt (eg.
- Sinks.Empty<T>: A base interface for standalone Sinks with complete-or-fail semantics.
- Sinks.Many<T>: A base interface for standalone Sinks with Flux semantics.
    - Sinks.ManySpec: Provides Sinks.Many specs for sinks which can emit multiple elements
- Sinks.ManyWithUpstream<T>: A Sinks.Many which additionally allows being subscribed to an upstream Publisher, which is an advanced pattern requiring external synchronization.
    - Sinks.ManyWithUpstreamUnsafeSpec: Instead of unsafe flavors of Sinks.Many, this spec provides Sinks.ManyWithUpstream implementations.
    - Sinks.MulticastReplaySpec: Provides multicast with history/replay capacity : 1 sink, N Subscriber
    - Sinks.MulticastSpec: Provides multicast : 1 sink, N Subscriber
- Sinks.One<T>: A base interface for standalone Sinks with Mono semantics.
    - Sinks.RootSpec:  Provides a choice of Sinks.One/Sinks.Empty factories and further specs for Sinks.Many.
    - Sinks.UnicastSpec: Provides unicast: 1 sink, 1 Subscriber

