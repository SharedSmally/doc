# eclipse platform
- [eclipse javadoc](https://javadoc.scijava.org/Eclipse/index.html)
- [IBM eclipse javadoc](https://www.ibm.com/docs/tr/rational-soft-arch/9.6.1?topic=r-api-reference)
- [Platform javadoc](https://www.ibm.com/docs/tr/rational-soft-arch/9.6.1?topic=reference-orgeclipsecoreresources)
- [Platform maven](https://mvnrepository.com/artifact/org.eclipse.platform)
- [RAP maven]https://mvnrepository.com/artifact/org.eclipse.rap)
- [eclipse project](https://projects.eclipse.org/)

The Eclipse platform is written using Java and a Java VM is required to run it. It is built from small units of functionality called plugins. 
Plugins are the basis of the Eclipse component model. A plugin is essentially a JAR file with a manifest which describes itself, 
its dependencies, and how it can be utilized, or extended. This manifest information was initially stored in a plug-in.xml file which 
resides in the root of the plugin directory. 

In order to encourage people to build upon the Eclipse platform, there needs to be a mechanism to make a contribution to the platform, and 
for the platform to accept this contribution. This is achieved through the use of extensions and extension points, another element of the 
Eclipse component model. The export identifies the interfaces that you expect others to use when writing their extensions, which limits 
the classes that are available outside your plugin to the ones that are exported. It also provides additional limitations on the resources 
that are available outside the plugin, as opposed to making all public methods or classes available to consumers. 
Exported plugins are considered public API.

![eclipse 3.0](https://www.aosabook.org/images/eclipse/rcp.png)

Eclipse 3.0 Architecture

The Eclipse 3.x Workbench UI was originally structured as a thin extension layer atop JFace/SWT. 
JFace/SWT provided the mechanisms for managing a UI (e.g., resource registries, windows and dialogs, key bindings), 
and the workbench defined various extension points for plugins to extend and customize the workbench. 
Over time, additional areas of functionality were added to the workbench, including theming support, control over 
the visibility of UI elements, accessing additional services.


![eclipse 4.0](https://wiki.eclipse.org/images/thumb/8/80/Eclipse_4_Architecture.png/640px-Eclipse_4_Architecture.png)

Eclipse 4.0 Architecture

Eclipse 4 breaks the workbench layer into two parts: a new Eclipse 4 Application Platform that builds on top of JFace/SWT, 
and a re-implementation of the Eclipse 3.x Workbench APIs on top of this new Eclipse 4 Application Platform. 

The original Workbench UI model has been simplified and is now represented through an EMF-based model. The model is 
entirely public, and allows programatic access to the UI model. This access means that a plugin could easily provide code 
to split an editor stack, or move a part from one part of the window.

Eclipse 4 uses CSS to providing theming support.Rather than having to through navigate a chain of objects, services are 
now provided using Dependency Injection (DI).


## Eclipse 4 Applicatin Platform - E4AP

![e4AP model](http://jaxenter.com/wp-content/uploads/2012/11/Eclipse-4-Workbench.png)

E4 application model

## eclipse javadoc
- compare
- core
    - command
    - databinding
    - filesystem
    - resources
    - runtime
- debug
- unittest
- equinox
    - app
    - p2
    - http
    - jsp
    - security
- osgi

### services
- help
- jsch
- ltk
- search
- team
- update

### eclipse ui 
- e4
    - core.di
    - ui.di
    - ui.model
    - ui.service
    - ui.worbench
- jface
    - text
- swt
- ui
    - editor
    - view
    - form
