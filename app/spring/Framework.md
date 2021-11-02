# Spring Framework
- [Project](https://spring.io/projects/spring-framework)
- [Reference](https://docs.spring.io/spring-framework/docs/current/reference/html/)
- [API doc](https://docs.spring.io/spring-framework/docs/current/javadoc-api/)

- IoC
- Data Access
- Integration

## IoC
IoC Container: A Spring IoC container (ApplicationContext) manages one or more beans. 
- [ApplicationContext](https://docs.spring.io/spring-framework/docs/5.3.12/javadoc-api/org/springframework/context/ApplicationContext.html) is a subinterface of [BeanFactory](https://docs.spring.io/spring-framework/docs/5.3.12/javadoc-api/org/springframework/beans/factory/BeanFactory.html) with the following implementations for:
- Application
    - ClassPathXmlApplicationContext 
    - FileSystemXmlApplicationContext
    - AnnotationConfigApplicationContext
- WebApplication:
    - AnnotationConfigWebApplicationContext
    - GroovyWebApplicationContext
    - XmlWebApplicationContext
    
Interface Methods with inheritance: (Config: setXxx; )
- **org.springframework.web.context.ConfigurableWebApplicationContext**:

 setConfigLocation, setConfigLocations
- **org.springframework.web.context.WebApplicationContext**:

 getServletContext
- **org.springframework.context.ConfigurableApplicationContext**:

addApplicationListener, addBeanFactoryPostProcessor, addProtocolResolver, close, getApplicationStartup, getBeanFactory, getEnvironment, isActive, refresh, registerShutdownHook, setApplicationStartup, setClassLoader, setEnvironment, setId, setParent
- **org.springframework.context.ApplicationContext**:

getApplicationName, getAutowireCapableBeanFactory, getDisplayName, getId, getParent, getStartupDate
- **org.springframework.core.env.EnvironmentCapable**:

 getEnvironment
 - **org.springframework.beans.factory.ListableBeanFactory**:
 
 containsBeanDefinition, findAnnotationOnBean, getBeanDefinitionCount, getBeanDefinitionNames, getBeanNamesForAnnotation, getBeanNamesForType, getBeanProvider, getBeansOfType, getBeansWithAnnotation
- **org.springframework.beans.factory.HierarchicalBeanFactory**:

containsLocalBean, getParentBeanFactory
- **org.springframework.beans.factory.BeanFactory**:

containsBean, getAliases, getBean, getBeanProvider, getType, isPrototype, isSingleton, isTypeMatch
- **org.springframework.context.MessageSource**:

getMessage
- **org.springframework.context.ApplicationEventPublisher**:

publishEvent
- **org.springframework.core.io.support.ResourcePatternResolver**:

getResources
- **org.springframework.core.io.ResourceLoader**:

getClassLoader, getResource

## Xml based Configuration
```
// create and configure beans
ApplicationContext context = new ClassPathXmlApplicationContext("services.xml", "daos.xml");

// retrieve configured instance
PetStoreService service = context.getBean("petStore", PetStoreService.class);

// use configured instance
List<String> userList = service.getUsernameList();

<beans>
    <import resource="services.xml"/>
    <import resource="resources/messageSource.xml"/>
    <import resource="/resources/themeSource.xml"/>

    <bean id="bean1" class="..."/>
    <bean id="bean2" class="..."/>
</beans>
```

## Java based Configuration
Java configuration typically uses @Bean-annotated methods within a @Configuration class.
-  @Configuration
-  @Bean
-  @Import
-  @DependsOn

## Bean
- Class
- Name: One Id and multiple aliases
- Scope
- Constructor arguments
- Properties
- Autowiring mode
- Lay initialization
- Initialization method
- Destruction method

## Aware

## Resource

## Environment


