# 带有Spring Boot的Eclipse RAP
- https://blog.csdn.net/danpu0978/article/details/106766502
- https://www.javacodegeeks.com/2018/11/eclipse-rap-spring-boot.html
- [RAP](https://javarepos.com/lib/eclipse-rap-runtime-remote-application-platform)
- https://www.eclipse.org/forums/index.php/t/1110729/
- https://github.com/bwolff/rwt-on-spring-boot   (without OSGi or workbench )


 Eclipse Framework中的UI基于两件事：
- 应用模型: 在较高的层次上处理许多UI组件的交互。 它以类似XML的格式定义。 它定义了窗口，部件，命令，处理程序，菜单等。
- SWT –标准小工具工具包, SWT是小部件的集合：按钮，标签，对话框。 这些小部件用于在比应用程序模型更低的级别上创建UI。 例如，零件（MPart类）中的UI是使用SWT创建的。 

Eclipse框架也可以用于创建Web应用程序。 它称为Eclipse RAP –远程应用程序平台。

##Option1: WAR文件中带有Spring Boot的RAP应用程序
第一种选择是使用Spring Boot和RAP创建WAR并将其部署到Tomcat.
- web.xml
```
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://java.sun.com/xml/ns/j2ee"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://java.sun.com/xml/ns/j2ee http://java.sun.com/xml/ns/j2ee/web-app_2_4.xsd"
  version="2.4">
 
  <context-param>
    <param-name>org.eclipse.rap.applicationConfiguration</param-name>
    <param-value>com.example.HelloWorldConfiguration</param-value>
  </context-param>
 
  <listener>
    <listener-class>org.eclipse.rap.rwt.engine.RWTServletContextListener</listener-class>
  </listener>
 
  <servlet>
    <servlet-name>rwtServlet</servlet-name>
    <servlet-class>org.eclipse.rap.rwt.engine.RWTServlet</servlet-class>
  </servlet>
 
  <servlet-mapping>
    <servlet-name>rwtServlet</servlet-name>
    <url-pattern>/hello</url-pattern>
  </servlet-mapping>
</web-app>
```
- 应用程序配置 ApplicationConfig
```
public class HelloWorldConfiguration implements ApplicationConfiguration {
  public void configure( Application application ) {
    application.addEntryPoint( "/hello", HelloWorld.class, null );
  }
}
```
- EntryPoint
```
public class HelloWorld extends AbstractEntryPoint {
  public void createContents( Composite parent ) {
    Label label = new Label( parent, SWT.NONE );
    label.setText( "Hello RAP World" );
  }
}
```
 为了使其与Maven WAR打包一起使用，请将web.xml放入src / main / webapp / WEB-INF。 必须在web.xml中为rwtServlet配置应用程序配置中的入口点。

- 对于Spring Boot，添加以下内容： 
```
@SpringBootApplication
public class SpringApp extends SpringBootServletInitializer {
  public SpringApplicationBuilder configure( SpringApplicationBuilder builder ) {
    return builder.web(WebApplicationType.NONE).sources(<configurations>);
  }
}
```
- 在pom.xml中，将包装设置为war。
<packaging>war</packaging>

Eclipse jar在Maven Central中不可用。 也许可以以某种方式使用p2存储库，使用了最新的可用版本RAP 3.5, 该jar为org.eclipse.rap.rwt_3.5.0.20180613-1038.jar。
将其手动安装到本地Maven存储库，并在pom中使用了依赖项。这足以构建一个WAR并在Tomcat 9中使用它。

## 可执行jar中带有Spring Boot的RAP应用程序
此选项看起来更方便。 能够在Spring Boot中使用RWTServlet真是太好了。 然后，所有功能（如可执行jar和嵌入式Tomcat）将立即可用。 
- 将主Spring Boot类恢复正常：
```
@SpringBootApplication
public class SpringApp {
    public static void main(String[] args) {
        SpringApplication.run(SpringApp.class, args);
    }
}
```
- Spring Boot使用ServletRegistrationBean添加一个Servlet：
```
@Bean
public ServletRegistrationBean<RWTServlet> servletRegistrationBean() {
    ServletRegistrationBean<RWTServlet> rwt = new 
        ServletRegistrationBean<RWTServlet>(new RWTServlet(),"/hello", "/hello2");
    return rwt;
}
```
- 需要将此RWTServlet特殊上下文绑定到ServletContext。 先前在WAR示例中，RWTServletContextListener处理了
```
public class RWTSCLSimple extends RWTServletContextListener {
     private ApplicationRunner applicationRunner;
 
    @Override
    public void contextInitialized( ServletContextEvent event ) {
        ServletContext servletContext = event.getServletContext();
        ApplicationConfiguration configuration = new HelloWorldConfiguration();
        applicationRunner = new ApplicationRunner( configuration, servletContext );
        applicationRunner.start();
    }
 
    @Override
    public void contextDestroyed( ServletContextEvent event ) {
        applicationRunner.stop();
        applicationRunner = null;
    }
}
```
- 必须将此类声明为Bean
```
@Bean
public RWTSCLSimple rwtSCListener() {
    return new RWTSCLSimple();
}
```
所有Spring Boot功能都可以直接使用，甚至是server.servlet.context-path
