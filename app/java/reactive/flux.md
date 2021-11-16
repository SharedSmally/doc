# [Flud](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/Flux.html)


## Static methods
- create
- generate
- with


## buffer
| Method | description |
|--------|-------------|
|Flux<List<T>> 	buffer() | Collect all incoming values into a single List buffer that will be emitted by the returned Flux once this Flux completes.|
|Flux<List<T>> 	buffer(Duration bufferingTimespan) | Collect incoming values into multiple List buffers that will be emitted by the returned Flux every bufferingTimespan.
 | Flux<List<T>> 	buffer(Duration bufferingTimespan, Duration openBufferEvery) | Collect incoming values into multiple List buffers created at a given openBufferEvery period.
 | Flux<List<T>> 	buffer(Duration bufferingTimespan, Duration openBufferEvery, Scheduler timer) | Collect incoming values into multiple List buffers created at a given openBufferEvery period, as measured on the provided Scheduler.
 | Flux<List<T>> 	buffer(Duration bufferingTimespan, Scheduler timer) | Collect incoming values into multiple List buffers that will be emitted by the returned Flux every bufferingTimespan, as measured on the provided Scheduler.
 | Flux<List<T>> 	buffer(int maxSize) | Collect incoming values into multiple List buffers that will be emitted by the returned Flux each time the given max size is reached or once this Flux completes.
 | Flux<List<T>> 	buffer(int maxSize, int skip) | Collect incoming values into multiple List buffers that will be emitted by the returned Flux each time the given max size is reached or once this Flux completes.
 | <C extends Collection<? super T>> Flux<C> 	buffer(int maxSize, int skip, Supplier<C> bufferSupplier) | Collect incoming values into multiple user-defined Collection buffers that will be emitted by the returned Flux each time the given max size is reached or once this Flux completes.
 | <C extends Collection<? super T>>Flux<C> 	buffer(int maxSize, Supplier<C> bufferSupplier) | Collect incoming values into multiple user-defined Collection buffers that will be emitted by the returned Flux each time the given max size is reached or once this Flux completes.
 | Flux<List<T>> 	buffer(Publisher<?> other) | Collect incoming values into multiple List buffers, as delimited by the signals of a companion Publisher this operator will subscribe to.
 | <C extends Collection<? super T>> Flux<C> 	buffer(Publisher<?> other, Supplier<C> bufferSupplier) | Collect incoming values into multiple user-defined Collection buffers, as delimited by the signals of a companion Publisher this operator will subscribe to.
 | Flux<List<T>> 	bufferTimeout(int maxSize, Duration maxTime) | Collect incoming values into multiple List buffers that will be emitted by the returned Flux each time the buffer reaches a maximum size OR the maxTime Duration elapses.
 | Flux<List<T>> 	bufferTimeout(int maxSize, Duration maxTime, Scheduler timer) | Collect incoming values into multiple List buffers that will be emitted by the returned Flux each time the buffer reaches a maximum size OR the maxTime Duration elapses, as measured on the provided Scheduler.
 | <C extends Collection<? super T>>Flux<C> 	bufferTimeout(int maxSize, Duration maxTime, Scheduler timer, Supplier<C> bufferSupplier) | Collect incoming values into multiple user-defined Collection buffers that will be emitted by the returned Flux each time the buffer reaches a maximum size OR the maxTime Duration elapses, as measured on the provided Scheduler.
 | <C extends Collection<? super T>> Flux<C> 	bufferTimeout(int maxSize, Duration maxTime, Supplier<C> bufferSupplier) | Collect incoming values into multiple user-defined Collection buffers that will be emitted by the returned Flux each time the buffer reaches a maximum size OR the maxTime Duration elapses.
 | Flux<List<T>> 	bufferUntil(Predicate<? super T> predicate) | Collect incoming values into multiple List buffers that will be emitted by the resulting Flux each time the given predicate returns true.
 | Flux<List<T>> 	bufferUntil(Predicate<? super T> predicate, boolean cutBefore) | Collect incoming values into multiple List buffers that will be emitted by the resulting Flux each time the given predicate returns true.
 | <V> Flux<List<T>> 	bufferUntilChanged() | Collect subsequent repetitions of an element (that is, if they arrive right after one another) into multiple List buffers that will be emitted by the resulting Flux.
 | <V> Flux<List<T>> 	bufferUntilChanged(Function<? super T,? extends V> keySelector) | Collect subsequent repetitions of an element (that is, if they arrive right after one another), as compared by a key extracted through the user provided Function, into multiple List buffers that will be emitted by the resulting Flux.
 | <V> Flux<List<T>> 	bufferUntilChanged(Function<? super T,? extends V> keySelector, BiPredicate<? super V,? super V> keyComparator) | Collect subsequent repetitions of an element (that is, if they arrive right after one another), as compared by a key extracted through the user provided Function and compared using a supplied BiPredicate, into multiple List buffers that will be emitted by the resulting Flux.
 | <U,V> Flux<List<T>> 	bufferWhen(Publisher<U> bucketOpening, Function<? super U,? extends Publisher<V>> closeSelector) | Collect incoming values into multiple List buffers started each time an opening companion Publisher emits.
 | <U,V,C extends Collection<? super T>> Flux<C> 	bufferWhen(Publisher<U> bucketOpening, Function<? super U,? extends Publisher<V>> closeSelector, Supplier<C> bufferSupplier) | Collect incoming values into multiple user-defined Collection buffers started each time an opening companion Publisher emits.
 | Flux<List<T>> 	bufferWhile(Predicate<? super T> predicate) | Collect incoming values into multiple List buffers that will be emitted by the resulting Flux. | 

## Cache
| Flux<T> 	cache()  | Turn this Flux into a hot source and cache last emitted signals for further Subscriber.
|Flux<T> 	cache(Duration ttl) | Turn this Flux into a hot source and cache last emitted signals for further Subscriber.
|Flux<T> 	cache(Duration ttl, Scheduler timer) | Turn this Flux into a hot source and cache last emitted signals for further Subscriber.
|Flux<T> 	cache(int history) | Turn this Flux into a hot source and cache last emitted signals for further Subscriber.
|Flux<T> 	cache(int history, Duration ttl) | Turn this Flux into a hot source and cache last emitted signals for further Subscriber.
|Flux<T> 	cache(int history, Duration ttl, Scheduler timer) | Turn this Flux into a hot source and cache last emitted signals for further Subscriber.
|Flux<T> 	cancelOn(Scheduler scheduler) | Prepare this Flux so that subscribers will cancel from it on a specified Scheduler.

## checkpoint
| Method | description |
|--------|-------------|
 | Flux<T> 	checkpoint() | Activate traceback (full assembly tracing) for this particular Flux, in case of an error upstream of the checkpoint.
 | Flux<T> 	checkpoint(String description) | Activate traceback (assembly marker) for this particular Flux by giving it a description that will be reflected in the assembly traceback in case of an error upstream of the checkpoint.
 | Flux<T> 	checkpoint(String description, boolean forceStackTrace) | Activate traceback (full assembly tracing or the lighter assembly marking depending on the forceStackTrace option).

## collect
| Method | description |
|--------|-------------|
 | <R,A> Mono<R> 	collect(Collector<? super T,A,? extends R> collector) |  | Collect all elements emitted by this Flux into a container, by applying a Java 8 Stream API Collector The collected result will be emitted when this sequence completes, emitting the empty container if the sequence was empty.
 | <E> Mono<E> 	collect(Supplier<E> containerSupplier, BiConsumer<E,? super T> collector) | Collect all elements emitted by this Flux into a user-defined container, by applying a collector BiConsumer taking the container and each element.
 | Mono<List<T>> 	collectList() | Collect all elements emitted by this Flux into a List that is emitted by the resulting Mono when this sequence completes, emitting the empty List if the sequence was empty.
 | <K> Mono<Map<K,T>> 	collectMap(Function<? super T,? extends K> keyExtractor) | Collect all elements emitted by this Flux into a hashed Map that is emitted by the resulting Mono when this sequence completes, emitting the empty Map if the sequence was empty.
 | <K,V> Mono<Map<K,V>> 	collectMap(Function<? super T,? extends K> keyExtractor, Function<? super T,? extends V> valueExtractor) | Collect all elements emitted by this Flux into a hashed Map that is emitted by the resulting Mono when this sequence completes, emitting the empty Map if the sequence was empty.
 | <K,V> Mono<Map<K,V>> 	collectMap(Function<? super T,? extends K> keyExtractor, Function<? super T,? extends V> valueExtractor, Supplier<Map<K,V>> mapSupplier) | Collect all elements emitted by this Flux into a user-defined Map that is emitted by the resulting Mono when this sequence completes, emitting the empty Map if the sequence was empty.
 | <K> Mono<Map<K,Collection<T>>> 	collectMultimap(Function<? super T,? extends K> keyExtractor) | Collect all elements emitted by this Flux into a multimap that is emitted by the resulting Mono when this sequence completes, emitting the empty multimap if the sequence was empty.
 | <K,V> Mono<Map<K,Collection<V>>> 	collectMultimap(Function<? super T,? extends K> keyExtractor, Function<? super T,? extends V> valueExtractor) | Collect all elements emitted by this Flux into a multimap that is emitted by the resulting Mono when this sequence completes, emitting the empty multimap if the sequence was empty.
 | <K,V> Mono<Map<K,Collection<V>>> 	collectMultimap(Function<? super T,? extends K> keyExtractor, Function<? super T,? extends V> valueExtractor, Supplier<Map<K,Collection<V>>> mapSupplier) | Collect all elements emitted by this Flux into a user-defined multimap that is emitted by the resulting Mono when this sequence completes, emitting the empty multimap if the sequence was empty.
 | Mono<List<T>> 	collectSortedList() | Collect all elements emitted by this Flux until this sequence completes, and then sort them in natural order into a List that is emitted by the resulting Mono.
 | Mono<List<T>> 	collectSortedList(Comparator<? super T> comparator) | Collect all elements emitted by this Flux until this sequence completes, and then sort them using a Comparator into a List that is emitted by the resulting Mono.

