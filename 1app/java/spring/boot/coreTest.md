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
- spring-boot-test-autoconfigure: supports auto-configuration for tests with @...Test
    
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
## Test Environment
### @SpringBootTest
Normal Spring Test uses spring-test/@ContextConfiguration to test the application, and @SpringBootTest for Spring boot application,  creating the ApplicationContext in the tests through SpringApplication, and Spring Boot features.
 @SpringBootTest webEnvironment attribute:
- MOCK(Default) : Loads a web ApplicationContext and provides a mock web environment, Embedded servers are not started, can be used with @AutoConfigureMockMvc or @AutoConfigureWebTestClient for mock-based testing
- RANDOM_PORT: Loads a WebServerApplicationContext and provides a real web environment. Embedded servers are started and listen on a random port.
- DEFINED_PORT: Loads a WebServerApplicationContext and provides a real web environment. Embedded servers are started and listen on a defined port via application.properties
- NONE: Loads an ApplicationContext by using SpringApplication but does not provide any web environment (mock or otherwise).
    
### Test Configuration
- @ContextConfiguration(classes=...): specify the Configuration to load. Alternatively, can used nested @Configuration classes within the test.
- @TestConfiguration: in addition to the application’s primary configuration
- @Import: including more configurations, such as configs in src/test/java, which are not scanned default.
- @WebMvcTest: focus only on the web layer and not start a complete ApplicationContext
- @SpringBootTest: By default, @SpringBootTest does not start the server. 
- @...Test: load only the parts of the configuration that are required to test a slice of the application. The auto-configuration classes can be excluded  by #excludeAutoConfiguration attribute, or @ImportAutoConfiguration#exclude.     
- @MockBean/@SpyBean: Wrapper of @Mock and @Spy to mock the Beans to be inserted into ApplicationContext
Use MocMvc to test with a mock environment:
```
@SpringBootTest
@AutoConfigureMockMvc
public class MockMvcExampleTests {
	@Autowired
	private MockMvc mvc;
	// @Autowired private TestRestTemplate restTemplate;
```
or WebClient for reactive Web:
```
@SpringBootTest
@AutoConfigureWebTestClient
public class MockWebTestClientExampleTests {
	@Autowired
	private WebTestClient webClient;
```
In RANDOM_PORT and DEFINED_PORT, the test application can autowire MockMvc/WebTestClient and TestRestTemplate.

If needs JMX:
```
@SpringBootTest(properties = "spring.jmx.enabled=true")
@DirtiesContext
public class SampleJmxTests {
	@Autowired
	private MBeanServer mBeanServer;
```

## Auto-configured tests((@...Test) and [AutoWired Beans](https://docs.spring.io/spring-boot/docs/2.0.4.RELEASE/reference/html/test-auto-configuration.html)
- **@JsonTest/@AutoConfigureJsonTesters**: for json
    - Jackson: Jackson **ObjectMapper**, any **@JsonComponent** beans, **JacksonTester**
    - Gson: **Gson**, **GsonTester**
    - Jsonb: **Jsonb**, **JsonbTester**
    - String: **BasicJsonTester** 
- **@WebMvcTest**: for sepcific Controller with autowire **MockMvc** (available in @SpringBootTest + @AutoConfigureMockMvc).
    Scanned beans to **@Controller, @ControllerAdvice, @JsonComponent, Converter, GenericConverter, Filter, WebMvcConfigurer**, and **HandlerMethodArgumentResolver**, not scan @Component. 
    If use HtmlUnit or Selenium, auto-configuration provides an HTMLUnit **WebClient** and/or a **WebDriver** bean
- **@WebFluxTest**: for Reactive Controller with autowire **WebTestClient**
- **@DataJpaTest**: for Data JPA with autowire **TestEntityManager/@AutoConfigureTestEntityManager,JdbcTemplate**, @Entity classes and JPA repositories,
- **@JdbcTest**: for JDBC Tests with autowire **JdbcTemplate**, No scan on @Component
- **@JooqTest**: for jOOQ Tests with autowire **DSLContext**,No scan on @Component
- **@DataMongoTest**: for Data MongoDB Tests with autowire **MongoTemplate** and @Document classes and Mongo repositories
- **@DataNeo4jTest**: for Data Neo4j Tests with autowire **@NodeEntity** classes and Neo4j repositories
- **@DataRedisTest**: for  Data Redis Tests with autowire **@RedisHash** classes and Redis repositories 
- **@DataLdapTest**: for Data LDAP Tests with autowire **LdapTemplate**, @Entry classes, and LDAP repositories.
- **@RestClientTest**: for REST Clients with autowire JSON,**RestTemplateBuilder,MockRestServiceServer**
- **@AutoConfigureRestDocs**: for Spring REST Docs Tests with **@WebMvcTest** and **RequestSpecification**


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



