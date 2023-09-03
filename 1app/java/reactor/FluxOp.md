# [Flux](https://projectreactor.io/docs/core/release/api/)

## Flux Operators

### Misc
```
int 	getPrefetch()     The prefetch configuration of the Flux
Mono<Boolean> 	all(Predicate<? super T> predicate)     Emit a single boolean true if all values of this sequence match the Predicate.
Mono<Boolean> 	any(Predicate<? super T> predicate)     Emit a single boolean true if any of the values of this Flux sequence match the predicate.
<P> P 	as(Function<? super Flux<T>,P> transformer)     Transform this Flux into a target type.

Mono<Long> 	count()                    Counts the number of values in this Flux.
Flux<T> 	defaultIfEmpty(T defaultV)   Provide a default unique value if this sequence is completed without any data
<X> Flux<X> 	dematerialize()          An operator working only if this Flux emits onNext, onError or onComplete Signal instances, transforming these materialized signals into real signals on the Subscriber.
Flux<Tuple2<Long,T>> 	elapsed()        Map this Flux into Tuple2<Long, T> of timemillis and source data.
Flux<Tuple2<Long,T>> 	elapsed(Scheduler scheduler)  Map this Flux into Tuple2<Long, T> of timemillis and source data.
Mono<T> 	elementAt(int index)         Emit only the element at the given index position or IndexOutOfBoundsException if the sequence is shorter.
Mono<T> 	elementAt(int index, T defaultValue)    Emit only the element at the given index position or fall back to a default value if the sequence is shorter.

<R> Flux<R> 	handle(BiConsumer<? super T,SynchronousSink<R>> handler)     Handle the items emitted by this Flux by calling a biconsumer with the output sink for each onNext.
Mono<Boolean> 	hasElement(T value)   Emit a single boolean true if any of the elements of this Flux sequence is equal to the provided value.
Mono<Boolean> 	hasElements()    Emit a single boolean true if this Flux sequence has at least one element.
Flux<T> 	hide()   Hides the identities of this Flux instance.
Mono<T> 	ignoreElements()   Ignores onNext signals (dropping them) and only propagate termination events.
```

### toXxx
```
Iterable<T> 	toIterable()                  Transform this Flux into a lazy Iterable blocking on Iterator.next() calls.
Iterable<T> 	toIterable(int batchSize)     Transform this Flux into a lazy Iterable blocking on Iterator.next() calls.
Iterable<T> 	toIterable(int batchSize, Supplier<Queue<T>> queueProvider)      Transform this Flux into a lazy Iterable blocking on Iterator.next() calls.
Stream<T> 	toStream()      Transform this Flux into a lazy Stream blocking for each source onNext call.
Stream<T> 	toStream(int batchSize)  Transform this Flux into a lazy Stream blocking for each source onNext call.
String 	toString() 
```

### Block First/Last
Subscribe to this Flux and block indefinitely until the upstream signals its first value or completes.
```
T 	blockFirst()
T 	blockFirst(Duration timeout)
T 	blockLast()
T 	blockLast(Duration timeout)
```
### Buffer
Collect all incoming values into a single List buffer that will be emitted by the returned Flux once this Flux completes.
```
Flux<List<T>> 	buffer()
Flux<List<T>> 	buffer(Duration bufferingTimespan)
Flux<List<T>> 	buffer(Duration bufferingTimespan, Duration openBufferEvery)
Flux<List<T>> 	buffer(Duration bufferingTimespan, Duration openBufferEvery, Scheduler timer)
Flux<List<T>> 	buffer(Duration bufferingTimespan, Scheduler timer)
Flux<List<T>> 	buffer(int maxSize)
Flux<List<T>> 	buffer(int maxSize, int skip)
<C extends Collection<? super T>> Flux<C> 	buffer(int maxSize, int skip, Supplier<C> bufferSupplier)
<C extends Collection<? super T>> Flux<C> 	buffer(int maxSize, Supplier<C> bufferSupplier)
Flux<List<T>> 	buffer(Publisher<?> other) <C extends Collection<? super T>> Flux<C> 	buffer(Publisher<?> other, Supplier<C> bufferSupplier)
Flux<List<T>> 	bufferTimeout(int maxSize, Duration maxTime)
Flux<List<T>> 	bufferTimeout(int maxSize, Duration maxTime, boolean fairBackpressure)
Flux<List<T>> 	bufferTimeout(int maxSize, Duration maxTime, Scheduler timer)
Flux<List<T>> 	bufferTimeout(int maxSize, Duration maxTime, Scheduler timer, boolean fairBackpressure)
<C extends Collection<? super T>> Flux<C> 	bufferTimeout(int maxSize, Duration maxTime, Scheduler timer, Supplier<C> bufferSupplier)
<C extends Collection<? super T>> Flux<C> 	bufferTimeout(int maxSize, Duration maxTime, Scheduler timer, Supplier<C> bufferSupplier, boolean fairBackpressure)
<C extends Collection<? super T>> Flux<C> 	bufferTimeout(int maxSize, Duration maxTime, Supplier<C> bufferSupplier)
<C extends Collection<? super T>> Flux<C> 	bufferTimeout(int maxSize, Duration maxTime, Supplier<C> bufferSupplier, boolean fairBackpressure)
Flux<List<T>> 	bufferUntil(Predicate<? super T> predicate)
Flux<List<T>> 	bufferUntil(Predicate<? super T> predicate, boolean cutBefore)
Flux<List<T>> 	bufferUntilChanged()
<V> Flux<List<T>> 	bufferUntilChanged(Function<? super T,? extends V> keySelector)
<V> Flux<List<T>> 	bufferUntilChanged(Function<? super T,? extends V> keySelector, BiPredicate<? super V,? super V> keyComparator)
<U,V> Flux<List<T>> 	bufferWhen(Publisher<U> bucketOpening, Function<? super U,? extends Publisher<V>> closeSelector)
<U,V,C extends Collection<? super T>> Flux<C> 	bufferWhen(Publisher<U> bucketOpening, Function<? super U,? extends Publisher<V>> closeSelector, Supplier<C> bufferSupplier)
Flux<List<T>> 	bufferWhile(Predicate<? super T> predicate)
```

