# Spring Boot

## Core Features
    
### Profiles
Any @Component, @Configuration or @ConfigurationProperties can be marked with @Profile to limit when it is loaded,

```
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Profile;

@Configuration(proxyBeanMethods = false)
@Profile("production")
public class ProductionConfiguration {
    // ...
}
```

The **spring.profiles.active** Environment property is used to specify which profiles are active:
```
spring.profiles.active=dev,hsqldb   # in application.properties
spring.profiles.default=none        # If no profile is active, a default profile is enabled. 
                                    # The name of the default profile is default
--spring.profiles.active=dev,hsqldb # on the command line
```

The **spring.profiles.include** property can be used to add active profiles on top of those activated by the **spring.profiles.active** property:
```
spring.profiles.include[0]=common
spring.profiles.include[1]=local
```
**spring.profiles.active**, **spring.profiles.default** and **spring.profiles.include** can only be used in non-profile specific documents. They cannot be included in profile specific files or documents activated by **spring.config.activate.on-profile**.

A profile group define a logical name for a related group of profiles.
```
spring.profiles.group.production[0]=proddb
spring.profiles.group.production[1]=prodmq
```
Use *--spring.profiles.active=production* to active the *production*, *proddb* and *prodmq* profiles in one hit.

The active profiles can be set by calling SpringApplication.setAdditionalProfiles() before the application runs, or Spring’s ConfigurableEnvironment interface.

### Logging

By default Logback is used for logging when using the Starters. 

- spring.output.ansi.enabled: support ANSI, color output
- logging.file.name or logging.file.path: for logging File Output
- logging.logback.rollingpolicy.\*: for File Rotation. Use the corresponding config files for other logging framework.
- logging.level.<logger-name>=<level>: for Log Level: ERROR, WARN, INFO, DEBUG, or TRACE.
- logging.group.xxx: for logging group, the group can be set using logging.level.xxx=<level>
- logging.register-shutdown-hook=false/true: trigger log system cleanup when the JVM exits is provided.
- logging.\*: Custom Log Configuration    
- logback.xml or logback-spring.xml to config Logback configuration
     - \<springProfile\>: include or exclude sections of configuration based on the active Spring profiles.
     - \<springProperty\>: expose properties from the Spring Environment for use within Logback.

### Internationalization
    
By default, Spring Boot looks for the presence of a messages resource (**spring.messages.\***) bundle at the root of the classpath. See [MessageSourceProperties](https://github.com/spring-projects/spring-boot/blob/v2.7.3/spring-boot-project/spring-boot-autoconfigure/src/main/java/org/springframework/boot/autoconfigure/context/MessageSourceProperties.java) for more supported options.

### JSON
Jackson (Gson/JSON-B) from  **spring-boot-starter-json** is the preferred and default library, and an **ObjectMapper** bean is automatically configured.   

- Custom Serializers and Deserializers    

Use the @JsonComponent annotation directly on JsonSerializer, JsonDeserializer or KeyDeserializer implementations. All @JsonComponent beans in the ApplicationContext are automatically registered with Jackson. 
```java
import java.io.IOException;

import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.core.ObjectCodec;
import com.fasterxml.jackson.databind.DeserializationContext;
import com.fasterxml.jackson.databind.JsonDeserializer;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.JsonSerializer;
import com.fasterxml.jackson.databind.SerializerProvider;

import org.springframework.boot.jackson.JsonComponent;

@JsonComponent
public class MyJsonComponent {

    public static class Serializer extends JsonSerializer<MyObject> {
        @Override
        public void serialize(MyObject value, JsonGenerator jgen, SerializerProvider serializers) throws IOException {
            jgen.writeStartObject();
            jgen.writeStringField("name", value.getName());
            jgen.writeNumberField("age", value.getAge());
            jgen.writeEndObject();
        }
    }

    public static class Deserializer extends JsonDeserializer<MyObject> {
        @Override
        public MyObject deserialize(JsonParser jsonParser, DeserializationContext ctxt) throws IOException {
            ObjectCodec codec = jsonParser.getCodec();
            JsonNode tree = codec.readTree(jsonParser);
            String name = tree.get("name").textValue();
            int age = tree.get("age").intValue();
            return new MyObject(name, age);
        }
    }
}
```
Alternatively using JsonObjectSerializer and JsonObjectDeserializer base classes:
```
import java.io.IOException;

import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.core.ObjectCodec;
import com.fasterxml.jackson.databind.DeserializationContext;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.SerializerProvider;

import org.springframework.boot.jackson.JsonComponent;
import org.springframework.boot.jackson.JsonObjectDeserializer;
import org.springframework.boot.jackson.JsonObjectSerializer;

@JsonComponent
public class MyJsonComponent {
    public static class Serializer extends JsonObjectSerializer<MyObject> {
        @Override
        protected void serializeObject(MyObject value, JsonGenerator jgen, SerializerProvider provider) throws IOException {
            jgen.writeStringField("name", value.getName());
            jgen.writeNumberField("age", value.getAge());
        }
    }

    public static class Deserializer extends JsonObjectDeserializer<MyObject> {
        @Override
        protected MyObject deserializeObject(JsonParser jsonParser, DeserializationContext context, ObjectCodec codec,
                JsonNode tree) throws IOException {
            String name = nullSafeValue(tree.get("name"), String.class);
            int age = nullSafeValue(tree.get("age"), Integer.class);
            return new MyObject(name, age);
        }
    }
}
```    

### Task Execution and Scheduling
In the absence of an Executor bean in the context, Spring Boot auto-configures a ThreadPoolTaskExecutor with sensible defaults that can be automatically associated to asynchronous task execution (@EnableAsync) and Spring MVC asynchronous request processing(requires an AsyncTaskExecutor implementation). The default settings can be fine-tuned using the **spring.task.execution** namespace:
```
spring.task.execution.pool.max-size=16
spring.task.execution.pool.queue-capacity=100
spring.task.execution.pool.keep-alive=10s
```    
A ThreadPoolTaskScheduler can be auto-configured if need to be associated to scheduled task execution (using @EnableScheduling for instance). The thread pool uses one thread by default and its settings can be fine-tuned using the **spring.task.scheduling** namespace:
```
spring.task.scheduling.thread-name-prefix=scheduling-
spring.task.scheduling.pool.size=2
```    
Both a TaskExecutorBuilder bean and a TaskSchedulerBuilder bean are made available in the context if a custom executor or scheduler needs to be created.

### Testing
Two modules:    
- spring-boot-test: contains core items
- spring-boot-test-autoconfigure: supports auto-configuration for tests    
The **spring-boot-starter-test** Starter imports both Spring Boot test modules as well as JUnit Jupiter, AssertJ, Hamcrest, and a number of other useful libraries.    
Add a dependency on **junit-vintage-engine** to support JUnit4(hamcrest-core is excluded in favor of org.hamcrest:hamcrest):
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

The **spring-boot-starter-test** Starter contains the following provided libraries:
- JUnit 5: The de-facto standard for unit testing Java applications.
- Spring Test & Spring Boot Test: Utilities and integration test support for Spring Boot applications.
- AssertJ: A fluent assertion library.
- Hamcrest: A library of matcher objects (also known as constraints or predicates).
- Mockito: A Java mocking framework.
- JSONassert: An assertion library for JSON.
- JsonPath: XPath for JSON.


    
    
    
