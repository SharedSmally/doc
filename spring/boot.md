# [Spring Boot](https://projects.spring.io/spring-boot/)
- 1.5.7: Spring Framework 4.0/Java 8/Servlet
- [2.0.0](https://docs.spring.io/spring-boot/docs/2.0.0.M7/reference/htmlsingle/): Spring Framework 5.0/Java 9/Reactive  

## Create pom.xml from [Initializer/Starter](https://start.spring.io/)
- Core: Security; Cache; Session; Validation; (JPA); Ops
- Web: REST;
- Web Template: Thymeleaf
- SQL: JPA + PostgreSQL(MySQL; H2; ....)
- NoSQL: (Reactive); Redis; Mongo; ...
- IO: Batch; Integration, LDAP;  ...
- Cloud 
    - Config: Config Client/Server(git/svn); Vault; Zookeeper
    - Service Discovery: 
    - Routing:
    - Circuit Breaker
    - Tracing: 
    - Messaging
    - Contract
    - AWS
    - Azure
    - Foundary
    
## Java Sample
```
import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.*;
import org.springframework.web.bind.annotation.*;

@RestController
@EnableAutoConfiguration
public class Example {
	@RequestMapping("/")
	String home() {
		return "Hello World!";
	}

	public static void main(String[] args) throws Exception {
		SpringApplication.run(Example.class, args);
	}
}

//////////////////////////////////////////////////////////////////////////////////
// Main Applicatin in a root package; EnableAutoConfiguration is in main App class
//@ComponentScan automatically pick up all Spring components, including @Configuration classes
package com.example.myapplication;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

@Configuration
@EnableAutoConfiguration
@ComponentScan
public class Application {
	public static void main(String[] args) {
		SpringApplication.run(Application.class, args);
	}
}

//@Component
//   @Repository/@Entity: for data
//   @Service: for service
//   @Controller/@RestController: for web
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication // same as @Configuration @EnableAutoConfiguration @ComponentScan
public class Application {
	public static void main(String[] args) {
		SpringApplication.run(Application.class, args);
	}
}
////////////////////////////////////////////////////////
package com.example.service;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class DatabaseAccountService implements AccountService {
	private final RiskAssessor riskAssessor;
	@Autowired
	public DatabaseAccountService(RiskAssessor riskAssessor) {
		this.riskAssessor = riskAssessor;
	}
	// ...
}
```
## Create Application
Run the App:
```
$ mvn spring-boot:run
```
Add build plugin to create executable Jar
```
<!-- Inherit defaults from Spring Boot -->
<parent>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-starter-parent</artifactId>
	<version>2.0.0.M7</version>
</parent>

<build>
	<plugins>
		<plugin>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-maven-plugin</artifactId>
		</plugin>
	</plugins>
</build>
```
Create an Executable Jar:
```
$ mvn package
$ java -jar target/myproject-0.0.1-SNAPSHOT.jar
```
