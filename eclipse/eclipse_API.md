# eclipse platform
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


![eclipse 4.0](https://www.aosabook.org/images/eclipse/rcp.png](https://wiki.eclipse.org/images/thumb/8/80/Eclipse_4_Architecture.png/640px-Eclipse_4_Architecture.png)

Eclipse 4.0 Architecture

## [eclipse javadoc](https://javadoc.scijava.org/Eclipse/index.html)
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
- jface.text
- swt
- ui
    - editor
    - view
    - form
