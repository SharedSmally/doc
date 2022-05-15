# Dependency Injection - DI
https://eclipsesource.com/blogs/tutorials/eclipse-4-e4-tutorial-part-4-dependency-injection-basics/

DI is essentially about how certain objects can access other objects from the outside.

Injected objects can be fields of a class, parameters of a constructor or parameters of a method that is called by the framework.
In the simplest case, required objects are marked by the annotation @Inject. 
There are a number of additional annotations that control the behavior and the timing of the injection. 
For instance, the annotation @Execute marks a method in a handler which is called during the execution of the handler. 
The required parameters for this method will be injected:
```
@ Execute
public void execute (MyObject requiredObject) {
   // Here is the actual handler code
}
```
## Eclipse Context
Eclipse context is a kind of list of objects that are ready for injection. Technically it is a map of strings and objects. 
Without further information, an object is saved under its full class name.

![Eclipse Context](https://eclipsesource.com/wp-content/uploads/2012/09/091812_1314_Eclipse4e41.png)

Eclipse 4 has more than one global context. Some elements of the Application Model have their own context during runtime, 
such as a window, a perspective or a part. These are hierarchically linked. 
![E4 Context](https://eclipsesource.com/wp-content/uploads/2012/09/091812_1314_Eclipse4e42.png)

Generally, all elements of the Application Context Models can be accessed along the ascending hierarchy. For example, 
in the context of a part, the window in which the part is contained can be injected:
```
@ Inject
public void myMethod (MWindow window) {
}
```
The context contains some SWT elements associated with the Application Model such as the composite of a part or the 
shell of the running application. Eclipse 4 services also ensure that certain commonly accessible objects, 
such as the current selection or the Eclipse Workbench Preferences are available in the context. 
The root context contains all OSGi services. The user can insert the items into the context.

## @Named
Specify a name for the injection to access to a specific type, and the specific instance of a type:
```
@ Inject
@ Named ("org.eclipse.swt.widgets.Composite")
Composite parent;
```
Eclipse 4 services also include some objects in the context under certain IDs, defined in IServiceConstants: 
```
@ Inject
@ Named (IServiceConstants.ACTIVE_SHELL)
Shell shell;
```

## @Optional
If a context does not contain a matching object that can be injected, Eclipse 4 displays an error, with an exception thrown. 
If an object marked with @Optional is not available in the context, null will be injected. In this case, prior to access to
the injected object, it has to be checked, if it is null.

## @Active
In certain use cases, it is necessary to access not only a specific type of an element from the application model, 
but the currently active item. With the annotation @Active, the currently active element is used for the injection to access the active part.
```
@Inject
public void save (@Active MPart part) {
   partService.save (part);
}
```

There are many use cases that it needs to react to certain events, e.g., if a view gets the focus or if an object is disposed.
Therefore, methods that need to be called by the framework at a certain point in time must be marked with corresponding annotations, e.g., @Focus.

## @PostConstruct and @PreDestroy
A method annotated with @PostConstruct is called after a class is initialized with its constructor and after all fields have been injected.
A method annotated with @PreDestroy is called when an object is not needed anymore, e.g., when the corresponding view is closed but before 
the object is destroyed. 
```
@Inject
MyService service;

@PostConstruct
public void postConstruct() {
   service.addListener(this);
}

@PreDestroy
public void preDestroy() {
   service.removeListener(this);
}
```
A service is injected as a field and can therefore not be accessed in the constructor.
The @PostConstruct method is used to register a listener on the service, 
the @PreDestroy method to deregister the listener.

@PostConstruct and @PreDestroy can be used for all classes, which are initialized by the framework or manually using the Injection Factory.

## @Focus
For visual elements, e.g., parts, there are additional events to which an implementation should react. A method marked with @Focus is 
called when the corresponding UI element receives the focus. In SWT applications, the focus must be forwarded to the central SWT 
element, e.g., a text field or a tree. If the implementation of a view contains several SWT controls, the developer has to choose a 
control, typically the first text field if it is a form editor.
```
@Focus
public void onFocus() {
   text.setFocus();
}
```

## @Persist
The annotation @Persist marks a method to be called if a save is triggered on a part. For example, if the parts
represent a text editor, the content of the text control is saved into a file.
```
@Persist
public void save(){
  //save the context of the part
}
```
The method is typically called from another place then the part itself, e.g., from a handler. 
The EPartService provides helper methods to save a specific part or all parts that are dirty:
```
@Execute
public void execute(@Named(IServiceConstants.ACTIVE_PART) MPart part,EPartService partService) {
   partService.savePart(part, false);
}
```

## @PersistState
A method marked with @PersistState is called before an object is disposed and before the method marked with @PreDestroy is called.
The purpose of this method is to persist the latest state of an element if required. If the method is a view, the latest input 
by the user could be stored for convenience.

## @Execute and @CanExecute
They are used especially for handlers: @Execute marks the method to be executed if the handler itself is executed. @CanExecute 
marks the method responsible for the enable state of the handler, and it needs to return a Boolean value, which tells the 
framework whether the implementation action is currently available or not. As a consequence, Eclipse 4 will enable or 
disable all menu and toolbar items linked to this handler. As for all annotations, all required parameters are injected.

@CanExecute works quite differently than other annotations. It is not called on a certain event or on a change of one parameter 
in the context. It is called continuously and is timer-based, so it is important to not spend too much execution time within this method.

A very common example for the implementation of a @CanExecute method is a check for the current selection, the active part or the 
active perspective.
```
@CanExecute
public boolean canExecute(@Named(IServiceConstants.ACTIVE_SELECTION) @Optional Object selection) {
   if (selection!=null && selection instanceof MyObject)
    return true;
   return false;
}
```

## Lifecycle Annotations
Eclipse 4 offers the possibility to hook into the lifecycle of a running application. A lifecycle handler needs to be registered as 
a property of the registered application:
```
<property name="lifeCycleURI" value="platform:/plugin/helloworld/helloworld.LifecycleHandler">
```

The implementation of the lifecycle handler itself is a POJO. It supports the following specific annotations:
### @PostContextCreate
Is called after the application’s context has been created. Can be used to add or remove objects from the context.

### @ProcessAdditions and @ProcessRemovals
Allows the modification of the application model before it is passed to the renderer that will display the application on screen. 
Allows the addition and removal of application model elements before the application is actually shown.

### @PreSave
Is called before the application model is persisted. Allows the modification of the model before saving it.
  
| Annotation | Package |
|------------|---------|
| @Active	| org.eclipse.e4.core.contexts| 
| @Creatable	| org.eclipse.e4.core.di.annotations| 
| @CanExecute	| org.eclipse.e4.core.di.annotations| 
| @Execute	| org.eclipse.e4.core.di.annotations| 
| @Inject	| javax.inject| 
| @Named	| javax.inject| 
| @Optional	| org.eclipse.e4.core.di.annotations| 
| @Persist	| org.eclipse.e4.ui.di| 
| @PersistState| 	org.eclipse.e4.ui.di| 
| @PostConstruct| 	javax.annotation| 
| @ProcessAdditions| 	org.eclipse.e4.ui.workbench.lifecycle| 
| @ProcessRemovals	| org.eclipse.e4.ui.workbench.lifecycle| 
| @PostContextCreate	| org.eclipse.e4.ui.workbench.lifecycle| 
| @PreDestroy	| javax.annotation| 
| @PreSave	| org.eclipse.e4.ui.workbench.lifecycle| 


## Injecting Objects
Normally, the injection is triggered via the @Inject annotation. It can be placed prior to methods, before the constructor or class fields. 
If a method or constructor is marked with @Inject, all their parameters are injected. Without further information with @Named, the lookup 
for the right object will be according to the corresponding type of the parameter or field. 

A crucial role is played by the order of injection. When a class is instantiated, the constructor and its parameters are injected first. 
Immediately following, the relevant fields are injected. As a consequence, fields can not be accessed in the constructor. 
Parameters of methods are injected when these methods are called by the framework. All methods marked with @Inject are also called 
to initialize the object after the constructor and the fields. If the injected object changes in context, it is re-injected. 
Methods are therefore called again, when the injected values change.

### Constructors
Constructors should include parameters that are essential for the existence of an object. 
Particularly the object initializations should be done in separate methods that are called after the constructor. 
A typical example of dependency injection in the constructor is the injection of the Parent composite of a view.
Since views are initialized in the context of a part of the application model, the specification of the type 
composite in this case is clear and no additional annotations are required.
```
@ Inject
public void MyView (Composite parent) {
   //Implement the View placed on the Parent
}
```

### Fields
After the constructor of a class, the class’ fields are injected. A typical application is 
the injection of services that will be available globally in the class. An example is the Selection 
Service to set the current selection of a view. 
```
@ Inject
ESelectionService service;
...
service.setSelection (mySelection);
```
Injected fields must not be marked as final, as they can potentially be re-injected. 
Final fields must be explicitly set through the constructor and its injection.

### Methods
After the constructor and the fields, while initializing a class, all annotated methods 
(with @Inject) are sequentially called. This also applies to methods that have no parameters. 
If one of the injected parameters of a method changes afterwards in the context, the method 
will be called again with the new parameters.
```
@ Inject
public void setSelection (@ Named (IServiceConstants.ACTIVE_SELECTION) @ Optional MyObject myObject) {
    //Process Selection
}
```



