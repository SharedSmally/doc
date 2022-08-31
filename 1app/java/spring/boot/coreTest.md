# Spring Boot
## Spring Core Features
- [Guide to Test a Spring Boot App](https://howtodoinjava.com/spring-boot2/testing/spring-boot-2-junit-5/)
- [EasyMock](https://www.baeldung.com/easymock)

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
- **@DataJpaTest**: disables full auto-configuration except for JPA tests. @Autowired the repository.
- **@Mock**:creates mock in mockit/easymock
- **@TestSubject**: object to be tested
- **@Autowired**: auto get Bean from Spring application context
- **@InjectMocks**: creates actual objects and injects mocked dependencies into it.
- **@MockBean** to add mock objects to the Spring application context.  


#### Auto Configuration
Auto-configuration can be associated to a starter that provides the auto-configuration code as well as the typical libraries that you would use with it.

- Understanding Auto-configured Beans

Auto-configuration is implemented with the @AutoConfiguration annotation, it is meta-annotated with @Configuration, making auto-configurations standard @Configuration classes. Additional @Conditional annotations are used to constrain when the auto-configuration should apply. Usually, auto-configuration classes use @ConditionalOnClass and @ConditionalOnMissingBean annotations. This ensures that auto-configuration applies only when relevant classes are found and when you have not declared your own @Configuration.



