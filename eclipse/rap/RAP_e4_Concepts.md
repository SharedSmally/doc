# RAP Tutorial: 1-7
https://eclipsesource.com/blogs/2012/05/10/eclipse-4-final-sprint-part-1-the-e4-application-model/

## Application Model vs. Views
In Eclipse 4, the workbench is defined in the so-called Application Model. This includes windows, views, 
perspectives, menu contributions, handlers and key bindings. Using the model you define the general design 
or “skeleton” of your application. Defining a model doesn’t already require that you implement the single 
components. For example, you can add a view to the model without implementing its contents. 
The implementation of the parts can use SWT or JavaFX.

## Windows, Parts and PartContainers
The cornerstones of the application model are windows, parts and part containers. e4 has combined views 
and editors into the concept of Parts, which represent views inside a window. A part added in the model
can be connected to the implementation of the selected view.

Trimmed Window is the Window with MenuBar, StatusBar

![Model-Implementation](https://eclipsesource.com/wp-content/uploads/2012/05/image18.png)

Parts are the controls, they cannot exist on their own, they are always contained in PartContainers. 
Those PartContainers create an application layout. Besides windows, there are two elements which can contain Parts: 

- PartSashes:  arrange contained elements either vertically or horizontally
- PartStacks: adds an area, where the contained elements are stacked behind each other, only one element is shown on top.

PartSash and PartStack can contain each other to create any kind of layout within a window. 

