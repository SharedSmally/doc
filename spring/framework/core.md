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
