# [JUnit5](https://junit.org/junit5)
- [User Guide](https://junit.org/junit5/docs/current/user-guide/)
- [API doc](https://junit.org/junit5/docs/current/api/)

## Modules: JUnit 5 = JUnit Platform + JUnit Jupiter + JUnit Vintage
- **Jupiter**: the combination of the new programming model and extension model for writing tests and extensions in JUnit 5. The Jupiter sub-project provides a TestEngine for running Jupiter based tests on the platform. 
    - **org.junit.jupiter**: Aggregates all JUnit Jupiter modules.
    - **org.junit.jupiter.api**: Defines JUnit Jupiter API for writing tests.
    - **org.junit.jupiter.engine**: Provides the JUnit Jupiter TestEngine implementation.
    - **org.junit.jupiter.migrationsupport**: Support for migrating from JUnit 4 to JUnit Jupiter.
    - **org.junit.jupiter.params**: JUnit Jupiter extension for parameterized tests.
  
- **Platform**: serves as a foundation for launching testing frameworks on the JVM. 
It also defines the TestEngine API for developing a testing framework that runs on the platform. 
It also provides a Console Launcher to launch the platform from the command line and a JUnit 4 
based Runner for running any TestEngine on the platform in a JUnit 4 based environment. 
    - **org.junit.platform.commons**: Common APIs and support utilities for the JUnit Platform.
    - **org.junit.platform.console**: Support for launching the JUnit Platform from the console.
    - **org.junit.platform.engine**: Public API for test engines.
    - **org.junit.platform.jfr**: Provides Java Flight Recorder events for the JUnit Platform.
    - **org.junit.platform.launcher**: Public API for configuring and launching test plans.
    - **org.junit.platform.reporting**: Defines the JUnit Platform Reporting API.
    - **org.junit.platform.runner**: Runner and annotations to configure and execute tests on the JUnit Platform in a JUnit 4 environment.
    - **org.junit.platform.suite**: Aggregates all JUnit Platform Suite modules.
    - **org.junit.platform.suite.api**: Annotations for configuring a test suite on the JUnit Platform.
    - **org.junit.platform.suite.commons**: Common support utilities for declarative test suite executors.
    - **org.junit.platform.suite.engine**: Provides a TestEngine for running declarative test suites.
    - **org.junit.platform.testkit**: Defines the Test Kit API for the JUnit Platform.

- **Vintage**: provides a TestEngine for running JUnit 3 and JUnit 4 based tests on the platform. It requires JUnit 4.12 or later to be present on the class/module path 
    - **org.junit.vintage.engine**: Provides a TestEngine for running JUnit 3 and 4 based tests on the platform.
## mvn dependencies
```
<dependencies>
    <dependency>
        <groupId>org.junit.platform</groupId>
        <artifactId>junit-platform-launcher</artifactId>
        <scope>test</scope>
    </dependency>
    <dependency>
        <groupId>org.junit.jupiter</groupId>
        <artifactId>junit-jupiter-engine</artifactId>
        <scope>test</scope>
    </dependency>
    <dependency>
        <groupId>org.junit.vintage</groupId>
        <artifactId>junit-vintage-engine</artifactId>
        <scope>test</scope>
    </dependency>
</dependencies>
<dependencyManagement>
    <dependencies>
        <dependency>
            <groupId>org.junit</groupId>
            <artifactId>junit-bom</artifactId>
            <version>5.8.1</version>
            <type>pom</type>
            <scope>import</scope>
        </dependency>
    </dependencies>
</dependencyManagement>
```
In order to have Maven Surefire or Maven Failsafe run any tests at all, at least one TestEngine implementation must be added to the test classpath.
```
<dependencies>
    <!-- ... -->
    <dependency>
        <groupId>org.junit.jupiter</groupId>
        <artifactId>junit-jupiter</artifactId>
        <version>5.8.1</version>
        <scope>test</scope>
    </dependency>
    <!-- to support JUnit 4 based tests, junit and vintage are needed -->
    <dependency>
        <groupId>junit</groupId>
        <artifactId>junit</artifactId>
        <version>4.13.2</version>
        <scope>test</scope>
    </dependency>
    <dependency>
        <groupId>org.junit.vintage</groupId>
        <artifactId>junit-vintage-engine</artifactId>
        <version>5.8.1</version>
        <scope>test</scope>
    </dependency>
    
</dependencies>
<build>
    <plugins>
        <plugin>
            <artifactId>maven-surefire-plugin</artifactId>
            <version>2.22.2</version>
        </plugin>
        <plugin>
            <artifactId>maven-failsafe-plugin</artifactId>
            <version>2.22.2</version>
        </plugin>
    </plugins>
</build>
```
## Sample
There are many [Assertions](https://junit.org/junit5/docs/current/api/org.junit.jupiter.api/org/junit/jupiter/api/Assertions.html): 
- assertAll
- assertArrayEquals; assertEquals/assertNotEquals; assertFalse/assertTrue; assertIterableEquals
- assertInstanceOf
- assertLinesMatch
- assertThrows/assertThrowsExactly/assertDoesNotThrow
- assertTimeout/assertTimeoutPreemptively
- assertNotNull/assertNull
- assertSame/assertNotSame
- fail
```
import example.util.Calculator;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

class MyFirstJUnitJupiterTests {
    private final Calculator calculator = new Calculator();

    @Test
    void addition() {
        assertEquals(2, calculator.add(1, 1));
    }
}
```

## Annotations
all core annotations are located in the org.junit.jupiter.api package in the [junit-jupiter-api](https://junit.org/junit5/docs/current/api/org.junit.jupiter.api/org/junit/jupiter/api/package-summary.html) module.

| Annotation |	Description |
|------------| -------------|
| @Test | Denotes that a method is a test method. Unlike JUnit 4’s @Test annotation, this annotation does not declare any attributes, since test extensions in JUnit Jupiter operate based on their own dedicated annotations. Such methods are inherited unless they are overridden. |
| @ParameterizedTest  |  Denotes that a method is a parameterized test. Such methods are inherited unless they are overridden. |
| @RepeatedTest | Denotes that a method is a test template for a repeated test. Such methods are inherited unless they are overridden. |
| @TestFactory | Denotes that a method is a test factory for dynamic tests. Such methods are inherited unless they are overridden. |
| @TestTemplate | Denotes that a method is a template for test cases designed to be invoked multiple times depending on the number of invocation contexts returned by the registered providers. Such methods are inherited unless they are overridden. | 
| @TestClassOrder | Used to configure the test class execution order for @Nested test classes in the annotated test class. Such annotations are inherited. |
| @TestMethodOrder | Used to configure the test method execution order for the annotated test class; similar to JUnit 4’s @FixMethodOrder. Such annotations are inherited. |
| @TestInstance | Used to configure the test instance lifecycle for the annotated test class. Such annotations are inherited. |
| @DisplayName | Declares a custom display name for the test class or test method. Such annotations are not inherited. |
| @DisplayNameGeneration | Declares a custom display name generator for the test class. Such annotations are inherited. |
| @BeforeEach | Denotes that the annotated method should be executed before each @Test, @RepeatedTest, @ParameterizedTest, or @TestFactory method in the current class; analogous to JUnit 4’s @Before. Such methods are inherited unless they are overridden. |
| @AfterEach | Denotes that the annotated method should be executed after each @Test, @RepeatedTest, @ParameterizedTest, or @TestFactory method in the current class; analogous to JUnit 4’s @After. Such methods are inherited unless they are overridden. |
| @BeforeAll | Denotes that the annotated method should be executed before all @Test, @RepeatedTest, @ParameterizedTest, and @TestFactory methods in the current class; analogous to JUnit 4’s @BeforeClass. Such methods are inherited (unless they are hidden or overridden) and must be static (unless the "per-class" test instance lifecycle is used). |
| @AfterAll | Denotes that the annotated method should be executed after all @Test, @RepeatedTest, @ParameterizedTest, and @TestFactory methods in the current class; analogous to JUnit 4’s @AfterClass. Such methods are inherited (unless they are hidden or overridden) and must be static (unless the "per-class" test instance lifecycle is used). |
| @Nested | Denotes that the annotated class is a non-static nested test class. @BeforeAll and @AfterAll methods cannot be used directly in a @Nested test class unless the "per-class" test instance lifecycle is used. Such annotations are not inherited. |
| @Tag | Used to declare tags for filtering tests, either at the class or method level; analogous to test groups in TestNG or Categories in JUnit 4. Such annotations are inherited at the class level but not at the method level. |
| @Disabled | Used to disable a test class or test method; analogous to JUnit 4’s @Ignore. Such annotations are not inherited. |
| @Timeout | Used to fail a test, test factory, test template, or lifecycle method if its execution exceeds a given duration. Such annotations are inherited. |
| @ExtendWith | Used to register extensions declaratively. Such annotations are inherited. |
| @RegisterExtension | Used to register extensions programmatically via fields. Such fields are inherited unless they are shadowed. |
| @TempDir | Used to supply a temporary directory via field injection or parameter injection in a lifecycle method or test method; located in the org.junit.jupiter.api.io package. |

## Test Classes and Methods
- Test Class: any top-level class, static member class, or @Nested class that contains at least one test method.
  Test classes must not be abstract and must have a single constructor.
- Test Method: any instance method that is directly annotated or meta-annotated with @Test, @RepeatedTest, @ParameterizedTest, @TestFactory, or @TestTemplate.
- Lifecycle Method: any method that is directly annotated or meta-annotated with @BeforeAll, @AfterAll, @BeforeEach, or @AfterEach.

Test methods and lifecycle methods may be declared locally within the current test class, inherited from superclasses, or inherited from interfaces (see Test Interfaces and Default Methods). In addition, test methods and lifecycle methods must not be abstract and must not return a value (except @TestFactory methods which are required to return a value).

A standard Test class:
```
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;

import static org.junit.jupiter.api.Assertions.fail;
import static org.junit.jupiter.api.Assumptions.assumeTrue;
import static org.junit.jupiter.api.Assertions.assertAll;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTimeout;
import static org.junit.jupiter.api.Assertions.assertTimeoutPreemptively;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertFalse;

@DisplayName("A special test case")
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

    @Test
    @DisplayName("Custom test name containing spaces")
    void testWithDisplayNameContainingSpaces() {
    }
    
    @DisplayName("A negative value for year is not supported by the leap year computation.")
    @ParameterizedTest(name = "For example, year {0} is not supported.")
    @ValueSource(ints = { -1, -4 })
    void if_it_is_negative(int year) {
    }

    @Nested
    @IndicativeSentencesGeneration(separator = " -> ", generator = DisplayNameGenerator.ReplaceUnderscores.class)
    class A_year_is_a_leap_year {
        @Test
        void if_it_is_divisible_by_4_but_not_by_100() {
        }

        @ParameterizedTest(name = "Year {0} is a leap year.")
        @ValueSource(ints = { 2016, 2020, 2048 })
        void if_it_is_one_of_the_following_years(int year) {
        }
    }

    @Test
    void groupedAssertions() {
        // In a grouped assertion all assertions are executed, and all
        // failures will be reported together.
        assertAll("person",
            () -> assertEquals("Jane", person.getFirstName()),
            () -> assertEquals("Doe", person.getLastName())
        );
    }

    @Test
    void timeoutNotExceededWithMethod() {
        // The following assertion invokes a method reference and returns an object.
        String actualGreeting = assertTimeout(ofMinutes(2), AssertionsDemo::greeting);
        assertEquals("Hello, World!", actualGreeting);
    }

    @Test
    void timeoutExceeded() {
        // The following assertion fails with an error message similar to:
        // execution exceeded timeout of 10 ms by 91 ms
        assertTimeout(ofMillis(10), () -> {
            // Simulate task that takes more than 10 ms.
            Thread.sleep(100);
        });
    }

    @Test
    void timeoutExceededWithPreemptiveTermination() {
        // The following assertion fails with an error message similar to:
        // execution timed out after 10 ms
        assertTimeoutPreemptively(ofMillis(10), () -> {
            // Simulate task that takes more than 10 ms.
            new CountDownLatch(1).await();
        });
    }
    
    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }
}
```

## Third-party Assertion Libraries
Can use of third-party assertion libraries such as AssertJ, Hamcrest, Truth:
```
import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;

import example.util.Calculator;

import org.junit.jupiter.api.Test;

class HamcrestAssertionsDemo {
    private final Calculator calculator = new Calculator();

    @Test
    void assertWithHamcrestMatcher() {
        assertThat(calculator.subtract(4, 1), is(equalTo(3)));
    }
}
```
## Conditional Test Execution
The ExecutionCondition extension API in JUnit Jupiter allows developers to either enable or disable a container or test based on certain conditions programmatically:
- Operating System Conditions: @EnabledOnOs/@DisabledOnOs:
```
@Test
@EnabledOnOs(MAC)
void onlyOnMacOs() {
    // ...
}

@TestOnMac
void testOnMac() {
    // ...
}

@Test
@EnabledOnOs({ LINUX, MAC })
void onLinuxOrMac() {
    // ...
}

@Test
@DisabledOnOs(WINDOWS)
void notOnWindows() {
    // ...
}
```
- Java Runtime Environment Conditions: @EnabledOnJre/@DisabledOnJre; @EnabledForJreRange/@DisabledForJreRange 
- System Property Conditions: @EnabledIfSystemProperty/@DisabledIfSystemProperty:
```
@Test
@EnabledIfSystemProperty(named = "os.arch", matches = ".*64.*")
void onlyOn64BitArchitectures() {
    // ...
}

@Test
@DisabledIfSystemProperty(named = "ci-server", matches = "true")
void notOnCiServer() {
    // ...
}
```
- Environment Variable Conditions: @EnabledIfEnvironmentVariable/@DisabledIfEnvironmentVariable :
```
@Test
@EnabledIfEnvironmentVariable(named = "ENV", matches = "staging-server")
void onlyOnStagingServer() {
    // ...
}

@Test
@DisabledIfEnvironmentVariable(named = "ENV", matches = ".*development.*")
void notOnDeveloperWorkstation() {
    // ...
}
```
- Custom Conditions: @EnabledIf/@DisabledIf
```
@Test
@EnabledIf("customCondition")
void enabled() {
    // ...
}

@Test
@DisabledIf("customCondition")
void disabled() {
    // ...
}

boolean customCondition() {
    return true;
}

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.EnabledIf;

class ExternalCustomConditionDemo {
    @Test
    @EnabledIf("example.ExternalCondition#customCondition")
    void enabled() {
        // ...
    }
}

class ExternalCondition {
    static boolean customCondition() {
        return true;
    }
}
```

## Tagging and Filtering
Test classes and methods can be tagged via the @Tag annotation. Those tags can later be used to filter test discovery and execution. 
```
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

@Tag("fast")
@Tag("model")
class TaggingDemo {
    @Test
    @Tag("taxes")
    void testingTaxCalculation() {
    }
}
```
##  Test Execution Order
- Method Order: @TestMethodOrder
```
import org.junit.jupiter.api.MethodOrderer.OrderAnnotation;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;

@TestMethodOrder(OrderAnnotation.class)
class OrderedTestsDemo {
    @Test
    @Order(1)
    void nullValues() {
        // perform assertions against null values
    }

    @Test
    @Order(2)
    void emptyValues() {
        // perform assertions against empty values
    }

    @Test
    @Order(3)
    void validValues() {
        // perform assertions against valid values
    }
}
```
-  Class Order: @TestClassOrder
```
import org.junit.jupiter.api.ClassOrderer;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestClassOrder;

@TestClassOrder(ClassOrderer.OrderAnnotation.class)
class OrderedNestedTestClassesDemo {
    @Nested
    @Order(1)
    class PrimaryTests {
        @Test
        void test1() {
        }
   }

    @Nested
    @Order(2)
    class SecondaryTests {
        @Test
        void test2() {
        }
    }
}
```
## Nested Tests
@Nested tests give the test writer more capabilities to express the relationship among several groups of tests. 

## Dependency Injection for Constructors and Methods
In all prior JUnit versions, test constructors or methods were not allowed to have parameters (at least not with the standard Runner implementations). As one of the major changes in JUnit Jupiter, both test constructors and methods are now permitted to have parameters. 

ParameterResolver defines the API for test extensions that wish to dynamically resolve parameters at runtime. If a test class constructor, a test method, or a lifecycle method (see Test Classes and Methods) accepts a parameter, the parameter must be resolved at runtime by a registered ParameterResolver.

There are currently three built-in resolvers that are registered automatically.
- TestInfoParameterResolver: if a constructor or method parameter is of type TestInfo, the TestInfoParameterResolver will supply an instance of TestInfo corresponding to the current container or test as the value for the parameter. 
- RepetitionInfoParameterResolver: if a method parameter in a @RepeatedTest, @BeforeEach, or @AfterEach method is of type RepetitionInfo, the RepetitionInfoParameterResolver will supply an instance of RepetitionInfo.
- TestReporterParameterResolver: if a constructor or method parameter is of type TestReporter, the TestReporterParameterResolver will supply an instance of TestReporter. 

## Test Interfaces and Default Methods

JUnit Jupiter allows @Test, @RepeatedTest, @ParameterizedTest, @TestFactory, @TestTemplate, @BeforeEach, and @AfterEach to be declared on interface default methods. @BeforeAll and @AfterAll can either be declared on static methods in a test interface or on interface default methods if the test interface or test class is annotated with @TestInstance(Lifecycle.PER_CLASS)
```
@TestInstance(Lifecycle.PER_CLASS)
interface TestLifecycleLogger {
    static final Logger logger = Logger.getLogger(TestLifecycleLogger.class.getName());

    @BeforeAll
    default void beforeAllTests() {
        logger.info("Before all tests");
    }

    @AfterAll
    default void afterAllTests() {
        logger.info("After all tests");
    }

    @BeforeEach
    default void beforeEachTest(TestInfo testInfo) {
        logger.info(() -> String.format("About to execute [%s]",testInfo.getDisplayName()));
    }

    @AfterEach
    default void afterEachTest(TestInfo testInfo) {
        logger.info(() -> String.format("Finished executing [%s]", testInfo.getDisplayName()));
    }
}
```

##  Repeated Tests
```
@RepeatedTest(10)
void repeatedTest() {
    // ...
}
```
The following placeholders are currently supported.
- {displayName}: display name of the @RepeatedTest method
- {currentRepetition}: the current repetition count
- {totalRepetitions}: the total number of repetitions

## Parameterized Tests
```
@ParameterizedTest
@ValueSource(strings = { "racecar", "radar", "able was I ere I saw elba" })
void palindromes(String candidate) {
    assertTrue(StringUtils.isPalindrome(candidate));
}
```
- @NullSource: provides a single null argument to the annotated @ParameterizedTest method.@NullSource cannot be used for a parameter that has a primitive type.
- @EmptySource: provides a single empty argument to the annotated @ParameterizedTest method for parameters of the following types: java.lang.String, java.util.List, java.util.Set, java.util.Map, primitive arrays (e.g., int[], char[][], etc.), object arrays (e.g.,String[], Integer[][], etc.).
- @NullAndEmptySource: a composed annotation that combines the functionality of @NullSource and @EmptySource.
- @EnumSource(ChronoUnit.class)
- @MethodSource("stringProvider")
- @CsvSource({XXX})
- @CsvFileSource(files = "src/test/resources/two-column.csv", numLinesToSkip = 1)
- @ArgumentsSource(MyArgumentsProvider.class)

## Test Templates
A @TestTemplate method is not a regular test case but rather a template for test cases. 

## Dynamic Tests
@TestFactory methods must not be private or static and may optionally declare parameters to be resolved by ParameterResolvers.

## Timeouts
The @Timeout annotation allows one to declare that a test, test factory, test template, or lifecycle method should fail if its execution time exceeds a given duration. 
```
class TimeoutDemo {
    @BeforeEach
    @Timeout(5)
    void setUp() {
        // fails if execution time exceeds 5 seconds
    }

    @Test
    @Timeout(value = 100, unit = TimeUnit.MILLISECONDS)
    void failsIfExecutionTimeExceeds100Milliseconds() {
        // fails if execution time exceeds 100 milliseconds
    }
}
```
