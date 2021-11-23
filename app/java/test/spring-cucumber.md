# Spring-Cucumber-junit5
- Needs cucumber(cucumber-core,cucumber-java,cucumber-junit,junit), cucumber-spring and spring
- Startup Point: Cucumber Test Runner
- ![Runner](https://thepracticaldeveloper.com/images/posts/uploads/2018/03/cucumber-spring-boot-1024.webp)
```
@RunWith(Cucumber.class)
@CucumberOptions(
    features = {"classpath:features"},  // feature files are defined in src/test/resources/features
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
- CucumberSpringTest
```
@CucumberContextConfiguration
@SpringBootTest(
   classes = { CucumberTestConfig.class }
) 
public ckass CucumberSpringTest {
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

## EasyMock

## PowerMock:
On EasyMock/Mockit to provide more features

## WireMock: Mock of Http Server

## TestContainer: Mock of container

## ServerMock: Mock of Network server 
