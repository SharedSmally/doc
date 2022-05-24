# Eclipse 4.x Remote Application Platform
- RAP project: https://www.eclipse.org
     - RAP e4 SDK
     - RAP Tools Resource
- Tutorial: 
    - Vogella Tutorial: https://www.vogella.com/tutorials/eclipse.html
    - Eclipse Source: Part1-7: https://eclipsesource.com/blogs/2012/05/10/eclipse-4-final-sprint-part-1-the-e4-application-model/
    - Eclipse E4 Tutorial: https://wiki.eclipse.org/Eclipse4/Tutorials
    - https://stackoverflow.com/questions/16325693/eclipse-4-rcp-aka-e4-documentation
    - https://o7planning.org/10361/create-eclipse-rap-widget-from-clientscripting-based-widget
    - https://o7planning.org/10121/eclipse-rap-tutorial-for-beginners-basic-application
- RAP: plugin (OSGi Bundle) with e4 application model and OSGi; WAR in servlet container 
    - Without BenchWork: 3rd parth OSGi; 
    - With BenchWork: Equinox OSGi;  	EntryPoint or IApplication
- RWT + Spring Boot: 
    - RWT: No OSGi 
    - https://www.javacodegeeks.com/2018/11/eclipse-rap-spring-boot.html
    - https://github.com/bwolff/rwt-on-spring-boot
- SWT: http://www.eclipse.org/swt/

## RAP 
### OSGi and Servlet Container
https://angelozerr.wordpress.com/2011/05/20/rap_step4/
- Embedding an HTTP server in Equinox:

![embed HTTP](https://angelozerr.files.wordpress.com/2011/05/embeddinghttpserverinequinox.png?w=595)

- Equinox in a Servlet Container

![Equinox in a Servlet Container](https://angelozerr.files.wordpress.com/2011/05/equinoxinservletcontainer.png?w=595)


## Start RAP Application
https://eclipsesource.com/blogs/2012/05/09/the-new-application-api-in-rap/
https://github.com/ralfstx/rap-helpers/tree/master/example.rwt.simple
- Implementing an ApplicationConfiguration
A RAP application consists of various parts, such as entrypoints, URL mappings, themes, service handlers, etc. All these parts constitute an ApplicationConfiguration. The configuration is like the blueprint for an application. Based on an ApplicationConfiguration, the framework can create and start an application instance. An ApplicationConfiguration is used to configure an application before it is started. 
```
public class SimpleConfiguration implements ApplicationConfiguration {
  public void configure( Application application ) {
    application.addEntryPoint( "/simple", SimpleEntryPoint.class, null );
    application.addEntryPoint( "/other", AnotherEntryPoint.class, null );
  }
}
```
- Registering the ApplicationConfiguration
When using OSGi, the ApplicationConfiguration can be registered as a service:
```
import org.eclipse.rap.rwt.application.ApplicationConfiguration;
import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;
import org.osgi.framework.ServiceRegistration;

public class Activator implements BundleActivator {
  private ServiceRegistration<?> registration;

  @Override
  public void start( BundleContext bundleContext ) throws Exception {
    ApplicationConfiguration configuration = new SimpleConfiguration();
    registration = bundleContext.registerService( ApplicationConfiguration.class.getName(),
                                                  configuration, null );
  }

  @Override
  public void stop( BundleContext bundleContext ) throws Exception {
    registration.unregister();
  }
}
```
The bundle org.eclipse.rap.rwt.osgi will automatically start this application on every available HttpService. When using Equinox, don’t forget to also include the org.eclipse.equinox.ds bundle.

- Starting an Application
When an ApplicationConfiguration has been registered as described above, the application is automatically started by the framework. Alternatively, it can also be started explicitly using an ApplicationRunner:
```
ApplicationConfiguration configuration = new SimpleConfiguration();
ApplicationRunner runner = new ApplicationRunner( configuration, servletContext );
runner.start();
```
https://stackoverflow.com/questions/62057321/using-swt-in-gradle-could-not-resolve-all-dependencies
