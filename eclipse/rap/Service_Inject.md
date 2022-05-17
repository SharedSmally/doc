# E4 Service
- [Tutorial](https://www.vogella.com/tutorials/Eclipse4Services/article.html)
- [E4/Eclipse Application Services](https://wiki.eclipse.org/E4/Eclipse_Application_Services)
- [Available Services in Eclipse 4](https://wiki.eclipse.org/E4/Contexts#Available_Services_in_Eclipse_e4)
    - Model: Model objects that are themselves MContext instances will be included in their own context. For example, MWindows and MParts are MContexts, so you can query their context for the model object. 
    - Services: Essentially, anything starting with E\*Service should be retrievable from the context, 
    - There are also some other things in there such as:
        - org.eclipse.e4.core.services.Adapter
        - org.eclipse.e4.core.services.StatusReporter
        - org.eclipse.e4.core.services.Logger
        - org.eclipse.e4.core.services.events.IEventBroker
        - org.eclipse.e4.workbench.ui.IPresentationEngine
        - org.eclipse.jface.window.IShellProvider
    - Misc:
        - org.eclipse.swt.widgets.Composite, this is provided by the renderer to parts for constructing the user interface
        - org.eclipse.core.runtime.RegistryContextFactory - Creates objects based on the registry's configuration element. Creates a user-specified class and injects into it contents of the configuration element and, optionally, the supplied context
        - org.eclipse.equinox.context.IEquinoxContext - This interface represents a hierarchical context with dependency injection capabilities. The context might have number of objects associated with it. For instance, a context might include log, status, and preferences. 
    - OSGi Services: 
    - Constants: defined in org.eclipse.e4.ui.services.IServiceConstants,such as ACTIVE_SELECTION, ACTIVE_PART and ACTIVE_SHELL.  need the @Named annotation
```
public class AccountsPart {
  @Inject
  @Named(IServiceConstants.ACTIVE_PART)
  private MPart part;
}
```
    
## Eclipse platform services

| Service | 	Description| 
| --------| ------------|
| EModelService| Used to search for elements in the model, create new model elements, clone existing snippets and insert new elements into the runtime application model.| 
| ESelectionService| Used to retrieve and set the current active selection in the user interface.| 
| ECommandService| Gives access to existing commands and allows you to create and change commands.| 
| EHandlerService| Allows you to access, change and trigger handlers.| 
| EPartService| Provides API to access and modify parts. It also allows you to switch perspectives and can be used to trigger that a method annotated with @Persist in dirty parts, i.e. if the corresponding part behaves like an editor.| 
| IEventBroker| Provides functionality to send event data and to register for specified events and event topics.| 
| EContextService| Activate and deactivate key bindings defined as BindingContext in the application model. The content referred to in this service is the BindingContext and not the IEclipseContext.| 
| IThemeEngine| Allows to switch the styling of the application at runtime.| 
| EMenuService| Registers a popup menu (MPopupMenu) for a control.| 
| org.eclipse.e4.core.services.Adapter |  An adapter can adapt an object to the specified type, allowing clients to request domain-specific behavior for an object. It integrates IAdaptable and IAdapterManager.| 
| org.eclipse.e4.core.services.Logger |  Provides logging functionality| 
| org.eclipse.jface.window.IShellProvider |  allows access to a Shell, depends on SWT.| 
| org.eclipse.e4.core.services.log.Logger | E4/EAS/Logging and Tracing |

### Selection service
The ESelectionService service allows you to retrieve and set the user interface selection in each top-level window and part. This selection is stored under the IServiceConstants.ACTIVE_SELECTION context key.
```
@Inject ESelectionService selectionService; 
viewer.addSelectionChangedListener(event -> { 
    IStructuredSelection selection = viewer.getStructuredSelection();
    //getSelection(partId): retrieve the selection of a specific part.
    selectionService.setSelection(selection.getFirstElement()); 
});

//Method is called if the current selection is a List
@Inject
public void setTasks(@Optional
          @Named(IServiceConstants.ACTIVE_SELECTION) List<Task> tasks) { 
        // do something with the list of todos
}

// 	Method is called if the current selection is a Task
@Inject
public void setTask(@Optional
        @Named(IServiceConstants.ACTIVE_SELECTION) Task task) { 
        // do something with the task
}
```

### Model Service
The model service gives you access to the application model at runtime and allows you to modify it. It allows you to search for existing model elements, create news onces (completely or based on snippets).
- Searching model elements: findElements() to search for specific model elements.
```
@Inject EModelService modelService;`

import java.util.ArrayList;
import java.util.List;

import org.eclipse.e4.core.di.annotations.Execute;
import org.eclipse.e4.ui.model.application.MApplication;
import org.eclipse.e4.ui.model.application.ui.MUIElement;
import org.eclipse.e4.ui.model.application.ui.basic.MPart;
import org.eclipse.e4.ui.workbench.modeling.EModelService;
import org.eclipse.e4.ui.model.application.ui.advanced.MPerspective;

public class ModelServiceExampleHandler {
    @Execute
    public void execute(MApplication application, EModelService service) {
        // find objects by ID
        findPartsById(application, service);

        // find objects by type
        findParts(application, service);

        // find objects by tags
        findObjectsByTag(application, service);
    }

    // example for search by ID
    private void findPartsById(MApplication application, EModelService service) {
        List<MPart> parts = service.findElements(application, "mypart", MPart.class, null);
        System.out.println("Found part(s) : " + parts.size());
    }

    // example for search by type
    private void findParts(MApplication application, EModelService service) {
        List<MPart> parts = service.findElements(application, null, MPart.class, null);
        System.out.println("Found parts(s) : " + parts.size());
    }

    // example for search by tag
    private void findObjectsByTag(MApplication application, EModelService service) {
        List<String> tags = new ArrayList<>();
        tags.add("justatag");
        List<MUIElement> elementsWithTags = service.findElements(application, null, null, tags);
        System.out.println("Found parts(s) : " + elementsWithTags.size());
    }
}

public class FindPerspectiveHandler {
    @Execute
    public void execute(MApplication application, EModelService service) {
        // search for a part with the following ID
        String ID = "com.example.e4.rcp.parts.tododetail";
        MUIElement element = service.find(ID, application);
        MPerspective perspective = service.getPerspectiveFor(element);
        System.out.println(perspective);
        // TODO do something useful with the perspective
    }
}

public class DynamicPartHandlerCode {
    // used as reference
    @Execute
    public void execute(MApplication application, EPartService partService, EModelService modelService) {
        // create new part
        MPart mPart = modelService.createModelElement(MPart.class);
        mPart.setLabel("Testing");
        mPart.setElementId("newid");
        mPart.setContributionURI("bundleclass://com.vogella.tasks.ui/com.vogella.tasks.ui.parts.DynamicPart");
        partService.showPart(mPart, PartState.ACTIVATE);
    }
}
```

### Par service
The part service allows you to find and perform actions on parts in the application model. 
It also allows you to switch perspectives and to create and activate new parts based on part descriptors in the application model.
```
@Inject private EPartService partService;

// search part with ID "com.example.todo.rcp.parts.tododetails" assume that a part with this ID exists
detailsTodoPart = partService.findPart("com.example.todo.rcp.parts.tododetails");

// hide the part
partService.hidePart(detailsTodoPart);

//show the part
detailsTodoPart.setVisible(true); // required if initial not visible
partService.showPart(detailsTodoPart, PartState.VISIBLE);
```
Switch perspectives
```
import java.util.List;

import org.eclipse.e4.core.di.annotations.Execute;
import org.eclipse.e4.ui.model.application.MApplication;
import org.eclipse.e4.ui.model.application.ui.MUIElement;
import org.eclipse.e4.ui.model.application.ui.advanced.MPerspective;
import org.eclipse.e4.ui.model.application.ui.basic.MPart;
import org.eclipse.e4.ui.workbench.modeling.EModelService;
import org.eclipse.e4.ui.workbench.modeling.EPartService;
import org.eclipse.e4.ui.workbench.modeling.EPartService.PartState;

public class SwitchPerspectiveHandler {
    @Execute
    public void execute(MApplication app, EPartService partService,
            EModelService modelService) {
        MPerspective element =
                (MPerspective) modelService.find("secondperspective", app);
        // now switch perspective
        partService.switchPerspective(element);
    }
}
```

### Using part descriptors
The part descriptor model element is a template for the creation of a part.

By defining a common set of attributes via such a blueprint it is possible to create concrete instances of it via the part service.
```
import org.eclipse.e4.core.di.annotations.Execute;
import org.eclipse.e4.ui.model.application.ui.basic.MPart;
import org.eclipse.e4.ui.workbench.modeling.EPartService;
import org.eclipse.e4.ui.workbench.modeling.EPartService.PartState;

public class OpenPartHandler {
    // the "com.vogella.tasks.ui.partdescriptor.fileeditor" ID is used for the part descriptor
    @Execute
    public void execute(EPartService partService) {
        // create a new part based on a part descriptor if multiple parts of this type are allowed a new part is always generated

        MPart part = partService.createPart("com.vogella.tasks.ui.partdescriptor.fileeditor");
        part.setLabel("New Dynamic Part");

         // the provided part is be shown
        partService.showPart(part, PartState.ACTIVATE);
    }
}
```

### Command and Handler service
- Execute a command
```
// create parameter for the command optional, can be null
Map<String, String> parameters = new HashMap<String, String>();
parameters.put(Constants.SEARCH_QUERY_ID, id);

ParameterizedCommand cmd = commandService.createCommand("com.example.mycommand", parameters);

// execute the registered handler for the command
handlerService.executeHandler(cmd);
```
- Assign a handler to a command
```
Command command = commandService.getCommand("com.example.mycommand");

// check if the command is defined
System.out.println(command.isDefined());

// activate handler, assumption: the AboutHandler() class exists already
handlerService.activateHandler("com.example.mycommand", new AboutHandler());

// prepare execution of command
ParameterizedCommand cmd = commandService.createCommand("com.example.mycommand", null);

// check if the command can get executed
if (handlerService.canExecute(cmd)){
    // execute the command
    handlerService.executeHandler(cmd);
}
```

### E4/EAS/Eventing System
- Listening for part activation events
```
IEventBroker eventBroker = (IEventBroker) eclipseContext.get(IEventBroker.class.getName());
eventBroker.subscribe(IUIEvents.ElementContainer.Topic, null,
    new EventHandler() {
        public void handleEvent(Event event) {
          if (event.getProperty(IUIEvents.EventTags.AttName).equals(IUIEvents.ElementContainer.ActiveChild)) {
            Object newPart = event.getProperty(IUIEvents.EventTags.NewValue);
            if (newPart instanceof MPart) {
              // do something
            }
          }
        }
    }, /* headless */ false);
```

- Sending out part activation events
```
Map data = new HashMap();
map.put(IUIEvents.EventTags.AttName, IUIEvents.ElementContainer.ActiveChild);
map.put(IUIEvents.EventTags.Element, partStack);
map.put(IUIEvents.EventTags.OldValue, oldPart);
map.put(IUIEvents.EventTags.NewValue, newPart);
map.put(IUIEvents.EventTags.Type, IUIEvents.EventTypes.Set);
 
IEventBroker eventBroker = (IEventBroker) eclipseContext.get(IEventBroker.class.getName());
eventBroker.send(IUIEvents.ElementContainer.Topic, data);
```
- Posting out asynchronous events
```
IEventBroker eventBroker = (IEventBroker) eclipseContext.get(IEventBroker.class.getName());
eventBroker.post(eventTopic, data);
```
### Schedule Task
```
@Inject Provider<RunnableContext> runnableContext; 
IRunnable runnable = new Runnable("My long-running operation...") {
  protected IStatus run(IProgressMonitor monitor) {
    IStatus status = Status.OK_STATUS;
    monitor.beginTask("foo", 100);
    try {
       doFirstHalfFoo();
       monitor.worked(50);
       doSecondHalfFoo();
    } catch (FooException e) {
       status = new Status(IStatus.ERROR, "id", "foo failure message", e);
    } finally {
       monitor.done();
    }
    return status;
  }
};
runnableContext.get().run(runnable);
```
