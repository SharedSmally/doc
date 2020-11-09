# Circuit Breaker

## [Concept](https://martinfowler.com/bliki/CircuitBreaker.html)
- Pattern: 

![pattern](https://martinfowler.com/bliki/images/circuitBreaker/sketch.png)

The basic idea behind the circuit breaker is very simple. You wrap a protected function call in a circuit breaker object, 
which monitors for failures. Once the failures reach a certain threshold, the circuit breaker trips, and all further calls
to the circuit breaker return with an error, without the protected call being made at all. 

- State:

![state](https://martinfowler.com/bliki/images/circuitBreaker/state.png)

Calling the circuit breaker will call the underlying block if the circuit is closed, but return an error if it's open.
