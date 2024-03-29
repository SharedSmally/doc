# [Flux](https://projectreactor.io/docs/core/release/api/)
![Flux](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/flux.svg)

## Create Flux
### Misc
```
static <T> Flux<T> 	empty(): Create a Flux that completes without emitting any item.
static <T> Flux<T> 	never(): Create a Flux that will never signal any data, error or completion signal.
static Flux<Integer> 	range(int start, int count): Build a Flux that will only emit a sequence of count incrementing integers, starting from start.
static <T> Flux<T> 	switchOnNext(Publisher<? extends Publisher<? extends T>> mergedPublishers)
Creates a Flux that mirrors the most recently emitted Publisher, forwarding its data until a new Publisher comes in the source.
```

### From single data
Create a Flux that emits the provided elements or a single element and then completes.
```
static <T> Flux<T> 	just(T... data)
static <T> Flux<T> 	just(T data)
```
### From the Source
Decorate the specified Publisher with the Flux API.
```
static <T> Flux<T> 	from(Publisher<? extends T> source)
static <T> Flux<T> 	fromArray(T[] array)
static <T> Flux<T> 	fromIterable(Iterable<? extends T> it)
static <T> Flux<T> 	fromStream(Stream<? extends T> s)
static <T> Flux<T> 	fromStream(Supplier<Stream<? extends T>> streamSupplier)
```
### Send Error
Create a Flux that terminates with an error immediately after being subscribed to.
```
static <T> Flux<T> 	error(Supplier<? extends Throwable> errorSupplier)
static <T> Flux<T> 	error(Throwable error)
static <O> Flux<O> 	error(Throwable throwable, boolean whenRequested)
```
### Combine Latest
Build a Flux whose data are generated by the combination of the most recently published value from each of the Publisher sources.

![ConbineLatest](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/combineLatest.svg)
```
static <T,V> Flux<V> 	combineLatest(Function<Object[],V> combinator, int prefetch, Publisher<? extends T>... sources)
static <T,V> Flux<V> 	combineLatest(Function<Object[],V> combinator, Publisher<? extends T>... sources)
static <T,V> Flux<V> 	combineLatest(Iterable<? extends Publisher<? extends T>> sources, Function<Object[],V> combinator)
static <T,V> Flux<V> 	combineLatest(Iterable<? extends Publisher<? extends T>> sources, int prefetch, Function<Object[],V> combinator)
static <T1,T2,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, BiFunction<? super T1,? super T2,? extends V> combinator)
static <T1,T2,T3,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Function<Object[],V> combinator)
static <T1,T2,T3,T4,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Function<Object[],V> combinator)
static <T1,T2,T3,T4,T5,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Function<Object[],V> combinator)
static <T1,T2,T3,T4,T5,T6,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6, Function<Object[],V> combinator)
```
### Concat
Concatenate all sources provided in an Iterable, forwarding elements emitted by the sources downstream.

![Concat](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/concatVarSources.svg)
```
static <T> Flux<T> 	concat(Iterable<? extends Publisher<? extends T>> sources)
static <T> Flux<T> 	concat(Publisher<? extends Publisher<? extends T>> sources)
static <T> Flux<T> 	concat(Publisher<? extends Publisher<? extends T>> sources, int prefetch)
static <T> Flux<T> 	concat(Publisher<? extends T>... sources)
static <T> Flux<T> 	concatDelayError(Publisher<? extends Publisher<? extends T>> sources)
static <T> Flux<T> 	concatDelayError(Publisher<? extends Publisher<? extends T>> sources, boolean delayUntilEnd, int prefetch)
static <T> Flux<T> 	concatDelayError(Publisher<? extends Publisher<? extends T>> sources, int prefetch)
static <T> Flux<T> 	concatDelayError(Publisher<? extends T>... sources)
```
### Create - Multiple threads
Programmatically create a Flux with the capability of emitting multiple elements in a synchronous or asynchronous manner through the FluxSink API.

![create](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/createForFlux.svg)
```
static <T> Flux<T> 	create(Consumer<? super FluxSink<T>> emitter)
static <T> Flux<T> 	create(Consumer<? super FluxSink<T>> emitter, FluxSink.OverflowStrategy backpressure)
```
### Defer
Lazily supply a Publisher every time a Subscription is made on the resulting Flux, so the actual source instantiation is deferred until each subscribe and the Supplier can create a subscriber-specific instance.

