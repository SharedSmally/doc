# Java Flux
- [API doc](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/Flux.html)
- [Tutorial]()

## [Sample](https://www.baeldung.com/flux-sequences-reactor)
### Synchronous Emission: generate() method
```
static <T,S> Flux<T> 	generate(Callable<S> stateSupplier, BiFunction<S,SynchronousSink<T>,S> generator)
static <T,S> Flux<T> 	generate(Callable<S> stateSupplier, BiFunction<S,SynchronousSink<T>,S> generator, Consumer<? super S> stateConsumer)
static <T> Flux<T> 	generate(Consumer<SynchronousSink<T>> generator)  // no state
```
- The Callable function sets up the initial state for the generator
- The BiFuntion function is a generator, consuming a SynchronousSink, then emitting an item in each round with the sink's next method and the current state
```
public class FibonacciState {
	    private int former;
	    private int latter;	 
	    // constructor, getters and setters
	}
  
public Flux<Integer> generateFibonacciWithCustomClass(int limit) {
	    return Flux.generate(
	      () -> new FibonacciState(0, 1),
	      (state, sink) -> {
	        sink.next(state.getFormer());
	        if (state.getLatter() > limit) {
	            sink.complete();
	        }
	        int temp = state.getFormer();
	        state.setFormer(state.getLatter());
	        state.setLatter(temp + state.getLatter());
	        return state;
	    });
	}
```

### Asynchronous Emission:
Use the create and push operators to produce multiple items in a round of emission in an asynchronous manner.
- create() method: produce items from multiple threads.
```
static <T> Flux<T> 	create(Consumer<? super FluxSink<T>> emitter)
static <T> Flux<T> 	create(Consumer<? super FluxSink<T>> emitter, FluxSink.OverflowStrategy backpressure)

public class SequenceCreator {
	    public Consumer<List<Integer>> consumer;
      
	    public Flux<Integer> createNumberSequence() {
	        return Flux.create(sink -> SequenceCreator.this.consumer = items -> items.forEach(sink::next));
	    }
	}
```

- push() method: similar to create, except that it allows only one producing thread to emit signals at a time.
```
static <T> Flux<T> 	push(Consumer<? super FluxSink<T>> emitter)
static <T> Flux<T> 	push(Consumer<? super FluxSink<T>> emitter, FluxSink.OverflowStrategy backpressure)
```

### Creators
- combine/concat/merge/zip
- create/defer
- error
- first
- from 
- generate
- interval
- just
- push
- switchOnNext
- using


#### combine method
- static <T,V> Flux<V> 	combineLatest(Function<Object[],V> combinator, int prefetch, Publisher<? extends T>... sources)

Build a Flux whose data are generated by the combination of the most recently published value from each of the Publisher sources.

- static <T,V> Flux<V> 	combineLatest(Function<Object[],V> combinator, Publisher<? extends T>... sources)

Build a Flux whose data are generated by the combination of the most recently published value from each of the Publisher sources.

- static <T,V> Flux<V> 	combineLatest(Iterable<? extends Publisher<? extends T>> sources, Function<Object[],V> combinator)

Build a Flux whose data are generated by the combination of the most recently published value from each of the Publisher sources provided in an Iterable.

- static <T,V> Flux<V> 	combineLatest(Iterable<? extends Publisher<? extends T>> sources, int prefetch, Function<Object[],V> combinator)

Build a Flux whose data are generated by the combination of the most recently published value from each of the Publisher sources provided in an Iterable.

- static <T1,T2,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, BiFunction<? super T1,? super T2,? extends V> combinator)

Build a Flux whose data are generated by the combination of the most recently published value from each of two Publisher sources.

- static <T1,T2,T3,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Function<Object[],V> combinator)

Build a Flux whose data are generated by the combination of the most recently published value from each of three Publisher sources.

- static <T1,T2,T3,T4,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Function<Object[],V> combinator)

Build a Flux whose data are generated by the combination of the most recently published value from each of four Publisher sources.

