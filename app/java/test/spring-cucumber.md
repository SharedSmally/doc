# Spring-Cucumber-junit5
- Needs cucumber(cucumber-java,cucumber-junit,junit), spring, and cucumber-spring
- Startup Point:
```
@RunWith(Cucumber.class)
@CucumberOptions(
    features = {"classpath:features"},  // feature files are defined in src/test/resources/features
    tags="not @ignore and @test",  // select cases with the tags to be tested
    glue={"com.cainet.test"},      // packages that implemented the tests attached with the feature files
    plugin={"pretty","junit:target/cucumber_junut.xml","html:target/cucumber"} // register plugins
) 
public class CucumberIntegrationTest {
    @ClassRule
    public static TestRule rule = new Xxx();
    
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
