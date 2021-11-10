# Spring State Machine
- [API Doc](https://docs.spring.io/spring-statemachine/docs/3.0.1/api/)

## [StateMachine<S,E>]()
|Methods|Description|
|-------|----------|
| ExtendedState getExtendedState() |Gets the state machine extended state.|
|State<S,E> 	getInitialState()|Gets the initial state S.|
|StateMachineAccessor<S,E> 	getStateMachineAccessor()|Gets the state machine accessor.|
|boolean 	hasStateMachineError()|Checks for state machine error.|
|void 	setStateMachineError(java.lang.Exception exception)|Sets the state machine error.|
