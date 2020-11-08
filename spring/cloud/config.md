# Spring Cloud Config
- Config Server
- Config Client
    - Vault Configuration
    - Zookeeper Configuration
    - Consul Configuration
    - Netflex

## Config Server
Needs spring-cloud-config-server dependencies
- Stand up a Config Server
```
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.config.server.EnableConfigServer;

@EnableConfigServer
@SpringBootApplication
public class ConfigurationServiceApplication {
  public static void main(String[] args) {
    SpringApplication.run(ConfigurationServiceApplication.class, args);
  }
}
```
Need a Config Service to act as a sort of intermediary between Spring applications and a version-controlled repository of 
configuration files. Use Spring Cloud’s @EnableConfigServer to standup a config server that can communicate with other applications.

The Config Server needs to know which repository to manage: 
- start with a Git-based filesystem repository. 
- point the Config Server to a Github or GitLab repository
- Specify the Git repository path by spring.cloud.config.server.git.uri property in src/main/resources/application.properties:
```
server.port=8888
spring.cloud.config.server.git.uri=${HOME}/Desktop/config
```

On the file system, 
- Create a new directory and run git init in it. 
- Add a file called a-bootiful-client.properties to the Git repository. 
- Run git commit in it
- Connect to the Config Server with a Spring Boot application whose spring.application.name property identifies it as a-bootiful-client to the Config Server.
- Add a simple property and value (message = Hello world) to the newly created a-bootiful-client.properties file and then git commit the change.

The Config Server knows which set of configuration to send to a specific client.
It also sends all the values from any file named application.properties or application.yml in the Git repository. 
Property keys in more specifically named files (such as a-bootiful-client.properties) override those in application.properties or application.yml.


## Config Client
Needs the Config Client, Spring Boot Actuator, and Spring Web dependencies.

- In src/main/resources/application.properties:
```
management.endpoints.web.exposure.include=*
```

- In src/main/resources/bootstrap.properties to config Config Server:
```
spring.application.name=a-bootiful-client
spring.cloud.config.uri=http://localhost:8888

```

Spring sees the configuration property files, as it would any property file loaded from application.properties or application.yml or any other PropertySource
The client can access any value in the Config Server by using the traditional mechanisms (such as @ConfigurationProperties or @Value("${...}") or through the Environment abstraction). 

## Refresh Config
- Update a-bootiful-client.properties, then run git commands: git add; git commit -m "xxx"
- Refresh client application: 
```
curl localhost:8080/actuator/refresh -d {} -H "Content-Type: application/json"
```
- Show the updated config value:
```
http://localhost:8080/message
```
