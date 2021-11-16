# Java Stream
- [API](https://docs.oracle.com/javase/8/docs/api/java/util/stream/Stream.html)
- Sample
```
     int sum = widgets.stream()
                      .filter(w -> w.getColor() == RED)
                      .mapToInt(w -> w.getWeight())
                      .sum();
```                      

## Method
boolean 	allMatch(Predicate<? super T> predicate)
boolean 	anyMatch(Predicate<? super T> predicate)
boolean 	noneMatch(Predicate<? super T> predicate)
long 	count()

Optional<T> 	max(Comparator<? super T> comparator)
Optional<T> 	min(Comparator<? super T> comparator)
Optional<T> 	findAny()
Optional<T> 	findFirst()
Optional<T> 	reduce(BinaryOperator<T> accumulator)
T 	reduce(T identity, BinaryOperator<T> accumulator)
<U> U 	reduce(U identity, BiFunction<U,? super T,U> accumulator, BinaryOperator<U> combiner)

<R,A> R 	collect(Collector<? super T,A,R> collector)
<R> R 	collect(Supplier<R> supplier, BiConsumer<R,? super T> accumulator, BiConsumer<R,R> combiner)
Object[] 	toArray()
<A> A[] 	toArray(IntFunction<A[]> generator)

void 	forEach(Consumer<? super T> action)
void 	forEachOrdered(Consumer<? super T> action)

Stream<T> 	distinct()
Stream<T> 	filter(Predicate<? super T> predicate)
<R> Stream<R> 	flatMap(Function<? super T,? extends Stream<? extends R>> mapper)
<R> Stream<R> 	map(Function<? super T,? extends R> mapper)
Stream<T> 	limit(long maxSize)
Stream<T> 	peek(Consumer<? super T> action)
Stream<T> 	skip(long n)
Stream<T> 	sorted()
Stream<T> 	sorted(Comparator<? super T> comparator)

DoubleStream 	flatMapToDouble(Function<? super T,? extends DoubleStream> mapper)
IntStream 	flatMapToInt(Function<? super T,? extends IntStream> mapper)
LongStream 	flatMapToLong(Function<? super T,? extends LongStream> mapper)
DoubleStream 	mapToDouble(ToDoubleFunction<? super T> mapper)
IntStream 	mapToInt(ToIntFunction<? super T> mapper)
LongStream 	mapToLong(ToLongFunction<? super T> mapper)

static <T> Stream.Builder<T> 	builder()
static <T> Stream<T> 	concat(Stream<? extends T> a, Stream<? extends T> b)
static <T> Stream<T> 	empty()
static <T> Stream<T> 	generate(Supplier<T> s)
static <T> Stream<T> 	iterate(T seed, UnaryOperator<T> f)
static <T> Stream<T> 	of(T... values)
static <T> Stream<T> 	of(T t)
```