- static <T1,T2,T3,T4,T5,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, 
Publisher<? extends T4> source4, Publisher<? extends T5> source5, Function<Object[],V> combinator)

Build a Flux whose data are generated by the combination of the most recently published value from each of five Publisher sources.

- static <T1,T2,T3,T4,T5,T6,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, 
Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6, Function<Object[],V> combinator)

Build a Flux whose data are generated by the combination of the most recently published value from each of six Publisher sources.

#### concat method
- static <T> Flux<T> 	concat(Iterable<? extends Publisher<? extends T>> sources)

Concatenate all sources provided in an Iterable, forwarding elements emitted by the sources downstream.

- static <T> Flux<T> 	concat(Publisher<? extends Publisher<? extends T>> sources)

Concatenate all sources emitted as an onNext signal from a parent Publisher, forwarding elements emitted by the sources downstream.

- static <T> Flux<T> 	concat(Publisher<? extends Publisher<? extends T>> sources, int prefetch)

Concatenate all sources emitted as an onNext signal from a parent Publisher, forwarding elements emitted by the sources downstream.

- static <T> Flux<T> 	concat(Publisher<? extends T>... sources)

Concatenate all sources provided as a vararg, forwarding elements emitted by the sources downstream.

- static <T> Flux<T> 	concatDelayError(Publisher<? extends Publisher<? extends T>> sources)

Concatenate all sources emitted as an onNext signal from a parent Publisher, forwarding elements emitted by the sources downstream.

- static <T> Flux<T> 	concatDelayError(Publisher<? extends Publisher<? extends T>> sources, boolean delayUntilEnd, int prefetch)

Concatenate all sources emitted as an onNext signal from a parent Publisher, forwarding elements emitted by the sources downstream.

- static <T> Flux<T> 	concatDelayError(Publisher<? extends Publisher<? extends T>> sources, int prefetch)

Concatenate all sources emitted as an onNext signal from a parent Publisher, forwarding elements emitted by the sources downstream.

- static <T> Flux<T> 	concatDelayError(Publisher<? extends T>... sources)

Concatenate all sources provided as a vararg, forwarding elements emitted by the sources downstream.

#### create
- static <T> Flux<T> 	create(Consumer<? super FluxSink<T>> emitter)

Programmatically create a Flux with the capability of emitting multiple elements in a synchronous or asynchronous manner through the FluxSink API.

- static <T> Flux<T> 	create(Consumer<? super FluxSink<T>> emitter, FluxSink.OverflowStrategy backpressure)

Programmatically create a Flux with the capability of emitting multiple elements in a synchronous or asynchronous manner through the FluxSink API.

#### defer
- static <T> Flux<T> 	defer(Supplier<? extends Publisher<T>> supplier)

Lazily supply a Publisher every time a Subscription is made on the resulting Flux, so the actual source instantiation is deferred until each subscribe and the Supplier can create a subscriber-specific instance.

- static <T> Flux<T> 	deferContextual(Function<ContextView,? extends Publisher<T>> contextualPublisherFactory)

Lazily supply a Publisher every time a Subscription is made on the resulting Flux, so the actual source instantiation is deferred until each subscribe and the Function can create a subscriber-specific instance.

#### error
- static <T> Flux<T> 	empty()

Create a Flux that completes without emitting any item.

- static <T> Flux<T> 	error(Supplier<? extends Throwable> errorSupplier)

Create a Flux that terminates with an error immediately after being subscribed to.

- static <T> Flux<T> 	error(Throwable error)

Create a Flux that terminates with the specified error immediately after being subscribed to.

- static <O> Flux<O> 	error(Throwable throwable, boolean whenRequested)

Create a Flux that terminates with the specified error, either immediately after being subscribed to or after being first requested.

#### first
- static <I> Flux<I> 	firstWithSignal(Iterable<? extends Publisher<? extends I>> sources)

