# Spring-Cucumber-junit5
- [Tutorial](https://thepracticaldeveloper.com/cucumber-tests-spring-boot-dependency-injection/)
- Needs cucumber(cucumber-core,cucumber-java,cucumber-junit,junit4/5), cucumber-spring and spring
- Entry Point: Cucumber Test Runner
- ![Runner](https://thepracticaldeveloper.com/images/posts/uploads/2018/03/cucumber-spring-boot-1024.webp)
```
@RunWith(Cucumber.class)
@CucumberOptions(
    features = {"classpath:features"},  // feature files are defined in src/test/resources/features:copied to target/
    tags="not @ignore and @test",  // select cases with the tags to be tested
    glue={"com.cainet.test"},      // packages that implemented the tests attached with the feature files
    plugin={"pretty","junit:target/cucumber_junut.xml","html:target/cucumber"} // register plugins
) 
public class CucumberRunnerTest {
    // global variables
    @ClassRule
    public static TestRule rule = new Xxx();    
}
```
- CucumberSpringTest: 

Annotate a configuration class on glue path with @CucumberContextConfiguration and with one of the following annotations: @ContextConfiguration, @ContextHierarchy or @BootstrapWith. see [](https://github.com/cucumber/cucumber-jvm/tree/main/spring)
```
import io.cucumber.spring.CucumberContextConfiguration;
import org.springframework.boot.test.context.SpringBootTest;

@CucumberContextConfiguration
@SpringBootTest(classes = TestConfig.class)
public class CucumberSpringConfiguration {
}
```
    - @CucumberContextConfiguration: tells Cucumber to use this class as the test context configuration for Spring
    
- Sharing state between steps

Beans containing glue code (i.e. step definitions, hooks, ect) are bound to the cucumber-glue scope, which starts prior to a scenario and ends after a scenario. All beans in this scope will be created before a scenario execution and disposed at the end of it.

By using the @ScenarioScope annotation additional components can be added to the glue scope. These components can be used to safely share state between steps inside a scenario.
```
import org.springframework.stereotype.Component;
import io.cucumber.spring.ScenarioScope;

@Component
@ScenarioScope
public class TestUserInformation {
    private User testUser;
    public void setTestUser(User testUser) {
        this.testUser = testUser;
    }
    public User getTestUser() {
        return testUser;
    }
}
```
The glue scoped component can then be autowired into a step definition:

- Define Step Definition classes:
- 
The components can be injected into the Cucumber step definition clas

```
public class UserStepDefinitions {
   @Autowired
   private UserService userService;
   @Autowired
   private TestUserInformation testUserInformation;

   @Given("there is a user")
   public void there_is_as_user() {
      User testUser = userService.createUser();
      testUserInformation.setTestUser(testUser);
   }
}

public class PurchaseStepDefinitions {
   @Autowired
   private PurchaseService purchaseService;

   @Autowired
   private TestUserInformation testUserInformation;

   @When("the user makes a purchase")
   public void the_user_makes_a_purchase(){
      Order order = ....
      User user = testUserInformation.getTestUser();
      purchaseService.purchase(user, order);
   }
}
```
- SpringBootConfiguration
```
@SpringBootConfiguration()  // Spring Config classes with @Config and @Bean
@PropertySource("classpath:application.properties")
public ckass TestSpringConfig {
   @Bean 
   public BeanTemplate testBeanTemplate() {
      ......
   }
}
```

src/test/resources/cucumber.properties
```
cucumber.publish.enabled=false
cucumber.publish.quite=true
```

## Hamcrest Matchers
- [Home](http://hamcrest.org/JavaHamcrest/index)
- [Tutorial](http://hamcrest.org/JavaHamcrest/tutorial)
- [API](http://hamcrest.org/JavaHamcrest/javadoc/2.2/)
```
import org.junit.jupiter.api.Test;
import static org.hamcrest.MatcherAssert.assertThat; 
import static org.hamcrest.Matchers.*;

public class BiscuitTest {
  @Test 
  public void testEquals() { 
    Biscuit theBiscuit = new Biscuit("Ginger"); 
    Biscuit myBiscuit = new Biscuit("Ginger"); 
    assertThat(theBiscuit, equalTo(myBiscuit)); 
  } 
} 
```
MatcherAssert class:
```
static void assertThat(java.lang.String reason, boolean assertion)          
static <T> void	assertThat(T actual, Matcher<? super T> matcher)
static <T> void assertThat(java.lang.String reason, T actual, Matcher<? super T> matcher)
```
Interface Matcher<T>
```
 void 	describeMismatch(java.lang.Object item, Description mismatchDescription)
 boolean 	matches(java.lang.Object item)
```

- Core
    
    - anything - always matches, useful if you don’t care what the object under test is
    - describedAs - decorator to adding custom failure description
    - is - decorator to improve readability - see “Sugar”, below
    
- Logical
    
    - allOf - matches if all matchers match, short circuits (like Java &&)
    - anyOf - matches if any matchers match, short circuits (like Java ||)
    - not - matches if the wrapped matcher doesn’t match and vice versa
    
- Object
    
    - equalTo - test object equality using Object.equals
    - hasToString - test Object.toString
    - instanceOf, isCompatibleType - test type
    - notNullValue, nullValue - test for null
    - sameInstance - test object identity
    
- Beans
    
    - hasProperty - test JavaBeans properties
    
- Collections
    
    - array - test an array’s elements against an array of matchers
    - hasEntry, hasKey, hasValue - test a map contains an entry, key or value
    - hasItem, hasItems - test a collection contains elements
    - hasItemInArray - test an array contains an element
    
- Number
    
    - closeTo - test floating point values are close to a given value
    - greaterThan, greaterThanOrEqualTo, lessThan, lessThanOrEqualTo - test ordering
    
- Text
    
    - equalToIgnoringCase - test string equality ignoring case
    - equalToIgnoringWhiteSpace - test string equality ignoring differences in runs of whitespace
    - containsString, endsWith, startsWith - test string matching
    
## [WireMock](http://wiremock.org/)
WireMock is a simulator for HTTP-based APIs (Http Server), consider as a service virtualization or a mock server.

- [Docs](http://wiremock.org/docs/)    
- [API](https://javadoc.io/doc/com.github.tomakehurst/wiremock-jre8/latest/index.html)    
- [OpenAPI](http://wiremock.org/docs/api/)    
- [Stubbing](http://wiremock.org/docs/stubbing/): stubFor/givenThat
- [Verifying](http://wiremock.org/docs/verifying/): verify(
- Using WireMockServer or WireMock(static methods)    
```
import static com.github.tomakehurst.wiremock.client.WireMock.*;    
```
- [Configuration](http://wiremock.org/docs/configuration/)    
    
## EasyMock

## PowerMock:
On EasyMock/Mockit to provide more features

## [TestContainer](https://www.testcontainers.org/): Mock of container
- [Features]()
- [API](https://javadoc.io/doc/org.testcontainers/testcontainers/latest/index.html)
     - [GenericContainer](https://javadoc.io/doc/org.testcontainers/testcontainers/latest/org/testcontainers/containers/GenericContainer.html)
- PostgresContainer
```
import java.util.Arrays;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.testcontainers.containers.GenericContainer;
import org.testcontainers.containers.Network;
import org.testcontainers.containers.wait.strategt.Wait;

public class PostgresContainer extends GenericContainer {
   private static final String IMAGE_NAME="postgres:latest";
   private static final String ALIAS="postgres";
   private static final Interger PORT=Integer.valueof(5432);
   
   private static final Logger logger=LoggerFactory.getLogger(PostgresContainer.class);
   
   public PostgresContainer(Network network) {
       super(IMAGE_NAME);
       withNetwork(network);
       withNetworkAliases(ALIAS);
       withExposedPorts(PORT);
       waitingFor(Wait.forListeningPort());
       //withLogConsumernew ContainerConsumer(ALIAS)); withLogConsumer(new Slf4jLogConsumer(log));
       setPortBindings(Arrays.asList(PORT+":"+PORT));
   }
   @Override
   public void start() {
      try {
          super.start();
          loadDataSchema();
      } catch (Exception ex) {
          logger.debug(ex);
          throw ex;
      }
   }

   private void loadDataSchema() throw Exception {
       execInContainer("psql", "-f", "classpath:meta/ddl/ddl.sql");
       execInContainer("psql", "-f", "classpath:meta/ddl/provision.sql");
   }
}
```


## ServerMock: Mock of Network server 
