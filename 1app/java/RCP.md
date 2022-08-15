# Eclipse RCP
IoC for OSGi and Application; based on EMF for MVC; Builder to provision context.
- https://www.vogella.com/tutorials/EclipseRCP/article.html

E4RCP Architecture
![Architecture](https://wiki.eclipse.org/images/thumb/8/80/Eclipse_4_Architecture.png/640px-Eclipse_4_Architecture.png)

E4RCP Context
![Context](https://www.vogella.com/tutorials/EclipseRCP/img/contexthierarchy_withosgi12.png)

E3 Product
![Product](https://www.javacodegeeks.com/wp-content/uploads/2018/11/pic1-2.png)
RCP is based on the same principles as the Eclipse IDE: the product includes some features, any feature includes some plugins.

The  model elements implement the MContext interface:
- MApplication
- MWindow
- MPerspective
- MPart
- MPopupMenu
```
 @Inject MPart part;   // IoC Inject to access the context element
 
 final IEclipseContext context = EclipseContextFactory.create();
 
 EclipseContextOSGi osgiContext = EclipseContextFactory.getServiceContext(BundleContext);
```

Get OSGi context:
```
BundleContext bundleContext = FrameworkUtil.getBundle(this.getClass()).getBundleContext();

Bundle bundle = FrameworkUtil.getBundle(this.getClass());
BundleContext bundleContext = bundle.getBundleContext();

Bundle[] bundles = InternalPlatform.getDefault().getBundleContext().getBundles();

bundleContext.registerService(IMyService.class.getName(), new MzServiceImpl(), null);
```
Spring Boot ApplicationContext: implement ApplicationContextAware
```
import org.springframework.beans.BeansException;
import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;
import org.springframework.stereotype.Component;

@Component
public class ApplicationContextProvider implements ApplicationContextAware {
    private ApplicationContext applicationContext;

    @Override
    public void setApplicationContext(ApplicationContext applicationContext) throws BeansException {
        this.applicationContext = applicationContext;
    }

    ApplicationContext getApplicationContext() {
        return this.applicationContext;
    }
}
```
AutoWire ApplicationContext:
```
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;

@SpringBootApplication
public class SpringGetApplicationContextApplication implements CommandLineRunner {
    @Autowired
    private ApplicationContext applicationContext;

    public static void main(String[] args) {
        SpringApplication.run(SpringGetApplicationContextApplication.class, args);
    }

    @Override
    public void run(String...args) throws Exception {
        Message message = applicationContext.getBean(Message.class);
        System.out.println(message.getMessage());
    }
}
```