### Cache
Turn this Flux into a hot source and cache last emitted signals for further Subscriber.
```
Flux<T> 	cache()
Flux<T> 	cache(Duration ttl)
Flux<T> 	cache(Duration ttl, Scheduler timer)
Flux<T> 	cache(int history)
Flux<T> 	cache(int history, Duration ttl)
Flux<T> 	cache(int history, Duration ttl, Scheduler timer)
Flux<T> 	cancelOn(Scheduler scheduler)
```
<E> Flux<E> 	cast(Class<E> clazz)
Cast the current Flux produced type into a target produced type.

### checkpoint
Activate traceback (full assembly tracing) for this particular Flux, in case of an error upstream of the checkpoint.
```
Flux<T> 	checkpoint()
Flux<T> 	checkpoint(String description)
Flux<T> 	checkpoint(String description, boolean forceStackTrace)
```

### Collect
Collect all elements emitted by this Flux into a container, by applying a Java 8 Stream API Collector The collected result will be emitted when this sequence completes, emitting the empty container if the sequence was empty.
```
<R,A> Mono<R> 	collect(Collector<? super T,A,? extends R> collector)
<E> Mono<E> 	collect(Supplier<E> containerSupplier, BiConsumer<E,? super T> collector)
Mono<List<T>> 	collectList()
<K> Mono<Map<K,T>> 	collectMap(Function<? super T,? extends K> keyExtractor)
<K,V> Mono<Map<K,V>> 	collectMap(Function<? super T,? extends K> keyExtractor, Function<? super T,? extends V> valueExtractor)
<K,V> Mono<Map<K,V>> 	collectMap(Function<? super T,? extends K> keyExtractor, Function<? super T,? extends V> valueExtractor, Supplier<Map<K,V>> mapSupplier)
<K> Mono<Map<K,Collection<T>>> 	collectMultimap(Function<? super T,? extends K> keyExtractor)
<K,V> Mono<Map<K,Collection<V>>> 	collectMultimap(Function<? super T,? extends K> keyExtractor, Function<? super T,? extends V> valueExtractor)
<K,V> Mono<Map<K,Collection<V>>> 	collectMultimap(Function<? super T,? extends K> keyExtractor, Function<? super T,? extends V> valueExtractor, Supplier<Map<K,Collection<V>>> mapSupplier)
Mono<List<T>> 	collectSortedList()
Mono<List<T>> 	collectSortedList(Comparator<? super T> comparator)
```

