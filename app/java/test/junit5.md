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

## Annotations
all core annotations are located in the org.junit.jupiter.api package in the junit-jupiter-api module.

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


