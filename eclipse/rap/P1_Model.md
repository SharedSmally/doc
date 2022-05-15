# Application Model: 

In Eclipse 4, the workbench is defined in Application Model. It includes windows, views, perspectives, menu contributions, 
handlers and key bindings. The model define the general design or “skeleton” of the application. Defining a model doesn’t 
already require to implement the single components. It separates the general workbench design and the implementation of single parts.

## Windows, Parts and PartContainers
The cornerstones of the application model are windows, parts and part containers. e4 has combined views and editors into the concept of Parts,
which represent views inside a window. If a part is added in the model, it can be connected to the implementation of the selected view later.

![Application Model](https://eclipsesource.com/wp-content/uploads/2012/05/image18.png)

Parts cannot exist on their own, they are always contained in PartContainers. Those PartContainers create an application layout.
Besides windows, there are two elements which can contain Parts: 
- PartSashes: arrange contained elements either vertically or horizontally.  
- PartStacks. adds an area, where the contained elements are stacked behind each other, only one element is shown on top.
PartSash and PartStack can contain each other to create any kind of layout within a window. 
![Parts](https://eclipsesource.com/wp-content/uploads/2012/05/image17.png)

## Creating an e4 Application: 
Create a e4 project using the “Eclipse 4 Application Project” entry within the “New Project” wizard. for Plugin Project 

## Edit Application Model
Edit Application.e4xmi using e4 Model Editor

## Model Spy (Live Editing)
Model Spy is a special version of the Model Editor, allows to access the application model of a running application, modify it and 
highlight selected components. The Model Spy is not yet part of the standard Eclipse Packages, it can be installed from the e4 update site.

Do not make the Model Spy a permanent part of the application, so it should not be added to the product. Instead, open the run 
configuration and add the bundle “” to it. Additionally click on “Add required” to include the required dependencies. 
In the running application you can start the live editor via ALT+SHIFT+F9. 

## Development vs. Runtime Model
![Model](https://eclipsesource.com/wp-content/uploads/2012/05/image29.png)
During runtime, there is a Java Object for every element of the deserialized Application Model, the EMF objects (EObjects). By using the EMF API 
to create or modify parts of the application programmatically, such as reacting to a user action. For example for class OpenHandler, there is a 
method execute() marked with the annotation @Execute, which will be called if the connected ToolItem is clicked by the user.

The Java Objects (interfaces) to access the Application Model at runtime are all prefixed with a "M", for example to access a Window using the 
interface "MWindow" or a Part using the interface "MPart".

```
@ Execute
public void execute(MApplication application) {
   MWindow mWindow = MBasicFactory.INSTANCE.createTrimmedWindow();
   mWindow.setHeight(200);
   mWindow.setWidth(400);
   mWindow.getChildren().add(MBasicFactory.INSTANCE.createPart());
   application.getChildren().add(mWindow);
}
```
