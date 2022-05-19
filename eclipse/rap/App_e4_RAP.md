# RAP e4 on Application Model
## Tutorial
- Chinese https://blog.csdn.net/danpu0978/article/details/106766502 from https://www.javacodegeeks.com/2018/11/eclipse-rap-spring-boot.html


## Eclipse IDE Setup
- Eclipse RCP/RAP IDE
- WindowBuilder 
- e4 Tools Developer Resources 
- RAP e4 Tooling 
- RAP Target Components
- RAP e4 Target Components

## Build RAP App
- [RAP App Sample](https://o7planning.org/10183/eclipse-rap-tutorial-for-beginners-workbench-application)
- [Save/Load Perspective](https://www.vogella.com/tutorials/Eclipse4ModelPersistence/article.html)
- [Eclipse Javadoc](https://javadoc.scijava.org/Eclipse/index.html)
- [Workbench Javadoc](https://javadoc.scijava.org/Eclipse/org/eclipse/e4/ui/workbench/package-tree.html) 
- [Workbench Modeling](https://javadoc.scijava.org/Eclipse/org/eclipse/e4/ui/workbench/modeling/package-summary.html)

| Interface | Description |
|-----------|-------------|
|EModelService 	| find, create and handle model elements |
|EPartService 	| provides clients with the functionalities of showing and hiding parts. |
| EPlaceholderResolver 	| resolve references from MPlaceholders. |
| ESelectionService 	| workbench selection service |

- [Eclipse 4 state and container model](https://javadoc.scijava.org/Eclipse/org/eclipse/e4/ui/model/application/ui/package-summary.html)
- 
| Interface | Description |
|-----------|-------------|
| MContext 	|  A representation of the model object 'Context'. getIEclipseContext() | 
| MCoreExpression 	| A representation of the model object 'Core Expression'.| 
| MDirtyable 	| A representation of the model object 'Dirtyable'.| 
| MElementContainer<T extends MUIElement> 	| A representation of the model object 'Element Container'.| 
| MExpression 	| A representation of the model object 'Expression'.| 
| MGenericStack<T extends MUIElement> 	| A representation of the model object 'Generic Stack'.| 
| MGenericTile<T extends MUIElement> 	| A representation of the model object 'Generic Tile'.| 
| MGenericTrimContainer<T extends MUIElement> 	| A representation of the model object 'Generic Trim Container'.| 
| MImperativeExpression 	| A representation of the model object 'Imperative Expression'.| 
| MLocalizable 	| A representation of the model object 'Localizable'.| 
| MSnippetContainer 	| A representation of the model object 'Snippet Container'.| 
| MUIElement 	| A representation of the model object 'UI Element'. manage the bindings between the concrete element and the UI 'widget' representing it in the UI.| 
| MUiFactory 	| The Factory for the model.| 
| MUILabel 	| A representation of the model object 'UI Label'.| 
    
- [ Eclipse 4 application model elements](https://javadoc.scijava.org/Eclipse/org/eclipse/e4/ui/model/application/package-summary.html)
	
| Interface | Description |
|-----------|-------------|
| MAddon 	| A representation of the model object 'Addon'.| 
| MApplication 	| A representation of the model object 'Application'.| 
| MApplicationElement 	| A representation of the model object 'Element'.| 
| MApplicationFactory 	| The Factory for the model.| 
| MContribution 	| A representation of the model object 'Contribution'.| 
    
- [Eclipse UI](https://javadoc.scijava.org/Eclipse/org/eclipse/ui/package-summary.html)    
The PlatformUI class provides access to a single workbench.  A workbench is the root object for the UI and has one or more workbench windows.  Each workbench window has a collection of workbench pages, only one of which is active and visible to the end user.  Each workbench page has a collection of workbench parts.  A page's parts are arranged (tiled or stacked) for presentation on the screen.  Within a page and its parts the user can interact with and modify a model (typically resources in a workspace).   There are two kinds of workbench parts: views and editors.  An editor is typically used to edit or browse a document or input object.  A view is typically used to navigate a hierarchy of information (like the workspace), open an editor, or display properties for the active editor. 

- [PlatformUI](https://javadoc.scijava.org/Eclipse/org/eclipse/ui/PlatformUI.html)   
The central class for access to the Eclipse Platform User Interface
    - creation of the workbench.
    - access to the workbench.
    
- [IWorkbench](https://javadoc.scijava.org/Eclipse/org/eclipse/ui/IWorkbench.html)
The root object for the Eclipse Platform user interface. It supports a few services:
     - IBindingService
     - ICommandService
     - IContextService
     - IHandlerService
 
    
## Create Project: 
- [RAP Demo](https://www.eclipse.org/rap/demos/)
    - [WorkBench](https://rap.eclipsesource.com/demo/release/workbench/)
     ![workbench](https://s1.o7planning.com/en/10385/images/756956.png) using Plugin project
- [Eclipse Dirigible](https://www.dirigible.io/help/development/)
    - [github](https://github.com/SAP-archive/cloud-dirigible)
- [RAP tutorial](https://o7planning.org/10955/eclipse-rap)
- [Tutorial](https://o7planning.org/10183/eclipse-rap-tutorial-for-beginners-workbench-application)
- [e4 tutorial](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwivj-mLpt33AhVHnHIEHZd2B84QFnoECB4QAQ&url=https%3A%2F%2Ftomsondev.files.wordpress.com%2F2010%2F07%2Ftutorial.pdf&usg=AOvVaw0JxTDRD0WsRADGS1Z37TJa)
File/New/Other... >Plugin Project (No for create a rich cleint application) > RAP e4 Application

- list of built-in command of the RAP framework at:

http://help.eclipse.org/mars/topic/org.eclipse.platform.doc.isv/reference/api/org/eclipse/ui/actions/ActionFactory.html


## Run the application
- Run directly
Right click the project and select:
    Run As/RAP Application

- Configure the port and the default browser to run RAP e4 application:
Right-click the RAPe4Tutorial project and select:
    Run As/Run Configurations... to set the port and browser

## Application Model: Application.e4xmi (e4>Model>new Application Model)
- Addons: Objects instantiated by Eclipse 4's dependency injection framework. They are global and are contained under the application.
- Binding Contexts
- Binding Tables
- Handlers: handling for the commands of Menu or Toolbar by clicking MenuItem or ToolItem
- Commands: Associate Handler to Item (MenuItem and ToolbarItem)
- Command Categories: group of commands
- Windows and Dialogs: TrimmedWindow - A Windows with trimmed MenuBar,and StatusBar
    - Handlers
    - Windows and Dialogs
    - Controls: Windows as parent
    - Shared Elements
    - TrimBars
- Part Contributions
- Menu Contributions
- Toolbar Contributions
- Trim Contributions
- Snippets

## Depoly as WAR
- Use an ApplicationConfiguration to bind different entrypoints to different url-patterns.
```
application.addEntryPoint("/start", MyEntryPoint.class, properties);
application.addEntryPoint("/admin", MyAdminEntryPoint.class, properties);
```
-  bind the RapServlet to all used url-patterns in the web.xml
```
<servlet>
    <servlet-name>RAPServlet</servlet-name>
    <servlet-class>org.eclipse.rwt.internal.engine.RWTDelegate</servlet-class>
</servlet>
<servlet-mapping>
    <servlet-name>RAPServlet</servlet-name>
    <url-pattern>/start</url-pattern>
</servlet-mapping>
<servlet-mapping>
    <servlet-name>RAPServlet</servlet-name>
    <url-pattern>/admin</url-pattern>
</servlet-mapping>
```

### [Command and Handler](https://www.vogella.com/tutorials/EclipseCommands/article.html)

#### Save model elements
Eclipse uses an instance of the IModelResourceHandler interface to load and save the application model at startup and shutdown. The default implementation is provided by the ResourceHandler class from the org.eclipse.e4.ui.internal.workbench package.
```
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import org.eclipse.e4.core.di.annotations.Execute;
import org.eclipse.e4.ui.internal.workbench.E4XMIResourceFactory;
import org.eclipse.e4.ui.model.application.ui.MUIElement;
import org.eclipse.e4.ui.model.application.ui.advanced.MPerspective;
import org.eclipse.e4.ui.model.application.ui.basic.MWindow;
import org.eclipse.e4.ui.workbench.modeling.EModelService;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.widgets.Shell;

public class SavePerspectiveHandler {
    @Execute
    public void execute(EModelService modelService, MWindow window, Shell shell) {
        // store model of the active perspective
        MPerspective activePerspective = modelService.getActivePerspective(window);
        if (activePerspective == null) {
            MessageDialog.openInformation(shell, "No perspective found", "Are you using perspectives?");
            // no perspective found, return
            return;
        }

        // create a resource, which is able to store e4 model elements
        E4XMIResourceFactory e4xmiResourceFactory = new E4XMIResourceFactory();
        Resource resource = e4xmiResourceFactory.createResource(null);

        // You must clone the perspective as snippet, otherwise the running
        // application would break, because the saving process of the resource
        // removes the element from the running application model
        MUIElement clonedPerspective = modelService.cloneElement(activePerspective, window);

        // add the cloned model element to the resource so that it may be stored
        resource.getContents().add((EObject) clonedPerspective);

        try (FileOutputStream outputStream = new FileOutputStream(getFileNameForPersistence())) {
            resource.save(outputStream, null);
            MessageDialog.openInformation(shell, "Persisted perspective", "Persisted as " + getFileNameForPersistence());
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }

     static String getFileNameForPersistence() {
        String currentUsersHomeDir = System.getProperty("user.home");
        return currentUsersHomeDir + File.separator + ".eclipse/perspective.xml";
    }
}
```
####  Load stored model elements
The created xmi file can be loaded via the load method of the Resource class.
```
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.List;

import org.eclipse.e4.core.di.annotations.Execute;
import org.eclipse.e4.ui.internal.workbench.E4XMIResourceFactory;
import org.eclipse.e4.ui.model.application.ui.MElementContainer;
import org.eclipse.e4.ui.model.application.ui.MUIElement;
import org.eclipse.e4.ui.model.application.ui.advanced.MPerspective;
import org.eclipse.e4.ui.model.application.ui.basic.MWindow;
import org.eclipse.e4.ui.workbench.modeling.EModelService;
import org.eclipse.e4.ui.workbench.modeling.EPartService;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.widgets.Shell;

public class ConstructPerspectiveFromExternalSource {
    @Execute
    public void execute(EPartService partService, EModelService modelService, MWindow window, Shell shell) throws IOException {
        // create a resource, which is able to store e4 model elements
        @SuppressWarnings("restriction")
        E4XMIResourceFactory e4xmiResourceFactory = new E4XMIResourceFactory();
        @SuppressWarnings("restriction")
        Resource resource = e4xmiResourceFactory.createResource(null);

        try (FileInputStream inputStream = new FileInputStream(SavePerspectiveHandler.getFileNameForPersistence())) {
            // load the stored model element
            resource.load(inputStream, null);

            if (!resource.getContents().isEmpty()) {
                // after the model element is loaded it can be obtained from the contents of the resource
                MPerspective loadedPerspective = (MPerspective) resource.getContents().get(0);

                // get the parent perspective stack, so that the loaded perspective can be added to it.
                MPerspective activePerspective = modelService.getActivePerspective(window);
                MElementContainer<MUIElement> perspectiveParent = activePerspective.getParent();

                // remove the current perspective, which should be replaced by the loaded one
                List<MPerspective> alreadyPresentPerspective = modelService.findElements(window,
                        loadedPerspective.getElementId(), MPerspective.class, null);
                for (MPerspective perspective : alreadyPresentPerspective) {
                    modelService.removePerspectiveModel(perspective, window);
                }

                // add the loaded perspective and switch to it
                perspectiveParent.getChildren().add(loadedPerspective);

                partService.switchPerspective(loadedPerspective);
                MessageDialog.openInformation(shell, "Perspective resetted", "Resetted perspective");
            }
        }
    }
}
```
#### Clear Perspective
```
public static void cleanPerspectives() {
	final EModelService e = PlatformUI.getWorkbench().getService(EModelService.class);
	final MApplication a = PlatformUI.getWorkbench().getService(MApplication.class);

	final List<PerspectiveImpl> perspectives = e.findElements(a, PerspectiveImpl.class, EModelService.ANYWHERE,
		element -> matches(element.getElementId()));
	for ( final PerspectiveImpl p : perspectives ) {
		// DEBUG.OUT("Dirty perspective implementation found and removed: " + p.getElementId());
		p.getParent().getChildren().remove(p);
	}

	final IPerspectiveRegistry reg = PlatformUI.getWorkbench().getPerspectiveRegistry();
	for ( final IPerspectiveDescriptor desc : reg.getPerspectives() ) {
		if ( matches(desc.getId()) ) {
			// DEBUG.OUT("Dirty perspective descriptor found and removed: " + desc.getId());
			reg.deletePerspective(desc);
		}
	}

	// DEBUG.OUT("Current perspectives: " + listCurrentPerspectives());
}    
```
