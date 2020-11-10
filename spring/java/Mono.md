# Java Mono
- [API doc](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/Mono.html)
![mono](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/doc-files/marbles/mono.svg)

## Method
### create
- static <T> Mono<T> 	create(Consumer<MonoSink<T>> callback)

Creates a deferred emitter that can be used with callback-based APIs to signal at most one value, a complete or an error signal.

### defer
- static <T> Mono<T> 	defer(Supplier<? extends Mono<? extends T>> supplier)

Create a Mono provider that will supply a target Mono to subscribe to for each Subscriber downstream.

- static <T> Mono<T> 	deferContextual(Function<ContextView,? extends Mono<? extends T>> contextualMonoFactory)

Create a Mono provider that will supply a target Mono to subscribe to for each Subscriber downstream.

- static Mono<Long> 	delay(Duration duration)

Create a Mono which delays an onNext signal by a given duration on a default Scheduler and completes.

- static Mono<Long> 	delay(Duration duration, Scheduler timer)

Create a Mono which delays an onNext signal by a given duration on a provided Scheduler and completes.

### error
- static <T> Mono<T> 	empty()

Create a Mono that completes without emitting any item.

- static <T> Mono<T> 	error(Supplier<? extends Throwable> errorSupplier)

Create a Mono that terminates with an error immediately after being subscribed to.

- static <T> Mono<T> 	error(Throwable error)

Create a Mono that terminates with the specified error immediately after being subscribed to.

### first
- static <T> Mono<T> 	firstWithSignal(Iterable<? extends Mono<? extends T>> monos)

Pick the first Mono to emit any signal (value, empty completion or error) and replay that signal, effectively behaving like the fastest of these competing sources.

- static <T> Mono<T> 	firstWithSignal(Mono<? extends T>... monos)

Pick the first Mono to emit any signal (value, empty completion or error) and replay that signal, effectively behaving like the fastest of these competing sources.

- static <T> Mono<T> 	firstWithValue(Iterable<? extends Mono<? extends T>> monos)

Pick the first Mono source to emit any value and replay that signal, effectively behaving like the source that first emits an onNext.

- static <T> Mono<T> 	firstWithValue(Mono<? extends T> first, Mono<? extends T>... others)

Pick the first Mono source to emit any value and replay that signal, effectively behaving like the source that first emits an onNext.

### from
- static <T> Mono<T> 	from(Publisher<? extends T> source)

Expose the specified Publisher with the Mono API, and ensure it will emit 0 or 1 item.

- static <T> Mono<T> 	fromCallable(Callable<? extends T> supplier)

Create a Mono producing its value using the provided Callable.

- static <T> Mono<T> 	fromCompletionStage(CompletionStage<? extends T> completionStage)

Create a Mono, producing its value using the provided CompletionStage.

- static <T> Mono<T> 	fromCompletionStage(Supplier<? extends CompletionStage<? extends T>> stageSupplier)

Create a Mono that wraps a CompletionStage on subscription, emitting the value produced by the CompletionStage.

- static <I> Mono<I> 	fromDirect(Publisher<? extends I> source)

