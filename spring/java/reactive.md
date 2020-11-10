# Java Reactive Programming

## Interfaces in reactor
- [Reference](https://projectreactor.io/docs/core/release/reference/)
- [API doc](https://projectreactor.io/docs/core/release/api/overview-summary.html)
- Java [Future](https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/Future.html)
```
public interface Future<V> {
   boolean	cancel(boolean mayInterruptIfRunning)
   boolean	isCancelled()
   boolean	isDone()   

   V	get()
   V	get(long timeout, TimeUnit unit)
}
```
- [Flux](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/Flux.html): for [N] elements
```
public interface CorePublisher<T> extends Publisher<T> {
   void	subscribe(CoreSubscriber<? super T> subscriber)
}
public interface CoreSubscriber<T> extends Subscriber<T> {
   default Context	currentContext()
   //onComplete, onError, onNext,	onSubscribe from Subscriber
}

public abstract class Flux<T> extends Object implements CorePublisher<T> {
   Flux<List<T>>	buffer[Timeout|Until|When|While\(...);
   Flux<T>	cache/checkpoint(...);
   <R,A> Mono<R> collect(...)
   <K,V> Mono<Map<K,V>>	collectMap(...)
   Flux<T>	concatXXX(...);
   Flux<T>	delayXxxx(Duration delay)
   Flux<T>	distinct(...)
   Flux<T>	doXxx(...)
   Mono<T>	elementAt(...)
   Flux<T>	expand(...)
   Flux<T>	filterXxx(Predicate<? super T> p)
   Flux<R>	flatMap(...)
   <K> Flux<GroupedFlux<K,T>>	groupBy(...)
   Flux<T>	onBackpressureBuffer(...)
   Flux<T>	onError(...)   
   Flux<T>	publish(...)
   Flux<T>	repeat(...)
   ConnectableFlux<T>	replay(...)
   Flux<T>	retry(...)
   Flux<T>	sample(...)
   Flux<T>	scan(...)
   Flux<T>	skip(...)
   Flux<T>	startWith(...)
   Disposable	subscribe(...)
   Flux<T>	take(...);
   <U> Flux<T>	timeout(...)
   
   static <T,V> Flux<V>	combineLatest(...)
   static <T> Flux<T>	concat/concatDelayError(...)
   static <T> Flux<T>	create(Consumer<? super FluxSink<T>> emitter)
   static <T> Flux<T>	defer(Supplier<? extends Publisher<T>> supplier)
   static <T> Flux<T>	error(...)
   static <I> Flux<I>	firstWithSignal(...)
   static <T> Flux<T>	from(...)
   static <T> Flux<T>	generate(...)
   static <I> Flux<I>	merge(...)
   static <T> Flux<T>	push(...)
   static <I,O> Flux<O>	zip(...)
}
```
Direct Known Subclasses: ConnectableFlux, FluxOperator, FluxProcessor, GroupedFlux
![Diagram](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/flux.svg)

- [Mono](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/Mono.html): for [0|1] element
```
public abstract class Mono<T> extends Object implements CorePublisher<T> {
   static <T> Mono<T>	empty()
   static <T> Mono<T>	error(Supplier<? extends Throwable> errorSupplier)
   static <T> Mono<T>	error(Throwable error)
   static <T> Mono<T>	firstWithSignal(...)
   static <T> Mono<T>	from(...)
   static <T,D> Mono<T>	using(...)
   static Mono<Void>	when(...)
   static <R> Mono<R>	zip(...)
  
   Mono<T>	cache(...)
   Mono<T>	delayXxx(...)
   Mono<T>	doXxx(...)
   Flux<T>	expand(...) 
   <E extends Throwable> Mono<T>	onErrorXxx(...)
   Flux<T>	repeatXxx(...)
   Mono<T>	retry(...)
   Mono<T>	take(...)
   Mono/Flux<T>	then(...)
   Mono<T>	timeout(...)
   <V> Mono<V>	transform(...)
   <R> Mono<R>	zipXxx(...)
}
```
Direct Known Subclasses: MonoOperator, MonoProcessor

![Diagram](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/mono.svg)



- Stream

## Interfaces in [concurrent](https://docs.oracle.com/javase/9/docs/api/java/util/concurrent/package-summary.html)
- Architecture 
![arch](https://drek4537l1klr.cloudfront.net/urma2/Figures/17fig03_alt.jpg)

- [Publisher](https://docs.oracle.com/javase/9/docs/api/java/util/concurrent/Flow.Publisher.html)
```
@FunctionalInterface
public static interface Flow.Publisher<T> {
   void	subscribe (Flow.Subscriber<? super T> subscriber)
}
```
- Subscriber
```
public static interface Flow.Subscriber<T> {
   void	onComplete()	
   void	onError(Throwable throwable)	
   void	onNext(T item)	
   void	onSubscribe(Flow.Subscription subscription)
}   
```
- Subscription: Message control linking a Flow.Publisher and Flow.Subscriber.
```
public static interface Flow.Subscription {
   void	cancel()	
   void	request(long n)
}  
```
-  Processor
```
public static interface Flow.Processor<T,R> extends Flow.Subscriber<T>, Flow.Publisher<R>
```
- SubmissionPublisher
```
public class SubmissionPublisher<T> extends Object implements Flow.Publisher<T>, AutoCloseable {
   SubmissionPublisher()	
   SubmissionPublisher(Executor executor, int maxBufferCapacity)	
   SubmissionPublisher(Executor executor, int maxBufferCapacity, BiConsumer<? super Flow.Subscriber<? super T>,? super Throwable> handler)

   void	close()	
   void	closeExceptionally(Throwable error)	
   CompletableFuture<Void>	consume(Consumer<? super T> consumer)	
   int	estimateMaximumLag()	
   long	estimateMinimumDemand()	
   Throwable	getClosedException()	
   Executor	getExecutor()	
   int	getMaxBufferCapacity()	
   int	getNumberOfSubscribers()	
   List<Flow.Subscriber<? super T>>	getSubscribers()	
   boolean	hasSubscribers()	
   boolean	isClosed()	
   boolean	isSubscribed(Flow.Subscriber<? super T> subscriber)	
   
   int	offer(T item, long timeout, TimeUnit unit, BiPredicate<Flow.Subscriber<? super T>,? super T> onDrop)	
   int	offer(T item, BiPredicate<Flow.Subscriber<? super T>,? super T> onDrop)	
   
   int	submit(T item)	
   void	subscribe(Flow.Subscriber<? super T> subscriber)
}
```

## Interface in [java.util.function]()
- Supplier:
```
@FunctionalInterface
public interface Supplier<T> {
   T	get()
}
```
- 
```
@FunctionalInterface
public interface Consumer<T> {
   void	accept(T t)
   default Consumer<T>	andThen(Consumer<? super T> after)
}
```
- Predicate
```
@FunctionalInterface
public interface Predicate<T> {
   static <T> Predicate<T>	isEqual(Object targetRef)
   default Predicate<T>	and(Predicate<? super T> other)
   default Predicate<T>	negate()
   default Predicate<T>	or(Predicate<? super T> other)
   boolean	test(T t)
}
```
- Function
```
@FunctionalInterface
public interface Function<T,R> {
   default <V> Function<T,V>	andThen(Function<? super R,? extends V> after)
   default <V> Function<V,R>	compose(Function<? super V,? extends T> before)
   
   R	apply(T t)

   static <T> Function<T,T>	identity()
}
```
- Callable
```
public interface Callable<V> {
   V	call();
}
```
