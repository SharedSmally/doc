# Java Reactive for asynchronous and non-blocking components
- [Java Stream](https://docs.oracle.com/javase/8/docs/api/java/util/stream/Stream.html):deal efficiently with stream of data
- [Java Stream Collectors](https://docs.oracle.com/javase/8/docs/api/java/util/stream/Collectors.html): static methods implementing various useful reduction operations
```
 Collection<Widget> widgets;
int sum = widgets.stream()
                     .filter(w -> w.getColor() == RED)
                     .mapToInt(w -> w.getWeight())
                     .sum();
static <T> Stream<T> 	concat(Stream<? extends T> a, Stream<? extends T> b)     
static <T> Stream<T> 	generate(Supplier<T> s)
static <T> Stream<T> 	iterate(T seed, UnaryOperator<T> f)
static <T> Stream<T> 	of(T... values)
static <T> Stream<T> 	of(T t)
```
- [Reactive](https://projectreactor.io/)
- Reactive Core
    - [Reference](https://projectreactor.io/docs/core/release/reference/)
    - [API Doc](https://projectreactor.io/docs/core/release/api/)
- Reactive Netty/Kafka/RabbitMQ/Pool/

Mono:
## Interface Publisher<T>:
| Method |	Description |
|--------| -------------|
|void 	subscribe (Subscriber<? super T> s) 	| Request Publisher to start streaming data.|

## Interface Subscriber<T>
| Method |	Description |
|--------| -------------|
|void 	onComplete() 	|Successful terminal state.|
|void 	onError(Throwable t) 	|Failed terminal state.|
|void 	onNext(T t) 	|Data notification sent by the Publisher in response to requests to Subscription.request(long).|
|void 	onSubscribe(Subscription s) 	| Invoked after calling Publisher.subscribe(Subscriber).|

## Interface Subscription  
- Represents a one-to-one lifecycle of a Subscriber subscribing to a Publisher.
- can only be used once by a single Subscriber.
- used to both signal desire for data and cancel demand (and allow resource cleanup).
| Method |	Description |
|--------| -------------|
|void 	cancel() 	|Request the Publisher to stop sending data and clean up resources.|
|void 	request(long n) 	|No events will be sent by a Publisher until demand is signaled via this method.|

## Interface CorePublisher<T>
| Method |	Description |
|--------| -------------|
|void 	subscribe(CoreSubscriber<? super T> subscriber)|An internal Publisher.subscribe(Subscriber) that will bypass Hooks.onLastOperator(Function) pointcut.|

## Interface CoreSubscriber<T>: Subscriber<T>
|Context 	currentContext()|Request a Context from dependent components which can include downstream operators during subscribing or a terminal Subscriber.|
|void 	onSubscribe(Subscription s)|Implementors should initialize any state used by Subscriber.onNext(Object) before calling Subscription.request(long).|

## Interface Context : ContextVew

## Class Mono<T>: extends Object implements CorePublisher<T>
![mono](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/mono.svg)
A Reactive Streams Publisher with basic rx operators that emits at most one item via the onNext signal then terminates with an onComplete signal (successful Mono, with or without value), or only emits a single onError signal (failed Mono). 


## Class reactor.core.publisher.Flux<T>: extends Object implements CorePublisher<T>
![flux](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/flux.svg)
A Reactive Streams Publisher with rx operators that emits 0 to N elements, and then completes (successfully or with an error). 
```
Mono<Boolean> 	all(Predicate<? super T> predicate)
Mono<Boolean> 	any(Predicate<? super T> predicate)
<P> P 	as(Function<? super Flux<T>,P> transformer)
T 	blockFirst()/blockFirst(Duration timeout)
T 	blockLast()/blockLas(Duration timeout)

Flux<List<T>> 	buffer()/bufferTimeout/bufferUntil/bufferUntilChanged/bufferWhen
Flux<T> 	cache()/cancelOn/cast
Flux<T> 	checkpoint()
Flux<T> 	collect()/collectList/collectMap/collectMultimap/collectSortedList
<V> Flux<V> 	concatMap(Function<? super T,? extends Publisher<? extends V>> mapper)
Flux<T> 	concatWith(Publisher<? extends T> other)
Flux<T> 	delayElements(Duration delay)
Flux<T> 	distinct()
Flux<T> 	doFirst/Last/onCancel/onComplete/onDiscard/onError/onTerminate
Flux<T> 	expand(Function<? super T,? extends Publisher<? extends T>> expander)
Flux<T> 	filter(Predicate<? super T> p)
<R> Flux<R> 	flatMap(Function<? super T,? extends Publisher<? extends R>> mapper)
<K> Flux<GroupedFlux<K,T>> 	groupBy(Function<? super T,? extends K> keyMapper)
<R> Flux<R> 	handle(BiConsumer<? super T,SynchronousSink<R>> handler)
Mono<T> 	first/last()/next
Flux<T> 	log(Logger logger)
<V> Flux<V> 	map(Function<? super T,? extends V> mapper)
Flux<T> 	onBackpressureBuffer()
<E extends Throwable> Flux<T> 	onErrorContinue(Predicate<E> errorPredicate, BiConsumer<Throwable,Object> errorConsumer)
ParallelFlux<T> 	parallel()
<R> Flux<R> 	publish(Function<? super Flux<T>,? extends Publisher<? extends R>> transform)
<A> Mono<A> 	reduce(A initial, BiFunction<A,? super T,A> accumulator)
Flux<T> 	repeat(BooleanSupplier predicate)
ConnectableFlux<T> 	replay(Duration ttl)
Flux<T> 	retry()
<U> Flux<T> 	sample(Publisher<U> sampler)
<A> Flux<A> 	scan(A initial, BiFunction<A,? super T,A> accumulator)
Mono<T> 	single()
Flux<T> 	skip(Duration timespan)
Flux<T> 	sort()
Disposable 	subscribe()
<V> Flux<V> 	switchMap(Function<? super T,Publisher<? extends V>> fn)
Flux<T> 	take(Duration timespan)
Mono<Void> 	then()
Flux<T> 	timeout(Duration timeout)
Stream<T> 	toStream()
Flux<Flux<T>> 	window(int maxSize)

static <T,V> Flux<V> combineLatest
static <T> Flux<T> 	concat(Iterable<? extends Publisher<? extends T>> sources)
static <T> Flux<T> 	concatDelayError(Publisher<? extends T>... sources)
static <T> Flux<T> 	create(Consumer<? super FluxSink<T>> emitter)
static <T> Flux<T> 	defer(Supplier<? extends Publisher<T>> supplier)
static <O> Flux<O> 	error(Throwable throwable, boolean whenRequested)
static <I> Flux<I> 	firstWithSignal(Iterable<? extends Publisher<? extends I>> sources)
static <T> Flux<T> 	from(Publisher<? extends T> source)
static <T,S> Flux<T> 	generate(Callable<S> stateSupplier, BiFunction<S,SynchronousSink<T>,S> generator)
static Flux<Long> 	interval(Duration period)
static <T> Flux<T> 	just(T... data)
static <I> Flux<I> 	merge(int prefetch, Publisher<? extends I>... sources)
static <T,D> Flux<T> 	using(Callable<? extends D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> sourceSupplier, Consumer<? super D> resourceCleanup)
static <I,O> Flux<O> 	zip(Function<? super Object[],? extends O> combinator, int prefetch, Publisher<? extends I>... sources)
```
