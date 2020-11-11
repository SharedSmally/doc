# Flux Samples
- [Example1](https://www.infoq.com/articles/reactor-by-example/)

## [map  vs flatmap](https://stackoverflow.com/questions/49115135/map-vs-flatmap-in-reactor)
- map is for synchronous, non-blocking, 1-to-1 transformations. It takes a Function<T, U> and returns a Flux<U>
- flatMap is for asynchronous (non-blocking) 1-to-N transformations. It takes a Function<T, Publisher<V>> and returns a Flux<V>
```
return Mono.just(Person("name", "age:12"))
        .map { 
            person -> EnhancedPerson(person, "id-set", "savedInDb")
        }.flatMap { 
            person -> reactiveMongoDb.save(person)
        }
```
## zip vs zipWith

## Example
```
private static List<String> words = Arrays.asList("the","quick",
        "brown", "fox", "jumped", "over", "the", "lazy", "dog" );
  
public void simpleCreation() {
     Flux<String> fewWords = Flux.just("Hello", "World");
     Flux<String> manyWords = Flux.fromIterable(words);

     fewWords.subscribe(System.out::println);
     System.out.println();
     manyWords.subscribe(System.out::println);
}
  
public void findingMissingLetter() {
  Flux<String> manyLetters = Flux.fromIterable(words)
        .flatMap(word -> Flux.fromArray(word.split("")))
        .distinct()  # filter out duplicate letters 
        .sort()      # sort
        .zipWith(Flux.range(1, Integer.MAX_VALUE),
              (string, count) -> String.format("%2d. %s", count, string));

  manyLetters.subscribe(System.out::println);
}
```
```
public void restoringMissingLetter() {
  Mono<String> missing = Mono.just("s");
  Flux<String> allLetters = Flux.fromIterable(words)
        .flatMap(word -> Flux.fromArray(word.split("")))
        .concatWith(missing)
        .distinct()
        .sort()
        .zipWith(Flux.range(1, Integer.MAX_VALUE),
              (string, count) -> String.format("%2d. %s", count, string));

  allLetters.subscribe(System.out::println);
}
```
