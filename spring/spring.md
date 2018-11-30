# Spring
- AppContext as the IoC container to get the @Bean. Existing beans are: ApplicationContext, 
- The Beans from [@Configuration](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/annotation/Configuration.html) class are put in the IoC
- Using interfaces instead of implementation classes for @AutoWired. The real

## Annotations
Package [org.springframework.context.annotation](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/annotation/package-summary.html):
- **Bean**: Indicates that a method produces a bean to be managed by the Spring container.
- **Configuration**: Indicates that a class declares one or more @Bean methods and may be processed by the Spring container to generate bean definitions and service requests for those beans at runtime, 

- **Import**: Indicates one or more @Configuration classes to import.
- **ImportResource**: Indicates one or more resources containing bean definitions to import.
- **ComponentScan**: Configures component scanning directives for use with @Configuration classes.
- **ComponentScans**: Container annotation that aggregates several ComponentScan annotations.

- **DependsOn**: Beans on which the current bean depends.
- **PropertySource**:  providing a convenient and declarative mechanism for adding a PropertySource to Spring's Environment.
- **PropertySources**: Container annotation that aggregates several PropertySource annotations.

- **Lazy**: Indicates whether a bean is to be lazily initialized.
- **Primary**: Indicates that a bean should be given preference when multiple candidates are qualified to autowire a single-valued dependency.
- **Profile**: Indicates that a component is eligible for registration when one or more specified profiles are active.
- **Role**: Indicates the 'role' hint for a given bean.
- **Scope**: Indicates the name of a scope to use for instances of the annotated type as a type-level annotation in conjunction with @Component

Package [org.springframework.stereotype](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/stereotype/package-summary.html):
- **Component**: Indicates that an annotated class is a "component", the classes considered as candidates for auto-detection when using annotation-based configuration and classpath scanning
- **Controller**: Indicates that an annotated class is a "Controller". (RestController) 
- **Repository**: Indicates that an annotated class is a "Repository".
- **Service**: Indicates that an annotated class is a "Service"
- **Indexed**: Indicate that the annotated element represents a stereotype for the index.

Package [org.springframework.beans.factory.annotation](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/factory/annotation/package-summary.html)
- **Autowired**:	Marks a constructor, field, setter method or config method as to be autowired by Spring's dependency injection facilities.
- **Configurable**: Marks a class as being eligible for Spring-driven configuration.
- **Lookup**: An annotation that indicates 'lookup' methods, to be overridden by the container to redirect them back to the BeanFactory for a getBean call.
- **Qualifier**: Used on a field or parameter as a qualifier for candidate beans when autowiring.
- **Value**: Annotation at the field or method/constructor parameter level that indicates a default value expression for the affected argument.

Package org.springframework.core.annotation
- **AliasFor**: Used to declare aliases for annotation attributes.
- **Order**:  defines the sort order for an annotated component.

Package org.springframework.format.annotation:
- **DateTimeFormat**: Declares that a field or method parameter should be formatted as a date or time.
- **NumberFormat**: Declares that a field or method parameter should be formatted as a number.

Package org.springframework.jms.annotation:
- **EnableJms**: Enable JMS listener annotated endpoints that are created under the cover by a JmsListenerContainerFactory.
- **JmsListener**: marks a method to be the target of a JMS message listener on the specified JmsListener.destination().
- **JmsListeners**: Container annotation that aggregates several JmsListener annotations.

Package org.springframework.jmx.export.annotation:
- **ManagedAttribute**: Method-level annotation that indicates to expose a given bean property as a JMX attribute, corresponding to the ManagedAttribute attribute.
- **ManagedMetric**: Method-level annotation that indicates to expose a given bean property as a JMX attribute, with added descriptor properties to indicate that it is a metric.
- **ManagedNotification**: Type-level annotation that indicates a JMX notification emitted by a bean.
- **ManagedNotifications**: Type-level annotation that indicates JMX notifications emitted by a bean, containing multiple ManagedNotifications.
- **ManagedOperation**: Method-level annotation that indicates to expose a given method as a JMX operation, corresponding to the ManagedOperation attribute.
- **ManagedOperationParameter**: Method-level annotation used to provide metadata about operation parameters, corresponding to a ManagedOperationParameter attribute.
- **ManagedOperationParameters**:Method-level annotation used to provide metadata about operation parameters, corresponding to an array of ManagedOperationParameter attributes.
- **ManagedResource**: Class-level annotation that indicates to register instances of a class with a JMX server, corresponding to the ManagedResource attribute.

Package org.springframework.messaging.handler.annotation:
- **DestinationVariable**: Annotation that indicates a method parameter should be bound to a template variable in a destination template string.
- **Header**: Annotation which indicates that a method parameter should be bound to a message header.
- **Headers**: Annotation which indicates that a method parameter should be bound to the headers of a message.
- **MessageExceptionHandler**: Annotation for handling exceptions thrown from message-handling methods within a specific handler class.
- **MessageMapping**: Annotation for mapping a Message onto message-handling methods by matching to the message destination.
- **Payload**: Annotation that binds a method parameter to the payload of a message.
- **SendTo**: Annotation that indicates a method's return value should be converted to a Message if necessary and sent to the specified destination.

Package org.springframework.messaging.simp.annotation:
- **SendToUser**: Indicates the return value of a message-handling method should be sent as a Message to the specified destination(s) further prepended with "/user/{username}" where the user name is extracted from the headers of the input message being handled.
- **SubscribeMapping**: Annotation for mapping subscription messages onto specific handler methods based on the destination of a subscription.


Package [org.springframework.scheduling.annotation](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/scheduling/annotation/package-summary.html)
- **Async**: Annotation that marks a method as a candidate for asynchronous execution.
- **EnableAsync**: Enables Spring's asynchronous method execution capability, similar to functionality found in Spring's <task:*> XML namespace.
- **EnableScheduling**: Enables Spring's scheduled task execution capability, similar to functionality found in Spring's <task:*> XML namespace.
- **Scheduled**: An annotation that marks a method to be scheduled.
- **Schedules**: Container annotation that aggregates several Scheduled annotations.

Package [org.springframework.cache.annotation](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/cache/annotation/package-summary.html)
- **Cacheable**: Annotation indicating that the result of invoking a method (or all methods in a class) can be cached.
- **CacheConfig**: @CacheConfig provides a mechanism for sharing common cache-related settings at the class level.
- **CacheEvict**: Annotation indicating that a method (or all methods on a class) triggers a cache evict operation.
- **CachePut**: Annotation indicating that a method (or all methods on a class) triggers a cache put operation.
- **Caching****: Group annotation for multiple cache annotations (of different or the same type).
- **EnableCaching**: Enables Spring's annotation-driven cache management capability, similar to the support found in Spring's <cache:*> XML namespace.


## Configuration
```
 import org.springframework.context.annotation.Bean;
 import org.springframework.context.annotation.Configuration;
  
 @Configuration
 public class AppConfig {

     @Bean
     public MyBean myBean() {
         // instantiate, configure and return bean ...
     }
 }
```

##
