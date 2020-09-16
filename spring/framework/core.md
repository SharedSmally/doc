# Spring Framework Core
- [Document](https://docs.spring.io/spring-framework/docs/current/spring-framework-reference/core.html#spring-core)
- [Java API](https://docs.spring.io/spring/docs/current/javadoc-api/overview-summary.html)

## IoC Container
- packages: org.springframework.beans, org.springframework.context, org.springframework.core.*
- interfaces: [BeanFactory](https://docs.spring.io/spring/docs/current/javadoc-api/org/springframework/beans/factory/BeanFactory.html) and its sub-interface [ApplicationContext](https://docs.spring.io/spring/docs/current/javadoc-api/org/springframework/context/ApplicationContext.html) and [WebApplicationContext](https://docs.spring.io/spring/docs/current/javadoc-api/org/springframework/web/context/WebApplicationContext.html).
```
org.springframework.web.context.WebApplicationContext:
ServletContext	getServletContext()

org.springframework.context.ApplicationContext
ApplicationContext	getParent()

org.springframework.beans.factory.BeanFactory: 
<T> T	getBean(Class<T> requiredType)
<T> T	getBean(Class<T> requiredType, Object... args)
Object	getBean(String name)
<T> T	getBean(String name, Class<T> requiredType)
Object	getBean(String name, Object... args)

org.springframework.core.env.EnvironmentCapable:
Environment	getEnvironment()

org.springframework.core.io.ResourcePatternResolver:
Resource[] getResources(String locationPattern) throws IOException

org.springframework.core.io.ResourceLoader:
ClassLoader	getClassLoader()
Resource	getResource(String location)

org.springframework.core.io.Resource:
File	getFile()

org.springframework.core.env.Environment extends PropertyResolver:
String[]	getActiveProfiles()
String[]	getDefaultProfiles()
```
Java configuration typically uses @Bean-annotated methods within a @Configuration class in [context annotation](https://docs.spring.io/spring/docs/current/javadoc-api/org/springframework/context/annotation/package-summary.html).
- Annocation: @Bean and @Configuration 

## [@Bean](https://docs.spring.io/spring/docs/current/javadoc-api/org/springframework/context/annotation/Bean.html)
```
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

 @Configuration
 public class AppConfig {
     @Bean
     public FooService fooService() {
         return new FooService(fooRepository());
     }
     @Bean({"b1", "b2"}) // bean available as 'b1' and 'b2', but not 'fooRepository'
     public FooRepository fooRepository() {
         return new JdbcFooRepository(dataSource());
     }
     @Bean
     @Profile("production")
     @Scope("prototype")
     public MyBean myBean() {
         // instantiate and configure MyBean obj
         return obj;
     }
 }
```
Typically, @Bean methods are declared within @Configuration classes. It can be used in conjunction with @Scope, @Lazy, @DependsOn and @Primary annotations to provide attributes for profile, scope, lazy, depends-on or primary.

@Bean methods may also be declared within classes that are not annotated with @Configuration, such as in a @Component class or even in a plain old class (lite mode). Bean methods in lite mode will be treated as plain factory methods by the container.

Special consideration must be taken for @Bean methods that return Spring BeanFactoryPostProcessor (BFPP) types. Because BFPP objects must be instantiated very early in the container lifecycle, they can interfere with processing of annotations such as @Autowired, @Value, and @PostConstruct within @Configuration classes. To avoid these lifecycle issues, mark BFPP-returning @Bean methods as static.
```
     @Bean
     public static PropertySourcesPlaceholderConfigurer pspc() {
         // instantiate, configure and return pspc ...
     }
```
### Scope
- singleton

(Default) Scopes a single bean definition to a single object instance for each Spring IoC container.

- prototype

Scopes a single bean definition to any number of object instances.

- request: @RequestScope

Scopes a single bean definition to the lifecycle of a single HTTP request. That is, each HTTP request has its own instance of a bean created off the back of a single bean definition. Only valid in the context of a web-aware Spring ApplicationContext.

- session: @SessionScope

Scopes a single bean definition to the lifecycle of an HTTP Session. Only valid in the context of a web-aware Spring ApplicationContext.

- application

Scopes a single bean definition to the lifecycle of a ServletContext. Only valid in the context of a web-aware Spring ApplicationContext.

- websocket

Scopes a single bean definition to the lifecycle of a WebSocket. Only valid in the context of a web-aware Spring ApplicationContext.

### Lifecycle callback interfaces
- Initialization Callbacks
The org.springframework.beans.factory.InitializingBean interface lets a bean perform initialization work after the container has set all necessary properties on the bean.
```
void afterPropertiesSet() throws Exception;

public class AnotherExampleBean implements InitializingBean {
    @Override
    public void afterPropertiesSet() {
        // do some initialization work
    }
}
```
Multiple lifecycle mechanisms configured for the same bean are called as follows:
    - Methods annotated with @PostConstruct
    - afterPropertiesSet() as defined by the InitializingBean callback interface
    - A custom configured init() method

- Destruction Callbacks
Implementing the org.springframework.beans.factory.DisposableBean interface lets a bean get a callback when the container that contains it is destroyed. 
```
void destroy() throws Exception;
```
Destroy methods are called in the same order:
    - Methods annotated with @PreDestroy
    - destroy() as defined by the DisposableBean callback interface
    -  A custom configured destroy() method

- Startup and Shutdown Callbacks
The Lifecycle interface defines the essential methods for any object that has its own lifecycle requirements:
```
public interface Lifecycle {
    void start();
    void stop();
    boolean isRunning();
}

public interface LifecycleProcessor extends Lifecycle {
    void onRefresh();
    void onClose();
}

public interface Phased {
    int getPhase();
}

public interface SmartLifecycle extends Lifecycle, Phased {
    boolean isAutoStartup();
    void stop(Runnable callback); //for asynchronous shutdown 
}
```
Any Spring-managed object may implement the Lifecycle interface. When the ApplicationContext itself receives start and stop signals, it cascades those calls to all Lifecycle implementations defined within that context.

When starting, the objects with the lowest phase start first. When stopping, the reverse order is followed. An object that implements SmartLifecycle and whose getPhase() method returns Integer.MIN_VALUE would be among the first to start and the last to stop.

- ApplicationContextAware and BeanNameAware
When an ApplicationContext creates an object instance that implements the org.springframework.context.ApplicationContextAware interface, the instance is provided with a reference to that ApplicationContext:
```
public interface ApplicationContextAware {
    void setApplicationContext(ApplicationContext applicationContext) throws BeansException;
}

public interface BeanNameAware {
    void setBeanName(String name) throws BeansException;
}
```
- Other Aware interfaces
    - ApplicationContextAware: Declaring ApplicationContext.
    - ApplicationEventPublisherAware: Event publisher of the enclosing ApplicationContext.
    - BeanClassLoaderAware: Class loader used to load the bean classes.
    - BeanFactoryAware: Declaring BeanFactory.
    - BeanNameAware: Name of the declaring bean.
    - BootstrapContextAware: Resource adapter BootstrapContext the container runs in. Typically available only in JCA-aware ApplicationContext instances.
    - LoadTimeWeaverAware: Defined weaver for processing class definition at load time.
    - MessageSourceAware: Configured strategy for resolving messages 
    - NotificationPublisherAware: Spring JMX notification publisher.
    - ResourceLoaderAware: Configured loader for low-level access to resources.
    - ServletConfigAware: Current ServletConfig the container runs in.
    - ServletContextAware: Current ServletContext the container runs in.

## [@Configuration](https://docs.spring.io/spring/docs/current/javadoc-api/org/springframework/context/annotation/Configuration.html)
### bootstrap
- @Configuration classes are typically bootstrapped using either AnnotationConfigApplicationContext or AnnotationConfigWebApplicationContext:
```
 AnnotationConfigApplicationContext ctx = new AnnotationConfigApplicationContext();
 ctx.register(AppConfig.class);
 ctx.refresh();
 MyBean myBean = ctx.getBean(MyBean.class);
 // use myBean ...
```

@Configuration is meta-annotated with @Component, therefore @Configuration classes are candidates for component scanning and may take advantage of @Autowired/@Inject like any regular @Component.

- @Configuration classes may not only be bootstrapped using component scanning, but may also themselves configure component scanning using the @ComponentScan annotation:
```
 @Configuration
 @ComponentScan("com.acme.app.services")
 public class AppConfig {
     // various @Bean definitions ...
 }
```
@ComponentScan with @Configuration is used to specify the packages to be scanned. @ComponentScan without arguments scan the current package and all of its sub-packages.
```
@Configuration
@ComponentScan  //@ComponentScan(basePackages = "com.jcpw.componentscan.springapp.xxx")
public class SpringComponentScanApp {
    private static ApplicationContext ctx;

    @Bean
    public ExampleBean exampleBean() {
        return new ExampleBean();
    }
 
    public static void main(String[] args) {
        ctx = new AnnotationConfigApplicationContext(SpringComponentScanApp.class);
        for (String beanName : ctx.getBeanDefinitionNames()) {
            System.out.println(beanName);
        }
    }
}

@Component
public class Dog {}

@Component
public class Cat {}
```

In Sprint Boot, @SpringBootApplication annotation is a combination of three annotations: @Configuration, @EnableAutoConfiguration, @ComponentScan.
```
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;

// ...
@SpringBootApplication
public class SpringBootComponentScanApp {
    private static ApplicationContext ctx;
     @Bean
    public ExampleBean exampleBean() {
        return new ExampleBean();
    }
     public static void main(String[] args) {
        ctx = SpringApplication.run(SpringBootComponentScanApp.class, args);
        for (String beanName : ctx.getBeanDefinitionNames()) {
            System.out.println(beanName);
        }
     }
```


### Working with externalized values
- Externalized values may be looked up by injecting the Spring Environment into a @Configuration class:
```
 @Configuration
 public class AppConfig {
     @Autowired Environment env;

     @Bean
     public MyBean myBean() {
         MyBean myBean = new MyBean();
         myBean.setName(env.getProperty("bean.name"));
         return myBean;
     }
 }
```
 - @Configuration can contribute property sources to the Environment object using the @PropertySource annotation
 ```
 @Configuration
 @PropertySource("classpath:/com/acme/app.properties")
 public class AppConfig {
     @Inject Environment env;
        
     @Bean
     public MyBean myBean() {
         return new MyBean(env.getProperty("bean.name"));
     }
 }
 ```
- Externalized values may be injected into @Configuration classes using the @Value annotation:
```
 @Configuration
 @PropertySource("classpath:/com/acme/app.properties")
 public class AppConfig {
     @Value("${bean.name}") String beanName;

     @Bean
     public MyBean myBean() {
         return new MyBean(beanName);
     }
 }
```
### Composing @Configuration classes:
- @Configuration classes may be composed using the @Import annotation:
```
 @Configuration
 public class DatabaseConfig {
     @Bean
     public DataSource dataSource() {
         // instantiate, configure and return DataSource
     }
 }

 @Configuration
 @Import(DatabaseConfig.class)
 public class AppConfig {
     private final DatabaseConfig dataConfig;

     public AppConfig(DatabaseConfig dataConfig) {
         this.dataConfig = dataConfig;
     }

     @Bean
     public MyBean myBean() {  // reference the dataSource() bean method
         return new MyBean(dataConfig.dataSource());
     }
 }
```

- @Configuration classes may be marked with the @Profile annotation to indicate they should be processed only if a given profile or profiles are active
```
 @Profile("development")
 @Configuration
 public class EmbeddedDatabaseConfig {
     @Bean
     public DataSource dataSource() {
         // instantiate, configure and return embedded DataSource
     }
 }

 @Profile("production")
 @Configuration
 public class ProductionDatabaseConfig {
     @Bean
     public DataSource dataSource() {
         // instantiate, configure and return production DataSource
     }
 }
```
- Declare profile conditions at the @Bean method level:
```
 @Configuration
 public class ProfileDatabaseConfig {
     @Bean("dataSource")
     @Profile("development")
     public DataSource embeddedDatabase() { ... }

     @Bean("dataSource")
     @Profile("production")
     public DataSource productionDatabase() { ... }
 }
```
- With Spring XML using the @ImportResource annotation
```
 @Configuration
 @ImportResource("classpath:/com/acme/database-config.xml")
 public class AppConfig {
     @Inject DataSource dataSource; // from XML

     @Bean
     public MyBean myBean() {
         // inject the XML-defined dataSource bean
         return new MyBean(this.dataSource);
     }
 }
```
- @Configuration classes may be nested within one another 
```
 @Configuration
 public class AppConfig {
     @Inject DataSource dataSource;

     @Bean
     public MyBean myBean() {
         return new MyBean(dataSource);
     }

     @Configuration
     static class DatabaseConfig {
         @Bean
         DataSource dataSource() {
             return new EmbeddedDatabaseBuilder().build();
         }
     }
 }
```
- Spring TestContext framework provides @ContextConfiguration annotation accepting an array of component class references — typically @Configuration or @Component classes.
```
 @RunWith(SpringRunner.class)
 @ContextConfiguration(classes = {AppConfig.class, DatabaseConfig.class})
 public class MyTests {
     @Autowired MyBean myBean;
     @Autowired DataSource dataSource;

     @Test
     public void test() {
         // assertions against myBean ...
     }
 }
```
Spring features such as asynchronous method execution, scheduled task execution, annotation driven transaction management, and Spring MVC can be enabled and configured from @Configuration classes using their respective "@Enable" annotations: @EnableAsync, @EnableScheduling, @EnableTransactionManagement, @EnableAspectJAutoProxy, @EnableWebMvc.

## [Components](https://docs.spring.io/spring/docs/current/javadoc-api/org/springframework/stereotype/package-summary.html) in org.springframework.stereotype 
These classes are considered as candidates for auto-detection when using annotation-based configuration and classpath scanning.
- Component: Indicates that an annotated class is a component
- Controller: Indicates that an annotated class is a Controller (RestController for REST)
- Indexed: Indicate that the annotated element represents a stereotype for the index.
- Repository: Indicates that an annotated class is a DAO Repository, a mechanism for encapsulating storage, retrieval, and search behavior which emulates a collection of objects
- Service	:Indicates that an annotated class is a Service, an operation offered as an interface that stands alone in the model, with no encapsulated state.
- Aspect