## combine
| Method | description |
|--------|-------------|
 | static <T,V> Flux<V> 	combineLatest(Function<Object[],V> combinator, int prefetch, Publisher<? extends T>... sources) | Build a Flux whose data are generated by the combination of the most recently published value from each of the Publisher sources.
 | static <T,V> Flux<V> 	combineLatest(Function<Object[],V> combinator, Publisher<? extends T>... sources) | Build a Flux whose data are generated by the combination of the most recently published value from each of the Publisher sources.
 | static <T,V> Flux<V> 	combineLatest(Iterable<? extends Publisher<? extends T>> sources, Function<Object[],V> combinator) | Build a Flux whose data are generated by the combination of the most recently published value from each of the Publisher sources provided in an Iterable.
 | static <T,V> Flux<V> 	combineLatest(Iterable<? extends Publisher<? extends T>> sources, int prefetch, Function<Object[],V> combinator) | Build a Flux whose data are generated by the combination of the most recently published value from each of the Publisher sources provided in an Iterable.
 | static <T1,T2,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, BiFunction<? super T1,? super T2,? extends V> combinator) | Build a Flux whose data are generated by the combination of the most recently published value from each of two Publisher sources.
 | static <T1,T2,T3,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Function<Object[],V> combinator) | Build a Flux whose data are generated by the combination of the most recently published value from each of three Publisher sources.
 | static <T1,T2,T3,T4,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Function<Object[],V> combinator) | Build a Flux whose data are generated by the combination of the most recently published value from each of four Publisher sources.
 | static <T1,T2,T3,T4,T5,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Function<Object[],V> combinator) | Build a Flux whose data are generated by the combination of the most recently published value from each of five Publisher sources.
 | static <T1,T2,T3,T4,T5,T6,V> Flux<V> 	combineLatest(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6, Function<Object[],V> combinator) | Build a Flux whose data are generated by the combination of the most recently published value from each of six Publisher sources.

## concat
| Method | description |
|--------|-------------|
 | static <T> Flux<T> 	concat(Iterable<? extends Publisher<? extends T>> sources) | Concatenate all sources provided in an Iterable, forwarding elements emitted by the sources downstream.
 | static <T> Flux<T> 	concat(Publisher<? extends Publisher<? extends T>> sources) | Concatenate all sources emitted as an onNext signal from a parent Publisher, forwarding elements emitted by the sources downstream.
 | static <T> Flux<T> 	concat(Publisher<? extends Publisher<? extends T>> sources, int prefetch) | Concatenate all sources emitted as an onNext signal from a parent Publisher, forwarding elements emitted by the sources downstream.
 | static <T> Flux<T> 	concat(Publisher<? extends T>... sources) | Concatenate all sources provided as a vararg, forwarding elements emitted by the sources downstream.
 | static <T> Flux<T> 	concatDelayError(Publisher<? extends Publisher<? extends T>> sources) | Concatenate all sources emitted as an onNext signal from a parent Publisher, forwarding elements emitted by the sources downstream.
 | static <T> Flux<T> 	concatDelayError(Publisher<? extends Publisher<? extends T>> sources, boolean delayUntilEnd, int prefetch) | Concatenate all sources emitted as an onNext signal from a parent Publisher, forwarding elements emitted by the sources downstream.
 | static <T> Flux<T> 	concatDelayError(Publisher<? extends Publisher<? extends T>> sources, int prefetch) | Concatenate all sources emitted as an onNext signal from a parent Publisher, forwarding elements emitted by the sources downstream.
 | static <T> Flux<T> 	concatDelayError(Publisher<? extends T>... sources) | Concatenate all sources provided as a vararg, forwarding elements emitted by the sources downstream.
 | <V> Flux<V> 	concatMap(Function<? super T,? extends Publisher<? extends V>> mapper) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux, sequentially and preserving order using concatenation.
 | <V> Flux<V> 	concatMap(Function<? super T,? extends Publisher<? extends V>> mapper, int prefetch) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux, sequentially and preserving order using concatenation.
 | <V> Flux<V> 	concatMapDelayError(Function<? super T,? extends Publisher<? extends V>> mapper) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux, sequentially and preserving order using concatenation.
 | <V> Flux<V> 	concatMapDelayError(Function<? super T,? extends Publisher<? extends V>> mapper, boolean delayUntilEnd, int prefetch) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux, sequentially and preserving order using concatenation.
 | <V> Flux<V> 	concatMapDelayError(Function<? super T,? extends Publisher<? extends V>> mapper, int prefetch) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux, sequentially and preserving order using concatenation.
 | <R> Flux<R> 	concatMapIterable(Function<? super T,? extends Iterable<? extends R>> mapper) | Transform the items emitted by this Flux into Iterable, then flatten the elements from those by concatenating them into a single Flux.
 | <R> Flux<R> 	concatMapIterable(Function<? super T,? extends Iterable<? extends R>> mapper, int prefetch) | Transform the items emitted by this Flux into Iterable, then flatten the emissions from those by concatenating them into a single Flux.
 | Flux<T> 	concatWith(Publisher<? extends T> other) | Concatenate emissions of this Flux with the provided Publisher (no interleave).
 | Flux<T> 	concatWithValues(T... values) | Concatenates the values to the end of the Flux

## create
| Method | description |
|--------|-------------|
 | static <T> Flux<T> 	create(Consumer<? super FluxSink<T>> emitter) | Programmatically create a Flux with the capability of emitting multiple elements in a synchronous or asynchronous manner through the FluxSink API.
 | static <T> Flux<T> 	create(Consumer<? super FluxSink<T>> emitter, FluxSink.OverflowStrategy backpressure) | Programmatically create a Flux with the capability of emitting multiple elements in a synchronous or asynchronous manner through the FluxSink API.

## defer
 | static <T> Flux<T> 	defer(Supplier<? extends Publisher<T>> supplier) | Lazily supply a Publisher every time a Subscription is made on the resulting Flux, so the actual source instantiation is deferred until each subscribe and the Supplier can create a subscriber-specific instance.
 | static <T> Flux<T> 	deferContextual(Function<ContextView,? extends Publisher<T>> contextualPublisherFactory) | Lazily supply a Publisher every time a Subscription is made on the resulting Flux, so the actual source instantiation is deferred until each subscribe and the Function can create a subscriber-specific instance.
 | static <T> Flux<T> 	deferWithContext(Function<Context,? extends Publisher<T>> contextualPublisherFactory) | Deprecated. use deferContextual(Function)

## delay
| Method | description |
|--------|-------------|
 | Flux<T> 	delayElements(Duration delay) | Delay each of this Flux elements (Subscriber.onNext(T) signals) by a given Duration.
 | Flux<T> 	delayElements(Duration delay, Scheduler timer) | Delay each of this Flux elements (Subscriber.onNext(T) signals) by a given Duration.
 | Flux<T> 	delaySequence(Duration delay) | Shift this Flux forward in time by a given Duration.
 | Flux<T> 	delaySequence(Duration delay, Scheduler timer) | Shift this Flux forward in time by a given Duration.
 | Flux<T> 	delaySubscription(Duration delay) | Delay the subscription to this Flux source until the given period elapses.
 | Flux<T> 	delaySubscription(Duration delay, Scheduler timer) | Delay the subscription to this Flux source until the given period elapses, as measured on the user-provided Scheduler.
 | <U> Flux<T> 	delaySubscription(Publisher<U> subscriptionDelay) | Delay the subscription to this Flux source until another Publisher signals a value or completes.
 | Flux<T> 	delayUntil(Function<? super T,? extends Publisher<?>> triggerProvider) | Subscribe to this Flux and generate a Publisher from each of this Flux elements, each acting as a trigger for relaying said element.


# Misc
| Method | description |
|--------|-------------|
Mono<Boolean> 	all(Predicate<? super T> predicate)
Emit a single boolean true if all values of this sequence match the Predicate.
Mono<Boolean> 	any(Predicate<? super T> predicate)
Emit a single boolean true if any of the values of this Flux sequence match the predicate.
<P> P 	as(Function<? super Flux<T>,P> transformer)
Transform this Flux into a target type.

## block
 | T 	blockFirst() | Subscribe to this Flux and block indefinitely until the upstream signals its first value or completes. | 
 | T 	blockFirst(Duration timeout) | Subscribe to this Flux and block until the upstream signals its first value, completes or a timeout expires. | 
 | T 	blockLast() | Subscribe to this Flux and block indefinitely until the upstream signals its last value or completes. | 
 | T 	blockLast(Duration timeout) | Subscribe to this Flux and block until the upstream signals its last value, completes or a timeout expires. | 


<E> Flux<E> 	cast(Class<E> clazz)
Cast the current Flux produced type into a target produced type.



Flux<T> 	contextWrite(ContextView contextToAppend)
Enrich the Context visible from downstream for the benefit of upstream operators, by making all values from the provided ContextView visible on top of pairs from downstream.
Flux<T> 	contextWrite(Function<Context,Context> contextModifier)
Enrich the Context visible from downstream for the benefit of upstream operators, by applying a Function to the downstream Context.
Mono<Long> 	count()
Counts the number of values in this Flux.


Flux<T> 	defaultIfEmpty(T defaultV)
Provide a default unique value if this sequence is completed without any data

<X> Flux<X> 	dematerialize()
An operator working only if this Flux emits onNext, onError or onComplete Signal instances, transforming these materialized signals into real signals on the Subscriber.