Pick the first Publisher to emit any signal (onNext/onError/onComplete) and replay all signals from that Publisher, effectively behaving like the fastest of these competing sources.

- static <I> Flux<I> 	firstWithSignal(Publisher<? extends I>... sources)

Pick the first Publisher to emit any signal (onNext/onError/onComplete) and replay all signals from that Publisher, effectively behaving like the fastest of these competing sources.

- static <I> Flux<I> 	firstWithValue(Iterable<? extends Publisher<? extends I>> sources)

Pick the first Publisher to emit any value and replay all values from that Publisher, effectively behaving like the source that first emits an onNext.

- static <I> Flux<I> 	firstWithValue(Publisher<? extends I> first, Publisher<? extends I>... others)

Pick the first Publisher to emit any value and replay all values from that Publisher, effectively behaving like the source that first emits an onNext.

#### from
- static <T> Flux<T> 	from(Publisher<? extends T> source)

Decorate the specified Publisher with the Flux API.

- static <T> Flux<T> 	fromArray(T[] array)

Create a Flux that emits the items contained in the provided array.

- static <T> Flux<T> 	fromIterable(Iterable<? extends T> it)

Create a Flux that emits the items contained in the provided Iterable.

- static <T> Flux<T> 	fromStream(Stream<? extends T> s)

Create a Flux that emits the items contained in the provided Stream.

- static <T> Flux<T> 	fromStream(Supplier<Stream<? extends T>> streamSupplier)

Create a Flux that emits the items contained in a Stream created by the provided Supplier for each subscription.

#### generate
- static <T,S> Flux<T> 	generate(Callable<S> stateSupplier, BiFunction<S,SynchronousSink<T>,S> generator)

Programmatically create a Flux by generating signals one-by-one via a consumer callback and some state.

- static <T,S> Flux<T> 	generate(Callable<S> stateSupplier, BiFunction<S,SynchronousSink<T>,S> generator, Consumer<? super S> stateConsumer)

Programmatically create a Flux by generating signals one-by-one via a consumer callback and some state, with a final cleanup callback.

- static <T> Flux<T> 	generate(Consumer<SynchronousSink<T>> generator)

Programmatically create a Flux by generating signals one-by-one via a consumer callback.

#### interval
- static Flux<Long> 	interval(Duration period)

Create a Flux that emits long values starting with 0 and incrementing at specified time intervals on the global timer.

- static Flux<Long> 	interval(Duration delay, Duration period)

Create a Flux that emits long values starting with 0 and incrementing at specified time intervals, after an initial delay, on the global timer.

- static Flux<Long> 	interval(Duration delay, Duration period, Scheduler timer)

Create a Flux that emits long values starting with 0 and incrementing at specified time intervals, after an initial delay, on the specified Scheduler.

- static Flux<Long> 	interval(Duration period, Scheduler timer)

Create a Flux that emits long values starting with 0 and incrementing at specified time intervals, on the specified Scheduler.

#### just
- static <T> Flux<T> 	just(T... data)

Create a Flux that emits the provided elements and then completes.

- static <T> Flux<T> 	just(T data)

Create a new Flux that will only emit a single element then onComplete.

#### merge
- static <I> Flux<I> 	merge(int prefetch, Publisher<? extends I>... sources)

Merge data from Publisher sequences contained in an array / vararg into an interleaved merged sequence.

- static <I> Flux<I> 	merge(Iterable<? extends Publisher<? extends I>> sources)

Merge data from Publisher sequences contained in an Iterable into an interleaved merged sequence.

- static <I> Flux<I> 	merge(Publisher<? extends I>... sources)

Merge data from Publisher sequences contained in an array / vararg into an interleaved merged sequence.

- static <T> Flux<T> 	merge(Publisher<? extends Publisher<? extends T>> source)

Merge data from Publisher sequences emitted by the passed Publisher into an interleaved merged sequence.

- static <T> Flux<T> 	merge(Publisher<? extends Publisher<? extends T>> source, int concurrency)

