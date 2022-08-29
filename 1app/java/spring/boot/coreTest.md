# Spring Boot
## Spring Core Features

### [Test](https://docs.spring.io/spring-boot/docs/current/reference/html/features.html#features.testing)
Two modules:    
- spring-boot-test: contains core items
- spring-boot-test-autoconfigure: supports auto-configuration for tests    
    
The **spring-boot-starter-test** Starter imports both Spring Boot test modules as well as JUnit Jupiter, AssertJ, Hamcrest, and a number of other useful libraries:
- JUnit 5: The de-facto standard for unit testing Java applications.
- Spring Test & Spring Boot Test: Utilities and integration test support for Spring Boot applications.
- AssertJ: A fluent assertion library.
- Hamcrest: A library of matcher objects (also known as constraints or predicates).
- Mockito: A Java mocking framework.
- JSONassert: An assertion library for JSON.
- JsonPath: XPath for JSON.
    
To support JUnit4, add a dependency on **junit-vintage-engine** (hamcrest-core is excluded in favor of org.hamcrest:hamcrest):
```
<dependency>
    <groupId>org.junit.vintage</groupId>
    <artifactId>junit-vintage-engine</artifactId>
    <scope>test</scope>
    <exclusions>
        <exclusion>
            <groupId>org.hamcrest</groupId>
            <artifactId>hamcrest-core</artifactId>
        </exclusion>
    </exclusions>
</dependency>    
``` 

#### Auto Configuration
Auto-configuration can be associated to a starter that provides the auto-configuration code as well as the typical libraries that you would use with it.

- Understanding Auto-configured Beans

Auto-configuration is implemented with the @AutoConfiguration annotation, it is meta-annotated with @Configuration, making auto-configurations standard @Configuration classes. Additional @Conditional annotations are used to constrain when the auto-configuration should apply. Usually, auto-configuration classes use @ConditionalOnClass and @ConditionalOnMissingBean annotations. This ensures that auto-configuration applies only when relevant classes are found and when you have not declared your own @Configuration.