## distinct
| Method | description |
|--------|-------------|
 | Flux<T> 	distinct() | For each Subscriber, track elements from this Flux that have been seen and filter out duplicates. | 
 | <V> Flux<T> 	distinct(Function<? super T,? extends V> keySelector) | For each Subscriber, track elements from this Flux that have been seen and filter out duplicates, as compared by a key extracted through the user provided Function. | 
 | <V,C extends Collection<? super V>> Flux<T> 	distinct(Function<? super T,? extends V> keySelector, Supplier<C> distinctCollectionSupplier) | For each Subscriber, track elements from this Flux that have been seen and filter out duplicates, as compared by a key extracted through the user provided Function and by the add method of the Collection supplied (typically a Set).
 | <V,C> Flux<T> 	distinct(Function<? super T,? extends V> keySelector, Supplier<C> distinctStoreSupplier, BiPredicate<C,V> distinctPredicate, Consumer<C> cleanup) | For each Subscriber, track elements from this Flux that have been seen and filter out duplicates, as compared by applying a BiPredicate on an arbitrary user-supplied <C> store and a key extracted through the user provided Function.
 | Flux<T> 	distinctUntilChanged() | Filter out subsequent repetitions of an element (that is, if they arrive right after one another).
 | <V> Flux<T> 	distinctUntilChanged(Function<? super T,? extends V> keySelector) | Filter out subsequent repetitions of an element (that is, if they arrive right after one another), as compared by a key extracted through the user provided Function using equality.
 | <V> Flux<T> 	distinctUntilChanged(Function<? super T,? extends V> keySelector, BiPredicate<? super V,? super V> keyComparator) | Filter out subsequent repetitions of an element (that is, if they arrive right after one another), as compared by a key extracted through the user provided Function and then comparing keys with the supplied BiPredicate.

## do
| Method | description |
|--------|-------------|
 | Flux<T> 	doAfterTerminate(Runnable afterTerminate) | Add behavior (side-effect) triggered after the Flux terminates, either by completing downstream successfully or with an error.
 | Flux<T> 	doFinally(Consumer<SignalType> onFinally) | Add behavior (side-effect) triggered after the Flux terminates for any reason, including cancellation.
 | Flux<T> 	doFirst(Runnable onFirst) | Add behavior (side-effect) triggered before the Flux is subscribed to, which should be the first event after assembly time.
 | Flux<T> 	doOnCancel(Runnable onCancel) | Add behavior (side-effect) triggered when the Flux is cancelled.
 | Flux<T> 	doOnComplete(Runnable onComplete) | Add behavior (side-effect) triggered when the Flux completes successfully.
 | <R> Flux<T> 	doOnDiscard(Class<R> type, Consumer<? super R> discardHook) | Potentially modify the behavior of the whole chain of operators upstream of this one to conditionally clean up elements that get discarded by these operators.
 | Flux<T> 	doOnEach(Consumer<? super Signal<T>> signalConsumer) | Add behavior (side-effects) triggered when the Flux emits an item, fails with an error or completes successfully.
 | <E extends Throwable> Flux<T> 	doOnError(Class<E> exceptionType, Consumer<? super E> onError) | Add behavior (side-effect) triggered when the Flux completes with an error matching the given exception type.
 | Flux<T> 	doOnError(Consumer<? super Throwable> onError) | Add behavior (side-effect) triggered when the Flux completes with an error.
 | Flux<T> 	doOnError(Predicate<? super Throwable> predicate, Consumer<? super Throwable> onError) | Add behavior (side-effect) triggered when the Flux completes with an error matching the given exception.
 | Flux<T> 	doOnNext(Consumer<? super T> onNext) | Add behavior (side-effect) triggered when the Flux emits an item.
 | Flux<T> 	doOnRequest(LongConsumer consumer) | Add behavior (side-effect) triggering a LongConsumer when this Flux receives any request.
 | Flux<T> 	doOnSubscribe(Consumer<? super Subscription> onSubscribe) | Add behavior (side-effect) triggered when the Flux is being subscribed, that is to say when a Subscription has been produced by the Publisher and is being passed to the Subscriber.onSubscribe(Subscription).
 | Flux<T> 	doOnTerminate(Runnable onTerminate) | Add behavior (side-effect) triggered when the Flux terminates, either by completing successfully or failing with an error.

## elapsed
| Method | description |
|--------|-------------|
 | Flux<Tuple2<Long,T>> 	elapsed() | Map this Flux into Tuple2<Long, T> of timemillis and source data.
 | Flux<Tuple2<Long,T>> 	elapsed(Scheduler scheduler) | Map this Flux into Tuple2<Long, T> of timemillis and source data.

 | Mono<T> 	elementAt(int index) | Emit only the element at the given index position or IndexOutOfBoundsException if the sequence is shorter.
 | Mono<T> 	elementAt(int index, T defaultValue) | Emit only the element at the given index position or fall back to a default value if the sequence is shorter.
 | static <T> Flux<T> 	empty() | Create a Flux that completes without emitting any item.

## error
| Method | description |
|--------|-------------|
 | static <T> Flux<T> 	error(Supplier<? extends Throwable> errorSupplier) | Create a Flux that terminates with an error immediately after being subscribed to.
 | static <T> Flux<T> 	error(Throwable error) | Create a Flux that terminates with the specified error immediately after being subscribed to.
 | static <O> Flux<O> 	error(Throwable throwable, boolean whenRequested) | Create a Flux that terminates with the specified error, either immediately after being subscribed to or after being first requested.

## expand
| Method | description |
|--------|-------------|
 | Flux<T> 	expand(Function<? super T,? extends Publisher<? extends T>> expander) | Recursively expand elements into a graph and emit all the resulting element using a breadth-first traversal strategy.
 | Flux<T> 	expand(Function<? super T,? extends Publisher<? extends T>> expander, int capacityHint) | Recursively expand elements into a graph and emit all the resulting element using a breadth-first traversal strategy.
 | Flux<T> 	expandDeep(Function<? super T,? extends Publisher<? extends T>> expander) | Recursively expand elements into a graph and emit all the resulting element, in a depth-first traversal order.
 | Flux<T> 	expandDeep(Function<? super T,? extends Publisher<? extends T>> expander, int capacityHint) | Recursively expand elements into a graph and emit all the resulting element, in a depth-first traversal order.

## filter
| Method | description |
|--------|-------------|
 | Flux<T> 	filter(Predicate<? super T> p) | Evaluate each source value against the given Predicate. | 
 | Flux<T> 	filterWhen(Function<? super T,? extends Publisher<Boolean>> asyncPredicate) | Test each value emitted by this Flux asynchronously using a generated Publisher<Boolean> test. | 
 | Flux<T> 	filterWhen(Function<? super T,? extends Publisher<Boolean>> asyncPredicate, int bufferSize) | Test each value emitted by this Flux asynchronously using a generated Publisher<Boolean> test. | 

## first
| Method | description |
|--------|-------------|
 | static <I> Flux<I> 	first(Iterable<? extends Publisher<? extends I>> sources) | Deprecated. use firstWithSignal(Iterable). To be removed in reactor 3.5.
 | static <I> Flux<I> 	first(Publisher<? extends I>... sources) | Deprecated. use firstWithSignal(Publisher[]). To be removed in reactor 3.5.
 | static <I> Flux<I> 	firstWithSignal(Iterable<? extends Publisher<? extends I>> sources) | Pick the first Publisher to emit any signal (onNext/onError/onComplete) and replay all signals from that Publisher, effectively behaving like the fastest of these competing sources.
 | static <I> Flux<I> 	firstWithSignal(Publisher<? extends I>... sources) | Pick the first Publisher to emit any signal (onNext/onError/onComplete) and replay all signals from that Publisher, effectively behaving like the fastest of these competing sources.
 | static <I> Flux<I> 	firstWithValue(Iterable<? extends Publisher<? extends I>> sources) | Pick the first Publisher to emit any value and replay all values from that Publisher, effectively behaving like the source that first emits an onNext.
 | static <I> Flux<I> 	firstWithValue(Publisher<? extends I> first, Publisher<? extends I>... others) | Pick the first Publisher to emit any value and replay all values from that Publisher, effectively behaving like the source that first emits an onNext.


## flatmap
| Method | description |
|--------|-------------|
 | <R> Flux<R> 	flatMap(Function<? super T,? extends Publisher<? extends R>> mapper) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux through merging, which allow them to interleave.
 | <R> Flux<R> 	flatMap(Function<? super T,? extends Publisher<? extends R>> mapperOnNext, Function<? super Throwable,? extends Publisher<? extends R>> mapperOnError, Supplier<? extends Publisher<? extends R>> mapperOnComplete)  | Transform the signals emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux through merging, which allow them to interleave.
 | <V> Flux<V> 	flatMap(Function<? super T,? extends Publisher<? extends V>> mapper, int concurrency) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux through merging, which allow them to interleave.
 | <V> Flux<V> 	flatMap(Function<? super T,? extends Publisher<? extends V>> mapper, int concurrency, int prefetch) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux through merging, which allow them to interleave.
 | <V> Flux<V> 	flatMapDelayError(Function<? super T,? extends Publisher<? extends V>> mapper, int concurrency, int prefetch) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux through merging, which allow them to interleave.
 | <R> Flux<R> 	flatMapIterable(Function<? super T,? extends Iterable<? extends R>> mapper) | Transform the items emitted by this Flux into Iterable, then flatten the elements from those by merging them into a single Flux.
 | <R> Flux<R> 	flatMapIterable(Function<? super T,? extends Iterable<? extends R>> mapper, int prefetch) | Transform the items emitted by this Flux into Iterable, then flatten the emissions from those by merging them into a single Flux.
 | <R> Flux<R> 	flatMapSequential(Function<? super T,? extends Publisher<? extends R>> mapper) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux, but merge them in the order of their source element.
 | <R> Flux<R> 	flatMapSequential(Function<? super T,? extends Publisher<? extends R>> mapper, int maxConcurrency) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux, but merge them in the order of their source element.
 | <R> Flux<R> 	flatMapSequential(Function<? super T,? extends Publisher<? extends R>> mapper, int maxConcurrency, int prefetch) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux, but merge them in the order of their source element.
 | <R> Flux<R> 	flatMapSequentialDelayError(Function<? super T,? extends Publisher<? extends R>> mapper, int maxConcurrency, int prefetch) | Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux, but merge them in the order of their source element.

