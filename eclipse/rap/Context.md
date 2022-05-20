# RAP/RCP Context
- Using the Eclipse context for RCP applications and plug-ins: https://www.vogella.com/tutorials/Eclipse4ContextUsage/article.html

## Accessing and extending the Eclipse context

### Accessing the context
You can place objects directly in the IEclipseContext hierarchy to make them available to other model objects.

To access an existing context you can use dependency injection if the relevant object is managed by the Eclipse runtime. 
This is the case for all model objects.
```
import org.eclipse.e4.core.contexts.IEclipseContext;
import org.eclipse.e4.core.di.annotations.Execute;

public class ShowMapHandler {
    @Execute
    public void execute(IEclipseContext context) {
        // add objects to the active local context injected into this handler
        // ...
    }
}
```

If a model object implements MContext, you can use dependency injection to get the model object injected and call the getContext() 
method to access its context. For example, MPart, MWindow, MApplication and MPerspective extend MContext.
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

        // add or access objects to and from the application context ...
    }

}
```

### Objects and context variables
You can add key / value pairs directly to the IEclipseContext.

Adding objects to a context can be done via the set() method of the IEclipseContext interface.
Via the setParent() method call, the new context is connected to the context hierarchy.
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
Such a context can be used to instantiate an object via the Eclipse framework.

A context variable is a key which is declared as modifiable via the declareModifiable(key) method call.
```
@Inject
public void addingContext(IEclipseContext context) {
    // putting in some values
    context.set("mykey1", "Hello1");
    context.set("mykey2", "Hello2");

    // declares the named value as modifiable by descendants of this context
    // if the value does not exist in this context, a null value is added for the name
    context.declareModifiable("mykey1");
}
```
Context variables are added to particular levels of the IEclipseContext hierarchy and can also be modified using the modify() method rather than set() method of the IEclipseContext. The modify() method searches up the chain to find the IEclipseContext defining the variable. If no entry is found in the context hierarchy, the value will be set in the IEclipseContext in which the call started.

If the key already exists in the context, then modify() requires that the key has been set to modifiable with the declareModifiable() method, if not, the method throws an exception.

You can add key/value pairs and Context variables at different levels of the context hierarchy to supply different objects in your application.

Instead of adding new objects to the IEclipseContext hierarchy, you can also override existing objects by using the same key.

You can change behavior of your application by overriding certain entries in the context. For example, you can modify the context of the MWindow model 
element. Its IEclipseContext is originally created by the WBWRenderer class. By default it puts an instance of the IWindowCloseHandler and the 
ISaveHandler interface into the local context of the MWindow model element. The IWindowCloseHandler object is responsible for the behavior 
once the MWindow model element is closed. 
```
@Execute
public void execute(final Shell shell, EModelService service, MWindow window) {
    IWindowCloseHandler handler = new IWindowCloseHandler() {
        @Override
        public boolean close(MWindow window) {
            return MessageDialog.openConfirm(shell, "Close", "You will loose data. Really close?");
        }
    };
    window.getContext().set(IWindowCloseHandler.class, handler);
}
```
### Accessing the IEclipseContext hierarchy from OSGi services
OSGi services are not directly part of the IEclipseContext hierarchy and are created by the OSGi runtime. 
The OSGi runtime does not support dependency injection based on the @Inject annotation.

The Eclipse framework registers the implementation of the MApplication interface also as an OSGi service. 
This allows OSGi services to use the OSGi API to access the MApplication and its context via the getContext() 
method. As the EModelService is part of the MApplication context you can search for other context elements via it.

###  Model add-ons

To participate in dependency injection with your custom Java objects you can add them as model add-ons to the application model. 
The classes referred to by the model add-ons can access and modify the IEclipseContext or interact with other services, e.g., the event system.
```
import javax.annotation.PostConstruct;
import org.eclipse.e4.core.contexts.IEclipseContext;

