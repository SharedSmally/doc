# Spring Boot
Auto Configuration based on Dependencies

## Reference
- [Site](https://spring.io/projects/spring-boot/)
- [Quick Start](https://spring.io/quickstart)
- [User Guide](https://docs.spring.io/spring-boot/docs/current/reference/html/)
- [API Javadoc](https://docs.spring.io/spring-boot/docs/current/api/)
- [Starters]()
- [AutoConfig Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/application-properties.html#appendix.application-properties):
Core,Cache,Mail,JSON,Data,Transaction,Data,Integration,Web,Templating,Server,Security,RSocket,Actuator,Devtools and Testing.
- [Auto-configuration Classes](https://docs.spring.io/spring-boot/docs/current/reference/html/auto-configuration-classes.html#appendix.auto-configuration-classes)
- [Test Auto Configuration Annotations](https://docs.spring.io/spring-boot/docs/current/reference/html/test-auto-configuration.html#appendix.test-auto-configuration):
@DataCassandraTest,@DataCouchbaseTest,@DataElasticsearchTest,@DataJdbcTest,@DataJpaTest,@DataLdapTest,@DataMongoTest,@DataNeo4jTest,@DataR2dbcTest,@DataRedisTest,@GraphQlTest,@JdbcTest,@JooqTest,@JsonTest,@RestClientTest,@WebFluxTest,@WebMvcTest,@WebServiceClientTest,@WebServiceServerTest
- [Dependency Versions](https://docs.spring.io/spring-boot/docs/current/reference/html/dependency-versions.html#appendix.dependency-versions)

## Tutorial


## Develop Tool
- Install Build systems: Maven/Gradle
- Install the Spring Boot CLI, use the command: **spring**
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
    @RestController
    @EnableAutoConfiguration
    public class MyApplication {
        @RequestMapping("/")
        String home() {  return "Hello World!"; }
        public static void main(String[] args) {
            SpringApplication.run(MyApplication.class, args);
        }
    }
```
@EnableAutoConfiguration tells Spring Boot to guess how to configure Spring based on the jar dependencies added. 

- Run the application
```shell
    $ mvn spring-boot:run
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


    Best practices: Code Structure | @Configuration | @EnableAutoConfiguration | Beans and Dependency Injection

    Running your code: IDE | Packaged | Maven | Gradle

    Packaging your app: Production jars

    Spring Boot CLI: Using the CLI
    
## Boot

    Spring Application: SpringApplication

    External Configuration: External Configuration

    Profiles: Profiles

    Logging: Logging

## Web


    Servlet Web Applications: Spring MVC, Jersey, Embedded Servlet Containers

    Reactive Web Applications: Spring Webflux, Embedded Servlet Containers

    Graceful Shutdown: Graceful Shutdown

    Spring Security: Default Security Configuration, Auto-configuration for OAuth2, SAML

    Spring Session: Auto-configuration for Spring Session

    Spring HATEOAS: Auto-configuration for Spring HATEOAS


## Data


    SQL: Configuring a SQL Datastore, Embedded Database support, Connection pools, and more.

    NOSQL: Auto-configuration for NOSQL stores such as Redis, MongoDB, Neo4j, and others.


## Messaging


    JMS: Auto-configuration for ActiveMQ and Artemis, Sending and Receiving messages through JMS

    AMQP: Auto-configuration for RabbitMQ

    Kafka: Auto-configuration for Spring Kafka

    RSocket: Auto-configuration for Spring Framework’s RSocket Support

    Spring Integration: Auto-configuration for Spring Integration


## IO


    Caching: Caching support EhCache, Hazelcast, Infinispan and more

    Quartz: Quartz Scheduling

    Mail: Sending Email

    Validation: JSR-303 Validation

    REST Clients: Calling REST Services with RestTemplate and WebClient

    Webservices: Auto-configuration for Spring Web Services

    JTA: Distributed Transactions with JTA


## Container Images

## Misc


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