Merge data from Publisher sequences emitted by the passed Publisher into an interleaved merged sequence.

- static <T> Flux<T> 	merge(Publisher<? extends Publisher<? extends T>> source, int concurrency, int prefetch)

Merge data from Publisher sequences emitted by the passed Publisher into an interleaved merged sequence.

- static <I> Flux<I> 	mergeDelayError(int prefetch, Publisher<? extends I>... sources)

Merge data from Publisher sequences contained in an array / vararg into an interleaved merged sequence.

- static <T> Flux<T> 	mergeOrdered(Comparator<? super T> comparator, Publisher<? extends T>... sources)

Merge data from provided Publisher sequences into an ordered merged sequence, by picking the smallest values from each source (as defined by the provided Comparator).

- static <T> Flux<T> 	mergeOrdered(int prefetch, Comparator<? super T> comparator, Publisher<? extends T>... sources)

Merge data from provided Publisher sequences into an ordered merged sequence, by picking the smallest values from each source (as defined by the provided Comparator).

- static <I extends Comparable<? super I>> Flux<I> 	mergeOrdered(Publisher<? extends I>... sources)

Merge data from provided Publisher sequences into an ordered merged sequence, by picking the smallest values from each source (as defined by their natural order).

#### mergeSequential
- static <I> Flux<I> 	mergeSequential(int prefetch, Publisher<? extends I>... sources)

Merge data from Publisher sequences provided in an array/vararg into an ordered merged sequence.

- static <I> Flux<I> 	mergeSequential(Iterable<? extends Publisher<? extends I>> sources)

Merge data from Publisher sequences provided in an Iterable into an ordered merged sequence.

- static <I> Flux<I> 	mergeSequential(Iterable<? extends Publisher<? extends I>> sources, int maxConcurrency, int prefetch)

Merge data from Publisher sequences provided in an Iterable into an ordered merged sequence.

- static <I> Flux<I> 	mergeSequential(Publisher<? extends I>... sources)

Merge data from Publisher sequences provided in an array/vararg into an ordered merged sequence.

- static <T> Flux<T> 	mergeSequential(Publisher<? extends Publisher<? extends T>> sources)

Merge data from Publisher sequences emitted by the passed Publisher into an ordered merged sequence.

- static <T> Flux<T> 	mergeSequential(Publisher<? extends Publisher<? extends T>> sources, int maxConcurrency, int prefetch)

Merge data from Publisher sequences emitted by the passed Publisher into an ordered merged sequence.

- static <I> Flux<I> 	mergeSequentialDelayError(int prefetch, Publisher<? extends I>... sources)

Merge data from Publisher sequences provided in an array/vararg into an ordered merged sequence.

- static <I> Flux<I> 	mergeSequentialDelayError(Iterable<? extends Publisher<? extends I>> sources, int maxConcurrency, int prefetch)

Merge data from Publisher sequences provided in an Iterable into an ordered merged sequence.

- static <T> Flux<T> 	mergeSequentialDelayError(Publisher<? extends Publisher<? extends T>> sources, int maxConcurrency, int prefetch)

Merge data from Publisher sequences emitted by the passed Publisher into an ordered merged sequence.

- static <T> Flux<T> 	never()

Create a Flux that will never signal any data, error or completion signal.


#### push
- static <T> Flux<T> 	push(Consumer<? super FluxSink<T>> emitter)

Programmatically create a Flux with the capability of emitting multiple elements from a single-threaded producer through the FluxSink API.

- static <T> Flux<T> 	push(Consumer<? super FluxSink<T>> emitter, FluxSink.OverflowStrategy backpressure)

Programmatically create a Flux with the capability of emitting multiple elements from a single-threaded producer through the FluxSink API.

- static Flux<Integer> 	range(int start, int count)

Build a Flux that will only emit a sequence of count incrementing integers, starting from start.


