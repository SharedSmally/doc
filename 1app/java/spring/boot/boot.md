# Spring Boot

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
    $ java -jar target/myproject-0.0.1-SNAPSHOT.jar --debug   #  enable debug
```
Open a web browser to localhost:8080

- Configuration Classes (@Depends)
     - **@Configuration**: build beans for the application. The class defining the main method is a good candidate as the primary @Configuration.
     - **@Import**: import additional configuration classes.
     - **@ImportResource**: load XML configuration files 
     - **@ComponentScan**: automatically pick up all Spring components, including @Configuration classes. All the application components (@Component, @Service, @Repository, @Controller, and others) are automatically registered as Spring Beans.
     - **@EnableAutoConfiguration/@SpringBootApplication**:attempts to automatically configure the Spring application based on the jar dependencies

- Add Developer Tools, can be configured by *spring-boot-devtools.properties/yaml/yml*.
     - Cache: can improve performance, the [cache options](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.property-defaults) are configured by settings in *application.properties* file.
     - [Automatic Restart](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.restart):Triggered by the updating of the classpath, can be disabled, and set/exclude the trigger files/resources. 
     - [Live Reload](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.livereload)
     - [Remote Application](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.devtools.remote-applications)
```xml
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-devtools</artifactId>
        <optional>true</optional>
    </dependency>
```



## Misc
### [Production-ready Features](https://docs.spring.io/spring-boot/docs/current/reference/html/actuator.html)

### [Deploying Spring Boot Applications](https://docs.spring.io/spring-boot/docs/current/reference/html/deployment.html)

### [Spring Boot CLI](https://docs.spring.io/spring-boot/docs/current/reference/html/cli.html)

### [Build Tool Plugins](https://docs.spring.io/spring-boot/docs/current/reference/html/build-tool-plugins.html)

### [How-to Guides](https://docs.spring.io/spring-boot/docs/current/reference/html/howto.html)