### ConcatMap
Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux, sequentially and preserving order using concatenation.
```
<V> Flux<V> 	concatMap(Function<? super T,? extends Publisher<? extends V>> mapper)
<V> Flux<V> 	concatMap(Function<? super T,? extends Publisher<? extends V>> mapper, int prefetch)
<V> Flux<V> 	concatMapDelayError(Function<? super T,? extends Publisher<? extends V>> mapper)
<V> Flux<V> 	concatMapDelayError(Function<? super T,? extends Publisher<? extends V>> mapper, boolean delayUntilEnd, int prefetch)
<V> Flux<V> 	concatMapDelayError(Function<? super T,? extends Publisher<? extends V>> mapper, int prefetch)
<R> Flux<R> 	concatMapIterable(Function<? super T,? extends Iterable<? extends R>> mapper)
<R> Flux<R> 	concatMapIterable(Function<? super T,? extends Iterable<? extends R>> mapper, int prefetch)
Flux<T> 	concatWith(Publisher<? extends T> other)
Flux<T> 	concatWithValues(T... values)
Flux<T> 	contextCapture()
Flux<T> 	contextWrite(ContextView contextToAppend)
Flux<T> 	contextWrite(Function<Context,Context> contextModifier)
```


### Delay
Delay each of this Flux elements (Subscriber.onNext(T) signals) by a given Duration.
```
Flux<T> 	delayElements(Duration delay)
Flux<T> 	delayElements(Duration delay, Scheduler timer)
Flux<T> 	delaySequence(Duration delay)
Flux<T> 	delaySequence(Duration delay, Scheduler timer)
Flux<T> 	delaySubscription(Duration delay)
Flux<T> 	delaySubscription(Duration delay, Scheduler timer)
<U> Flux<T> 	delaySubscription(Publisher<U> subscriptionDelay)
Flux<T> 	delayUntil(Function<? super T,? extends Publisher<?>> triggerProvider)
```

### Distinct
For each Subscriber, track elements from this Flux that have been seen and filter out duplicates.
```
Flux<T> 	distinct()
<V> Flux<T> 	distinct(Function<? super T,? extends V> keySelector)
<V,C extends Collection<? super V>> Flux<T> 	distinct(Function<? super T,? extends V> keySelector, Supplier<C> distinctCollectionSupplier)
<V,C> Flux<T> 	distinct(Function<? super T,? extends V> keySelector, Supplier<C> distinctStoreSupplier, BiPredicate<C,V> distinctPredicate, Consumer<C> cleanup)
Flux<T> 	distinctUntilChanged()
<V> Flux<T> 	distinctUntilChanged(Function<? super T,? extends V> keySelector)
<V> Flux<T> 	distinctUntilChanged(Function<? super T,? extends V> keySelector, BiPredicate<? super V,? super V> keyComparator)
```

### do operators
Add behavior (side-effect) triggered after the Flux terminates, either by completing downstream successfully or with an error.
```
Flux<T> 	doAfterTerminate(Runnable afterTerminate)
Flux<T> 	doFinally(Consumer<SignalType> onFinally)
Flux<T> 	doFirst(Runnable onFirst)
Flux<T> 	doOnCancel(Runnable onCancel)
Flux<T> 	doOnComplete(Runnable onComplete)
<R> Flux<T> 	doOnDiscard(Class<R> type, Consumer<? super R> discardHook)
Flux<T> 	doOnEach(Consumer<? super Signal<T>> signalConsumer)
<E extends Throwable> Flux<T> 	doOnError(Class<E> exceptionType, Consumer<? super E> onError)
Flux<T> 	doOnError(Consumer<? super Throwable> onError)
Flux<T> 	doOnError(Predicate<? super Throwable> predicate, Consumer<? super Throwable> onError)
Flux<T> 	doOnNext(Consumer<? super T> onNext)
Flux<T> 	doOnRequest(LongConsumer consumer)
Flux<T> 	doOnSubscribe(Consumer<? super Subscription> onSubscribe)
Flux<T> 	doOnTerminate(Runnable onTerminate)
```
### expand
Recursively expand elements into a graph and emit all the resulting element using a breadth-first traversal strategy.

```
Flux<T> 	expand(Function<? super T,? extends Publisher<? extends T>> expander)
Flux<T> 	expand(Function<? super T,? extends Publisher<? extends T>> expander, int capacityHint)
Flux<T> 	expandDeep(Function<? super T,? extends Publisher<? extends T>> expander)
Flux<T> 	expandDeep(Function<? super T,? extends Publisher<? extends T>> expander, int capacityHint)
```
### Filter
Evaluate each source value against the given Predicate.
```
Flux<T> 	filter(Predicate<? super T> p)
Flux<T> 	filterWhen(Function<? super T,? extends Publisher<Boolean>> asyncPredicate)
Flux<T> 	filterWhen(Function<? super T,? extends Publisher<Boolean>> asyncPredicate, int bufferSize)
```
### Flat Map
Transform the elements emitted by this Flux asynchronously into Publishers, then flatten these inner publishers into a single Flux through merging, which allow them to interleave.