#### switch
- static <T> Flux<T> 	switchOnNext(Publisher<? extends Publisher<? extends T>> mergedPublishers)

Creates a Flux that mirrors the most recently emitted Publisher, forwarding its data until a new Publisher comes in in the source.

- static <T> Flux<T> 	switchOnNext(Publisher<? extends Publisher<? extends T>> mergedPublishers, int prefetch)

Creates a Flux that mirrors the most recently emitted Publisher, forwarding its data until a new Publisher comes in in the source.

#### use
- static <T,D> Flux<T> 	using(Callable<? extends D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> sourceSupplier, Consumer<? super D> resourceCleanup)

Uses a resource, generated by a supplier for each individual Subscriber, while streaming the values from a Publisher derived from the same resource and makes sure the resource is released if the sequence terminates or the Subscriber cancels.

- static <T,D> Flux<T> 	using(Callable<? extends D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> sourceSupplier, Consumer<? super D> resourceCleanup, boolean eager)

Uses a resource, generated by a supplier for each individual Subscriber, while streaming the values from a Publisher derived from the same resource and makes sure the resource is released if the sequence terminates or the Subscriber cancels.

- static <T,D> Flux<T> 	usingWhen(Publisher<D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> resourceClosure, Function<? super D,? extends Publisher<?>> asyncCleanup)

Uses a resource, generated by a Publisher for each individual Subscriber, while streaming the values from a Publisher derived from the same resource.

- static <T,D> Flux<T> 	usingWhen(Publisher<D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> resourceClosure, Function<? super D,? extends Publisher<?>> asyncComplete, BiFunction<? super D,? super Throwable,? extends Publisher<?>> asyncError, Function<? super D,? extends Publisher<?>> asyncCancel)

Uses a resource, generated by a Publisher for each individual Subscriber, while streaming the values from a Publisher derived from the same resource.
	

#### zip
- static <I,O> Flux<O> 	zip(Function<? super Object[],? extends O> combinator, int prefetch, Publisher<? extends I>... sources)

Zip multiple sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).

- static <I,O> Flux<O> 	zip(Function<? super Object[],? extends O> combinator, Publisher<? extends I>... sources)

Zip multiple sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).

- static <O> Flux<O> 	zip(Iterable<? extends Publisher<?>> sources, Function<? super Object[],? extends O> combinator)

Zip multiple sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).

- static <O> Flux<O> 	zip(Iterable<? extends Publisher<?>> sources, int prefetch, Function<? super Object[],? extends O> combinator)

Zip multiple sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).

- static <TUPLE extends Tuple2,V> Flux<V> 	zip(Publisher<? extends Publisher<?>> sources, Function<? super TUPLE,? extends V> combinator)

Zip multiple sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).

- static <T1,T2> Flux<Tuple2<T1,T2>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2)

Zip two sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple2.

- static <T1,T2,O> Flux<O> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, BiFunction<? super T1,? super T2,? extends O> combinator)

Zip two sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).

- static <T1,T2,T3> Flux<Tuple3<T1,T2,T3>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3)

Zip three sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple3.

- static <T1,T2,T3,T4> Flux<Tuple4<T1,T2,T3,T4>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4)

Zip four sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple4.

- static <T1,T2,T3,T4,T5> Flux<Tuple5<T1,T2,T3,T4,T5>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5)

Zip five sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple5.

- static <T1,T2,T3,T4,T5,T6> Flux<Tuple6<T1,T2,T3,T4,T5,T6>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6)

Zip six sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple6.

- static <T1,T2,T3,T4,T5,T6,T7> Flux<Tuple7<T1,T2,T3,T4,T5,T6,T7>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6, Publisher<? extends T7> source7)

Zip seven sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple7.

- static <T1,T2,T3,T4,T5,T6,T7,T8> Flux<Tuple8<T1,T2,T3,T4,T5,T6,T7,T8>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6, Publisher<? extends T7> source7, Publisher<? extends T8> source8)

Zip eight sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple8.

