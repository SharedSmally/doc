# Java Flux
- [Flux API doc](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/Flux.html)
- [Tutorial](https://www.codingame.com/playgrounds/929/reactive-programming-with-reactor-3/Flux)


A Flux<T> is a Reactive Streams Publisher, augmented with a lot of operators that can be used to generate, transform, orchestrate Flux sequences.

It can emit 0 to n <T> elements (onNext event) then either completes or errors (onComplete and onError terminal events). If no terminal event is triggered, the Flux is infinite.

- Static factories on Flux allow to create sources, or generate them from several callbacks types.
- Instance methods, the operators, let you build an asynchronous processing pipeline that will produce an asynchronous sequence.
- Each Flux#subscribe() or multicasting operation such as Flux#publish and Flux#publishNext will materialize a dedicated instance of the pipeline and trigger the data flow inside it.


## Create Flux via static methods

## operators
- map


