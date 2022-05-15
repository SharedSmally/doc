# Eclipse Platform
The Eclipse platform is structured around the concept of plug-ins. Plug-ins are structured bundles of code and/or data 
that contribute functionality to the system. Functionality can be contributed in the form of code libraries 
(Java classes with public API), platform extensions, or even documentation. Plug-ins can define extension points, 
well-defined places where other plug-ins can add functionality.

![Platform](http://help.eclipse.org/latest/topic/org.eclipse.platform.doc.isv/guide/images/sdk-arch.svg)

The platform runtime core implements the runtime engine that starts the platform base and dynamically discovers and 
runs plug-ins. A plug-in is a structured component that describes itself to the system using an OSGi manifest 
(MANIFEST.MF) file and a plug-in manifest (plugin.xml) file. The platform maintains a registry of installed 
plug-ins and the functionality they provide.

The platform runtime is implemented using the OSGi services model. An Eclipse plug-in is, in effect, an OSGi bundle.

## Runtime 
The Eclipse runtime defines the plug-ins (org.eclipse.osgi and org.eclipse.core.runtime) on which all other plug-ins depend.
The runtime is responsible for defining a structure for plug-ins and the implementation detail (bundles and classloaders) 
behind them. The runtime is also responsible for finding and executing the main Eclipse application and for maintaining a 
registry of plug-ins, their extensions, and extension points.

The runtime also provides an assortment of utilities, such as logging, debug trace options, adapters, a preference store, and 
a concurrency infrastructure. Of course, as a minimal kernel, the runtime is only interesting once plug-ins that make use of 
it and perform some kind of task are created. Like Atlas, the runtime plug-in stoically resides at the bottom of the plug-in 
heap, holding the Eclipse universe aloft on its steady shoulders. 

## Plugins
### Resource management
The resource management plug-in defines a common resource model for managing the artifacts of tool plug-ins. Plug-ins can 
create and modify projects, folders, and files for organizing and storing development artifacts on disk.

###  Workbench UI: SWT/JFace
The workbench UI plug-in implements the workbench UI and defines a number of extension points that allow other plug-ins to 
contribute menu and toolbar actions, drag and drop operations, dialogs, wizards, and custom views and editors.

### Team support
The Team plug-ins allow other plug-ins to define and register implementations for team programming, repository access, and versioning.

### Debug support
The Debug plug-ins allow other plug-ins to implement language specific program launchers and debuggers. 

### Help System
The Help plug-in implements a platform optimized help web server and document integration facility.  
It defines extension points that plug-ins can use to contribute help or other plug-in documentation as browsable books.  
The documentation web server includes special facilities to allow plug-ins to reference files by using logical, 
plug-in based URLs instead of file system URLs.

###  Java development tools (JDT)
The Java development tools (JDT) plug-ins extend the platform workbench by providing specialized features for editing, 
viewing, compiling, debugging, and running Java code.

### Plug-in Development Environment (PDE)
The Plug-in Development Environment (PDE) supplies tools that automate the creation, manipulation, debugging, and deploying of plug-ins.  
