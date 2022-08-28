# Spring Boot
Auto Configuration based on Dependencies

## Reference
- [Site](https://spring.io/projects/spring-boot/)
- [Quick Start](https://spring.io/quickstart)
- [User Guide](https://docs.spring.io/spring-boot/docs/current/reference/html/)
- [API Javadoc](https://docs.spring.io/spring-boot/docs/current/api/)
- [Starters](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.build-systems.starters): spring-boot-starter-\*, a set of convenient dependency descriptors that can be included in the application. 
- [AutoConfig Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/application-properties.html#appendix.application-properties):
Core,Cache,Mail,JSON,Data,Transaction,Data,Integration,Web,Templating,Server,Security,RSocket,Actuator,Devtools and Testing.
- [Auto-configuration Classes](https://docs.spring.io/spring-boot/docs/current/reference/html/auto-configuration-classes.html#appendix.auto-configuration-classes)
- [Test Auto Configuration Annotations](https://docs.spring.io/spring-boot/docs/current/reference/html/test-auto-configuration.html#appendix.test-auto-configuration):
@DataCassandraTest,@DataCouchbaseTest,@DataElasticsearchTest,@DataJdbcTest,@DataJpaTest,@DataLdapTest,@DataMongoTest,@DataNeo4jTest,@DataR2dbcTest,@DataRedisTest,@GraphQlTest,@JdbcTest,@JooqTest,@JsonTest,@RestClientTest,@WebFluxTest,@WebMvcTest,@WebServiceClientTest,@WebServiceServerTest
- [Dependency Versions](https://docs.spring.io/spring-boot/docs/current/reference/html/dependency-versions.html#appendix.dependency-versions)

## Tutorial


## Developing
- Install Build systems: Maven/Gradle
- Install the Spring Boot CLI(*spring-boot-cli*), use the command: **spring grab|help|jar|run|test|version**
- Create pom.xml:
```xml
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.7.3</version>
    </parent>

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
    </dependencies>
```
- Application.java
```java
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;

import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;

@RestController
@EnableAutoConfiguration
//disable AutoConfiguration using exclude or excludeName 
//@SpringBootApplication(exclude = { DataSourceAutoConfiguration.class })
public class MyApplication {
    @RequestMapping("/")
    String home() {  return "Hello World!"; }
    public static void main(String[] args) {
        SpringApplication.run(MyApplication.class, args);
    }
}
```
**@EnableAutoConfiguration** tells Spring Boot to guess how to configure Spring based on the jar dependencies added. 
**@SpringBootApplication** does more than @EnableAutoConfiguration does, it is a combination: and **@SpringBootConfiguration**(enable registration of extra beans in the context or the import of additional configuration classes) from **@Configuration**(for Java-based configuration on Spring framework), **@ComponentScan**(enable component scanning of components like @Controller in current and sub-packages), and **@EnableAutoConfgiuration**(allow for auto-configuration in Spring Boot application).

- Run the application
```shell
    $ mvn spring-boot:run
    $ export MAVEN_OPTS=-Xmx1024m
```
or
```shell
    $ gradle bootRun
    $ export JAVA_OPTS=-Xmx1024m
```
or
```shell
    $ spring run
```
- Creating an Executable Jar
```xml
    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>
```
```shell
    $ mvn package
    $ java -jar target/myproject-0.0.1-SNAPSHOT.jar
```
Open a web browser to localhost:8080

- Configuration Classes (@Depends)
     - **@Configuration**: build beans for the application. The class defining the main method is a good candidate as the primary @Configuration.
     - **@Import**: import additional configuration classes.
     - **@ImportResource**: load XML configuration files 
     - **@ComponentScan**: automatically pick up all Spring components, including @Configuration classes. All the application components (@Component, @Service, @Repository, @Controller, and others) are automatically registered as Spring Beans.
     - **@EnableAutoConfiguration/@SpringBootApplication**:attempts to automatically configure the Spring application based on the jar dependencies

- Add Developer Tools, can be configured by *spring-boot-devtools.properties/yaml/yml*.
```xml
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-devtools</artifactId>
        <optional>true</optional>
    </dependency>
```

     - Cache: can improve performance, the [cache options](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.property-defaults) are configured by settings in *application.properties* file.
     - [Automatic Restart](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.restart):Triggered by the updating of the classpath, can be disabled, and set/exclude the trigger files/resources. 
     - [Live Reload](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.livereload)
     - [Remote Application](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.remote-applications)
    
## [Boot](https://docs.spring.io/spring-boot/docs/current/reference/html/features.html)

    Spring Application: SpringApplication

    External Configuration: External Configuration

    Profiles: Profiles

    Logging: Logging

## [Web](https://docs.spring.io/spring-boot/docs/current/reference/html/web.html)


    Servlet Web Applications: Spring MVC, Jersey, Embedded Servlet Containers

    Reactive Web Applications: Spring Webflux, Embedded Servlet Containers

    Graceful Shutdown: Graceful Shutdown

    Spring Security: Default Security Configuration, Auto-configuration for OAuth2, SAML

    Spring Session: Auto-configuration for Spring Session

    Spring HATEOAS: Auto-configuration for Spring HATEOAS


## [Data](https://docs.spring.io/spring-boot/docs/current/reference/html/data.html)


    SQL: Configuring a SQL Datastore, Embedded Database support, Connection pools, and more.

    NOSQL: Auto-configuration for NOSQL stores such as Redis, MongoDB, Neo4j, and others.


## [Messaging](https://docs.spring.io/spring-boot/docs/current/reference/html/messaging.html)


    JMS: Auto-configuration for ActiveMQ and Artemis, Sending and Receiving messages through JMS

    AMQP: Auto-configuration for RabbitMQ

    Kafka: Auto-configuration for Spring Kafka

    RSocket: Auto-configuration for Spring Framework’s RSocket Support

    Spring Integration: Auto-configuration for Spring Integration


## [IO](https://docs.spring.io/spring-boot/docs/current/reference/html/io.html)


    Caching: Caching support EhCache, Hazelcast, Infinispan and more

    Quartz: Quartz Scheduling

    Mail: Sending Email

    Validation: JSR-303 Validation

    REST Clients: Calling REST Services with RestTemplate and WebClient

    Webservices: Auto-configuration for Spring Web Services

    JTA: Distributed Transactions with JTA


## [Container Images](https://docs.spring.io/spring-boot/docs/current/reference/html/container-images.html)

## Misc
### [Production-ready Features](https://docs.spring.io/spring-boot/docs/current/reference/html/actuator.html)

### [Deploying Spring Boot Applications](https://docs.spring.io/spring-boot/docs/current/reference/html/deployment.html)

### [Spring Boot CLI](https://docs.spring.io/spring-boot/docs/current/reference/html/cli.html)

### [Build Tool Plugins](https://docs.spring.io/spring-boot/docs/current/reference/html/build-tool-plugins.html)

### [How-to Guides](https://docs.spring.io/spring-boot/docs/current/reference/html/howto.html)




## [Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/configuration-metadata.html#appendix.configuration-metadata) sample
```java
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.boot.context.properties.DeprecatedConfigurationProperty;

@ConfigurationProperties("my.app")
public class MyProperties {
    private String name;
    public String getName() {
        return this.name;
    }
    public void setName(String name) {
        this.name = name;
    }
    @Deprecated
    @DeprecatedConfigurationProperty(replacement = "my.app.name")
    public String getTarget() {
        return this.name;
    }
    @Deprecated
    public void setTarget(String target) {
        this.name = target;
    }
}
```
## Auto Configuration
