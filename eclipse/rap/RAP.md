# Eclipse Remote Application Platform - RAP 

## Eclipse 3.x 
- WorkBench
- Extension for Plugin: 
    - Extension points

## Eclipse 4.x: e4 using DI (Dependency Injection)
- [Eclipse API doc](https://javadoc.scijava.org/Eclipse/index.html)
     - di
     - ui
         - model
              - application
                  - [commands](https://javadoc.scijava.org/Eclipse/org/eclipse/e4/ui/model/application/commands/package-summary.html)
- Tools with Eclipse J2EE
    - WindowBuilder
    - e4 Tools Developer Resources
    - RAP e4 Tooling
    - RAP Target Components
    - RAP e4 Target Components
- Tutorial
    - [Eclipse 4 (e4) Tutorial - EclipseSource](https://eclipsesource.com/about/contact-us/eclipse-4-tutorial-pdf-download/)
    - [Eclipse RCP 4 Tutorial for Beginners](https://o7planning.org/10181/eclipse-rcp-tutorial-for-beginners-workbench-application)
- Application Model: *Application.e4xmi*
     separate application model and implementations(using Inject to get it needs)
- extension for Plugins:
    - model fragments: a small application model that defines elements added to the root application model 
    - model processors: programmtically extend the application model

## Application Model
- Addon
To participate in dependency injection with customized Java objects, they can be added as model add-ons to the application model. The classes referred to by the model add-ons can access and modify the IEclipseContext or interact with other services, e.g., the event system.
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
- Binding Contexts
- Bindin Tables
- Handlers
- Commands
- Command Categories
- Windows and Dialogs
- Part Descriptors
- Menu Contributions
- Toolbar Contributions
- Trim Contributions
- Snippets

## DI

## Addons
- [e4 context](https://www.vogella.com/tutorials/Eclipse4ContextUsage/article.html)
using @Inject, IEclipseContext and MContext.

If a model object implements MContext, can use dependency injection to get the model object injected and call the getContext() method to access its context. For example, MPart, MWindow, MDialog,MApplication and MPerspective extend MContext.

## Services

## Application Model components
- Handler: need declare the ID, Handler class and Command.
The classes handling for the commands of Menu or Toolbar. When MenuItem or ToolItem is clicked,it means the call to execute a command, 
Handler will be executed before the Command is executed, can cancel the command is executed in Handler.

Handler is the classes that when executed, it will execute the task is written in method annotated by @Execute.
```
import org.eclipse.e4.core.di.annotations.Execute;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.widgets.Shell;
public class AboutHandler { 
   @Execute
   public void execute(Shell shell) {
       MessageDialog.openInformation(shell, "About", "Eclipse 4 RCP Application");
   }
}
```
- Command
- Item (MenuItem;ToolbarItem)
- Part: A new Panel
```
import javax.annotation.PostConstruct;
import javax.inject.Inject;

import org.eclipse.e4.ui.di.Focus;
import org.eclipse.e4.ui.di.Persist;
import org.eclipse.e4.ui.model.application.ui.MDirtyable;
import org.eclipse.jface.viewers.TableViewer;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Text;

public class SamplePart {
    private Text txtInput;
    private TableViewer tableViewer;

    @Inject
    private MDirtyable dirty;

    @PostConstruct
    public void createComposite(Composite parent) {
        parent.setLayout(new GridLayout(1, false));

        txtInput = new Text(parent, SWT.BORDER);
        txtInput.setMessage("Enter text to mark part as dirty");
        txtInput.addModifyListener(new ModifyListener() {
            @Override
            public void modifyText(ModifyEvent e) {
                dirty.setDirty(true);
            }
        });
        txtInput.setLayoutData(new GridData(GridData.FILL_HORIZONTAL));

        tableViewer = new TableViewer(parent);

        tableViewer.add("Sample item 1");
        tableViewer.add("Sample item 2");
        tableViewer.add("Sample item 3");
        tableViewer.add("Sample item 4");
        tableViewer.add("Sample item 5");
        tableViewer.getTable().setLayoutData(new GridData(GridData.FILL_BOTH));
    }

    @Focus
    public void setFocus() {
        tableViewer.getTable().setFocus();
    }

    @Persist
    public void save() {
        dirty.setDirty(false);
    }
}
```
