# Java Test (docker plugin)
## Unit Test: surefire plugin
- Test Framework:
    - Junit
    - TestNG: 
    -  Provide Assert, Before, Test.
See [difference](https://www.guru99.com/junit-vs-testng.html). TestNG is powerful than JUnit. 

- Mock
    - EasyMock/MockIt: mocking system 
    - PowerMock: Extra features on Mocking syste
    - WireMock: https://wiremock.org/
    - Server Mock: https://mock-server.com/
    - Container Mock: https://www.testcontainers.org

## Integration Test: failsafe plugin 
- Framework

      - Cucumber: https://cucumber.io/

## [TestNG](https://testng.org/doc/)
- [Document](https://testng.org/doc/documentation-main.html)
```
<!-- https://mvnrepository.com/artifact/org.powermock/powermock-module-testng:
     depends or powermock-core, testng -->
<dependency>
    <groupId>org.powermock</groupId>
    <artifactId>powermock-module-testng</artifactId>
    <version>2.0.9</version>
    <scope>test</scope>
</dependency>
```
```
public class Test1 {
  @Test(groups = { "functest", "checkintest" })
  public void testMethod1() {
  }
 
  @Test(groups = {"functest", "checkintest"} )
  public void testMethod2() {
  }
 
  @Test(groups = { "functest" })
  public void testMethod3() {
  }
}
```

## Junit
- [junit4](https://junit.org/junit4/)
- [junit5-Jupiter](https://junit.org/junit5/)
```
impoort org.junit.Assert;
impoort org.junit.Before;
impoort org.junit.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import example.util.Calculator;
import org.junit.jupiter.api.Test;

class MyFirstJUnitJupiterTests {
    private final Calculator calculator = new Calculator();

    @Test
    void addition() {
        assertEquals(2, calculator.add(1, 1));
    }
}
```

- Test Class: any top-level class, static member class, or @Nested class that contains at least one test method. Test classes must not be abstract and must have a single constructor.
- Test Method: any instance method that is directly annotated or meta-annotated with @Test, @RepeatedTest, @ParameterizedTest, @TestFactory, or @TestTemplate.
- Lifecycle Method: any method that is directly annotated or meta-annotated with @BeforeAll, @AfterAll, @BeforeEach, or @AfterEach.
- Test classes and test methods can declare custom display names via @DisplayName
```
import static org.junit.jupiter.api.Assertions.fail;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

class StandardTests {
    @BeforeAll
    static void initAll() {
    }

    @BeforeEach
    void init() {
    }

    @Test
    void succeedingTest() {
    }

    @Test
    void failingTest() {
        fail("a failing test");
    }

    @Test
    @Disabled("for demonstration purposes")
    void skippedTest() {
        // not executed
    }

    @Test
    void abortedTest() {
        assumeTrue("abc".contains("Z"));
        fail("test should have been aborted");
    }

    @AfterEach
    void tearDown() {
    }
    
    @AfterAll
    static void tearDownAll() {
    }
}
```

## [EasyMock](https://easymock.org/)
When generating a mock, we can simulate the target object, specify its behavior, and finally verify whether it's used as expected.

Working with EasyMock's mocks involves four steps, Each is relate to methods in org.easymock.EasyMock:
- creating a mock of the target class: mock(…): generates a mock of the target class, be it a concrete class or an interface. Once created, a mock is in “recording” mode, meaning that EasyMock will record any action the Mock Object takes, and replay them in the “replay” mode
- recording its expected behavior, including the action, result, exceptions, etc. With expect(…) to set expectations, including calls, results, and exceptions, for associated recording actions
- using mocks in tests: replay(…): switches a given mock to “replay” mode. Then, any action triggering previously recorded method calls will replay “recorded results”
- verifying if it's behaving as expected: verify(…): verifies that all expectations were met and that no unexpected call was performed on a mock


- strictMock(…) to check the order of method calls. 
- mock(…) and strictMock(…): any unexpected method calls would cause an AssertionError.
- niceMock(…): allow any method call for the mock

```
impoort org.easymock.EasyMock;
impoort org.easymock.EasyMockSupport;

public class MyServiceTest extends EasyMockSupport {
   private MyService service;
   
   /** Run before each test */
   @Before
   public void setup() {
       service = createMockBuilder(MyService.class).addMockMethod("testMethod").createMock();
   }
   
   /** test first method */
   @Test
   public void testIsRunning() {
      replayAll();
      Assert.assertFalse(service.isRunning(false));
      verifyAll();
   }
   
   /** test second method */
   @Test
   public void testIsComplete() {
      expect(service.testMethod(EasyMock.antObject())).andReturn(new Long(1));
      replayAll();
      Assert.assertFalse(service.isCompleted(false));
      verifyAll();
   }
}
```

### Mock With Annotation
A mock object returns a dummy data corresponding to some dummy input passed to it.
 
Run unit tests with EasyMockRunner to processes @Mock and @TestSubject annotations.
```
@RunWith(EasyMockRunner.class)
public class BaeldungReaderAnnotatedTest {
    @Mock
    ArticleReader mockArticleReader;

    @TestSubject
    TestObject obj = new TestObject();

    @Test
    public void whenReadNext_thenNextArticleRead() {
        expect(mockArticleReader.next()).andReturn(null);
        replay(mockArticleReader);
        testObject.readNext();
        verify(mockArticleReader);
    }
}
```
EasyMockSupport in EasyMock helps keep track of mocks, such that we can replay and verify them in a batch,
```
public class TestReaderMockSupportTest extends EasyMockSupport{
    @Test
    public void whenReadAndWriteSequencially_thenWorks(){
        expect(mockArticleReader.next()).andReturn(null)
          .times(2).andThrow(new NoSuchElementException());
        expect(mockArticleWriter.write("title", "content"))
          .andReturn("BAEL-201801");
        replayAll();

        // execute read and write operations consecutively
        verifyAll();
 
        assertEquals(NoSuchElementException.class, expectedException.getClass());
        assertEquals("BAEL-201801", articleId);
    }
}
```

## [Power Mock](https://powermock.github.io/)
PowerMock is an extension of Mocking frameworks like Mockito or EasyMock with more powerful capabilities. Mockito/EasyMock and PowerMock can be combined into the same unit test.

Normally Mockito is used for unit testing and PowerMock is used for extra features as testing static methods and constructor.

```
    //Creating a mock using the PowerMockito.mock
    //method for the EmployeeService class.
    EmployeeService mock =PowerMockito.mock(EmployeeService.class);
    
    //Next statement essentially says that when getProjectedEmployeeCount method
    //is called on the mocked EmployeeService instance, return 8.
    PowerMockito.when(mock.getEmployeeCount()).thenReturn(8);
    
 <dependencies>
  <!-- https://mvnrepository.com/artifact/org.easymock/easymock -->
  <dependency>
   <groupId>org.easymock</groupId>
   <artifactId>easymock</artifactId>
   <version>4.3</version>
  </dependency>

  <!-- https://mvnrepository.com/artifact/org.powermock/powermock-module-junit4 -->
  <dependency>
   <groupId>org.powermock</groupId>
   <artifactId>powermock-module-junit4</artifactId>
   <version>2.0.9</version>
  </dependency>

  <!-- https://mvnrepository.com/artifact/org.powermock/powermock-api-easymock -->
  <dependency>
   <groupId>org.powermock</groupId>
   <artifactId>powermock-api-easymock</artifactId>
   <version>2.0.9</version>
  </dependency>

 </dependencies>
```
