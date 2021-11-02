# Java Test
- Junit: Provide Assert, Before, Test 
- Easy Mock: 
- Power Mock

## Junit
```
impoort org.junit.Assert;
impoort org.junit.Before;
impoort org.junit.Test;
```

## EasyMock
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
