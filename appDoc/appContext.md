# Application
## Application Context
- Spring Application Context: https://zetcode.com/springboot/applicationcontext/
- Eclipse Application Context: https://www.vogella.com/tutorials/Eclipse4ContextUsage/article.html
- RCP vs RAP: https://owenou.com/introducing-eclipse-rap/
![RCP-RAP](https://owenou.com/assets/images/posts/rap_archi.png)


## Eclipse Application Context
Use @Inject or other annocations, such as @Execute, to place IEclipseContext available directly.
```
import org.eclipse.e4.core.contexts.IEclipseContext;
import org.eclipse.e4.core.di.annotations.Execute;

public class ShowMapHandler {
    @Execute
    public void execute(IEclipseContext context) { // context is available to use
        // add objects to the active local context injected into this handler
    }
}
```
- Use MContext objects, such MPart, MWindow, MApplication and MPerspective, to get Context directly 
```
import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

import org.eclipse.e4.core.contexts.IEclipseContext;
import org.eclipse.e4.ui.model.application.ui.basic.MPart;
import org.eclipse.swt.widgets.Composite;

public class TodoDetailsPart {
    @PostConstruct
    public void createControls(Composite parent, MApplication application) {
        // getting the IEclipseContext of the application via the MApplication object
        IEclipseContext context = application.getContext();

        // add or access objects to and from the application context
    }
}
```
- Build Context hierarchy 
```
@Inject
public void addingContext(IEclipseContext context) {
    // create a new IEclipseContext instance
    IEclipseContext myContext = EclipseContextFactory.create();

    // add objects to context
    myContext.set("mykey1", "Hello1");
    myContext.set("mykey2", "Hello2");

    // adding a parent relationship
    myContext.setParent(context);

    // alternatively you can create a new context which has a parent/child
    // relationship via the context.createChild() method call
}
```
- Accessing the IEclipseContext hierarchy from OSGi services

OSGi services are not directly part of the IEclipseContext hierarchy and are created by the OSGi runtime. 
The OSGi runtime does not support dependency injection based on the @Inject annotation.

The Eclipse framework registers the implementation of the MApplication interface also as an OSGi service. 
This allows OSGi services to use the OSGi API to access the MApplication and its context via the getContext() method. 
For the EModelService is part of the MApplication context, it can be used to search for other context elements via it.

## Spring Application Context
- $ gradlew -q bootRun
- Using ApplicationContextAware:
```
import org.springframework.beans.BeansException;
import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;
import org.springframework.stereotype.Component;

@Component
public class ApplicationContextProvider implements ApplicationContextAware {
    ApplicationContext applicationContext;

    @Override
    public void setApplicationContext(ApplicationContext applicationContext) throws BeansException {
        this.applicationContext = applicationContext;
    }

    public ApplicationContext getApplicationContext() {
        return applicationContext;
    }
}

@Component
public class MyBeanString {
    public String getApplicationId() {
        return "MyBeanString";
    }
}

@Component
public class MyBean implements ApplicationContextAware {
    String applicationId;

    @Override
    public void setApplicationContext(ApplicationContext applicationContext) throws BeansException {
        applicationId = applicationContext.getId();
    }

    public String getApplicationId() {
        return applicationId;
    }
}
```
- Autowire ApplicationContext directly
```
import com.zetcode.bean.MyBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;

@SpringBootApplication
public class Application implements CommandLineRunner {
    @Autowired
    private ApplicationContext applicationContext;
    
    @Autowired
    private ApplicationContextProvider applicationContextProvider;
    
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }

    @Override
    public void run(String... args) throws Exception {
        System.out.println(applicationContext.getDisplayName());
        System.out.println(applicationContext.getId());

        MyBean myBean = applicationContext.getBean(MyBean.class);
        System.out.println(myBean.getApplicationId());
        MyBeanString myBeanStr = applicationContext.getBean(MyBeanString.class);
        System.out.println(myBeanStr.getApplicationId());
        
        MyBean myBean0 = applicationContextProvider.getApplicationContext().getBean(MyBean.class);
        System.out.println(myBean0.getApplicationId());
        MyBeanString myBeanStr0 = applicationContextProvider.getApplicationContext().getBean(MyBeanString.class);
        System.out.println(myBeanStr0.getApplicationId());
    }
}
```
