# Views
e4 seperates the application model and the implementation of the application’s parts, such as view.
The application model has no UI toolkit dependencies at all, it can be used for implementing applications 
in other technologies than SWT, for example in JavaFX as provided by the e(fx)clipse project.

## View
In Eclipse 4, views do not have to implement a given interface. Instead, views define the parameters that 
the workbench needs to provide. In one of the simplest cases, an SWT view just requires a parent composite, 
on which the view can be placed. The annotation “@Inject” will be used later on by the Eclipse 4 framework to 
determine if the parameters of the view should be “injected”. 
```
public class ExampleView {
   @Inject
   public ExampleView(Composite parent) {
      Label label = new Label(parent, SWT.NONE);
      label.setText("Hello World!");
   }
}
```
## Application
Using the application model, this view can be shown as part of the workbench in an application:
```
public static void main(String[] args) {
   Display display = new Display();
   Shell shell = new Shell(display);
   shell.setLayout(new FillLayout());
   new ExampleView(shell);
   shell.open();
   while( !shell.isDisposed() ) {
      if( ! display.readAndDispatch() ) {
         display.sleep();
      }
   }
}
```
## Reunion
Bring the application model and view implementation together, by adding an element (“Part”) in the application model 
representing the view within the workbench. The part will be linked to the implementation of the view:
![View](https://eclipsesource.com/wp-content/uploads/2012/06/image07.png)
To link the part to the implementation of the view, the view’s class has to be selected in the properties of the part under “Class URI”. 
![Impl](https://eclipsesource.com/wp-content/uploads/2012/06/image06.png)

## Handlers
Handler is triggered by a button in the toolbar of the application. They are the components, define some specific behavior to be triggered.

In Eclipse 4, handlers don’t have to implement a given interface. Instead, they define the required parameters. 
This is the implementation of a very basic handler for opening a “Hello World!” dialog. The handler needs only one parameter, a shell, to open the dialog.
```
public class MyHandler {
   @Execute
   public static void execute(Shell shell){
      MessageDialog.openInformation(shell, "", "Hello World!");
   }
}
```
The testing application:
```
public static void main(String[] args) {
   Display display = new Display();
   Shell shell = new Shell(display);
   shell.open();
   MyHandler.execute(shell);
   while( !shell.isDisposed() ) {
      if( ! display.readAndDispatch() ) {
         display.sleep();
      }
   }
}
```

To integrate the handler with a button in a toolbar, it needs another element in the application model. 
The easiest way to integrate the handler is using a "Direct ToolItem". The ToolItem is placed in the 
ToolBar and therefore specifies, that there is another button to be clicked.
![Handler](https://eclipsesource.com/wp-content/uploads/2012/06/adddirecttoolitem.png)

Using a "Direct ToolItem" is the fastest way to integrate a handler with an item in the toolbar. 
Using commands and handlers is more flexibility and better reuse. This enables to have alternative 
implementations of a certain user action and also to use key bindings for triggering handlers.
![Commands](https://eclipsesource.com/wp-content/uploads/2012/06/image14.png)

items and handlers reference a certain command and are thereby bound to each other. It is possible to bind several 
items to the same command, e.g. to show an action in a menu and in a toolbar at the same time. It is also possible 
to bind multiple handlers to the same command providing alternative implementations of an action, but only one handler
must be active at the same time. The Eclipse 4 Application platform will automatically activate handlers in the current application context
![Links](https://eclipsesource.com/wp-content/uploads/2012/06/image09.png)

After all three elements are created, both the handler and the item need to be bound to the command. Commands can now be reused within the 
application, as an example, key bindings can be used to trigger the execution of a command or other items can be bound to it.
![CmdLinks](https://eclipsesource.com/wp-content/uploads/2012/06/image13.png)

