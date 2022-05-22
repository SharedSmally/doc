# PDE - Plugin Development Environment

## Tutorial
- [Plug-ins, Features, Update Sites and IDE Extensions](https://www.vogella.com/tutorials/EclipsePlugin/article.html)

## Concepts
- Plugin: the basic OSGi Bundle using MANIFEST.MF with plugin.xml
- Feature: Reference a list of plugins in feature.xml file:  File > New > Other > Plug-in Development > Feature Project
- Product: Product configuration for a feature in \*.product: File > New > Othe > Plug-in Development > Product Configuration
- Category Definition: Reference a feature in category.xml: File > New > Other > Plug-in development > Category Definition
- Update Site: for plugin/feature: File > Export > Deployable features
- Extension Point schema
- Component Configuration: for OSGi services
- Traget Platform: Running platform
- Run Configuration: 

## plugin.xml
The plug-in manifest file, plugin.xml, describes how the plug-in extends the platform, what extensions it publishes itself, and how it implements its functionality.
- [When to start](https://wiki.eclipse.org/FAQ_When_does_a_plug-in_get_started%3F)
a plug-in can be activated in three ways.
    - If a plug-in contributes an executable extension, another plug-in may run it, causing the plug-in to be automatically loaded. It is in IExecutableExtension in the org.eclipse.core.runtime package.
    - If a plug-in exports one of its libraries (JAR files), another plug-in can reference and instantiate its classes directly. Loading a class belonging to a plug-in causes it to be started automatically.
    - a plug-in can be activated explicitly, using the API method Platform.getPlugin(). This method returns a fully initialized plug-in instance.

Should not activate the plug-in when the workbench starts, for lazy plug-in activation is very important in a platform with an open-ended set of plug-ins.
Can use the org.eclipse.ui.startup extension point to activate the plug-in as soon as the workbench starts up.

The startup extension point allows to specify a class that implements the IStartup interface. If the class is omitted from the extension, the Plugin subclass will be used and therefore must implement IStartup. This class will be loaded in a background thread after the workbench starts, and its earlyStartup method will be run. The Plugin class will be loaded first, and its startup method will be called before any other classes are loaded. The earlyStartup method essentially distinguish eager activation from normal plug-in activation. 

### plugin.xml contents
- **Dependencies**: list all the plug-ins required on the classpth to compile and run
- **Runtime**: list the libraries for the runtime of this plugin
- **Extensions**: delares contributions this plugin makes to the platform
- **Extension Points**: declare new functions piints this plugin adds to the platform