## from
| Method | description |
|--------|-------------|
 | static <T> Flux<T> 	from(Publisher<? extends T> source) | Decorate the specified Publisher with the Flux API. | 
 | static <T> Flux<T> 	fromArray(T[] array) | Create a Flux that emits the items contained in the provided array.
 | static <T> Flux<T> 	fromIterable(Iterable<? extends T> it) | Create a Flux that emits the items contained in the provided Iterable.
 | static <T> Flux<T> 	fromStream(Stream<? extends T> s) | Create a Flux that emits the items contained in the provided Stream.
 | static <T> Flux<T> 	fromStream(Supplier<Stream<? extends T>> streamSupplier) | Create a Flux that emits the items contained in a Stream created by the provided Supplier for each subscription.

## generate
| Method | description |
|--------|-------------|
 | static <T,S> Flux<T> 	generate(Callable<S> stateSupplier, BiFunction<S,SynchronousSink<T>,S> generator) | Programmatically create a Flux by generating signals one-by-one via a consumer callback and some state.
 | static <T,S> Flux<T> 	generate(Callable<S> stateSupplier, BiFunction<S,SynchronousSink<T>,S> generator, Consumer<? super S> stateConsumer) | Programmatically create a Flux by generating signals one-by-one via a consumer callback and some state, with a final cleanup callback.
 | static <T> Flux<T> 	generate(Consumer<SynchronousSink<T>> generator) | Programmatically create a Flux by generating signals one-by-one via a consumer callback.

int 	getPrefetch()
The prefetch configuration of the Flux

## groupby
| Method | description |
|--------|-------------|
 | <K> Flux<GroupedFlux<K,T>> 	groupBy(Function<? super T,? extends K> keyMapper) | Divide this sequence into dynamically created Flux (or groups) for each unique key, as produced by the provided keyMapper Function.
 | <K,V> Flux<GroupedFlux<K,V>> 	groupBy(Function<? super T,? extends K> keyMapper, Function<? super T,? extends V> valueMapper) | Divide this sequence into dynamically created Flux (or groups) for each unique key, as produced by the provided keyMapper Function.
 | <K,V> Flux<GroupedFlux<K,V>> 	groupBy(Function<? super T,? extends K> keyMapper, Function<? super T,? extends V> valueMapper, int prefetch) | Divide this sequence into dynamically created Flux (or groups) for each unique key, as produced by the provided keyMapper Function.
 | <K> Flux<GroupedFlux<K,T>> 	groupBy(Function<? super T,? extends K> keyMapper, int prefetch) | Divide this sequence into dynamically created Flux (or groups) for each unique key, as produced by the provided keyMapper Function.
 | <TRight,TLeftEnd,TRightEnd,R> Flux<R> 	groupJoin(Publisher<? extends TRight> other, Function<? super T,? extends Publisher<TLeftEnd>> leftEnd, Function<? super TRight,? extends Publisher<TRightEnd>> rightEnd, BiFunction<? super T,? super Flux<TRight>,? extends R> resultSelector) | Map values from two Publishers into time windows and emit combination of values in case their windows overlap.


<R> Flux<R> 	handle(BiConsumer<? super T,SynchronousSink<R>> handler)
Handle the items emitted by this Flux by calling a biconsumer with the output sink for each onNext.
Mono<Boolean> 	hasElement(T value)
Emit a single boolean true if any of the elements of this Flux sequence is equal to the provided value.
Mono<Boolean> 	hasElements()
Emit a single boolean true if this Flux sequence has at least one element.
Flux<T> 	hide()
Hides the identities of this Flux instance.
Mono<T> 	ignoreElements()
Ignores onNext signals (dropping them) and only propagate termination events.
Flux<Tuple2<Long,T>> 	index()
Keep information about the order in which source values were received by indexing them with a 0-based incrementing long, returning a Flux of Tuple2<(index, value)>.
<I> Flux<I> 	index(BiFunction<? super Long,? super T,? extends I> indexMapper)
Keep information about the order in which source values were received by indexing them internally with a 0-based incrementing long then combining this information with the source value into a I using the provided BiFunction, returning a Flux<I>.

## interval
| Method | description |
|--------|-------------|
 | static Flux<Long> 	interval(Duration period) | Create a Flux that emits long values starting with 0 and incrementing at specified time intervals on the global timer.
 | static Flux<Long> 	interval(Duration delay, Duration period) | Create a Flux that emits long values starting with 0 and incrementing at specified time intervals, after an initial delay, on the global timer.
 | static Flux<Long> 	interval(Duration delay, Duration period, Scheduler timer) | Create a Flux that emits long values starting with 0 and incrementing at specified time intervals, after an initial delay, on the specified Scheduler.
 | static Flux<Long> 	interval(Duration period, Scheduler timer) | Create a Flux that emits long values starting with 0 and incrementing at specified time intervals, on the specified Scheduler.


 | <TRight,TLeftEnd,TRightEnd,R> | Flux<R> 	join(Publisher<? extends TRight> other, Function<? super T,? extends Publisher<TLeftEnd>> leftEnd, Function<? super TRight,? extends Publisher<TRightEnd>> rightEnd, BiFunction<? super T,? super TRight,? extends R> resultSelector) | Combine values from two Publishers in case their windows overlap.

## just
| Method | description |
|--------|-------------|
 | static <T> Flux<T> 	just(T... data) | Create a Flux that emits the provided elements and then completes. | 
 | static <T> Flux<T> 	just(T data) | Create a new Flux that will only emit a single element then onComplete. | 

## first/last
 | Mono<T> 	last() | Emit the last element observed before complete signal as a Mono, or emit NoSuchElementException error if the source was empty. | 
 | Mono<T> 	last(T defaultValue) | Emit the last element observed before complete signal as a Mono, or emit the defaultValue if the source was empty. | 

## limit
| Method | description |
|--------|-------------|
 | Flux<T> 	limitRate(int prefetchRate) | Ensure that backpressure signals from downstream subscribers are split into batches capped at the provided prefetchRate when propagated upstream, effectively rate limiting the upstream Publisher. | 
 | Flux<T> 	limitRate(int highTide, int lowTide) | Ensure that backpressure signals from downstream subscribers are split into batches capped at the provided highTide first, then replenishing at the provided lowTide, effectively rate limiting the upstream Publisher.
 | Flux<T> 	limitRequest(long n) | Deprecated. replace with take(n, true) in 3.4.x, then take(long) in 3.5.0. To be removed in 3.6.0 at the earliest. See https://github.com/reactor/reactor-core/issues/2339

## log
| Method | description |
|--------|-------------|
 | Flux<T> 	log() | Observe all Reactive Streams signals and trace them using Logger support. | 
 | Flux<T> 	log(Logger logger) | Observe Reactive Streams signals matching the passed filter options and trace them using a specific user-provided Logger, at Level.INFO level. | 
 | Flux<T> 	log(Logger logger, Level level, boolean showOperatorLine, SignalType... options) | Observe Reactive Streams signals matching the passed filter options and trace them using a specific user-provided Logger, at the given Level. | 
 | Flux<T> 	log(String category) | Observe all Reactive Streams signals and trace them using Logger support. | 
 | Flux<T> 	log(String category, Level level, boolean showOperatorLine, SignalType... options) | Observe Reactive Streams signals matching the passed filter options and trace them using Logger support. | 
 | Flux<T> 	log(String category, Level level, SignalType... options) | Observe Reactive Streams signals matching the passed filter options and trace them using Logger support. | 

## map
| Method | description |
|--------|-------------|
 | <V> Flux<V> 	map(Function<? super T,? extends V> mapper) | Transform the items emitted by this Flux by applying a synchronous function to each item. | 
 | <V> Flux<V> 	mapNotNull(Function<? super T,? extends V> mapper) | Transform the items emitted by this Flux by applying a synchronous function to each item, which may produce null values. | 

 | Flux<Signal<T>> 	materialize() | Transform incoming onNext, onError and onComplete signals into Signal instances, materializing these signals. | 