```
<R> Flux<R> 	flatMap(Function<? super T,? extends Publisher<? extends R>> mapper)
<R> Flux<R> 	flatMap(Function<? super T,? extends Publisher<? extends R>> mapperOnNext, Function<? super Throwable,? extends Publisher<? extends R>> mapperOnError, Supplier<? extends Publisher<? extends R>> mapperOnComplete)
<V> Flux<V> 	flatMap(Function<? super T,? extends Publisher<? extends V>> mapper, int concurrency)
<V> Flux<V> 	flatMap(Function<? super T,? extends Publisher<? extends V>> mapper, int concurrency, int prefetch)
<V> Flux<V> 	flatMapDelayError(Function<? super T,? extends Publisher<? extends V>> mapper, int concurrency, int prefetch)
<R> Flux<R> 	flatMapIterable(Function<? super T,? extends Iterable<? extends R>> mapper)
<R> Flux<R> 	flatMapIterable(Function<? super T,? extends Iterable<? extends R>> mapper, int prefetch)
<R> Flux<R> 	flatMapSequential(Function<? super T,? extends Publisher<? extends R>> mapper)
<R> Flux<R> 	flatMapSequential(Function<? super T,? extends Publisher<? extends R>> mapper, int maxConcurrency)
<R> Flux<R> 	flatMapSequential(Function<? super T,? extends Publisher<? extends R>> mapper, int maxConcurrency, int prefetch)
<R> Flux<R> 	flatMapSequentialDelayError(Function<? super T,? extends Publisher<? extends R>> mapper, int maxConcurrency, int prefetch)
```

### Group By
Divide this sequence into dynamically created Flux (or groups) for each unique key, as produced by the provided keyMapper Function.
```
<K> Flux<GroupedFlux<K,T>> 	groupBy(Function<? super T,? extends K> keyMapper)
<K,V> Flux<GroupedFlux<K,V>> 	groupBy(Function<? super T,? extends K> keyMapper, Function<? super T,? extends V> valueMapper)
<K,V> Flux<GroupedFlux<K,V>> 	groupBy(Function<? super T,? extends K> keyMapper, Function<? super T,? extends V> valueMapper, int prefetch)
<K> Flux<GroupedFlux<K,T>> 	groupBy(Function<? super T,? extends K> keyMapper, int prefetch)
<TRight,TLeftEnd,TRightEnd,R> Flux<R> 	groupJoin(Publisher<? extends TRight> other, Function<? super T,? extends Publisher<TLeftEnd>> leftEnd, Function<? super TRight,? extends Publisher<TRightEnd>> rightEnd, BiFunction<? super T,? super Flux<TRight>,? extends R> resultSelector)
```
### Index
Keep information about the order in which source values were received by indexing them with a 0-based incrementing long, returning a Flux of Tuple2<(index, value)>.
```
Flux<Tuple2<Long,T>> 	index()
<I> Flux<I> 	index(BiFunction<? super Long,? super T,? extends I> indexMapper)
```

### Join
Combine values from two Publishers in case their windows overlap.
```
<TRight,TLeftEnd,TRightEnd,R>
Flux<R> 	join(Publisher<? extends TRight> other, Function<? super T,? extends Publisher<TLeftEnd>> leftEnd, Function<? super TRight,? extends Publisher<TRightEnd>> rightEnd, BiFunction<? super T,? super TRight,? extends R> resultSelector)
Mono<T> 	last()
Emit the last element observed before complete signal as a Mono, or emit NoSuchElementException error if the source was empty.
Mono<T> 	last(T defaultValue)
Emit the last element observed before complete signal as a Mono, or emit the defaultValue if the source was empty.
Flux<T> 	limitRate(int prefetchRate)
Ensure that backpressure signals from downstream subscribers are split into batches capped at the provided prefetchRate when propagated upstream, effectively rate limiting the upstream Publisher.
Flux<T> 	limitRate(int highTide, int lowTide)
Ensure that backpressure signals from downstream subscribers are split into batches capped at the provided highTide first, then replenishing at the provided lowTide, effectively rate limiting the upstream Publisher.
Flux<T> 	limitRequest(long n)
Deprecated. 
replace with take(n, true) in 3.4.x, then take(long) in 3.5.0. To be removed in 3.6.0 at the earliest. See https://github.com/reactor/reactor-core/issues/2339
```

### log
Observe all Reactive Streams signals and trace them using Logger support.
```
Flux<T> 	log()
Flux<T> 	log(Logger logger)
Flux<T> 	log(Logger logger, Level level, boolean showOperatorLine, SignalType... options)
Flux<T> 	log(String category)
Flux<T> 	log(String category, Level level, boolean showOperatorLine, SignalType... options)
Flux<T> 	log(String category, Level level, SignalType... options)
```

