# Spring
- AppContext as the IoC container to get the @Bean. Existing beans are: ApplicationContext, 
- The Beans from [@Configuration](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/annotation/Configuration.html) class are put in the IoC
- Using interfaces instead of implementation classes for @AutoWired. The real

## Annotations
Package [org.springframework.context.annotation](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/annotation/package-summary.html):
- Bean: Indicates that a method produces a bean to be managed by the Spring container.
- Configuration: Indicates that a class declares one or more @Bean methods and may be processed by the Spring container to generate bean definitions and service requests for those beans at runtime, 

- Import: Indicates one or more @Configuration classes to import.
- ImportResource: Indicates one or more resources containing bean definitions to import.
- ComponentScan: Configures component scanning directives for use with @Configuration classes.
- ComponentScans: Container annotation that aggregates several ComponentScan annotations.

- DependsOn: Beans on which the current bean depends.
- PropertySource:  providing a convenient and declarative mechanism for adding a PropertySource to Spring's Environment.
- PropertySources: Container annotation that aggregates several PropertySource annotations.

- Lazy: Indicates whether a bean is to be lazily initialized.
- Primary: Indicates that a bean should be given preference when multiple candidates are qualified to autowire a single-valued dependency.
- Profile: Indicates that a component is eligible for registration when one or more specified profiles are active.
- Role: Indicates the 'role' hint for a given bean.
- Scope: Indicates the name of a scope to use for instances of the annotated type as a type-level annotation in conjunction with @Component

Package [org.springframework.stereotype](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/stereotype/package-summary.html):
- Component: Indicates that an annotated class is a "component", the classes considered as candidates for auto-detection when using annotation-based configuration and classpath scanning
- Controller: Indicates that an annotated class is a "Controller". (RestController) 
- Repository: Indicates that an annotated class is a "Repository".
- Service: Indicates that an annotated class is a "Service"
- Indexed: Indicate that the annotated element represents a stereotype for the index.

Package [org.springframework.beans.factory.annotation](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/factory/annotation/package-summary.html)
- Autowired:	Marks a constructor, field, setter method or config method as to be autowired by Spring's dependency injection facilities.
- Configurable: Marks a class as being eligible for Spring-driven configuration.
- Lookup: An annotation that indicates 'lookup' methods, to be overridden by the container to redirect them back to the BeanFactory for a getBean call.
- Qualifier: Used on a field or parameter as a qualifier for candidate beans when autowiring.
- Value: Annotation at the field or method/constructor parameter level that indicates a default value expression for the affected argument.

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
