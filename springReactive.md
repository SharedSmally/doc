## Netty

## Java 9 Reactive Stream
- [Flow](https://docs.oracle.com/javase/9/docs/api/java/util/concurrent/Flow.html)
- Publisher<T>
   - void	subscribe(Flow.Subscriber<? super T> subscriber)
   - Implementing Classes: SubmissionPublisher
- Subscriber<T>
   - void	onComplete()
   - void	onError(Throwable throwable)
   - void	onNext(T item)
   - void	onSubscribe(Flow.Subscription subscription)
- Processor<T,R> extends Flow.Subscriber<T>, Flow.Publisher<R>
- Subscription
   - void	cancel()
   - void	request(long n)

## [Project Reactor](https://projectreactor.io/docs)
- Reactor Core
   - Mono<T>: 0..1 element
   - Flux<T>: 0..N elements
- Reactor Core.JS
- Reactor Core.Net
- Reactor Test
- Reactor Adapter
- Reactor Extra
- Reactor Netty
- Reactor Kafka
- Reactor RabbitMQ