### Map
Transform the items emitted by this Flux by applying a synchronous function to each item.

```
<V> Flux<V> 	map(Function<? super T,? extends V> mapper)
<V> Flux<V> 	mapNotNull(Function<? super T,? extends V> mapper)
Flux<Signal<T>> 	materialize()
Transform incoming onNext, onError and onComplete signals into Signal instances, materializing these signals.
```

### Merge
Merge data from this Flux and a Publisher into a reordered merge sequence, by picking the smallest value from each sequence as defined by a provided Comparator.

```
Flux<T> 	mergeComparingWith(Publisher<? extends T> other, Comparator<? super T> otherComparator)
Flux<T> 	mergeOrderedWith(Publisher<? extends T> other, Comparator<? super T> otherComparator)
Flux<T> 	mergeWith(Publisher<? extends T> other)
```
Flux<T> 	name(String name)
Give a name to this sequence, which can be retrieved using Scannable.name() as long as this is the first reachable Scannable.parents().
Mono<T> 	next()
Emit only the first item emitted by this Flux, into a new Mono.
<U> Flux<U> 	ofType(Class<U> clazz)
Evaluate each accepted value against the given Class type.

### onBackpressureBuffer
Request an unbounded demand and push to the returned Flux, or park the observed elements if not enough demand is requested downstream.
```
Flux<T> 	onBackpressureBuffer()
Flux<T> 	onBackpressureBuffer(Duration ttl, int maxSize, Consumer<? super T> onBufferEviction)
Flux<T> 	onBackpressureBuffer(Duration ttl, int maxSize, Consumer<? super T> onBufferEviction, Scheduler scheduler)
Flux<T> 	onBackpressureBuffer(int maxSize)
Flux<T> 	onBackpressureBuffer(int maxSize, BufferOverflowStrategy bufferOverflowStrategy)
Flux<T> 	onBackpressureBuffer(int maxSize, Consumer<? super T> onOverflow)
Flux<T> 	onBackpressureBuffer(int maxSize, Consumer<? super T> onBufferOverflow, BufferOverflowStrategy bufferOverflowStrategy)
Flux<T> 	onBackpressureDrop()
Flux<T> 	onBackpressureDrop(Consumer<? super T> onDropped)
Flux<T> 	onBackpressureError()
Flux<T> 	onBackpressureLatest()
```

### onError
Simply complete the sequence by replacing an onError signal with an onComplete signal.
```
Flux<T> 	onErrorComplete()
Flux<T> 	onErrorComplete(Class<? extends Throwable> type)
Flux<T> 	onErrorComplete(Predicate<? super Throwable> predicate)
Flux<T> 	onErrorContinue(BiConsumer<Throwable,Object> errorConsumer)
<E extends Throwable> Flux<T> 	onErrorContinue(Class<E> type, BiConsumer<Throwable,Object> errorConsumer)
<E extends Throwable> Flux<T> 	onErrorContinue(Predicate<E> errorPredicate, BiConsumer<Throwable,Object> errorConsumer)
<E extends Throwable> Flux<T> 	onErrorMap(Class<E> type, Function<? super E,? extends Throwable> mapper)
Flux<T> 	onErrorMap(Function<? super Throwable,? extends Throwable> mapper)
Flux<T> 	onErrorMap(Predicate<? super Throwable> predicate, Function<? super Throwable,? extends Throwable> mapper)
<E extends Throwable> Flux<T> 	onErrorResume(Class<E> type, Function<? super E,? extends Publisher<? extends T>> fallback)
Flux<T> 	onErrorResume(Function<? super Throwable,? extends Publisher<? extends T>> fallback)
Flux<T> 	onErrorResume(Predicate<? super Throwable> predicate, Function<? super Throwable,? extends Publisher<? extends T>> fallback)

Simply emit a captured fallback value when an error matching the given predicate is observed on this Flux.

<E extends Throwable> Flux<T> 	onErrorReturn(Class<E> type, T fallbackValue)
Flux<T> 	onErrorReturn(Predicate<? super Throwable> predicate, T fallbackValue)
Flux<T> 	onErrorReturn(T fallbackValue)

If an onErrorContinue(BiConsumer) variant has been used downstream, reverts to the default 'STOP' mode where errors are terminal events upstream.
Flux<T> 	onErrorStop()
Detaches both the child Subscriber and the Subscription on termination or cancellation.
Flux<T> 	onTerminateDetach()

Flux<T> 	or(Publisher<? extends T> other)
Pick the first Publisher between this Flux and another publisher to emit any signal (onNext/onError/onComplete) and replay all signals from that Publisher, effectively behaving like the fastest of these competing sources.
```
### parallel
Prepare this Flux by dividing data on a number of 'rails' matching the number of CPU cores, in a round-robin fashion.
```
ParallelFlux<T> 	parallel()
ParallelFlux<T> 	parallel(int parallelism)
ParallelFlux<T> 	parallel(int parallelism, int prefetch)
```
### publish
Prepare a ConnectableFlux which shares this Flux sequence and dispatches values to subscribers in a backpressure-aware manner.
```
ConnectableFlux<T> 	publish()
<R> Flux<R> 	publish(Function<? super Flux<T>,? extends Publisher<? extends R>> transform)
<R> Flux<R> 	publish(Function<? super Flux<T>,? extends Publisher<? extends R>> transform, int prefetch)
ConnectableFlux<T> 	publish(int prefetch)
Mono<T> 	publishNext()
Flux<T> 	publishOn(Scheduler scheduler)
Flux<T> 	publishOn(Scheduler scheduler, boolean delayError, int prefetch)
Flux<T> 	publishOn(Scheduler scheduler, int prefetch)
```
### reduce
Reduce the values from this Flux sequence into a single object matching the type of a seed value.
```
<A> Mono<A> 	reduce(A initial, BiFunction<A,? super T,A> accumulator)
Mono<T> 	reduce(BiFunction<T,T,T> aggregator)
<A> Mono<A> 	reduceWith(Supplier<A> initial, BiFunction<A,? super T,A> accumulator)
```
### repeat
Repeatedly and indefinitely subscribe to the source upon completion of the previous subscription.

