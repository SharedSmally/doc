# [JUnit5](https://junit.org/junit5)
- [User Guide](https://junit.org/junit5/docs/current/user-guide/)
- [API doc](https://junit.org/junit5/docs/current/api/)

## Modules
- *Jupiter*: the combination of the new programming model and extension model for writing tests and extensions in JUnit 5. The Jupiter sub-project provides a TestEngine for running Jupiter based tests on the platform. 
    - org.junit.jupiter: Aggregates all JUnit Jupiter modules.
    - org.junit.jupiter.api: Defines JUnit Jupiter API for writing tests.
    - org.junit.jupiter.engine: Provides the JUnit Jupiter TestEngine implementation.
    - org.junit.jupiter.migrationsupport: Support for migrating from JUnit 4 to JUnit Jupiter.
    - org.junit.jupiter.params: JUnit Jupiter extension for parameterized tests.
  
- *Platform*: serves as a foundation for launching testing frameworks on the JVM. 
It also defines the TestEngine API for developing a testing framework that runs on the platform. 
It also provides a Console Launcher to launch the platform from the command line and a JUnit 4 
based Runner for running any TestEngine on the platform in a JUnit 4 based environment. 
    - org.junit.platform.commons: Common APIs and support utilities for the JUnit Platform.
    - org.junit.platform.console: Support for launching the JUnit Platform from the console.
    - org.junit.platform.engine: Public API for test engines.
    - org.junit.platform.jfr: Provides Java Flight Recorder events for the JUnit Platform.
    - org.junit.platform.launcher: Public API for configuring and launching test plans.
    - org.junit.platform.reporting: Defines the JUnit Platform Reporting API.
    - org.junit.platform.runner: Runner and annotations to configure and execute tests on the JUnit Platform in a JUnit 4 environment.
    - org.junit.platform.suite: Aggregates all JUnit Platform Suite modules.
    - org.junit.platform.suite.api: Annotations for configuring a test suite on the JUnit Platform.
    - org.junit.platform.suite.commons: Common support utilities for declarative test suite executors.
    - org.junit.platform.suite.engine: Provides a TestEngine for running declarative test suites.
    - org.junit.platform.testkit: Defines the Test Kit API for the JUnit Platform.

- *Vintage*: provides a TestEngine for running JUnit 3 and JUnit 4 based tests on the platform. 
    - org.junit.vintage.engine: Provides a TestEngine for running JUnit 3 and 4 based tests on the platform.


