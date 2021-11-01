# Spring Framework
- [Project](https://spring.io/projects/spring-framework)
- [Reference](https://docs.spring.io/spring-framework/docs/current/reference/html/)
- [API doc](https://docs.spring.io/spring-framework/docs/current/javadoc-api/)

- IoC
- Data Access
- Integration

## IoC
IoC Container: 
- [ApplicationContext](https://docs.spring.io/spring-framework/docs/5.3.12/javadoc-api/org/springframework/context/ApplicationContext.html) is a subinterface of [BeanFactory](https://docs.spring.io/spring-framework/docs/5.3.12/javadoc-api/org/springframework/beans/factory/BeanFactory.html) with the following implementations:
- Application
    - ClassPathXmlApplicationContext 
    - FileSystemXmlApplicationContext
    - AnnotationConfigApplicationContext
- WebApplication:
    - AnnotationConfigWebApplicationContext
    - GroovyWebApplicationContext
    - XmlWebApplicationContext
    
Interface Methods
- org.springframework.web.context.ConfigurableWebApplicationContext
setConfigLocation, setConfigLocations

- org.springframework.web.context.WebApplicationContext
getServletContext

-  org.springframework.context.ConfigurableApplicationContext
addApplicationListener, addBeanFactoryPostProcessor, addProtocolResolver, close, getApplicationStartup, getBeanFactory, getEnvironment, isActive, refresh, registerShutdownHook, setApplicationStartup, setClassLoader, setEnvironment, setId, setParent

-  org.springframework.context.ApplicationContext
  getApplicationName, getAutowireCapableBeanFactory, getDisplayName, getId, getParent, getStartupDate

- org.springframework.core.env.EnvironmentCapable
   getEnvironment

 - org.springframework.beans.factory.ListableBeanFactory
   containsBeanDefinition, findAnnotationOnBean, getBeanDefinitionCount, getBeanDefinitionNames, getBeanNamesForAnnotation, getBeanNamesForType, getBeanNamesForType, getBeanNamesForType, getBeanNamesForType, getBeanProvider, getBeanProvider, getBeansOfType, getBeansOfType, getBeansWithAnnotation

- org.springframework.beans.factory.HierarchicalBeanFactory
   containsLocalBean, getParentBeanFactory

- org.springframework.beans.factory.BeanFactory
  containsBean, getAliases, getBean, getBean, getBean, getBean, getBean, getBeanProvider, getBeanProvider, getType, getType, isPrototype, isSingleton, isTypeMatch, isTypeMatch

 - interface org.springframework.context.MessageSource
    getMessage, getMessage, getMessage

- org.springframework.context.ApplicationEventPublisher
   publishEvent, publishEvent

- org.springframework.core.io.support.ResourcePatternResolver
    getResources

- org.springframework.core.io.ResourceLoader
    getClassLoader, getResource



## Data Access
### transactions
### DAO support
### JDBC
### ORM
### Marshalling XML

## Integration
### Remoting
### JMS
### JCA
### JMX
### Jmail
### Tasks
### Scheduling
### Cache
