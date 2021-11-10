# Spring State Machine
- [API Doc](https://docs.spring.io/spring-statemachine/docs/3.0.1/api/)

Using StateMachineFactory: could define multiple Factories
```
@Configuration
@EnableStateMachineFactory(name = "smfactory1")
public class FactoryConfiguration1  extends EnumStateMachineConfigurerAdapter<States, Events> {
    private Logger logger = LoggerFactory.getLogger(getClass());

    @PostConstruct
    public void init() {
        logger.info(" ++++++++++ POSTCONSTRUCTOR FOR factory_config_1 ++++++++++");
    }

    @Override
    public void configure(StateMachineConfigurationConfigurer<States, Events> config) throws Exception {
         // set global configurations; register Listener, ... 
    }

    @Override
    public void configure(StateMachineStateConfigurer<States, Events> states) throws Exception {
         // define states, and related actions... 
    }

    @Override
    public void configure(StateMachineTransitionConfigurer<States, Events> transitions) throws Exception {
        // define transitions: target, event, source, and related action: ... 
    }
    .....
}
```
In the Component:
```
@Service
public class StateMachineWorker {
   @Autowired
   @Qualifier("smfactory1")
   private StateMachineFactory<States, Events> smfactory1;

   @Autowired
   @Qualifier("smfactory2")
   private StateMachineFactory<States, Events> smfactory2;
   
   private StateMachine<States, Events> stateMachine;
   static private Logger logger = LoggerFactory.getLogger(getClass());
   
   @PostConstruct
   public void init() {
      stateMachine = smfactory2.getStateMachine();
      stateMachine.start();
   }
}
```

## Main classes
- StateMachine<S,E>: from Region<S,E> from StateMachineReactiveLifecycle; use ExtendedState() to store additioal messages.
|Methods|Description|
|-------|----------|
|void 	addStateListener(StateMachineListener<S,E> listener)|Adds the state listener.|
|void 	removeStateListener(StateMachineListener<S,E> listener)|Removes the state listener.|
|boolean 	sendEvent(E event)|in favor of sendEvent(Mono)|
|boolean 	sendEvent(Message<E> event)|in favor of sendEvent(Mono)|
  
  
## Interface StateMachineReactiveLifecycle
|Methods|Description|
|-------|----------|
|Mono<Void> 	startReactively()|Starts component reactively.|
|Mono<Void> 	stopReactively()|Stops component reactively.|

## Interface Region<S,E>: Inherit from StateMachineReactiveLifecycle
|Methods|Description|
|-------|----------|
|String 	getId()|Gets the region and state machine id.|
|UUID 	getUuid()|Gets the region and state machine unique id.|
|boolean 	isComplete()|Checks if region complete.|
|State<S,E> 	getState()|Gets the current State.|
|State<S,E>[] 	getStates()|Gets the States defined in this region.|
|Transition<S,E>[] 	getTransitions()|Gets a Transitions for this region.|
|boolean 	sendEvent(E event)|in favor of sendEvent(Mono)|
|boolean 	sendEvent(Message<E> event)|in favor of sendEvent(Mono)|
|Flux<StateMachineEventResult<S,E>>	sendEvent(Mono<Message<E>> event)|Send a Mono of event and return a Flux of StateMachineEventResults.|
|Mono<<StateMachineEventResult<S,E>>>	sendEventCollect(Mono<Message<E>> event)|Send a Mono of event and return a Mono of collected StateMachineEventResults as a list.|
|Flux<StateMachineEventResult<S,E>> sendEvents(Flux<Message<E>> events)|Send a Flux of events and return a Flux of StateMachineEventResults.|
|void 	start()|in favor of StateMachineReactiveLifecycle.startReactively()|
|void 	stop()| in favor of StateMachineReactiveLifecycle.stopReactively()| 

## Interface StateMachine<S,E> : Region<S,E>
|Methods|Description|
|-------|----------|
| ExtendedState getExtendedState() |Gets the state machine extended state.|
|State<S,E> 	getInitialState()|Gets the initial state S.|
|StateMachineAccessor<S,E> 	getStateMachineAccessor()|Gets the state machine accessor.|
|boolean 	hasStateMachineError()|Checks for state machine error.|
|void 	setStateMachineError(java.lang.Exception exception)|Sets the state machine error.|

## ExtendedState
|Methods|Description|
|-------|----------|
|<T> T get(Object key, Class<T> type)|Gets a variable which is automatically casted into a type.|
|Map<Object,Object> 	getVariables()|Gets the extended state variables.|
|void 	setExtendedStateChangeListener(ExtendedStateChangeListener listener)|Sets the extended state change listener.|

## Interface StateContext<S,E>  
|Methods|
|-------|
|StateMachine<S,E> 	getStateMachine()|  
|E 	getEvent()|
|Exception 	getException()|
|ExtendedState 	getExtendedState()|
|Message<E> 	getMessage()|
|Object 	getMessageHeader(Object header)|
|MessageHeaders 	getMessageHeaders()|
|State<S,E> 	getSource()|
|State<S,E>[] 	getSources()|
|StateContext.Stage 	getStage()|
|State<S,E> 	getTarget()|
|State<S,E>[] 	getTargets()|
|Transition<S,E> 	getTransition()|

## Interface Action<S,E>: Function, executing an Action with a StateContext.
|Methods|Description|
|-------|----------|  
|void	execute(StateContext<S,E> context)|Execute action with a StateContext.|
Action<S,E> getAction() { return ctx->{ ....; }; }
  
  
## Interface StateMachineListener<S,E>
|Methods|
|-------|
|void 	eventNotAccepted(Message<E> event)|
|void 	extendedStateChanged(Object key, Object value)|
|void 	stateChanged(State<S,E> from, State<S,E> to)|
|void 	stateContext(StateContext<S,E> stateContext)|
|void 	stateEntered(State<S,E> state)|
|void 	stateExited(State<S,E> state)|
|void 	stateMachineError(StateMachine<S,E> stateMachine, Exception exception)|
|void 	stateMachineStarted(StateMachine<S,E> stateMachine)|
|void 	stateMachineStopped(StateMachine<S,E> stateMachine)|
|void 	transition(Transition<S,E> transition)|
|void 	transitionEnded(Transition<S,E> transition)|
|void 	transitionStarted(Transition<S,E> transition)|

  


## State<S,E>
|Methods|Description|
|-------|----------|
|void addActionListener(ActionListener<S,E> listener)|Adds the action listener.|
|void removeActionListener(ActionListener<S,E> listener)|Removes the action listener.|
|void addStateListener(StateListener<S,E> listener)|Adds the state listener.|
|void removeStateListener(StateListener<S,E> listener)|Removes the state listener.|
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
  