```
Flux<T> 	repeat()
Flux<T> 	repeat(BooleanSupplier predicate)
Flux<T> 	repeat(long numRepeat)
Flux<T> 	repeat(long numRepeat, BooleanSupplier predicate)
Flux<T> 	repeatWhen(Function<Flux<Long>,? extends Publisher<?>> repeatFactory)
```
### replay
Turn this Flux into a hot source and cache last emitted signals for further Subscriber.
```
ConnectableFlux<T> 	replay()
ConnectableFlux<T> 	replay(Duration ttl)
ConnectableFlux<T> 	replay(Duration ttl, Scheduler timer)
ConnectableFlux<T> 	replay(int history)
ConnectableFlux<T> 	replay(int history, Duration ttl)
ConnectableFlux<T> 	replay(int history, Duration ttl, Scheduler timer)
```
### retry
Re-subscribes to this Flux sequence if it signals any error, indefinitely.

```
Flux<T> 	retry()
Flux<T> 	retry(long numRetries)
Flux<T> 	retryWhen(Retry retrySpec)
```
### sample
Sample this Flux by periodically emitting an item corresponding to that Flux latest emitted value within the periodical time window.

```
Flux<T> 	sample(Duration timespan)
<U> Flux<T> 	sample(Publisher<U> sampler)
Flux<T> 	sampleFirst(Duration timespan)
<U> Flux<T> 	sampleFirst(Function<? super T,? extends Publisher<U>> samplerFactory)
<U> Flux<T> 	sampleTimeout(Function<? super T,? extends Publisher<U>> throttlerFactory)
<U> Flux<T> 	sampleTimeout(Function<? super T,? extends Publisher<U>> throttlerFactory, int maxConcurrency)
```
### scan
Reduce this Flux values with an accumulator BiFunction and also emit the intermediate results of this function.
```
<A> Flux<A> 	scan(A initial, BiFunction<A,? super T,A> accumulator)
Flux<T> 	scan(BiFunction<T,T,T> accumulator)
<A> Flux<A> 	scanWith(Supplier<A> initial, BiFunction<A,? super T,A> accumulator)
```
### Share
Returns a new Flux that multicasts (shares) the original Flux.
```
Flux<T> 	share()
Mono<T> 	shareNext()
```
### Single
Expect and emit a single item from this Flux source or signal NoSuchElementException for an empty source, or IndexOutOfBoundsException for a source with more than one element.

```
Mono<T> 	single()
Mono<T> 	single(T defaultValue)
Mono<T> 	singleOrEmpty()
```
### skip
Skip elements from this Flux emitted within the specified initial duration.
```
Flux<T> 	skip(Duration timespan)
Flux<T> 	skip(Duration timespan, Scheduler timer)
Flux<T> 	skip(long skipped)
Flux<T> 	skipLast(int n)
Flux<T> 	skipUntil(Predicate<? super T> untilPredicate)
Flux<T> 	skipUntilOther(Publisher<?> other)
Flux<T> 	skipWhile(Predicate<? super T> skipPredicate)
```
### sort
Sort elements from this Flux by collecting and sorting them in the background then emitting the sorted sequence once this sequence completes.

