# [Spring Boot](https://spring.io/projects/spring-boot)
Auto Config for the basic services

## Spring Boot CLI
- Install sdkman
```
$ curl -s "https://get.sdkman.io" | bash
$ source "$HOME/.sdkman/bin/sdkman-init.sh"
$ sdk version
$ sdk help
$ sdk list
```
- Install Spring Boot CLI
```
$ sdk install springboot
$ spring version
$ sdk ls springboot
$ spring help
```
- Simple Spring Boot App

app.groovy
```
@RestController
class ThisWillActuallyRun {    
    @RequestMapping("/")    
    String home() {       
        "Hello World!"    
    }
}
```
Run application
```
$spring run app.groovy
```

## Application

Common Layout: Domain Xxx class, with Repository interface, Service(using Repository to access data) and Controller(Web page to use Service to access data). data-rest automatically provides CRUD REST Controllers for Repository. 
```
com
 +- example
     +- myapplication
         +- Application.java
         |
         +- customer
         |   +- Customer.java
         |   +- CustomerController.java
         |   +- CustomerService.java
         |   +- CustomerRepository.java
         |
         +- order
             +- Order.java
             +- OrderController.java
             +- OrderService.java
             +- OrderRepository.java
```
The Application.java file declares main method(the primary @Configuration), along with the basic @SpringBootApplication:
```
package com.example.myapplication;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class Application {
    public static void main(String[] args) {
        // Simple without config, use application.properties or application.yml in resource/
        SpringApplication.run(Application.class, args);
        // App with Config
        SpringApplication app = new SpringApplication(Application.class);
        app.setBannerMode(Banner.Mode.OFF);
        app.run(args);
        // build an ApplicationContext hierarchy
        new SpringApplicationBuilder()
        .sources(Parent.class)
        .child(Application.class)
        .bannerMode(Banner.Mode.OFF)
        .run(args);
    }
}
```
A single [@SpringBootApplication](https://docs.spring.io/spring-boot/docs/current/api/org/springframework/boot/autoconfigure/SpringBootApplication.html) annotation can be used to enable the following features:
- @EnableAutoConfiguration: enable Spring Boot’s auto-configuration mechanism
- @ComponentScan: enable @Component scan on the package where the application is located
- @ConfigurationPropertiesScan: enable @ConfigurationProperties scan on the package where the application is located 
- @Configuration: allow to register extra beans in the context or import additional configuration classes. The @Import annotation can be used to import additional configuration classes. The @ImportResource annotation can be used to load XML configuration files.

Start the application with the --debug switch can find out what auto-configuration is currently being applied, and why. can use the exclude attribute of @EnableAutoConfiguration to disable some specific auto-configuration classes.

When adding @ComponentScan without any arguments in Application class, all the application components (@Component, @Service, @Repository, @Controller etc.) are automatically registered as Spring Beans.
```
package com.example.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class DatabaseAccountService implements AccountService {
    private final RiskAssessor riskAssessor;   //provided in contrsuctor, and cannot be change later

    @Autowired   //Can be omitted if a bean has one constructor
    public DatabaseAccountService(RiskAssessor riskAssessor) {
        this.riskAssessor = riskAssessor;
    }
    // ...
}
```

## Application Configuration
You can use properties files, YAML files, environment variables, and command-line arguments to externalize configuration. Property values can be injected directly into beans by using the @Value annotation, accessed through Spring’s Environment abstraction, or be bound to structured objects through @ConfigurationProperties.

Spring Boot uses a very particular PropertySource order that is designed to allow sensible overriding of values. Properties are considered in the following order:
- Devtools global settings properties in the $HOME/.config/spring-boot folder when devtools is active.
- @TestPropertySource annotations on your tests.
- properties attribute on your tests. Available on @SpringBootTest and the test annotations for testing a particular slice of your application.
- Command line arguments.
- Properties from SPRING_APPLICATION_JSON (inline JSON embedded in an environment variable or system property).
- ServletConfig init parameters.
- ServletContext init parameters.
- JNDI attributes from java:comp/env.
- Java System properties (System.getProperties()).
- OS environment variables.
- A RandomValuePropertySource that has properties only in random.*.
- Profile-specific application properties outside of your packaged jar (application-{profile}.properties and YAML variants).
- Profile-specific application properties packaged inside your jar (application-{profile}.properties and YAML variants).
- Application properties outside of your packaged jar (application.properties and YAML variants).
- Application properties packaged inside your jar (application.properties and YAML variants).
- @PropertySource annotations on your @Configuration classes.
- Default properties (specified by setting SpringApplication.setDefaultProperties).

```
import org.springframework.stereotype.*;
import org.springframework.beans.factory.annotation.*;

@Component
public class MyBean {
    @Value("${name}")
    private String name;
    // ...
}
```
```
@ConfigurationProperties(prefix="my")
public class AcmeProperties {
    private List<String> servers = new ArrayList<String>();

    public List<String> getServers() {
        return this.servers;
    }
}

@Service
public class MyService {
    private final AcmeProperties properties;

    @Autowired
    public MyService(AcmeProperties properties) {
        this.properties = properties;
    }
    //...

    @PostConstruct
    public void openConnection() {
        Server server = new Server(this.properties.getRemoteAddress());
        // ...
    }
}
```

### Multi-profile YAML Documents
You can specify multiple profile-specific YAML documents in a single file by using a spring.profiles key to indicate when the document applies, as shown in the following example:
```
server:
    address: 192.168.1.100
---
spring:
    profiles: development
server:
    address: 127.0.0.1
---
spring:
    profiles: production & eu-central
server:
    address: 192.168.1.120
```

### Application Property Files
SpringApplication loads properties from application.properties files in the following locations and adds them to the Spring Environment:
- A /config subdirectory of the current directory
- The current directory
- A classpath /config package
- The classpath root

### [Boot Autoconfiguration]
- [Reference](https://docs.spring.io/spring-boot/docs/2.2.0.RELEASE/reference/html/appendix-auto-configuration-classes.html#auto-configuration-classes)
- [github](https://github.com/spring-projects/spring-boot/tree/master/spring-boot-project/spring-boot-actuator-autoconfigure/src/main/java/org/springframework/boot/actuate/autoconfigure)
    - spring-boot-autoconfigure
    - spring-boot-actuator-autoconfigure

### [Boot Application Properties](https://docs.spring.io/spring-boot/docs/2.2.0.RELEASE/reference/html/appendix-application-properties.html)
- Core properties
    - logging
    - spring.banner
    - spring.info
    - spring.jmx
    - spring.messages
    - spring.quartz
    - spring.task    
- Cache properties
    - spring.cache
- Mail properties
    - spring.mail
    - spring.sendgrid
- JSON properties
    - spring.gson
    - spring.jackson
- Data properties
    - spring.couchbase
    - spring.data.cassandra
    - spring.data.couchbase
    - spring.data.elasticsearch
    - spring.data.jpa/jdbc
    - spring.data.mongodb
    - spring.data.neo4j
    - spring.data.rest
    - spring.data.solr
    - spring.data.web
    - spring.datasource (dbcp2/hikari/tomcat)
    - spring.elasticsearch (jest/rest)
    - spring.h2
    - spring.influx
    - spring.jdbc
    - spring.jpa
    - spring.mongodb
    - spring.redis
- Transaction properties
    - spring.jta
    - spring.jta.atomikos
    - spring.jta.bitronix
- Data migration properties
    - spring.flyway
    - spring.liquibase
- Integration properties
    - spring.activemq
    - spring.artemis.embedded
    - spring.artemis
    - spring.batch
    - spring.jms
    - spring.kafka.admin
    - spring.kafka
    - spring.kafka.consumer
    - spring.kafka.jaas
    - spring.kafka.listener
    - spring.kafka.producer
    - spring.kafka.streams
    - spring.rabbitmq
    - spring.rabbitmq.listener
    - spring.rabbitmq.template
    - spring.webservices
- Web properties
    - spring.http
    - spring.jersey
    - spring.mvc
    - spring.resources
    - spring.servlet
- Templating properties
    - spring.freemarker
    - spring.groovy.template
    - spring.mustache
    - spring.thymeleaf
- Server properties
    - server
    - server.jetty
    - server.servlet
    - server.tomcat
    - server.undertow
- Security properties
    - spring.ldap
    - spring.security
    - spring.session    
- RSocket properties
    - spring.rsocket.server
- Actuator properties
    - management.endpoin
    - management.health
    - management.info
    - management.metrics
    - management.server
- Devtools properties
    - spring.devtools    
- Testing properties
    - spring.test


