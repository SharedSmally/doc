# [Java Streaming](https://docs.oracle.com/javase/8/docs/api/java/util/stream/Stream.html)
```
 int sum = widgets.stream()
                  .filter(w -> w.getColor() == RED)
                  .mapToInt(w -> w.getWeight())
                  .sum();
```
To perform a computation, stream operations are composed into a stream pipeline. A stream pipeline consists of a source (which might be an array, a collection, a generator function, an I/O channel, etc), zero or more intermediate operations (which transform a stream into another stream, such as filter(Predicate)), and a terminal operation (which produces a result or side-effect, such as count() or forEach(Consumer)). Streams are lazy; computation on the source data is only performed when the terminal operation is initiated, and source elements are consumed only as needed. 

| Method | Description |
| Stream<T> 	filter(Predicate<? super T> predicate) |Returns a stream consisting of the elements of this stream that match the given predicate.|
|<R> Stream<R> 	flatMap(Function<? super T,? extends Stream<? extends R>> mapper)|Returns a stream consisting of the results of replacing each element of this stream with the contents of a mapped stream produced by applying the provided mapping function to each element.|
|void 	forEach(Consumer<? super T> action)|Performs an action for each element of this stream.|
|<R> Stream<R> 	map(Function<? super T,? extends R> mapper)|Returns a stream consisting of the results of applying the given function to the elements of this stream.|
Optional<T> 	reduce(BinaryOperator<T> accumulator)
Performs a reduction on the elements of this stream, using an associative accumulation function, and returns an Optional describing the reduced value, if any.
|T 	reduce(T identity, BinaryOperator<T> accumulator)|Performs a reduction on the elements of this stream, using the provided identity value and an associative accumulation function, and returns the reduced value.|
|Stream<T> 	peek(Consumer<? super T> action)|Returns a stream consisting of the elements of this stream, additionally performing the provided action on each element as elements are consumed from the resulting stream.|
|Object[] 	toArray()|Returns an array containing the elements of this stream.|