```
Flux<T> 	sort()
Flux<T> 	sort(Comparator<? super T> sortFunction)
```

### start with
Prepend the given Iterable before this Flux sequence.
```
Flux<T> 	startWith(Iterable<? extends T> iterable)
Flux<T> 	startWith(Publisher<? extends T> publisher)
Flux<T> 	startWith(T... values)
```
### subscribe
Subscribe to this Flux and request unbounded demand.
```
Disposable 	subscribe()
Disposable 	subscribe(Consumer<? super T> consumer)
Disposable 	subscribe(Consumer<? super T> consumer, Consumer<? super Throwable> errorConsumer)
Disposable 	subscribe(Consumer<? super T> consumer, Consumer<? super Throwable> errorConsumer, Runnable completeConsumer)
Disposable 	subscribe(Consumer<? super T> consumer, Consumer<? super Throwable> errorConsumer, Runnable completeConsumer, Consumer<? super Subscription> subscriptionConsumer)
Disposable 	subscribe(Consumer<? super T> consumer, Consumer<? super Throwable> errorConsumer, Runnable completeConsumer, Context initialContext)
abstract void 	subscribe(CoreSubscriber<? super T> actual)
void 	subscribe(Subscriber<? super T> actual) 
```
### subscribeOn
Run subscribe, onSubscribe and request on a specified Scheduler's Scheduler.Worker.
```
Flux<T> 	subscribeOn(Scheduler scheduler)
Flux<T> 	subscribeOn(Scheduler scheduler, boolean requestOnSeparateThread)
<E extends Subscriber<? super T>> E 	subscribeWith(E subscriber)
```
### switch
Switch to an alternative Publisher if this sequence is completed without any data.
```
Flux<T> 	switchIfEmpty(Publisher<? extends T> alternate)
<V> Flux<V> 	switchMap(Function<? super T,Publisher<? extends V>> fn)
<V> Flux<V> 	switchMap(Function<? super T,Publisher<? extends V>> fn, int prefetch)
<V> Flux<V> 	switchOnFirst(BiFunction<Signal<? extends T>,Flux<T>,Publisher<? extends V>> transformer)
<V> Flux<V> 	switchOnFirst(BiFunction<Signal<? extends T>,Flux<T>,Publisher<? extends V>> transformer, boolean cancelSourceOnComplete)
```
### tag
Tag this flux with a key/value pair.
```
Flux<T> 	tag(String key, String value)
```
### take
Relay values from this Flux until the specified Duration elapses.
```
Flux<T> 	take(Duration timespan)
Flux<T> 	take(Duration timespan, Scheduler timer)
Flux<T> 	take(long n)
Flux<T> 	take(long n, boolean limitRequest)
Flux<T> 	takeLast(int n)
Flux<T> 	takeUntil(Predicate<? super T> predicate)
Flux<T> 	takeUntilOther(Publisher<?> other)
Flux<T> 	takeWhile(Predicate<? super T> continuePredicate)
```
### tap
Tap into Reactive Streams signals emitted or received by this Flux and notify a stateful per-Subscriber SignalListener.
```
Flux<T> 	tap(Function<ContextView,SignalListener<T>> listenerGenerator)
Flux<T> 	tap(SignalListenerFactory<T,?> listenerFactory)
Flux<T> 	tap(Supplier<SignalListener<T>> simpleListenerGenerator)
```
### then
Return a Mono<Void> that completes when this Flux completes.
```
Mono<Void> 	then()
<V> Mono<V> 	then(Mono<V> other)
Mono<Void> 	thenEmpty(Publisher<Void> other)
<V> Flux<V> 	thenMany(Publisher<V> other)
```
### timed
Times Subscriber.onNext(Object) events, encapsulated into a Timed object that lets downstream consumer look at various time information gathered with nanosecond resolution using the default clock (Schedulers.parallel()): Timed.elapsed(): the time in nanoseconds since last event, as a Duration.
```
Flux<Timed<T>> 	timed()
Flux<Timed<T>> 	timed(Scheduler clock)
```
### timeout
```
Flux<T> 	timeout(Duration timeout)
Flux<T> 	timeout(Duration timeout, Publisher<? extends T> fallback)
Flux<T> 	timeout(Duration timeout, Publisher<? extends T> fallback, Scheduler timer)
Flux<T> 	timeout(Duration timeout, Scheduler timer)
<U> Flux<T> 	timeout(Publisher<U> firstTimeout)
<U,V> Flux<T> 	timeout(Publisher<U> firstTimeout, Function<? super T,? extends Publisher<V>> nextTimeoutFactory)
<U,V> Flux<T> 	timeout(Publisher<U> firstTimeout, Function<? super T,? extends Publisher<V>> nextTimeoutFactory, Publisher<? extends T> fallback)
```
### timestamp
Emit a Tuple2 pair of T1 the current clock time in millis (as a Long measured by the parallel Scheduler) and T2 the emitted data (as a T), for each item from this Flux.
```
Flux<Tuple2<Long,T>> 	timestamp()
Flux<Tuple2<Long,T>> 	timestamp(Scheduler scheduler)
```