![Defer](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/deferForFlux.svg)
```
static <T> Flux<T> 	defer(Supplier<? extends Publisher<T>> supplier)
static <T> Flux<T> 	deferContextual(Function<ContextView,? extends Publisher<T>> contextualPublisherFactory)
```
### First
Pick the first Publisher to emit any signal (onNext/onError/onComplete) and replay all signals from that Publisher, effectively behaving like the fastest of these competing sources.

![First](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/firstWithSignalForFlux.svg)
```
static <I> Flux<I> 	first(Iterable<? extends Publisher<? extends I>> sources)
static <I> Flux<I> 	first(Publisher<? extends I>... sources)
static <I> Flux<I> 	firstWithSignal(Iterable<? extends Publisher<? extends I>> sources)
static <I> Flux<I> 	firstWithSignal(Publisher<? extends I>... sources)
static <I> Flux<I> 	firstWithValue(Iterable<? extends Publisher<? extends I>> sources)
static <I> Flux<I> 	firstWithValue(Publisher<? extends I> first, Publisher<? extends I>... others)
```
### Generate - Single thread
Programmatically create a Flux by generating signals one-by-one via a consumer callback and some state.

![generate](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/generateStateless.svg)

```
static <T,S> Flux<T> 	generate(Callable<S> stateSupplier, BiFunction<S,SynchronousSink<T>,S> generator)
static <T,S> Flux<T> 	generate(Callable<S> stateSupplier, BiFunction<S,SynchronousSink<T>,S> generator, Consumer<? super S> stateConsumer)
static <T> Flux<T> 	generate(Consumer<SynchronousSink<T>> generator)
```
### Interval
Create a Flux that emits long values starting with 0 and incrementing at specified time intervals on the global timer.

![Interval](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/interval.svg)
```
static Flux<Long> 	interval(Duration period)
static Flux<Long> 	interval(Duration delay, Duration period)
static Flux<Long> 	interval(Duration delay, Duration period, Scheduler timer)
static Flux<Long> 	interval(Duration period, Scheduler timer)
```
### Merge
Merge data from Publisher sequences contained in an array / vararg into an interleaved merged sequence.

![Merge](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/mergeAsyncSources.svg)
```
static <I> Flux<I> 	merge(int prefetch, Publisher<? extends I>... sources)
static <I> Flux<I> 	merge(Iterable<? extends Publisher<? extends I>> sources)
static <I> Flux<I> 	merge(Publisher<? extends I>... sources)
static <T> Flux<T> 	merge(Publisher<? extends Publisher<? extends T>> source)
static <T> Flux<T> 	merge(Publisher<? extends Publisher<? extends T>> source, int concurrency)
static <T> Flux<T> 	merge(Publisher<? extends Publisher<? extends T>> source, int concurrency, int prefetch)

static <T> Flux<T> 	mergeComparing(Comparator<? super T> comparator, Publisher<? extends T>... sources)
static <T> Flux<T> 	mergeComparing(int prefetch, Comparator<? super T> comparator, Publisher<? extends T>... sources)
static <I extends Comparable<? super I>> Flux<I> 	mergeComparing(Publisher<? extends I>... sources)
static <T> Flux<T> 	mergeComparingDelayError(int prefetch, Comparator<? super T> comparator, Publisher<? extends T>... sources)
static <I> Flux<I> 	mergeDelayError(int prefetch, Publisher<? extends I>... sources)
static <T> Flux<T> 	mergeOrdered(Comparator<? super T> comparator, Publisher<? extends T>... sources)
static <T> Flux<T> 	mergeOrdered(int prefetch, Comparator<? super T> comparator, Publisher<? extends T>... sources)
static <I extends Comparable<? super I>> Flux<I> 	mergeOrdered(Publisher<? extends I>... sources)
static <T> Flux<T> 	mergePriority(Comparator<? super T> comparator, Publisher<? extends T>... sources)
static <T> Flux<T> 	mergePriority(int prefetch, Comparator<? super T> comparator, Publisher<? extends T>... sources)
static <I extends Comparable<? super I>> Flux<I> 	mergePriority(Publisher<? extends I>... sources)
static <T> Flux<T> 	mergePriorityDelayError(int prefetch, Comparator<? super T> comparator, Publisher<? extends T>... sources)
```
### Merge Sequential
Merge data from Publisher sequences provided in an Iterable into an ordered merged sequence.