Convert a Publisher to a Mono without any cardinality check (ie this method doesn't cancel the source past the first element).

- static <T> Mono<T> 	fromFuture(CompletableFuture<? extends T> future)

Create a Mono, producing its value using the provided CompletableFuture.

- static <T> Mono<T> 	fromFuture(Supplier<? extends CompletableFuture<? extends T>> futureSupplier)

Create a Mono that wraps a CompletableFuture on subscription, emitting the value produced by the Future.

- static <T> Mono<T> 	fromRunnable(Runnable runnable)

Create a Mono that completes empty once the provided Runnable has been executed.

- static <T> Mono<T> 	fromSupplier(Supplier<? extends T> supplier)

Create a Mono, producing its value using the provided Supplier.

### just

- static <T> Mono<T> 	ignoreElements(Publisher<T> source)

Create a new Mono that ignores elements from the source (dropping them), but completes when the source completes.

- static <T> Mono<T> 	just(T data)

Create a new Mono that emits the specified item, which is captured at instantiation time.

- static <T> Mono<T> 	justOrEmpty(Optional<? extends T> data)

Create a new Mono that emits the specified item if Optional.isPresent() otherwise only emits onComplete.

- static <T> Mono<T> 	justOrEmpty(T data)

Create a new Mono that emits the specified item if non null otherwise only emits onComplete.

- static <T> Mono<T> 	never()

Return a Mono that will never signal any data, error or completion signal, essentially running indefinitely.

### sequenceEqual

- static <T> Mono<Boolean> 	sequenceEqual(Publisher<? extends T> source1, Publisher<? extends T> source2)

Returns a Mono that emits a Boolean value that indicates whether two Publisher sequences are the same by comparing the items emitted by each Publisher pairwise.

- static <T> Mono<Boolean> 	sequenceEqual(Publisher<? extends T> source1, Publisher<? extends T> source2, BiPredicate<? super T,? super T> isEqual)

Returns a Mono that emits a Boolean value that indicates whether two Publisher sequences are the same by comparing the items emitted by each Publisher pairwise based on the results of a specified equality function.

- static <T> Mono<Boolean> 	sequenceEqual(Publisher<? extends T> source1, Publisher<? extends T> source2, BiPredicate<? super T,? super T> isEqual, int prefetch)

Returns a Mono that emits a Boolean value that indicates whether two Publisher sequences are the same by comparing the items emitted by each Publisher pairwise based on the results of a specified equality function.

### using
- static <T,D> Mono<T> 	using(Callable<? extends D> resourceSupplier, Function<? super D,? extends Mono<? extends T>> sourceSupplier, Consumer<? super D> resourceCleanup)

Uses a resource, generated by a supplier for each individual Subscriber, while streaming the value from a Mono derived from the same resource and makes sure the resource is released if the sequence terminates or the Subscriber cancels.

- static <T,D> Mono<T> 	using(Callable<? extends D> resourceSupplier, Function<? super D,? extends Mono<? extends T>> sourceSupplier, Consumer<? super D> resourceCleanup, boolean eager)

Uses a resource, generated by a supplier for each individual Subscriber, while streaming the value from a Mono derived from the same resource and makes sure the resource is released if the sequence terminates or the Subscriber cancels.

- static <T,D> Mono<T> 	usingWhen(Publisher<D> resourceSupplier, Function<? super D,? extends Mono<? extends T>> resourceClosure, Function<? super D,? extends Publisher<?>> asyncCleanup)

Uses a resource, generated by a Publisher for each individual Subscriber, to derive a Mono.

- static <T,D> Mono<T> 	usingWhen(Publisher<D> resourceSupplier, Function<? super D,? extends Mono<? extends T>> resourceClosure, Function<? super D,? extends Publisher<?>> asyncComplete, BiFunction<? super D,? super Throwable,? extends Publisher<?>> asyncError, Function<? super D,? extends Publisher<?>> asyncCancel)

Uses a resource, generated by a Publisher for each individual Subscriber, to derive a Mono.Note that all steps of the operator chain that would need the resource to be in an open stable state need to be described inside the resourceClosure Function.

#### when
- static Mono<Void> 	when(Iterable<? extends Publisher<?>> sources)

Aggregate given publishers into a new Mono that will be fulfilled when all of the given Publishers have completed.

- static Mono<Void> 	when(Publisher<?>... sources)

Aggregate given publishers into a new Mono that will be fulfilled when all of the given sources have completed.

- static Mono<Void> 	whenDelayError(Iterable<? extends Publisher<?>> sources)

Aggregate given publishers into a new Mono that will be fulfilled when all of the given sources have completed.

- static Mono<Void> 	whenDelayError(Publisher<?>... sources)

Merge given publishers into a new Mono that will be fulfilled when all of the given sources have completed.

#### zip
- static <R> Mono<R> 	zip(Function<? super Object[],? extends R> combinator, Mono<?>... monos)

Aggregate given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values according to the provided combinator function.

- static <R> Mono<R> 	zip(Iterable<? extends Mono<?>> monos, Function<? super Object[],? extends R> combinator)

Aggregate given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values according to the provided combinator function.

- static <T1,T2> Mono<Tuple2<T1,T2>> 	zip(Mono<? extends T1> p1, Mono<? extends T2> p2)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple2.

- static <T1,T2,O> Mono<O> 	zip(Mono<? extends T1> p1, Mono<? extends T2> p2, BiFunction<? super T1,? super T2,? extends O> combinator)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values as defined by the combinator function.

- static <T1,T2,T3> Mono<Tuple3<T1,T2,T3>> 	zip(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple3.

- static <T1,T2,T3,T4> Mono<Tuple4<T1,T2,T3,T4>> 	zip(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3, Mono<? extends T4> p4)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple4.

- static <T1,T2,T3,T4,T5> Mono<Tuple5<T1,T2,T3,T4,T5>> 	zip(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3, Mono<? extends T4> p4, Mono<? extends T5> p5)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple5.

- static <T1,T2,T3,T4,T5,T6> Mono<Tuple6<T1,T2,T3,T4,T5,T6>> 	zip(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3, Mono<? extends T4> p4, Mono<? extends T5> p5, Mono<? extends T6> p6)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple6.

- static <T1,T2,T3,T4,T5,T6,T7> Mono<Tuple7<T1,T2,T3,T4,T5,T6,T7>> 	zip(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3, Mono<? extends T4> p4, Mono<? extends T5> p5, Mono<? extends T6> p6, Mono<? extends T7> p7)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple7.

- static <T1,T2,T3,T4,T5,T6,T7,T8> Mono<Tuple8<T1,T2,T3,T4,T5,T6,T7,T8>> 	zip(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3, Mono<? extends T4> p4, Mono<? extends T5> p5, Mono<? extends T6> p6, Mono<? extends T7> p7, Mono<? extends T8> p8)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple8.

- static <R> Mono<R> 	zipDelayError(Function<? super Object[],? extends R> combinator, Mono<?>... monos)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values according to the provided combinator function and delaying errors.

- static <R> Mono<R> 	zipDelayError(Iterable<? extends Mono<?>> monos, Function<? super Object[],? extends R> combinator)

Aggregate given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item.

- static <T1,T2> Mono<Tuple2<T1,T2>> 	zipDelayError(Mono<? extends T1> p1, Mono<? extends T2> p2)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple2 and delaying errors.

- static <T1,T2,T3> Mono<Tuple3<T1,T2,T3>> 	zipDelayError(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3)

Merge given monos into a new Mono that will be fulfilled when all of the given Mono Monos have produced an item, aggregating their values into a Tuple3 and delaying errors.

- static <T1,T2,T3,T4> Mono<Tuple4<T1,T2,T3,T4>> 	zipDelayError(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3, Mono<? extends T4> p4)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple4 and delaying errors.

- static <T1,T2,T3,T4,T5> Mono<Tuple5<T1,T2,T3,T4,T5>> 	zipDelayError(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3, Mono<? extends T4> p4, Mono<? extends T5> p5)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple5 and delaying errors.

- static <T1,T2,T3,T4,T5,T6> Mono<Tuple6<T1,T2,T3,T4,T5,T6>> 	zipDelayError(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3, Mono<? extends T4> p4, Mono<? extends T5> p5, Mono<? extends T6> p6)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple6 and delaying errors.

- static <T1,T2,T3,T4,T5,T6,T7> Mono<Tuple7<T1,T2,T3,T4,T5,T6,T7>> 	zipDelayError(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3, Mono<? extends T4> p4, Mono<? extends T5> p5, Mono<? extends T6> p6, Mono<? extends T7> p7)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple7 and delaying errors.

- static <T1,T2,T3,T4,T5,T6,T7,T8> Mono<Tuple8<T1,T2,T3,T4,T5,T6,T7,T8>> 	zipDelayError(Mono<? extends T1> p1, Mono<? extends T2> p2, Mono<? extends T3> p3, Mono<? extends T4> p4, Mono<? extends T5> p5, Mono<? extends T6> p6, Mono<? extends T7> p7, Mono<? extends T8> p8)

Merge given monos into a new Mono that will be fulfilled when all of the given Monos have produced an item, aggregating their values into a Tuple8 and delaying errors.

