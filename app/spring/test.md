# Spring Test
- [Doc](https://docs.spring.io/spring-framework/docs/current/reference/html/testing.html)
- [Sample]()


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
//
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

@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
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
    // ...
}
```

