# [EasyMock](https://easymock.org/)
- [Start up](https://easymock.org/getting-started.html)
- [User Guide](https://easymock.org/user-guide.html)
- [API document](https://easymock.org/api/)

Sample:
```
<dependency>
  <groupId>org.easymock</groupId>
  <artifactId>easymock</artifactId>
  <version>4.3</version>
  <scope>test</scope>
</dependency>

public interface Collaborator {
    void documentAdded(String title);
}

public class ClassTested {
  private Collaborator listener;
  public void setListener(Collaborator listener) {
    this.listener = listener;
  }

  public void addDocument(String title, String document) {
    listener.documentAdded(title);
  }
}

import static org.easymock.EasyMock.*;
import org.easymock.*;
import org.junit.*;

public class ExampleTest extends EasyMockSupport {
    @Rule
    public EasyMockRule rule = new EasyMockRule(this);

    @Mock
    private Collaborator collaborator; // 1. create a mock

    @TestSubject
    private ClassTested classUnderTest = new ClassTested(); // 2. create class to be tested

    @Test
    public void addDocument() {
        collaborator.documentAdded("New Document"); // 3. Record what we expect the mock to do
        replayAll(); // 4.Tell all mocks now doing the actual testing
        classUnderTest.addDocument("New Document", "content"); // 5. Test
        verifyAll(); // 6. Make sure everything that was supposed to be called was called
    }
}
```
- Extending (or delegating to) EasyMockSupport is useful but not mandatory. It allows to call replayAll instead of replay(mock1, mock2, ...) for instance
- Mock injection is done on fields (by EasyMockRule) so no need a setter only used for testing
- testing that documentAdded is called only once and receiving this exact parameter. Any other call to our mock is a test failure

## Annotation Types
- Mock: 
    - String 	fieldName
    - String 	name 
    - MockType 	type : NICE/STRICT
    - MockType 	value 
- Preview
- TestSubject: set on a field so EasyMockRunner, EasyMockRule or EasyMockSupport.injectMocks(Object) will inject mocks created with Mock on its fields.

## Classes
- Capture: contain what was captured by the capture() matcher
    - T 	getValue()
    - List<T> 	getValues()
    - boolean	hasCaptured() 
    - void Reset()
    - void setValue(T value)
    - static <T> Capture<T> 	newInstance()
    - static <T> Capture<T> 	newInstance(CaptureType type)
- ConstructorArgs
    - Constructor<?> 	getConstructor() 
    - Object[] 	getInitArgs() 
- EasyMock: All static methods
    - X and/or(X1, X2); X or(X1, X2);
    - X anyX()
    - X[] aryEq(X[])
    - static <T> T 	capture(Capture<T> captured)
    - static void 	checkOrder(Object mock, boolean state)
    - cmp
    - static IMocksControl 	createControl()
    - static <T> T 	createMock(MockType type, Class<?> toMock)
    - static <T> T 	mock(Class<?> toMock)
    - T eq(T)/eq(T1,T2); T gt(T); T lt(T);  T not(T)
    - static <T extends Comparable<T>> T 	geq(T value)
    - static <T extends Comparable<T>> T 	leq(T value)
    - static <T> IExpectationSetters<T> expect(T value) 
    - static <T> IExpectationSetters<T> 	expectLastCall()
    - static void 	replay(Object... mocks)
    - static void 	reset(Object... mocks)
    - static void 	verify(Object... mocks)
    - static void 	verifyRecording(Object... mocks)
    - static void 	verifyUnexpectedCalls(Object... mocks)
- IExpectationSetters<T>
    - IExpectationSetters<T> 	anyTimes()/	atLeastOnce()/once()/times(int count)/times(int min, int max)
    - IExpectationSetters<T> 	andThrow(Throwable throwable)/andVoid()/andReturn(T value)/andDelegateTo(Object delegateTo)/andAnswer(IAnswer<? extends T> answer)    
    - void 	asStub()/andStubThrow(Throwable throwable)/andStubVoid()/andStubReturn(T value)/andStubDelegateTo(Object delegateTo)/andStubAnswer(IAnswer<? extends T> answer)
- EasyMockExtension
- EasyMockListener
- EasyMockRule
- EasyMockRunner
- EasyMockSupport
    - IMocksControl create(Nice|Strict)Control
    - <T,R> R create(Nice|Strict)Mock: Same as @Mock
    - <T,R> R (nice|strict)Mock
    - replayAll()
    - void resetAll[To(Default|Nice|Strict)]()
    -	verifyAll()/verifyAllRecordings()/verifyAllUnexpectedCalls()
    - <T> IMockBuilder<T> 	(partial)MockBuilder(Class<T> toMock)
```
 public class SupportTest extends EasyMockSupport {
     @Test
     public void test() {
         firstMock = createMock(A.class);
         secondMock = createMock(B.class);

         replayAll(); // put both mocks in replay mode
         // ... use mocks ..
         verifyAll(); // verify both mocks
     }
 }
```

```
import org.easymock.EasyMock;
import org.easymock.EasyMockRunner;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(EasyMockRunner.class)
public class MathApplicationTester {
   private MathApplication mathApplication;
   private CalculatorService calcService;
   
   @Before
   public void setUp(){
      mathApplication = new MathApplication();
      calcService = EasyMock.createMock(CalculatorService.class);
      mathApplication.setCalculatorService(calcService);
   }
   @Test
   public void testAddAndSubtract(){
      //add the behavior to add numbers
      EasyMock.expect(calcService.add(20.0,10.0)).andReturn(30.0);
      
      //subtract the behavior to subtract numbers
      EasyMock.expect(calcService.subtract(20.0,10.0)).andReturn(10.0);
      
      //activate the mock
      EasyMock.replay(calcService);	
	
      //test the subtract functionality
      Assert.assertEquals(mathApplication.subtract(20.0, 10.0),10.0,0);
      
      //test the add functionality
      Assert.assertEquals(mathApplication.add(20.0, 10.0),30.0,0);
      
      //verify call to calcService is made or not
      EasyMock.verify(calcService);
   }
}
```