## merge
| Method | description |
|--------|-------------|
 | static <I> Flux<I> 	merge(int prefetch, Publisher<? extends I>... sources) | Merge data from Publisher sequences contained in an array / vararg into an interleaved merged sequence. | 
 | static <I> Flux<I> 	merge(Iterable<? extends Publisher<? extends I>> sources) | Merge data from Publisher sequences contained in an Iterable into an interleaved merged sequence. | 
 | static <I> Flux<I> 	merge(Publisher<? extends I>... sources) | Merge data from Publisher sequences contained in an array / vararg into an interleaved merged sequence. | 
 | static <T> Flux<T> 	merge(Publisher<? extends Publisher<? extends T>> source) | Merge data from Publisher sequences emitted by the passed Publisher into an interleaved merged sequence. | 
 | static <T> Flux<T> 	merge(Publisher<? extends Publisher<? extends T>> source, int concurrency) | Merge data from Publisher sequences emitted by the passed Publisher into an interleaved merged sequence. | 
 | static <T> Flux<T> 	merge(Publisher<? extends Publisher<? extends T>> source, int concurrency, int prefetch) | Merge data from Publisher sequences emitted by the passed Publisher into an interleaved merged sequence. | 
 | static <T> Flux<T> 	mergeComparing(Comparator<? super T> comparator, Publisher<? extends T>... sources) |  Merge data from provided Publisher sequences into an ordered merged sequence, by picking the smallest values from each source (as defined by the provided Comparator). | 
 | static <T> Flux<T> 	mergeComparing(int prefetch, Comparator<? super T> comparator, Publisher<? extends T>... sources) | Merge data from provided Publisher sequences into an ordered merged sequence, by picking the smallest values from each source (as defined by the provided Comparator). | 
 | static <I extends Comparable<? super I>> Flux<I> 	mergeComparing(Publisher<? extends I>... sources) | Merge data from provided Publisher sequences into an ordered merged sequence, by picking the smallest values from each source (as defined by their natural order). | 
 | static <T> Flux<T> 	mergeComparingDelayError(int prefetch, Comparator<? super T> comparator, Publisher<? extends T>... sources) | Merge data from provided Publisher sequences into an ordered merged sequence, by picking the smallest values from each source (as defined by the provided Comparator).
 | Flux<T> 	mergeComparingWith(Publisher<? extends T> other, Comparator<? super T> otherComparator) | Merge data from this Flux and a Publisher into a reordered merge sequence, by picking the smallest value from each sequence as defined by a provided Comparator.
 | static <I> Flux<I> 	mergeDelayError(int prefetch, Publisher<? extends I>... sources) | Merge data from Publisher sequences contained in an array / vararg into an interleaved merged sequence.
 | static <T> Flux<T> 	mergeOrdered(Comparator<? super T> comparator, Publisher<? extends T>... sources) | Deprecated. Use mergeComparingDelayError(int, Comparator, Publisher[]) instead (as mergeComparing(Publisher[]) don't have this operator's delayError behavior). To be removed in 3.6.0 at the earliest. | 
 | static <T> Flux<T> 	mergeOrdered(int prefetch, Comparator<? super T> comparator, Publisher<? extends T>... sources) | Deprecated. Use mergeComparingDelayError(int, Comparator, Publisher[]) instead (as mergeComparing(Publisher[]) don't have this operator's delayError behavior). To be removed in 3.6.0 at the earliest. | 
 | static <I extends Comparable<? super I>> Flux<I> 	mergeOrdered(Publisher<? extends I>... sources) | Deprecated. Use mergeComparingDelayError(int, Comparator, Publisher[]) instead (as mergeComparing(Publisher[]) don't have this operator's delayError behavior). To be removed in 3.6.0 at the earliest. | 
 | Flux<T> 	mergeOrderedWith(Publisher<? extends T> other, Comparator<? super T> otherComparator) | Deprecated. Use mergeComparingWith(Publisher, Comparator) instead (with the caveat that it defaults to NOT delaying errors, unlike this operator). To be removed in 3.6.0 at the earliest. | 
 | static <I> Flux<I> 	mergeSequential(int prefetch, Publisher<? extends I>... sources) | Merge data from Publisher sequences provided in an array/vararg into an ordered merged sequence. | 
 | static <I> Flux<I> 	mergeSequential(Iterable<? extends Publisher<? extends I>> sources) | Merge data from Publisher sequences provided in an Iterable into an ordered merged sequence. | 
 | static <I> Flux<I> 	mergeSequential(Iterable<? extends Publisher<? extends I>> sources, int maxConcurrency, int prefetch) | Merge data from Publisher sequences provided in an Iterable into an ordered merged sequence.
 | static <I> Flux<I> 	mergeSequential(Publisher<? extends I>... sources) | Merge data from Publisher sequences provided in an array/vararg into an ordered merged sequence.
 | static <T> Flux<T> 	mergeSequential(Publisher<? extends Publisher<? extends T>> sources) | Merge data from Publisher sequences emitted by the passed Publisher into an ordered merged sequence.
 | static <T> Flux<T> 	mergeSequential(Publisher<? extends Publisher<? extends T>> sources, int maxConcurrency, int prefetch) | Merge data from Publisher sequences emitted by the passed Publisher into an ordered merged sequence.
 | static <I> Flux<I> 	mergeSequentialDelayError(int prefetch, Publisher<? extends I>... sources) | Merge data from Publisher sequences provided in an array/vararg into an ordered merged sequence.
 | static <I> Flux<I> 	mergeSequentialDelayError(Iterable<? extends Publisher<? extends I>> sources, int maxConcurrency, int prefetch) | Merge data from Publisher sequences provided in an Iterable into an ordered merged sequence.
 | static <T> Flux<T> 	mergeSequentialDelayError(Publisher<? extends Publisher<? extends T>> sources, int maxConcurrency, int prefetch) | Merge data from Publisher sequences emitted by the passed Publisher into an ordered merged sequence.
 | Flux<T> 	mergeWith(Publisher<? extends T> other) | Merge data from this Flux and a Publisher into an interleaved merged sequence. | 

 | Flux<T> 	metrics() | Activate metrics for this sequence, provided there is an instrumentation facade on the classpath (otherwise this method is a pure no-op). | 
 | Flux<T> 	name(String name) | Give a name to this sequence, which can be retrieved using Scannable.name() as long as this is the first reachable Scannable.parents(). | 

 | static <T> Flux<T> 	never() | Create a Flux that will never signal any data, error or completion signal. | 
 | Mono<T> 	next() | Emit only the first item emitted by this Flux, into a new Mono. | 
 | <U> Flux<U> 	ofType(Class<U> clazz) | Evaluate each accepted value against the given Class type. | 

## onXxx
| Method | description |
|--------|-------------|
protected static <T> ConnectableFlux<T> 	onAssembly(ConnectableFlux<T> source)
To be used by custom operators: invokes assembly Hooks pointcut given a ConnectableFlux, potentially returning a new ConnectableFlux.
protected static <T> Flux<T> 	onAssembly(Flux<T> source)
To be used by custom operators: invokes assembly Hooks pointcut given a Flux, potentially returning a new Flux.
Flux<T> 	onBackpressureBuffer()
Request an unbounded demand and push to the returned Flux, or park the observed elements if not enough demand is requested downstream.
Flux<T> 	onBackpressureBuffer(Duration ttl, int maxSize, Consumer<? super T> onBufferEviction)
Request an unbounded demand and push to the returned Flux, or park the observed elements if not enough demand is requested downstream, within a maxSize limit and for a maximum Duration of ttl (as measured on the parallel Scheduler).
Flux<T> 	onBackpressureBuffer(Duration ttl, int maxSize, Consumer<? super T> onBufferEviction, Scheduler scheduler)
Request an unbounded demand and push to the returned Flux, or park the observed elements if not enough demand is requested downstream, within a maxSize limit and for a maximum Duration of ttl (as measured on the provided Scheduler).
Flux<T> 	onBackpressureBuffer(int maxSize)
Request an unbounded demand and push to the returned Flux, or park up to maxSize elements when not enough demand is requested downstream.
Flux<T> 	onBackpressureBuffer(int maxSize, BufferOverflowStrategy bufferOverflowStrategy)
Request an unbounded demand and push to the returned Flux, or park the observed elements if not enough demand is requested downstream, within a maxSize limit.
Flux<T> 	onBackpressureBuffer(int maxSize, Consumer<? super T> onOverflow)
Request an unbounded demand and push to the returned Flux, or park up to maxSize elements when not enough demand is requested downstream.
Flux<T> 	onBackpressureBuffer(int maxSize, Consumer<? super T> onBufferOverflow, BufferOverflowStrategy bufferOverflowStrategy)
Request an unbounded demand and push to the returned Flux, or park the observed elements if not enough demand is requested downstream, within a maxSize limit.
Flux<T> 	onBackpressureDrop()
Request an unbounded demand and push to the returned Flux, or drop the observed elements if not enough demand is requested downstream.
Flux<T> 	onBackpressureDrop(Consumer<? super T> onDropped)
Request an unbounded demand and push to the returned Flux, or drop and notify dropping Consumer with the observed elements if not enough demand is requested downstream.
Flux<T> 	onBackpressureError()
Request an unbounded demand and push to the returned Flux, or emit onError fom Exceptions.failWithOverflow() if not enough demand is requested downstream.
Flux<T> 	onBackpressureLatest()
Request an unbounded demand and push to the returned Flux, or only keep the most recent observed item if not enough demand is requested downstream.

## onError
| Method | description |
|--------|-------------|
Flux<T> 	onErrorContinue(BiConsumer<Throwable,Object> errorConsumer)
Let compatible operators upstream recover from errors by dropping the incriminating element from the sequence and continuing with subsequent elements.
<E extends Throwable>
Flux<T> 	onErrorContinue(Class<E> type, BiConsumer<Throwable,Object> errorConsumer)
Let compatible operators upstream recover from errors by dropping the incriminating element from the sequence and continuing with subsequent elements.
<E extends Throwable>
Flux<T> 	onErrorContinue(Predicate<E> errorPredicate, BiConsumer<Throwable,Object> errorConsumer)
Let compatible operators upstream recover from errors by dropping the incriminating element from the sequence and continuing with subsequent elements.
<E extends Throwable>
Flux<T> 	onErrorMap(Class<E> type, Function<? super E,? extends Throwable> mapper)
Transform an error emitted by this Flux by synchronously applying a function to it if the error matches the given type.
Flux<T> 	onErrorMap(Function<? super Throwable,? extends Throwable> mapper)
Transform any error emitted by this Flux by synchronously applying a function to it.
Flux<T> 	onErrorMap(Predicate<? super Throwable> predicate, Function<? super Throwable,? extends Throwable> mapper)
Transform an error emitted by this Flux by synchronously applying a function to it if the error matches the given predicate.
<E extends Throwable>
Flux<T> 	onErrorResume(Class<E> type, Function<? super E,? extends Publisher<? extends T>> fallback)
Subscribe to a fallback publisher when an error matching the given type occurs, using a function to choose the fallback depending on the error.
Flux<T> 	onErrorResume(Function<? super Throwable,? extends Publisher<? extends T>> fallback)
Subscribe to a returned fallback publisher when any error occurs, using a function to choose the fallback depending on the error.
Flux<T> 	onErrorResume(Predicate<? super Throwable> predicate, Function<? super Throwable,? extends Publisher<? extends T>> fallback)
Subscribe to a fallback publisher when an error matching a given predicate occurs.
<E extends Throwable>
Flux<T> 	onErrorReturn(Class<E> type, T fallbackValue)
Simply emit a captured fallback value when an error of the specified type is observed on this Flux.
Flux<T> 	onErrorReturn(Predicate<? super Throwable> predicate, T fallbackValue)
Simply emit a captured fallback value when an error matching the given predicate is observed on this Flux.
Flux<T> 	onErrorReturn(T fallbackValue)
Simply emit a captured fallback value when any error is observed on this Flux.
Flux<T> 	onErrorStop()
If an onErrorContinue(BiConsumer) variant has been used downstream, reverts to the default 'STOP' mode where errors are terminal events upstream.
Flux<T> 	onTerminateDetach()
Detaches both the child Subscriber and the Subscription on termination or cancellation.