public class MyModelAddon {
    @PostConstruct
    public void init(IEclipseContext context) {
        // injected IEclipseContext comes from the application
        context.set("test1", "Hello");
    }
}
```

### RunAndTrack
The IEclipseContext allows you via the runAndTrack() method to register a Java object of type RunAndTrack.

A RunAndTrack object is basically a Runnable which has access to the context.

If the context changes, the RunAndTrack is called by the Eclipse framework. The runnable does not need to be 
explicitly unregistered from this context when it is no longer interested in tracking changes. If the RunAndTrack 
is invoked by the Eclipse platform and it returns false from its RunAndTrack.changed() method, it is automatically 
unregistered from change tracking on this context.
```
```

## Extending the objects available for the dependency injection
- create objects which declare their dependencies with @Inject based on a an IEclipseContext context. 
- Using Eclipse dependency container to create the custom objects automatically on demand and then get 
  them injected into your model objects. 
  - Create the custom objects automatically with @Creatable 
  - Create automatically objects in the application context with @Singleton.

### Creating and injecting custom objects
Using dependency injection is not limited to the objects created by the Eclipse runtime.
You can use the same approach to create an instance of a given class based on a given IEclipseContext. 
The given class can contain @Inject annotations. For this you use the ContextInjectionFactory class.
```
// create instance of class
ContextInjectionFactory.make(MyJavaObject.class, context);
```
The ContextInjectionFactory.make() method creates the object. You can also put it into the IEclipseContext 
hierarchy after the creation. If you place it into the IEclipseContext of the application, the created object is globally available.
```
IEclipseContext context = EclipseContextFactory.create();

// add your Java objects to the context
context.set(MyDataObject.class.getName(), data);
context.set(MoreStuff.class, moreData);

// dispose the context if you are done with it
context.dispose();
```

For this you can either use an existing IEclipseContext or create a new IEclipseContext. The new context object 
can be connected to the context hierarchy. Using a new context might be preferable to avoid collision of keys and 
to isolate your changes in a local context. Call the dispose method on your local context, if the object is not needed anymore.
```
public void createObjectInPart(IEclipseContext ctx) {
    // create a new local_ context
    IEclipseContext localCtx = EclipseContextFactory.create();
    localCtx.set(String.class, "Hello");

    // connect new local context with context hierarchy
    localCtx.setParent(ctx);

    // create object of type MyJavaObject via DI uses the localCtx and searches upwards for required objects
    MyJavaObject o = ContextInjectionFactory.make(MyJavaObject.class,localCtx);

    //TODO do something with the "o" object
}
```

### Create custom objects automatically with @Creatable

If you want the Eclipse framework to create your custom objects for you, annotate them with @Creatable.
This way you are telling the Eclipse DI container that it should create a new instance of this object if 
it does not find an instance in the context. The automatically-generated instance is not stored in the context.

If you have a non default-constructor, you must use the @Inject annotation on the constructor to indicate 
that Eclipse should try to run dependency injection on it.
```
import org.eclipse.e4.core.di.annotations.Creatable;

@Creatable
public class Dependent {
    public Dependent() {
        // placeholder
    }
}
```
```
import javax.inject.Inject;
import org.eclipse.e4.core.di.annotations.Creatable;
import com.vogella.tasks.model.TaskService;

@Creatable
public class YourObject {
    // constructor
    @Inject
    public YourObject(Dependent depend, TaskService service) {
        // placeholder
    }
}
```
## Create automatically objects in the application context with @Singleton
If the object should be created in the application context, use the @Singleton annotation in addition to the @Creatable annotation.
This ensures that only one instance of the object is created in your application.
```
import javax.inject.Inject;
import org.eclipse.e4.core.di.annotations.Creatable;
import com.vogella.tasks.model.TaskService;

@Creatable
@Singleton
public class YourObject {
    // constructor
    @Inject
    public YourObject(Dependent depend, TaskService service) {
        // placeholder
    }
}
```





