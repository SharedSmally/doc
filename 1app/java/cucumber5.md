# Cucumber + JUnit5 + Spring Boot
- [creating Cucumber based BDD tests using JUnit5 and Spring Dependency Injection](https://palashray.com/example-of-creating-cucumber-based-bdd-tests-using-junit5-and-spring-dependency-injection/)

## Install Lombok in Eclipse/STS
- Download lombok.jar from the official site: https://projectlombok.org/
- Run the command: java -jar lombok.jar
- Check with Help > About to make sure lombok is installed

## Dependencies
- Cucumber pom
- JUnit pom
- [github](https://github.com/paawak/spring-boot-demo/tree/master/cucumber/cucumber-with-junit5-spring)

## Components:
- Cucumber TestRunner: Entry Point
- TestContextConfig: Set the TestConfig(s) for the testing
- TestConfig: Define @Bean to be DI 