Flux<T> 	or(Publisher<? extends T> other)
Pick the first Publisher between this Flux and another publisher to emit any signal (onNext/onError/onComplete) and replay all signals from that Publisher, effectively behaving like the fastest of these competing sources.

## parallel
| Method | description |
|--------|-------------|
ParallelFlux<T> 	parallel()
Prepare this Flux by dividing data on a number of 'rails' matching the number of CPU cores, in a round-robin fashion.
ParallelFlux<T> 	parallel(int parallelism)
Prepare this Flux by dividing data on a number of 'rails' matching the provided parallelism parameter, in a round-robin fashion.
ParallelFlux<T> 	parallel(int parallelism, int prefetch)
Prepare this Flux by dividing data on a number of 'rails' matching the provided parallelism parameter, in a round-robin fashion and using a custom prefetch amount and queue for dealing with the source Flux's values.

## publish
| Method | description |
|--------|-------------|
ConnectableFlux<T> 	publish()
Prepare a ConnectableFlux which shares this Flux sequence and dispatches values to subscribers in a backpressure-aware manner.
<R> Flux<R> 	publish(Function<? super Flux<T>,? extends Publisher<? extends R>> transform)
Shares a sequence for the duration of a function that may transform it and consume it as many times as necessary without causing multiple subscriptions to the upstream.
<R> Flux<R> 	publish(Function<? super Flux<T>,? extends Publisher<? extends R>> transform, int prefetch)
Shares a sequence for the duration of a function that may transform it and consume it as many times as necessary without causing multiple subscriptions to the upstream.
ConnectableFlux<T> 	publish(int prefetch)
Prepare a ConnectableFlux which shares this Flux sequence and dispatches values to subscribers in a backpressure-aware manner.
Mono<T> 	publishNext()
Deprecated. 
use shareNext() instead, or use `publish().next()` if you need to `connect(). To be removed in 3.5.0
Flux<T> 	publishOn(Scheduler scheduler)
Run onNext, onComplete and onError on a supplied Scheduler Worker.
Flux<T> 	publishOn(Scheduler scheduler, boolean delayError, int prefetch)
Run onNext, onComplete and onError on a supplied Scheduler Scheduler.Worker.
Flux<T> 	publishOn(Scheduler scheduler, int prefetch)
Run onNext, onComplete and onError on a supplied Scheduler Scheduler.Worker.

## push
| Method | description |
|--------|-------------|
static <T> Flux<T> 	push(Consumer<? super FluxSink<T>> emitter)
Programmatically create a Flux with the capability of emitting multiple elements from a single-threaded producer through the FluxSink API.
static <T> Flux<T> 	push(Consumer<? super FluxSink<T>> emitter, FluxSink.OverflowStrategy backpressure)
Programmatically create a Flux with the capability of emitting multiple elements from a single-threaded producer through the FluxSink API.

## range
| Method | description |
|--------|-------------|
static Flux<Integer> 	range(int start, int count)
Build a Flux that will only emit a sequence of count incrementing integers, starting from start.

## reduce
| Method | description |
|--------|-------------|
<A> Mono<A> 	reduce(A initial, BiFunction<A,? super T,A> accumulator)
Reduce the values from this Flux sequence into a single object matching the type of a seed value.
Mono<T> 	reduce(BiFunction<T,T,T> aggregator)
Reduce the values from this Flux sequence into a single object of the same type than the emitted items.
<A> Mono<A> 	reduceWith(Supplier<A> initial, BiFunction<A,? super T,A> accumulator)
Reduce the values from this Flux sequence into a single object matching the type of a lazily supplied seed value.

## repeat
| Method | description |
|--------|-------------|
Flux<T> 	repeat()
Repeatedly and indefinitely subscribe to the source upon completion of the previous subscription.
Flux<T> 	repeat(BooleanSupplier predicate)
Repeatedly subscribe to the source if the predicate returns true after completion of the previous subscription.
Flux<T> 	repeat(long numRepeat)
Repeatedly subscribe to the source numRepeat times.
Flux<T> 	repeat(long numRepeat, BooleanSupplier predicate)
Repeatedly subscribe to the source if the predicate returns true after completion of the previous subscription.
Flux<T> 	repeatWhen(Function<Flux<Long>,? extends Publisher<?>> repeatFactory)
Repeatedly subscribe to this Flux when a companion sequence emits elements in response to the flux completion signal.

## replay  
 | Method | description |
|--------|-------------|
ConnectableFlux<T> 	replay()
Turn this Flux into a hot source and cache last emitted signals for further Subscriber.
ConnectableFlux<T> 	replay(Duration ttl)
Turn this Flux into a connectable hot source and cache last emitted signals for further Subscriber.
ConnectableFlux<T> 	replay(Duration ttl, Scheduler timer)
Turn this Flux into a connectable hot source and cache last emitted signals for further Subscriber.
ConnectableFlux<T> 	replay(int history)
Turn this Flux into a connectable hot source and cache last emitted signals for further Subscriber.
ConnectableFlux<T> 	replay(int history, Duration ttl)
Turn this Flux into a connectable hot source and cache last emitted signals for further Subscriber.
ConnectableFlux<T> 	replay(int history, Duration ttl, Scheduler timer)
Turn this Flux into a connectable hot source and cache last emitted signals for further Subscriber.

## retry  
 | Method | description |
|--------|-------------|
Flux<T> 	retry()
Re-subscribes to this Flux sequence if it signals any error, indefinitely.
Flux<T> 	retry(long numRetries)
Re-subscribes to this Flux sequence if it signals any error, for a fixed number of times.
Flux<T> 	retryWhen(Retry retrySpec)
Retries this Flux in response to signals emitted by a companion Publisher.

## sample  
 | Method | description |
|--------|-------------|
Flux<T> 	sample(Duration timespan)
Sample this Flux by periodically emitting an item corresponding to that Flux latest emitted value within the periodical time window.
<U> Flux<T> 	sample(Publisher<U> sampler)
Sample this Flux by emitting an item corresponding to that Flux latest emitted value whenever a companion sampler Publisher signals a value.
Flux<T> 	sampleFirst(Duration timespan)
Repeatedly take a value from this Flux then skip the values that follow within a given duration.
<U> Flux<T> 	sampleFirst(Function<? super T,? extends Publisher<U>> samplerFactory)
Repeatedly take a value from this Flux then skip the values that follow before the next signal from a companion sampler Publisher.
<U> Flux<T> 	sampleTimeout(Function<? super T,? extends Publisher<U>> throttlerFactory)
Emit the latest value from this Flux only if there were no new values emitted during the window defined by a companion Publisher derived from that particular value.
<U> Flux<T> 	sampleTimeout(Function<? super T,? extends Publisher<U>> throttlerFactory, int maxConcurrency)
Emit the latest value from this Flux only if there were no new values emitted during the window defined by a companion Publisher derived from that particular value.

## scan
| Method | description |
|--------|-------------|
<A> Flux<A> 	scan(A initial, BiFunction<A,? super T,A> accumulator)
Reduce this Flux values with an accumulator BiFunction and also emit the intermediate results of this function.
Flux<T> 	scan(BiFunction<T,T,T> accumulator)
Reduce this Flux values with an accumulator BiFunction and also emit the intermediate results of this function.
<A> Flux<A> 	scanWith(Supplier<A> initial, BiFunction<A,? super T,A> accumulator)
Reduce this Flux values with the help of an accumulator BiFunction and also emits the intermediate results.

## share/single
| Method | description |
|--------|-------------|
Flux<T> 	share()
Returns a new Flux that multicasts (shares) the original Flux.
Mono<T> 	shareNext()
Prepare a Mono which shares this Flux sequence and dispatches the first observed item to subscribers.
Mono<T> 	single()
Expect and emit a single item from this Flux source or signal NoSuchElementException for an empty source, or IndexOutOfBoundsException for a source with more than one element.
Mono<T> 	single(T defaultValue)
Expect and emit a single item from this Flux source and emit a default value for an empty source, but signal an IndexOutOfBoundsException for a source with more than one element.
Mono<T> 	singleOrEmpty()
Expect and emit a single item from this Flux source, and accept an empty source but signal an IndexOutOfBoundsException for a source with more than one element.

## skip
| Method | description |
|--------|-------------|
Flux<T> 	skip(Duration timespan)
Skip elements from this Flux emitted within the specified initial duration.
Flux<T> 	skip(Duration timespan, Scheduler timer)
Skip elements from this Flux emitted within the specified initial duration, as measured on the provided Scheduler.
Flux<T> 	skip(long skipped)
Skip the specified number of elements from the beginning of this Flux then emit the remaining elements.
Flux<T> 	skipLast(int n)
Skip a specified number of elements at the end of this Flux sequence.
Flux<T> 	skipUntil(Predicate<? super T> untilPredicate)
Skips values from this Flux until a Predicate returns true for the value.
Flux<T> 	skipUntilOther(Publisher<?> other)
Skip values from this Flux until a specified Publisher signals an onNext or onComplete.
Flux<T> 	skipWhile(Predicate<? super T> skipPredicate)
Skips values from this Flux while a Predicate returns true for the value.

## sort
| Method | description |
|--------|-------------|
Flux<T> 	sort()
Sort elements from this Flux by collecting and sorting them in the background then emitting the sorted sequence once this sequence completes.
Flux<T> 	sort(Comparator<? super T> sortFunction)
Sort elements from this Flux using a Comparator function, by collecting and sorting elements in the background then emitting the sorted sequence once this sequence completes.

## startwith
| Method | description |
|--------|-------------|
Flux<T> 	startWith(Iterable<? extends T> iterable)
Prepend the given Iterable before this Flux sequence.
Flux<T> 	startWith(Publisher<? extends T> publisher)
Prepend the given Publisher sequence to this Flux sequence.
Flux<T> 	startWith(T... values)
Prepend the given values before this Flux sequence.

## subscribe
| Method | description |
|--------|-------------|
Disposable 	subscribe()
Subscribe to this Flux and request unbounded demand.
Disposable 	subscribe(Consumer<? super T> consumer)
Subscribe a Consumer to this Flux that will consume all the elements in the sequence.
Disposable 	subscribe(Consumer<? super T> consumer, Consumer<? super Throwable> errorConsumer)
Subscribe to this Flux with a Consumer that will consume all the elements in the sequence, as well as a Consumer that will handle errors.
Disposable 	subscribe(Consumer<? super T> consumer, Consumer<? super Throwable> errorConsumer, Runnable completeConsumer)
Subscribe Consumer to this Flux that will respectively consume all the elements in the sequence, handle errors and react to completion.
Disposable 	subscribe(Consumer<? super T> consumer, Consumer<? super Throwable> errorConsumer, Runnable completeConsumer, Consumer<? super Subscription> subscriptionConsumer)
Deprecated. 
Because users tend to forget to request the subsciption. If the behavior is really needed, consider using subscribeWith(Subscriber). To be removed in 3.5.
Disposable 	subscribe(Consumer<? super T> consumer, Consumer<? super Throwable> errorConsumer, Runnable completeConsumer, Context initialContext)
Subscribe Consumer to this Flux that will respectively consume all the elements in the sequence, handle errors and react to completion.
abstract void 	subscribe(CoreSubscriber<? super T> actual)
An internal Publisher.subscribe(Subscriber) that will bypass Hooks.onLastOperator(Function) pointcut.
void 	subscribe(Subscriber<? super T> actual) 
Flux<T> 	subscribeOn(Scheduler scheduler)
Run subscribe, onSubscribe and request on a specified Scheduler's Scheduler.Worker.
Flux<T> 	subscribeOn(Scheduler scheduler, boolean requestOnSeparateThread)
Run subscribe and onSubscribe on a specified Scheduler's Scheduler.Worker.
Flux<T> 	subscriberContext(Context mergeContext)
Deprecated. Use contextWrite(ContextView) instead. To be removed in 3.5.0.
Flux<T> 	subscriberContext(Function<Context,Context> doOnContext)
Deprecated. Use contextWrite(Function) instead. To be removed in 3.5.0.
<E extends Subscriber<? super T>>
E 	subscribeWith(E subscriber)
Subscribe the given Subscriber to this Flux and return said Subscriber (eg.

## switch
| Method | description |
|--------|-------------|
Flux<T> 	switchIfEmpty(Publisher<? extends T> alternate)
Switch to an alternative Publisher if this sequence is completed without any data.
<V> Flux<V> 	switchMap(Function<? super T,Publisher<? extends V>> fn)
Switch to a new Publisher generated via a Function whenever this Flux produces an item.
<V> Flux<V> 	switchMap(Function<? super T,Publisher<? extends V>> fn, int prefetch)
Deprecated. to be removed in 3.6.0 at the earliest. In 3.5.0, you should replace calls with prefetch=0 with calls to switchMap(fn), as the default behavior of the single-parameter variant will then change to prefetch=0.
<V> Flux<V> 	switchOnFirst(BiFunction<Signal<? extends T>,Flux<T>,Publisher<? extends V>> transformer)
Transform the current Flux once it emits its first element, making a conditional transformation possible.
<V> Flux<V> 	switchOnFirst(BiFunction<Signal<? extends T>,Flux<T>,Publisher<? extends V>> transformer, boolean cancelSourceOnComplete)
Transform the current Flux once it emits its first element, making a conditional transformation possible.
static <T> Flux<T> 	switchOnNext(Publisher<? extends Publisher<? extends T>> mergedPublishers)
Creates a Flux that mirrors the most recently emitted Publisher, forwarding its data until a new Publisher comes in in the source.
static <T> Flux<T> 	switchOnNext(Publisher<? extends Publisher<? extends T>> mergedPublishers, int prefetch)
Deprecated. to be removed in 3.6.0 at the earliest. In 3.5.0, you should replace calls with prefetch=0 with calls to switchOnNext(mergedPublishers), as the default behavior of the single-parameter variant will then change to prefetch=0.

## tag
| Method | description |
|--------|-------------|
Flux<T> 	tag(String key, String value)
Tag this flux with a key/value pair.

## take
| Method | description |
|--------|-------------|
Flux<T> 	take(Duration timespan)
Relay values from this Flux until the specified Duration elapses.
Flux<T> 	take(Duration timespan, Scheduler timer)
Relay values from this Flux until the specified Duration elapses, as measured on the specified Scheduler.
Flux<T> 	take(long n)
Take only the first N values from this Flux, if available.
Flux<T> 	take(long n, boolean limitRequest)
Take only the first N values from this Flux, if available.
Flux<T> 	takeLast(int n)
Emit the last N values this Flux emitted before its completion.
Flux<T> 	takeUntil(Predicate<? super T> predicate)
Relay values from this Flux until the given Predicate matches.
Flux<T> 	takeUntilOther(Publisher<?> other)
Relay values from this Flux until the given Publisher emits.
Flux<T> 	takeWhile(Predicate<? super T> continuePredicate)
Relay values from this Flux while a predicate returns TRUE for the values (checked before each value is delivered).

## then
| Method | description |
|--------|-------------|
Mono<Void> 	then()
Return a Mono<Void> that completes when this Flux completes.
<V> Mono<V> 	then(Mono<V> other)
Let this Flux complete then play signals from a provided Mono.
Mono<Void> 	thenEmpty(Publisher<Void> other)
Return a Mono<Void> that waits for this Flux to complete then for a supplied Publisher<Void> to also complete.
<V> Flux<V> 	thenMany(Publisher<V> other)
Let this Flux complete then play another Publisher.

## time
| Method | description |
|--------|-------------|
Flux<Timed<T>> 	timed()
Times Subscriber.onNext(Object) events, encapsulated into a Timed object that lets downstream consumer look at various time information gathered with nanosecond resolution using the default clock (Schedulers.parallel()): Timed.elapsed(): the time in nanoseconds since last event, as a Duration.
Flux<Timed<T>> 	timed(Scheduler clock)
Times Subscriber.onNext(Object) events, encapsulated into a Timed object that lets downstream consumer look at various time information gathered with nanosecond resolution using the provided Scheduler as a clock: Timed.elapsed(): the time in nanoseconds since last event, as a Duration.
Flux<T> 	timeout(Duration timeout)
Propagate a TimeoutException as soon as no item is emitted within the given Duration from the previous emission (or the subscription for the first item).
Flux<T> 	timeout(Duration timeout, Publisher<? extends T> fallback)
Switch to a fallback Flux as soon as no item is emitted within the given Duration from the previous emission (or the subscription for the first item).
Flux<T> 	timeout(Duration timeout, Publisher<? extends T> fallback, Scheduler timer)
Switch to a fallback Flux as soon as no item is emitted within the given Duration from the previous emission (or the subscription for the first item), as measured on the specified Scheduler.
Flux<T> 	timeout(Duration timeout, Scheduler timer)
Propagate a TimeoutException as soon as no item is emitted within the given Duration from the previous emission (or the subscription for the first item), as measured by the specified Scheduler.
<U> Flux<T> 	timeout(Publisher<U> firstTimeout)
Signal a TimeoutException in case the first item from this Flux has not been emitted before the given Publisher emits.
<U,V> Flux<T> 	timeout(Publisher<U> firstTimeout, Function<? super T,? extends Publisher<V>> nextTimeoutFactory)
Signal a TimeoutException in case the first item from this Flux has not been emitted before the firstTimeout Publisher emits, and whenever each subsequent elements is not emitted before a Publisher generated from the latest element signals.
<U,V> Flux<T> 	timeout(Publisher<U> firstTimeout, Function<? super T,? extends Publisher<V>> nextTimeoutFactory, Publisher<? extends T> fallback)
Switch to a fallback Publisher in case the first item from this Flux has not been emitted before the firstTimeout Publisher emits, and whenever each subsequent elements is not emitted before a Publisher generated from the latest element signals.
Flux<Tuple2<Long,T>> 	timestamp()
Emit a Tuple2 pair of T1 the current clock time in millis (as a Long measured by the parallel Scheduler) and T2 the emitted data (as a T), for each item from this Flux.
Flux<Tuple2<Long,T>> 	timestamp(Scheduler scheduler)
Emit a Tuple2 pair of T1 the current clock time in millis (as a Long measured by the provided Scheduler) and T2 the emitted data (as a T), for each item from this Flux.

## to
| Method | description |
|--------|-------------|
Iterable<T> 	toIterable()
Transform this Flux into a lazy Iterable blocking on Iterator.next() calls.
Iterable<T> 	toIterable(int batchSize)
Transform this Flux into a lazy Iterable blocking on Iterator.next() calls.
Iterable<T> 	toIterable(int batchSize, Supplier<Queue<T>> queueProvider)
Transform this Flux into a lazy Iterable blocking on Iterator.next() calls.
Stream<T> 	toStream()
Transform this Flux into a lazy Stream blocking for each source onNext call.
Stream<T> 	toStream(int batchSize)
Transform this Flux into a lazy Stream blocking for each source onNext call.
String 	toString() 

## transform
| Method | description |
|--------|-------------|
<V> Flux<V> 	transform(Function<? super Flux<T>,? extends Publisher<V>> transformer)
Transform this Flux in order to generate a target Flux.
<V> Flux<V> 	transformDeferred(Function<? super Flux<T>,? extends Publisher<V>> transformer)
Defer the transformation of this Flux in order to generate a target Flux type.
<V> Flux<V> 	transformDeferredContextual(BiFunction<? super Flux<T>,? super ContextView,? extends Publisher<V>> transformer)
Defer the given transformation to this Flux in order to generate a target Flux type.

## using
| Method | description |
|--------|-------------|
static <T,D> Flux<T> 	using(Callable<? extends D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> sourceSupplier, Consumer<? super D> resourceCleanup)
Uses a resource, generated by a supplier for each individual Subscriber, while streaming the values from a Publisher derived from the same resource and makes sure the resource is released if the sequence terminates or the Subscriber cancels.
static <T,D> Flux<T> 	using(Callable<? extends D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> sourceSupplier, Consumer<? super D> resourceCleanup, boolean eager)
Uses a resource, generated by a supplier for each individual Subscriber, while streaming the values from a Publisher derived from the same resource and makes sure the resource is released if the sequence terminates or the Subscriber cancels.
static <T,D> Flux<T> 	usingWhen(Publisher<D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> resourceClosure, Function<? super D,? extends Publisher<?>> asyncCleanup)
Uses a resource, generated by a Publisher for each individual Subscriber, while streaming the values from a Publisher derived from the same resource.
static <T,D> Flux<T> 	usingWhen(Publisher<D> resourceSupplier, Function<? super D,? extends Publisher<? extends T>> resourceClosure, Function<? super D,? extends Publisher<?>> asyncComplete, BiFunction<? super D,? super Throwable,? extends Publisher<?>> asyncError, Function<? super D,? extends Publisher<?>> asyncCancel)
Uses a resource, generated by a Publisher for each individual Subscriber, while streaming the values from a Publisher derived from the same resource.

## window  
 | Method | description |
|--------|-------------|
Flux<Flux<T>> 	window(Duration windowingTimespan)
Split this Flux sequence into continuous, non-overlapping windows that open for a windowingTimespan Duration (as measured on the parallel Scheduler).
Flux<Flux<T>> 	window(Duration windowingTimespan, Duration openWindowEvery)
Split this Flux sequence into multiple Flux windows that open for a given windowingTimespan Duration, after which it closes with onComplete.
Flux<Flux<T>> 	window(Duration windowingTimespan, Duration openWindowEvery, Scheduler timer)
Split this Flux sequence into multiple Flux windows that open for a given windowingTimespan Duration, after which it closes with onComplete.
Flux<Flux<T>> 	window(Duration windowingTimespan, Scheduler timer)
Split this Flux sequence into continuous, non-overlapping windows that open for a windowingTimespan Duration (as measured on the provided Scheduler).
Flux<Flux<T>> 	window(int maxSize)
Split this Flux sequence into multiple Flux windows containing maxSize elements (or less for the final window) and starting from the first item.
Flux<Flux<T>> 	window(int maxSize, int skip)
Split this Flux sequence into multiple Flux windows of size maxSize, that each open every skip elements in the source.
Flux<Flux<T>> 	window(Publisher<?> boundary)
Split this Flux sequence into continuous, non-overlapping windows where the window boundary is signalled by another Publisher
Flux<Flux<T>> 	windowTimeout(int maxSize, Duration maxTime)
Split this Flux sequence into multiple Flux windows containing maxSize elements (or less for the final window) and starting from the first item.
Flux<Flux<T>> 	windowTimeout(int maxSize, Duration maxTime, Scheduler timer)
Split this Flux sequence into multiple Flux windows containing maxSize elements (or less for the final window) and starting from the first item.
Flux<Flux<T>> 	windowUntil(Predicate<T> boundaryTrigger)
Split this Flux sequence into multiple Flux windows delimited by the given predicate.
Flux<Flux<T>> 	windowUntil(Predicate<T> boundaryTrigger, boolean cutBefore)
Split this Flux sequence into multiple Flux windows delimited by the given predicate.
Flux<Flux<T>> 	windowUntil(Predicate<T> boundaryTrigger, boolean cutBefore, int prefetch)
Split this Flux sequence into multiple Flux windows delimited by the given predicate and using a prefetch.
<V> Flux<Flux<T>> 	windowUntilChanged()
Collect subsequent repetitions of an element (that is, if they arrive right after one another) into multiple Flux windows.
<V> Flux<Flux<T>> 	windowUntilChanged(Function<? super T,? extends V> keySelector, BiPredicate<? super V,? super V> keyComparator)
Collect subsequent repetitions of an element (that is, if they arrive right after one another), as compared by a key extracted through the user provided Function and compared using a supplied BiPredicate, into multiple Flux windows.
<V> Flux<Flux<T>> 	windowUntilChanged(Function<? super T,? super V> keySelector)
Collect subsequent repetitions of an element (that is, if they arrive right after one another), as compared by a key extracted through the user provided Function, into multiple Flux windows.
<U,V> Flux<Flux<T>> 	windowWhen(Publisher<U> bucketOpening, Function<? super U,? extends Publisher<V>> closeSelector)
Split this Flux sequence into potentially overlapping windows controlled by items of a start Publisher and end Publisher derived from the start values.
Flux<Flux<T>> 	windowWhile(Predicate<T> inclusionPredicate)
Split this Flux sequence into multiple Flux windows that stay open while a given predicate matches the source elements.
Flux<Flux<T>> 	windowWhile(Predicate<T> inclusionPredicate, int prefetch)
Split this Flux sequence into multiple Flux windows that stay open while a given predicate matches the source elements.

## with
| Method | description |
|--------|-------------|
<U,R> Flux<R> 	withLatestFrom(Publisher<? extends U> other, BiFunction<? super T,? super U,? extends R> resultSelector)
Combine the most recently emitted values from both this Flux and another Publisher through a BiFunction and emits the result.

## zip
| Method | description |
|--------|-------------|
static <I,O> Flux<O> 	zip(Function<? super Object[],? extends O> combinator, int prefetch, Publisher<? extends I>... sources)
Zip multiple sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).
static <I,O> Flux<O> 	zip(Function<? super Object[],? extends O> combinator, Publisher<? extends I>... sources)
Zip multiple sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).
static <O> Flux<O> 	zip(Iterable<? extends Publisher<?>> sources, Function<? super Object[],? extends O> combinator)
Zip multiple sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).
static <O> Flux<O> 	zip(Iterable<? extends Publisher<?>> sources, int prefetch, Function<? super Object[],? extends O> combinator)
Zip multiple sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).
static <TUPLE extends Tuple2,V>
Flux<V> 	zip(Publisher<? extends Publisher<?>> sources, Function<? super TUPLE,? extends V> combinator)
Zip multiple sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).
static <T1,T2> Flux<Tuple2<T1,T2>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2)
Zip two sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple2.
static <T1,T2,O> Flux<O> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, BiFunction<? super T1,? super T2,? extends O> combinator)
Zip two sources together, that is to say wait for all the sources to emit one element and combine these elements once into an output value (constructed by the provided combinator).
static <T1,T2,T3> Flux<Tuple3<T1,T2,T3>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3)
Zip three sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple3.
static <T1,T2,T3,T4>
Flux<Tuple4<T1,T2,T3,T4>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4)
Zip four sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple4.
static <T1,T2,T3,T4,T5>
Flux<Tuple5<T1,T2,T3,T4,T5>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5)
Zip five sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple5.
static <T1,T2,T3,T4,T5,T6>
Flux<Tuple6<T1,T2,T3,T4,T5,T6>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6)
Zip six sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple6.
static <T1,T2,T3,T4,T5,T6,T7>
Flux<Tuple7<T1,T2,T3,T4,T5,T6,T7>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6, Publisher<? extends T7> source7)
Zip seven sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple7.
static <T1,T2,T3,T4,T5,T6,T7,T8>
Flux<Tuple8<T1,T2,T3,T4,T5,T6,T7,T8>> 	zip(Publisher<? extends T1> source1, Publisher<? extends T2> source2, Publisher<? extends T3> source3, Publisher<? extends T4> source4, Publisher<? extends T5> source5, Publisher<? extends T6> source6, Publisher<? extends T7> source7, Publisher<? extends T8> source8)
Zip eight sources together, that is to say wait for all the sources to emit one element and combine these elements once into a Tuple8.
<T2> Flux<Tuple2<T,T2>> 	zipWith(Publisher<? extends T2> source2)
Zip this Flux with another Publisher source, that is to say wait for both to emit one element and combine these elements once into a Tuple2.
<T2,V> Flux<V> 	zipWith(Publisher<? extends T2> source2, BiFunction<? super T,? super T2,? extends V> combinator)
Zip this Flux with another Publisher source, that is to say wait for both to emit one element and combine these elements using a combinator BiFunction The operator will continue doing so until any of the sources completes.
<T2> Flux<Tuple2<T,T2>> 	zipWith(Publisher<? extends T2> source2, int prefetch)
Zip this Flux with another Publisher source, that is to say wait for both to emit one element and combine these elements once into a Tuple2.
<T2,V> Flux<V> 	zipWith(Publisher<? extends T2> source2, int prefetch, BiFunction<? super T,? super T2,? extends V> combinator)
Zip this Flux with another Publisher source, that is to say wait for both to emit one element and combine these elements using a combinator BiFunction The operator will continue doing so until any of the sources completes.
<T2> Flux<Tuple2<T,T2>> 	zipWithIterable(Iterable<? extends T2> iterable)
Zip elements from this Flux with the content of an Iterable, that is to say combine one element from each, pairwise, into a Tuple2.
<T2,V> Flux<V> 	zipWithIterable(Iterable<? extends T2> iterable, BiFunction<? super T,? super T2,? extends V> zipper)
Zip elements from this Flux with the content of an Iterable, that is to say combine one element from each, pairwise, using the given zipper BiFunction.