![MergeSeq](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/mergeSequentialAsyncSources.svg)
```
static <I> Flux<I> 	mergeSequential(int prefetch, Publisher<? extends I>... sources)
static <I> Flux<I> 	mergeSequential(Iterable<? extends Publisher<? extends I>> sources)
static <I> Flux<I> 	mergeSequential(Iterable<? extends Publisher<? extends I>> sources, int maxConcurrency, int prefetch)
static <I> Flux<I> 	mergeSequential(Publisher<? extends I>... sources)
static <T> Flux<T> 	mergeSequential(Publisher<? extends Publisher<? extends T>> sources)
static <T> Flux<T> 	mergeSequential(Publisher<? extends Publisher<? extends T>> sources, int maxConcurrency, int prefetch)
static <I> Flux<I> 	mergeSequentialDelayError(int prefetch, Publisher<? extends I>... sources)
static <I> Flux<I> 	mergeSequentialDelayError(Iterable<? extends Publisher<? extends I>> sources, int maxConcurrency, int prefetch)
static <T> Flux<T> 	mergeSequentialDelayError(Publisher<? extends Publisher<? extends T>> sources, int maxConcurrency, int prefetch)
```
###  push
Programmatically create a Flux with the capability of emitting multiple elements from a single-threaded producer through the FluxSink API.
```
static <T> Flux<T> 	push(Consumer<? super FluxSink<T>> emitter)
static <T> Flux<T> 	push(Consumer<? super FluxSink<T>> emitter, FluxSink.OverflowStrategy backpressure)
```

### Using
Uses a resource, generated by a supplier for each individual Subscriber, while streaming the values from a Publisher derived from the same resource and makes sure the resource is released if the sequence terminates or the Subscriber cancels.

![Using](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/usingForFlux.svg)
```
static <T,D> Flux<T> 	using(Callable<? extends D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> sourceSupplier, Consumer<? super D> resourceCleanup)
static <T,D> Flux<T> 	using(Callable<? extends D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> sourceSupplier, Consumer<? super D> resourceCleanup, boolean eager)
static <T,D> Flux<T> 	usingWhen(Publisher<D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> resourceClosure, Function<? super D,? extends Publisher<?>> asyncCleanup)
static <T,D> Flux<T> 	usingWhen(Publisher<D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> resourceClosure, Function<? super D,? extends Publisher<?>> asyncComplete, BiFunction<? super D,? super Throwable,? extends Publisher<?>> asyncError, Function<? super D,? extends Publisher<?>> asyncCancel)
```
### ZIP
Zip multiple sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).

![zip](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/zipTwoSourcesWithZipperForFlux.svg)
```
static <I,O> Flux<O> 	zip(Function<? super Object[],? extends O> combinator, int prefetch, Publisher<? extends I>... sources)
static <I,O> Flux<O> 	zip(Function<? super Object[],? extends O> combinator, Publisher<? extends I>... sources)
static <O> Flux<O> 	zip(Iterable<? extends Publisher<?>> sources, Function<? super Object[],? extends O> combinator)
static <O> Flux<O> 	zip(Iterable<? extends Publisher<?>> sources, int prefetch, Function<? super Object[],? extends O> combinator)
static <TUPLE extends Tuple2,V> Flux<V> 	zip(Publisher<? extends Publisher<?>> sources, Function<? super TUPLE,? extends V> combinator)
static <T1,T2> Flux<Tuple2<T1,T2>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2)
static <T1,T2,O> Flux<O> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, BiFunction<? super T1,? super T2,? extends O> combinator)
static <T1,T2,T3> Flux<Tuple3<T1,T2,T3>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3)
static <T1,T2,T3,T4> Flux<Tuple4<T1,T2,T3,T4>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4)
static <T1,T2,T3,T4,T5> Flux<Tuple5<T1,T2,T3,T4,T5>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5)
static <T1,T2,T3,T4,T5,T6> Flux<Tuple6<T1,T2,T3,T4,T5,T6>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6)
static <T1,T2,T3,T4,T5,T6,T7> Flux<Tuple7<T1,T2,T3,T4,T5,T6,T7>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6, Publisher<? extends T7> source7)
static <T1,T2,T3,T4,T5,T6,T7,T8> Flux<Tuple8<T1,T2,T3,T4,T5,T6,T7,T8>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6, Publisher<? extends T7> source7, Publisher<? extends T8> source8)
```


