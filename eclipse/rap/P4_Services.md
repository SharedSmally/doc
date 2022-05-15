# Services
Dependency injection is the technique to get access to certain objects to be used in a class. 
One type of objects to retrieve using dependency injection are services.

Eclipse 4 import services: 
- the selection service (ESelectionService)
- the model service (EModelService) 
- the part service (EPartService). 

In Eclipse 3.x:
```
PlatformUI.getWorkbench().getActiveWorkbenchWindow().getSelectionService().getSelection();
```
In Eclipse 4.x, instead of providing one big API, framework features have been split into a number of services. 
Every Eclipse 4 service has a specific focus, e.g., managing the selection or dealing with parts and perspectives. 
All services can be accessed using dependency injection. For example for the selection service:
```
@Inject
ESelectionService selectionService;
```

## Selection Service (ESelectionService)
The selection service is responsible for managing the active selection of an application. The selection of an application is 
typically an object a user can select from a view, e.g., a file for a file browser or an e-mail in an e-mail application. 
There are two different users of the selection service:
- Selection providers are elements that set the active selection. 
- Selection providers are typically UI elements that allow the user to select an element, e.g., a tree viewer. 
The selection is then forwarded to the selection service. Selection consumers are interested in the element currently 
selected in an application. For example, the enabling of a handler can be dependent on the current selection. Thus, 
the enabling of the handler “Export File” could only be enabled if the current selection is a file.
![Selection](https://eclipsesource.com/wp-content/uploads/2013/09/image00.png)

