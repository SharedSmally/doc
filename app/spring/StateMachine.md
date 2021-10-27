# Spring State Machine
- [Doc Reference](https://docs.spring.io/spring-statemachine/docs/3.0.1/reference/)
- [Tutorial1](https://www.baeldung.com/spring-state-machine)
- [Tutorial2](https://nagilla748.medium.com/introducing-spring-state-machine-77d446f85e13)
- [Tutorial3](https://medium.com/@chundi.vamsikrishna/spring-state-machine-for-beginners-e6ac8363d890)

## Tutorial:

## Configure SM
Need to define the states and state transitions by the events
```
@Configuration
@EnableStateMachine
//@EnableStateMachineFactory

public enum OrderStates { SUBMITTED, PAID, FULFILLED, CANCELLED }
public enum OrderEvents { FULFILL, PAY,  CANCEl }

private static final class StateMachineListener extends StateMachineListenerAdapter<OrderStates,OrderEvents>{
   @Override
   public void stateChanged(State<OrderStates, OrderEvents> from, State<OrderStates, OrderEvents> to) {
       System.out.println("state changed from "+from.toString()+"to"+to.toString());  
   }
}

public class PaymentAction implements Action<OrderStates, OrderEvents> {
   @Override
   public void execute(StateContext< OrderStates, OrderEvents > context){
       final String orderId = context.getExtendedState()
               .get("PRODUCT_ID", String.class);
       System.out.println(“order id" + orderId);
       // System.out.println(1/0);  // to trigger ErrorAction; which is called when this execution fails(throw exception)
   }
}
// could be StateMachineConfigurerAdapter<String,String> 
public class StateMachineConfiguration extends StateMachineConfigurerAdapter<OrderStates,OrderEvents> {
   @Override
   public void configure(StateMachineStateConfigurer<Order States, OrderEvents> states) throws Exception {
       states.withStates()
               .initial(OrderStates.SUBMITTED)
               .state(OrderStates.PAID)  
               //.states(EnumSet.allOf(OrderStates.class))
               .end(OrderStates.FULFILLED)
               .end(OrderStates.CANCELLED);
   }

   @Override
   public void configure(StateMachineConfigurationConfigurer<OrderStates, OrderEvents> config) throws Exception {
       config.withConfiguration()
            .autoStartup(false)
            .listener(new StateMachineListener());
   }
   
   @Override
   public void configure(StateMachineTransitionConfigurer<OrderStates, OrderEvents> transitions) throws Exception {
       transitions
         .withExternal()
            .source(OrderStates.SUBMITTED).target(OrderStates.PAID)
            .event(OrderEvents.PAY)
         .and()
         .withExternal()
            .source(OrderStates.PAID).target(OrderStates.FULFILLED)
            .event(OrderEvents.FULFILL)
         .withExternal()
            .source(OrderStates.SUBMITTED).target(OrderStates.PAID)
            .event(OrderEvents.PAY)
            .action(paymentAction(), errorAction())
            .guard(checkGuard())
            //.guardExpression("extendedState.variables.approvalCount > 0")
         .and()
         .withExternal()
            .source(OrderStates.FULFILLED).target(OrderStates.CANCELLED)
            .event(OrderEvents.CANCEl);
   }
   
   @Bean
   Action<OrderStates,OrderEvents> paymentAction() {
      return new PaymentAction(); 
   }
   
	 @Bean
	 public Guard<States, Events> checkGuard() {
		 return new Guard<States, Events>() {
			 @Override
			 public boolean evaluate(StateContext<States, Events> context) {
			  	return true;
			}
		};
	}
  
  @Bean
  public Guard<String, String> simpleGuard() {
    return ctx -> (int) ctx.getExtendedState()
      .getVariables()
      .getOrDefault("approvalCount", 0) > 0;
  }
}
```
- @EnableStateMachine — Need a configuration to create an instance of StateMachine. Spring context build an instance of a SM and started immediately on application startup.
- @EnableStateMachineFactory — Need a configuration to create an instance of a StateMachineFactory from which to get instance of StateMachine. Instance of SM is not created immediately on startup but started through the factory.

Usually @Configuration class extends adapters (EnumStateMachineConfigurerAdapter or StateMachineConfigurerAdapter), which provides override configuration callback methods.

SSM supports two ways of implementing states and events:
- string
- enumeration
- 
Normally both StatesEnum and EventsEnum are of Enums containing the Strings.
- StatesEnum: Enum of all the States occurring in State machine
- EventsEnum: Enum of all the Events Triggered in State machine

StateMachineTransitionConfigurer interface is used for transitions from one state(source) to another state(target) based on events triggered (event):
- .withExternal(): transition from one state to another state 
- .withInternal(): transition from state to same state

To use action and guard, need to declare paymentAction(),errorAction() bean definitions by creating the object of the class implementing interface Action<States,Event>.
A guard can be used to validate some data before a transition to a state is executed. 
A guard returns a true or false which will inform the state machine whether the transition should be allowed to occur.

### Hierarchical States
using multiple withStates() in conjunction with parent():
```
states
  .withStates()
    .initial("SI")
    .state("SI")
    .end("SF")
    .and()
  .withStates()
    .parent("SI")
    .initial("SUB1")
    .state("SUB2")
    .end("SUBEND");
```

### Junctions (Choices)
- mark a state a junction (choice) in the state definition:
```
states
  .withStates()
  .junction("SJ")
```
- in the transitions, define first/then/last options corresponding to an if-then-else structure:
```
.withJunction()
  .source("SJ")
  .first("high", highGuard())
  .then("medium", mediumGuard())
  .last("low")
```
- first and then take a second argument which is a regular guard which will be invoked to find out which path to take:
```
@Bean
public Guard<String, String> mediumGuard() {
    return ctx -> false;
}
@Bean
public Guard<String, String> highGuard() {
    return ctx -> false;
}
```
A transition does not stop at a junction node but will immediately execute defined guards and go to one of the designated routes.
state machine transites to SJ for both guards return false.

### Fork States
Split the execution into multiple independent execution paths.
- designate a node as a fork node and create hierarchical regions into which the state machine will perform the split:
```
states
  .withStates()
  .initial("SI")
  .fork("SFork")
  .and()
  .withStates()
    .parent("SFork")
    .initial("Sub1-1")
    .end("Sub1-2")
  .and()
  .withStates()
    .parent("SFork")
    .initial("Sub2-1")
    .end("Sub2-2");
```
- Define fork transition:
```
transitions
  .withFork()
    .source("SFork")
    .target("Sub1-1")
    .target("Sub2-1");
```
### Join States
The complement of the fork operation is the join. It allows us to set a state transitioning to which is dependent on completing some other states:
- designate a join node in the state definition:
```
states
  .withStates()
  .join("SJoin")
```
- In transitions, define which states need to complete to enable our join state:
```
transitions
  .withJoin()
    .source("Sub1-2")
    .source("Sub2-2")
    .target("SJoin");
```    
## Sending Events
After the configuration is done, a typed instance of StateMachine<States, Event> can immediately be accessed and autowired to the business logic. 
An initial state is already triggered. Driving a SM is realized via transitions which are triggered by the appropriate events:
```
@Autowired 
private StateMachine<States, Events> stateMachine;

stateMachine.start();  // start SM
stateMachine.getState(); // get state

public void run() {
  stateMachine.sendEvent(Events.assemble);
  stateMachine.sendEvent(Events.deliver);
}
```
Two methods to send events:
- simply sent a type safe event using sendEvent(E event)
```
 sm.sendEvent(OrderEvents.PAY); // sm is instance of state machine
```
- send event wrapped in a Spring messaging Message using sendEvent(Message<E> message) with a custom event headers. 
  This allows user to add arbitrary extra information with an event which is then visible to StateContext when in the implementing actions.
```
Message<OrderEvents> fullfillMessage = 
      MessageBuilder.withPayload(OrderEvents.FULFILL)
                    .setHeader(ORDER_ID_HEADER,orderId)
                    .build();
sm.sendEvent(fullfillMessage); // sm is instance of state machine
```
## SM Interceptor 
The same SM is created, but 
An interceptor must be registered via StateMachineAccessor even before the SM has been initialized. 
For the system uses the same instance of the SM, the message information on the event should be send. An interface can be created:
```
public interface OrderStateChangeListener {
  void onStateChange(State<States, Events> state, Message<Events> message); 
}
```  
The event related info is wrapped to the appropriate message object context.The publisher and consumers must then be aware of this type of object. 
```
@Component 
public class OrdersStateHandler extends LifecycleObjectSupport {
  @Autowired 
  private StateMachine<States, Events> stateMachine; 

  private Set<OrderStateChangeListener> listeners = new HashSet<>();

  @Override 
  protected void onInit() throws Exception {
    stateMachine
      .getStateMachineAccessor()
      .doWithAllRegions(new StateMachineFunction<State-MachineAccess<States, Events>>() { 
        @Override 
        public void apply(StateMachineAccess<States, Events> function) {  
          function.addStateMachineInterceptor(new StateMachineInterceptorAdapter<States, Events>() { 
          @Override 
          public void preStateChange(State<States, Events> state, Message message) { 
            listeners.forEach(listener -> listener.onStateChange(state, message)); 
          } 
        }); 
      } 
    }); 
  }
 
  public void registerListener(OrderStateChangeListener listener) { 
    listeners.add(listener); 
  }

  public void handleEvent(Message event, States sourceState) { 
    stateMachine.stop(); 
    stateMachine
      .getStateMachineAccessor()
      .doWithAllRegions(access -> access.resetStateMachine(new DefaultStateMachineContext<States, Events>(sourceState, null, null, null)));
    stateMachine.start(); 
    stateMachine.sendEvent(event); 
  } 
}
```
For the publisher responsible for delivering the order to the customer:
```
stateHandler.handleEvent(
  MessageBuilder.withPayload(Events.deliver)
    .setHeader("order-id", or-derId)
    .build(), States.ASSEMBLED);
```
 
Consumer must implement the appropriate interface OrderStateChangeListener and register itself by a handler.
```
@Override 
public void onStateChange(State<States, Events> state, Message message) {
  Long orderId = message.getHeaders().get("order-id", Long.class);
  Order order = repository.findOne(orderId);
  order.setState(state.getId()); 
  repository.save(order); 
}  
```  
