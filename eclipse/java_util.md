# Java Utils

- Google
    - Guava: Google Core Libraries For Java:  implementation 'com.google.guava:guava:31.1-jre'/31.1-android
    - Guice: Depdenency Injecton: https://github.com/google/guice

- testContainer: https://www.testcontainers.org/
    - testImplementation "org.testcontainers:testcontainers:1.16.3"
    - implementation platform('org.testcontainers:testcontainers-bom:1.16.3') //import bom
    - testImplementation('org.testcontainers:mysql') //no version specified

- Mock-Server: https://mock-server.com/

- Cucumber Test: https://cucumber.io/

- JUnit Test
- Mocker
    - EasyMocker
    - Mockito
    - Power Mocker


## Dependency Injection Implementation in Core Java
- https://medium.com/globant/dependency-injection-implementation-in-core-java-fe9729f8ae27
Defined customized Annotation. Handle all classes with the specific associated Annotations; and autowired them.
