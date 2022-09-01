# Spring Boot Test
## Spring Core Features
- [Guide to Test a Spring Boot App](https://howtodoinjava.com/spring-boot2/testing/spring-boot-2-junit-5/)
- [EasyMock](https://www.baeldung.com/easymock)
- [mockit](https://javadoc.io/doc/org.mockito/mockito-core/latest/org/mockito/Mockito.html)
    - **mock()/@Mock**: create mock; and **when()/given()** to specify how a mock should behave via Answer/MockSettings
    - **spy()/@Spy**: partial mocking, real methods are invoked but still can be verified and stubbed
    - **@InjectMocks**: automatically inject mocks/spies fields annotated with @Spy or @Mock
    - **verify()**: to check methods were called with given arguments, or any expression via the **any()**
    - **@Captor**: capture what arguments were called

## Lombok Setup
- Download lombok from https://projectlombok.org/
- Run the command: java -jar lombok
- Verify the installation: Eclipse > Help > About
- In java class: use log to log the message by adding:
```
import lombok.extern.slf4j.Slf4j;
@Slf4j
```

### [Test](https://docs.spring.io/spring-boot/docs/current/reference/html/features.html#features.testing)
Two modules:    
- spring-boot-test: contains core items
- spring-boot-test-autoconfigure: supports auto-configuration for tests    
    
The **spring-boot-starter-test** Starter imports both Spring Boot test modules as well as JUnit Jupiter, AssertJ, Hamcrest, and a number of other useful libraries:
- JUnit 5: The de-facto standard for unit testing Java applications.
- Spring Test & Spring Boot Test: Utilities and integration test support for Spring Boot applications.
- AssertJ: A fluent assertion library.
- Hamcrest: A library of matcher objects (also known as constraints or predicates).
- Mockito: A Java mocking framework.
- JSONassert: An assertion library for JSON.
- JsonPath: XPath for JSON.
    
To support JUnit4, add a dependency on **junit-vintage-engine** (hamcrest-core is excluded in favor of org.hamcrest:hamcrest):
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

## [Test Web Application](https://spring.io/guides/gs/testing-web/)
- Simple sanity check test that will fail if the application context cannot start.
```
import static org.assertj.core.api.Assertions.assertThat;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
public class SmokeTest {
	@Autowired
	private HomeController controller;

	@Test
	public void contextLoads() throws Exception {
		assertThat(controller).isNotNull();
	}
}
```
The application context is cached between tests, can use @DirtiesContext to control the cache.

- Start the application to listen for a connection, then send an HTTP request and assert the response
```
import static org.assertj.core.api.Assertions.assertThat;
import org.junit.jupiter.api.Test;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.context.SpringBootTest.WebEnvironment;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.boot.web.server.LocalServerPort;

@SpringBootTest(webEnvironment = WebEnvironment.RANDOM_PORT)
public class HttpRequestTest {
	@LocalServerPort
	private int port;
	@Autowired
	private TestRestTemplate restTemplate; //Spring Boot provides a TestRestTemplate

	@Test
	public void greetingShouldReturnDefaultMessage() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/",
				String.class)).contains("Hello, World");
	}
}
```
- Start full Sprimg application context without the server, and test only the web layer 
```
import org.junit.jupiter.api.Test;

import static org.hamcrest.Matchers.containsString;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;
import static org.springframework.test.web.servlet.result.MockMvcResultHandlers.*; //print,content,status;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.web.servlet.MockMvc;

@SpringBootTest
@AutoConfigureMockMvc
public class TestingWebApplicationTest {
	@Autowired
	private MockMvc mockMvc;

	@Test
	public void shouldReturnDefaultMessage() throws Exception {
		this.mockMvc.perform(get("/")).andDo(print()).andExpect(status().isOk())
				.andExpect(content().string(containsString("Hello, World")));
	}
}
```
- Instantiates only the web layer rather than the whole context using @WebMvcTest
```
import static org.hamcrest.Matchers.containsString;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;
import static org.springframework.test.web.servlet.result.MockMvcResultHandlers.print;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.content;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

import org.junit.jupiter.api.Test;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.test.web.servlet.MockMvc;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@WebMvcTest   #@WebMvcTest(HomeController.class) for specific Controller
public class WebLayerTest {
	@Autowired
	private MockMvc mockMvc;

	@Test
	public void shouldReturnDefaultMessage() throws Exception {
		log.info("TestingWebApplicationTest with MockMvc for webLayer only");
		this.mockMvc.perform(get("/")).andDo(print()).andExpect(status().isOk())
				.andExpect(content().string(containsString("Hello, World")));
	}
}
```
- Automatically injects the service dependency into the controller: use **@MockBean** to create and inject a mock for the GreetingService. 
```
import org.junit.jupiter.api.Test;

import static org.hamcrest.Matchers.containsString;
import static org.mockito.Mockito.when;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;
import static org.springframework.test.web.servlet.result.MockMvcResultHandlers.*; //print,content,status;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.test.web.servlet.MockMvc;

@WebMvcTest(GreetingController.class)
public class WebMockTest {
	@Autowired
	private MockMvc mockMvc;
	@MockBean
	private GreetingService service;
	@Test
	public void greetingShouldReturnMessageFromService() throws Exception {
		when(service.greet()).thenReturn("Hello, Mock");
		this.mockMvc.perform(get("/greeting")).andDo(print()).andExpect(status().isOk())
				.andExpect(content().string(containsString("Hello, Mock")));
	}
}
```

## Test 
-  Unit Testing the REST Controller: @WebMvcTest and mock the service layer
```
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.jsonPath;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;
 
import java.util.Arrays;
import java.util.List;
 
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.test.context.junit.jupiter.SpringExtension;
import org.springframework.test.web.servlet.MockMvc;
 
import com.howtodoinjava.employees.model.Employee;
import com.howtodoinjava.employees.services.EmployeeService;
 
@ExtendWith(SpringExtension.class)
@WebMvcTest(EmployeeController.class)
public class StandaloneControllerTests {
  @MockBean  EmployeeService employeeService;
  @Autowired  MockMvc mockMvc;
  @Test  public void testfindAll() throws Exception {
    Employee employee = new Employee("Lokesh", "Gupta");
    List<Employee> employees = Arrays.asList(employee);
    Mockito.when(employeeService.findAll()).thenReturn(employees);
    mockMvc.perform(get("/employee"))
        .andExpect(status().isOk())
        .andExpect(jsonPath("$", Matchers.hasSize(1)))
        .andExpect(jsonPath("$[0].firstName", Matchers.is("Lokesh")));
  }
}

```
- Unit Testing the Service Layer: mock the DAO layer, and  @InjectMocks the Service layer.
```

```
-  Unit testing DAO / Repository Layer:

### Annotaions
- **@TestSubject**: object to be tested from junit
- **@Mock**:creates mock in mockit/easymock
- **@InjectMocks**: creates actual objects and injects mocked dependencies into it.
- **@Autowired**: auto get Bean from Spring application context
- **@MockBean**: create and add mock objects to the Spring application context.  
- **@DataJpaTest**: disables full auto-configuration except for JPA tests. @Autowired the repository.

## Mock
- @TestSubject: an actual instance of a class and any method invoked using object reference will execute the method body defined in the class file.
- @Mock: a proxy interface to hide an underlying dependency with cannot be tested in a test environment e.g. database, network locations etc. A method invoked using mocked reference does not execute the actual method body defined in the class file, rather the method behavior is configured using when(...).thenReturn(...) methods.
    - In a junit test, we create objects for the class which need to be tested and its methods to be invoked.
    - Create mocks for the dependencies which will not be present in the test environment and objects are dependent on it to complete the method call.
    
### @Mock, @InjectMocks and @MockBean
- @Mock, @InjectMocks: plain mockito annotations 
- @MockBean: spring wrappers for mockito, create mock object and insert into context.

In mockito-based junit tests, @Mock annotation creates mocks and @InjectMocks creates actual objects and injects mocked dependencies into it.
- Use @InjectMocks to create class instances that need to be tested in the test class. 
- Use @InjectMocks when actual method body needs to be executed for a given class.
- Use @InjectMocks when need all or few internal dependencies initialized with mock objects to work method correctly.
- Use @Mock to create mocks that are needed to support the testing of SUT.
- Must define the when(...).thenReturn(...) methods for mock objects whose class methods will be invoked during actual test execution.
    
#### Auto Configuration
Auto-configuration can be associated to a starter that provides the auto-configuration code as well as the typical libraries that you would use with it.

- Understanding Auto-configured Beans

Auto-configuration is implemented with the @AutoConfiguration annotation, it is meta-annotated with @Configuration, making auto-configurations standard @Configuration classes. Additional @Conditional annotations are used to constrain when the auto-configuration should apply. Usually, auto-configuration classes use @ConditionalOnClass and @ConditionalOnMissingBean annotations. This ensures that auto-configuration applies only when relevant classes are found and when you have not declared your own @Configuration.



