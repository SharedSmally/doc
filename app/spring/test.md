# Spring Test
- [Doc](https://docs.spring.io/spring-framework/docs/current/reference/html/testing.html)

## Java Test
- Unit Test: junit4/5 + mockit/easymock + powermock + hamcrest-matcher + [WireMock/MockServer for Http(s) server]
- Integration Test: [cucumber](https://cucumber.io/docs/cucumber/)
```
Feature: Some terse yet descriptive text of what is desired
     Textual description of the business value of this feature
     Business rules that govern the scope of the feature
     Any additional information that will make the feature easier to understand

Background:
    Given some precondition needed for all scenarios in this file
        And another precondition

Scenario: Some determinable business situation
  Textual description of the business value of this scenario
  Business rules that govern the scope of the scenario
  Any additional information that will make the scenario easier to understand
    Given some precondition
      And some other precondition
    When some action by the actor
      And some other action
      And yet another action
    Then some testable outcome is achieved
      And something else we can check happens too
      But something else we can check does not happen

Scenario Outline: Some determinable business situation
    Given I am <precondition>
        And some other precondition
    When some action by the actor
    Then I have <outcome> rights

Examples:
    | precondition | outcome  |
    | username1    | customer |
    | username2    | admin    |
```

## Basic Unit Test
### @SpringRunner: for Spring unit-test in JUnit4
```
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.TestPropertySource;
import org.springframework.test.context.junit4.SpringRunner;

import static org.hamcrest.CoreMatchers.equalTo;
import static org.junit.Assert.assertThat;

@RunWith(SpringRunner.class)
@ContextConfiguration(classes={HelloService.class})
@TestPropertySource("/appTest.properties")
public class HelloServiceTest {
    @Value("${app.message}")
    private String message;

    @Autowired
    private HelloService helloService;

    @Test
    public void testHelloMessage() {
        var message = helloService.sayHello();
        assertThat(message, equalTo(message));
    }
}
```
### @SpringJUnitConfig: for Spring unit-test in JUnit5
```
@ExtendWith(SpringExtension.class)  // JUnit5
@ContextConfiguration(classes={TestConfig.class})  //For ApplicationContext, the @Configuration or @Component
//@SpringJUnitConfig(TestConfig.class) = @ExtendWith + @ContextConfiguration
public class TodoServiceTest {
    @Autowired  // Bean from TestConfig class
    private TodoService todoService;
    
    @Test
    // ...    
}
```
 A Spring ApplicationContext will be created using TestConfig as the primary configuration. It then gets the 
 TodoService instance from the container and injects it into the test class. Spring application needs to 
 create ApplicationContext using 1 primary configuration.
 
If the configuration class is not specified, Spring will look for configuration embedded in the test class:
```
@SpringJUnitConfig
public class TodoServiceTest {
    @Configuration
    static class TestConfig {
        @Bean
        public TodoService todoService() {
            // ...
        }
    }
    // ...
}
```
ApplicationContext is instantiated only once and shared among all the test methods in the class.

Using @TestPropertySource to pass in custom properties for testing:
```
@SpringJUnitConfig(TestConfig.class)
@TestPropertySource(properties={"username=foo", "password=bar"},
    locations="classpath:todo-test.properties")
public class TodoServiceTests {
    // ...
}
```

## Testing with Spring Boot

Spring Boot introduces new annotations, such as:
- @SpringBootTest
- @WebMvcTest
- @DataJpaTest, @DataJdbcTest, @JdbcTest
- @MockBean

### @SpringBootTest for Integration Test

Unlike @SpringJUnitConfig, @SpringBootTest, by default, starts the whole application context the same as 
when run the Spring Boot application. Spring then searchs for a class with @SpringBootConfiguration and 
use it as the primary configuration to create ApplicationContext. It also does the auto-configuration 
for TestRestTemplate which can be wired into the test class and use to call APIs.
```
@SpringBootApplication // includes meta annotation @SpringBootConfiguration
public class SpringtestingApplication {
    // ...
}

@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT, classes = {XxxRepository.class, XxxService.class})
public class TodoControllerTest {
    @Autowired
    TestRestTemplate restTemplate;
    // ...
}
```
### @WebMvcTest: Unit test for controller layer

Tests with @WebMvcTest will apply only configuration relevant to MVC tests. The full configuration will be disabled. 
Spring Test Framework also auto-configures MockMvc which can be injected into the test class and use to call tested APIs:
```
@WebMvcTest(TodoController.class)
public class TodoControllerTest {
    @Autowired
    private MockMvc mockMvc;

    @MockBean
    private TodoService todoService;
    
    @Test
	public void getCarShouldReturnCarDetails() {
    	given(this.carService.schedulePickup(new Date(), new Route());)
        	.willReturn(new Date());
    	this.mvc.perform(get("/schedulePickup")
        	.accept(MediaType.JSON)
        	.andExpect(status().isOk());
	}
}
```

### @DataJpaTest: 
only loads @Repository spring components, not loading @Service, @Controller, etc.
```
@RunWith(SpringRunner.class)
@DataJpaTest
public class MapTests {
	@Autowired
	private MapRepository repository;

	@Test
	public void findByUsernameShouldReturnUser() {
    	final String expected = "NJ";
    	String actual = repository.findByZip("07677")
    	assertThat(expected).isEqualTo(actual);
	}
}

```
