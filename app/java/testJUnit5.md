# JUnit 5

## JUnit5 Annotations
| Annotation | Description |
|------------|-------------|
| @Test| Denotes that a method is a test method. Unlike JUnit 4’s @Test annotation, this annotation does not declare any attributes, since test extensions in JUnit Jupiter operate based on their own dedicated annotations. Such methods are inherited unless they are overridden.| 
| @ParameterizedTest| Denotes that a method is a parameterized test. Such methods are inherited unless they are overridden.| 
| @RepeatedTest| Denotes that a method is a test template for a repeated test. Such methods are inherited unless they are overridden.| 
| @TestFactory| Denotes that a method is a test factory for dynamic tests. Such methods are inherited unless they are overridden.| 
| @TestTemplate| Denotes that a method is a template for test cases designed to be invoked multiple times depending on the number of invocation contexts returned by the registered providers. Such methods are inherited unless they are overridden.| 
| @TestClassOrder| Used to configure the test class execution order for @Nested test classes in the annotated test class. Such annotations are inherited.| 
| @TestMethodOrder| Used to configure the test method execution order for the annotated test class; similar to JUnit 4’s @FixMethodOrder. Such annotations are inherited.| 
| @TestInstance| Used to configure the test instance lifecycle for the annotated test class. Such annotations are inherited.| 
| @DisplayName| Declares a custom display name for the test class or test method. Such annotations are not inherited.| 
| @DisplayNameGeneration| Declares a custom display name generator for the test class. Such annotations are inherited.| 
| @BeforeEach| Denotes that the annotated method should be executed before each @Test, @RepeatedTest, @ParameterizedTest, or @TestFactory method in the current class; analogous to JUnit 4’s @Before. Such methods are inherited – unless they are overridden or superseded (i.e., replaced based on signature only, irrespective of Java’s visibility rules).| 
| @AfterEach| Denotes that the annotated method should be executed after each @Test, @RepeatedTest, @ParameterizedTest, or @TestFactory method in the current class; analogous to JUnit 4’s @After. Such methods are inherited – unless they are overridden or superseded (i.e., replaced based on signature only, irrespective of Java’s visibility rules).| 
| @BeforeAll| Denotes that the annotated method should be executed before all @Test, @RepeatedTest, @ParameterizedTest, and @TestFactory methods in the current class; analogous to JUnit 4’s @BeforeClass. Such methods are inherited – unless they are hidden, overridden, or superseded, (i.e., replaced based on signature only, irrespective of Java’s visibility rules) – and must be static unless the "per-class" test instance lifecycle is used.| 
| @AfterAll| Denotes that the annotated method should be executed after all @Test, @RepeatedTest, @ParameterizedTest, and @TestFactory methods in the current class; analogous to JUnit 4’s @AfterClass. Such methods are inherited – unless they are hidden, overridden, or superseded, (i.e., replaced based on signature only, irrespective of Java’s visibility rules) – and must be static unless the "per-class" test instance lifecycle is used.| 
| @Nested| Denotes that the annotated class is a non-static nested test class. On Java 8 through Java 15, @BeforeAll and @AfterAll methods cannot be used directly in a @Nested test class unless the "per-class" test instance lifecycle is used. Beginning with Java 16, @BeforeAll and @AfterAll methods can be declared as static in a @Nested test class with either test instance lifecycle mode. Such annotations are not inherited.| 
| @Tag| Used to declare tags for filtering tests, either at the class or method level; analogous to test groups in TestNG or Categories in JUnit 4. Such annotations are inherited at the class level but not at the method level.| 
| @Disabled| Used to disable a test class or test method; analogous to JUnit 4’s @Ignore. Such annotations are not inherited.| 
| @Timeout| Used to fail a test, test factory, test template, or lifecycle method if its execution exceeds a given duration. Such annotations are inherited.| 
| @ExtendWith| Used to register extensions declaratively. Such annotations are inherited.| 
| @RegisterExtension| Used to register extensions programmatically via fields. Such fields are inherited unless they are shadowed.| 
| @TempDir| Used to supply a temporary directory via field injection or parameter injection in a lifecycle method or test method; located in the org.junit.jupiter.api.io package.| 

## Assertions
-  assertEquals() and assertNotEquals()
```
public static void assertEquals(int expected, int actual)
public static void assertEquals(int expected, int actual, String message)
public static void assertEquals(int expected, int actual, Supplier<String< messageSupplier)

public static void assertNotEquals(Object expected, Object actual)
public static void assertNotEquals(Object expected, Object actual, String message)
public static void assertNotEquals(Object expected, Object actual, Supplier<String> messageSupplier)
```
```
void test() {
    //Test will pass
    Assertions.assertEquals(4, Calculator.add(2, 2));
     
    //Test will fail 
    Assertions.assertEquals(3, Calculator.add(2, 2), "Calculator.add(2, 2) test failed");
     
    //Test will fail 
    Supplier<String> messageSupplier  = () -> "Calculator.add(2, 2) test failed";
    Assertions.assertEquals(3, Calculator.add(2, 2), messageSupplier);
}

void test()
{
	//Test will pass
	Assertions.assertNotEquals(3, Calculator.add(2, 2));

	//Test will fail
	Assertions.assertNotEquals(4, Calculator.add(2, 2), "Calculator.add(2, 2) test failed");

	//Test will fail
	Supplier<String> messageSupplier  = () -> "Calculator.add(2, 2) test failed";
	Assertions.assertNotEquals(4, Calculator.add(2, 2), messageSupplier);
}
```
- assertArrayEquals()
```
public static void assertArrayEquals(int[] expected, int[] actual)
public static void assertArrayEquals(int[] expected, int[] actual, String message)
public static void assertArrayEquals(int[] expected, int[] actual, Supplier<String> messageSupplier)
```


## @Tag for testsuites
- Apply the @Tag annotation on a test class or test method or both.
```
@Tag("development")
public class ClassATest
{
    @Test
    @Tag("userManagement")
    void testCaseA(TestInfo testInfo) {
    }
    
    @Test
    @Tag("development")
    @Tag("production")
    void testCaseA(TestInfo testInfo) {
    }
}
```
- Create Suite by filtering or including tests.
```
import org.junit.platform.runner.JUnitPlatform;
import org.junit.platform.suite.api.SelectPackages;
import org.junit.runner.RunWith;

//@IncludeTags example
@Suite
@SelectPackages("com.howtodoinjava.junit5.examples")
@IncludeTags("production")
public class MultipleTagsExample
{
}

//@ExcludeTags example
@Suite
@SelectPackages("com.howtodoinjava.junit5.examples")
@ExcludeTags("production")
public class MultipleTagsExample
{
}

// add more than one tag
@Suite
@SelectPackages("com.howtodoinjava.junit5.examples")
@IncludeTags({"production","development"})
public class MultipleTagsExample
{
}
```

## JUnit 5 vs JUnit 4
| Feature | 	JUnit 4 | Junit 5 |
|---------|-----------|---------|
|Supported JVM|<Java 5 | > Java 8 |
| Declare a test method | @Test | @Test |
| Execute before all test methods in the current class | @BeforeClass | @BeforeAll | 
| Execute after all test methods in the current class | @AfterClass | @AfterAll | 
| Execute before each test method | @Before | @BeforeEach | 
| Execute after each test method | @After | @AfterEach | 
| Disable a test method/class | @Ignore | @Disabled | 
| Test factory for dynamic tests | NA | @TestFactory | 
| Nested tests | NA | @Nested | 
| Tagging and filtering | @Category | @Tag | 
| Register custom extensions | NA | @ExtendWith | 
