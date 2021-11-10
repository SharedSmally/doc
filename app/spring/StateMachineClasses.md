# Spring State Machine
- [API Doc](https://docs.spring.io/spring-statemachine/docs/3.0.1/api/)

## StateMachine<S,E>
|Methods|Description|
|-------|----------|
| ExtendedState getExtendedState() |Gets the state machine extended state.|
|State<S,E> 	getInitialState()|Gets the initial state S.|
|StateMachineAccessor<S,E> 	getStateMachineAccessor()|Gets the state machine accessor.|
|boolean 	hasStateMachineError()|Checks for state machine error.|
|void 	setStateMachineError(java.lang.Exception exception)|Sets the state machine error.|

## State<S,E>
|Methods|Description|
|-------|----------|
|void addActionListener(ActionListener<S,E> listener)|Adds the action listener.|
|void 	removeActionListener(ActionListener<S,E> listener)|Removes the action listener.|
|void 	addStateListener(StateListener<S,E> listener)|Adds the state listener.|
|void 	removeStateListener(StateListener<S,E> listener)|Removes the state listener.|
|Mono<java.lang.Void> 	entry(StateContext<S,E> context)|Initiate an entry sequence for the state.|
|Mono<java.lang.Void> 	exit(StateContext<S,E> context)|Initiate an exit sequence for the state.|
|E[] 	getDeferredEvents()|Gets the deferred events for this state.|
[Mono<java.lang.Void>[]| 	getEntryActions()|Gets Actions executed entering in this state.|
|Mono<java.lang.Void>[]| 	getExitActions()|Gets Actions executed exiting from this state.|
|S 	getId()|Gets the state identifier.|
|S[] 	getIds()|Gets the state identifiers.|
|PseudoState<S,E> 	getPseudoState()|Gets a PseudoState attached to a State.|
|Mono 	getStateActions()|Gets Actions executed once in this state.|
|State<S,E>[] 	getStates()|Gets all possible states this state knows about including itself and substates.|
|boolean 	isComposite()|Checks if state is a composite state.|
|boolean 	isOrthogonal()|Checks if state is an orthogonal state.|
|boolean 	isSimple()|Checks if state is a simple state.|
|boolean 	isSubmachineState()|Checks if state is a submachine state.}
|Flux<StateMachineEventResult<S,E>> sendEvent(Message<E> event)|Send an event E wrapped with a Message to the state |
|boolean 	shouldDefer(Message<E> event)|Checks if state wants to defer an event.|
  
