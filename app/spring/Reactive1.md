# Reactive Programming

## Mono Sample:
Normal:
```
public Person findCurrentUser() {
    if (isAuthenticated()) return new Person("Jane", "Doe");
    else return null;
}
```
Java 8:
```
public Optional<Person> findCurrentUser() {
    if (isAuthenticated()) return Optional.of(new Person("Jane", "Doe"));
    else return Optional.empty();
}
```
Reactive:
```
public Mono<Person> findCurrentUser() {
    if (isAuthenticated()) return Mono.just(new Person("Jane", "Doe"));
    else return Mono.empty();
}
```

## Flux Sample:
Normal:
```
public List<Person> findAll() {
    return Arrays.asList(
        new Person("Jane", "Doe"),
        new Person("John", "Doe")
    );
}
```
Java 8:
```
public Stream<Person> findAll() {
    return Stream.of(
        new Person("Jane", "Doe"),
        new Person("John", "Doe")
    );
}
```
Reactive:
```
public Flux<Person> findAll() {
    return Flux.just(
        new Person("Jane", "Doe"),
        new Person("John", "Doe")
    );
}
```

## Subscriber:
```
Flux
    .just(1, 2, 3, 4)
    .reduce(Integer::sum)
    .log();
```
Reactive streams are lazy, and won’t start as long as there is no subscriber present. That means that a subscriber is always necessary with reactive streams.
To get the result:
```
AtomicInteger sum = new AtomicInteger(0);
Flux
    .just(1, 2, 3, 4)
    .reduce(Integer::sum)
    .subscribe(sum::set);
log.info("Sum is: {}", sum.get());

Flux
    .just(1, 2, 3, 4)
    .reduce(Integer::sum)
    .susbcribe(sum -> logger.info("Sum is: {}", sum);
```