### transform
Transform this Flux in order to generate a target Flux.
```
<V> Flux<V> 	transform(Function<? super Flux<T>,? extends Publisher<V>> transformer)
<V> Flux<V> 	transformDeferred(Function<? super Flux<T>,? extends Publisher<V>> transformer)
<V> Flux<V> 	transformDeferredContextual(BiFunction<? super Flux<T>,? super ContextView,? extends Publisher<V>> transformer)
```
### window
Split this Flux sequence into continuous, non-overlapping windows that open for a windowingTimespan Duration (as measured on the parallel Scheduler).
```
Flux<Flux<T>> 	window(Duration windowingTimespan)
Flux<Flux<T>> 	window(Duration windowingTimespan, Duration openWindowEvery)
Flux<Flux<T>> 	window(Duration windowingTimespan, Duration openWindowEvery, Scheduler timer)
Flux<Flux<T>> 	window(Duration windowingTimespan, Scheduler timer)
Flux<Flux<T>> 	window(int maxSize)
Flux<Flux<T>> 	window(int maxSize, int skip)
Flux<Flux<T>> 	window(Publisher<?> boundary)
Flux<Flux<T>> 	windowTimeout(int maxSize, Duration maxTime)
Flux<Flux<T>> 	windowTimeout(int maxSize, Duration maxTime, boolean fairBackpressure)
Flux<Flux<T>> 	windowTimeout(int maxSize, Duration maxTime, Scheduler timer)
Flux<Flux<T>> 	windowTimeout(int maxSize, Duration maxTime, Scheduler timer, boolean fairBackpressure)
Flux<Flux<T>> 	windowUntil(Predicate<T> boundaryTrigger)
Flux<Flux<T>> 	windowUntil(Predicate<T> boundaryTrigger, boolean cutBefore)
Flux<Flux<T>> 	windowUntil(Predicate<T> boundaryTrigger, boolean cutBefore, int prefetch)
Flux<Flux<T>> 	windowUntilChanged()
<V> Flux<Flux<T>> 	windowUntilChanged(Function<? super T,? extends V> keySelector, BiPredicate<? super V,? super V> keyComparator)
<V> Flux<Flux<T>> 	windowUntilChanged(Function<? super T,? super V> keySelector)
<U,V> Flux<Flux<T>> 	windowWhen(Publisher<U> bucketOpening, Function<? super U,? extends Publisher<V>> closeSelector)
Flux<Flux<T>> 	windowWhile(Predicate<T> inclusionPredicate)
Flux<Flux<T>> 	windowWhile(Predicate<T> inclusionPredicate, int prefetch)
<U,R> Flux<R> 	withLatestFrom(Publisher<? extends U> other, BiFunction<? super T,? super U,? extends R> resultSelector)
```
### zip
Zip this Flux with another Publisher source, that is to say wait for both to emit one element and combine these elements once into a Tuple2.
```
<T2> Flux<Tuple2<T,T2>> 	zipWith(Publisher<? extends T2> source2)
<T2,V> Flux<V> 	zipWith(Publisher<? extends T2> source2, BiFunction<? super T,? super T2,? extends V> combinator)
<T2> Flux<Tuple2<T,T2>> 	zipWith(Publisher<? extends T2> source2, int prefetch)
<T2,V> Flux<V> 	zipWith(Publisher<? extends T2> source2, int prefetch, BiFunction<? super T,? super T2,? extends V> combinator)
<T2> Flux<Tuple2<T,T2>> 	zipWithIterable(Iterable<? extends T2> iterable)
<T2,V> Flux<V> 	zipWithIterable(Iterable<? extends T2> iterable, BiFunction<? super T,? super T2,? extends V> zipper)
```
