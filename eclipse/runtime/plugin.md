# PDE - Plugin Development Environment

## Tutorial
- [Plug-ins, Features, Update Sites and IDE Extensions](https://www.vogella.com/tutorials/EclipsePlugin/article.html)

## Concepts
- Plugin: the basic OSGi Bundle using MANIFEST.MF with plugin.xml: the exntensions and extension points
- Feature: Reference a list of plugins in feature.xml file:  **File > New > Other > Plug-in Development > Feature Project**. A list of plugins
- Product: Product configuration for a feature in \*.product: **File > New > Othe > Plug-in Development > Product Configuration**: 
- Category: Reference a feature in category.xml: **File > New > Other > Plug-in development > Category Definition**
- Update Site: for plugin/feature in site.xml: **File > Export > Deployable features**
- Extension Point schema
- Component Configuration: for OSGi services
- Traget Platform: what to be included and where to get the dependencies
- Run Configuration: 

## Update Site: site.xml 
Final build procedure to generate jar files
- Add the features to be published on the site
- Browse the siite, and categorize the features
- Build the features

## Category Definition
Group and Organize the plugins and features
- Organize which plugins and features belong in each category
- Specify additional repositories that can be searched for content

## Product definition
How to start the product
- Contents: list all the plugins and fragments that constitute the product
- Configuration:
- Lauching: Execution environment; Program Launcher; Icon
- Spash Icon
- Branding: Icon; About Dialog; Welcome page
- Customization
- Licensing
- Updates

## Target Platform 
Where to get the dependencies
- [Tutorial](https://www.modumind.com/2009/09/01/creating-an-eclipse-rcp-target-platform/)

Target platform definitiion outlines what should be included in the product and where the features and bundles can be located. It can also be checked in to the version control repository and shared among the members of your team. Eclipse 3.5 supports four types of locations:
- directories
- installations
- features
- software sites. 

Typically, an RCP application needs to set the target platform to the Eclipse RCP SDK which is made up of two features (RAP with e4):
- org.eclipse.rcp
- org.eclipse.rcp.source

Start by clicking **Add** in the Target Definition Editor. Then select **Software Site** on the Add Content dialog and click **Next**.

## Feature
- feature project: 
    - feature.xml
        - information, includeing copyright, license
        - included plugins
        - included features
        - Dependencies
    - build.properties
- feature patch:

Need reference to an existing feature, the same structure as Feature project.

## Fragment project
Need reference to an existing plugin as the host. The same structure as Plugin.


## Plugin 
The basic unit for Eclipse application, similar to the Bundle in OSGi.

### Extension Point Schema
Define the extension point for the plugin

### Component Definition
Component (Service) used/handled by the OSGi framework (in BundleContext)

### plugin.xml contents

The plug-in manifest file, **plugin.xml**, describes how the plug-in extends the platform, what extensions it publishes itself, and how it implements its functionality.
- **Dependencies**: list all the plug-ins required on the classpth to compile and run
- **Runtime**: list the libraries for the runtime of this plugin
- **Extensions**: delares contributions this plugin makes to the platform
- **Extension Points**: declare new functions piints this plugin adds to the platform

### make executable plugin:
Run the plugin outside eclipse - launch as a stand alone application(
- Create an Eclipse RCP product, then export this product and run as an application.
    - RCP
    - Prodcut config
    - Product Export
```
public static void main(String[] args) {
    Display display = new Display();
    Shell shell = new Shell(display);
    shell.setSize(0, 0);
    shell.setVisible(false);
    shell.open();

    WizardDialog dialog = new WizardDialog(shell, new __YOUR_WIZARD());
    dialog.open();

    shell.dispose();
    display.dispose();
}
```
- Create Java project and add the following 12 plugin jars as referenced libraries
    - org.eclipse.osgi
    - org.eclipse.core.commands 
    - org.eclipse.equinox.common
    - org.eclipse.equinox.registry
    - org.eclipse.core.runtime
    - org.eclipse.text
    - org.eclipse.swt.win32.win32.x86_64
    - org.eclipse.jface,eclipse.jface.text
    - org.eclipe.ui.workbench
    - com.ibm.icu_50.1.1
    - org.eclipse.ui.forms
    
This will work out for any SWT application that need to be launched directly without any RCP product.This can also be done via a tool "Windows Builder" wherein the dependencies are automatically added when a SWT/JFACE Java project is created

### [When to start](https://wiki.eclipse.org/FAQ_When_does_a_plug-in_get_started%3F)
A plug-in can be activated in three ways:
    - If a plug-in contributes an executable extension, another plug-in may run it, causing the plug-in to be automatically loaded. It is in IExecutableExtension in the org.eclipse.core.runtime package.
    - If a plug-in exports one of its libraries (JAR files), another plug-in can reference and instantiate its classes directly. Loading a class belonging to a plug-in causes it to be started automatically.
    - a plug-in can be activated explicitly, using the API method Platform.getPlugin(). This method returns a fully initialized plug-in instance.

Should not activate the plug-in when the workbench starts, for lazy plug-in activation is very important in a platform with an open-ended set of plug-ins.
Can use the org.eclipse.ui.startup extension point to activate the plug-in as soon as the workbench starts up.

The startup extension point allows to specify a class that implements the IStartup interface. If the class is omitted from the extension, the Plugin subclass will be used and therefore must implement IStartup. This class will be loaded in a background thread after the workbench starts, and its earlyStartup method will be run. The Plugin class will be loaded first, and its startup method will be called before any other classes are loaded. The earlyStartup method essentially distinguish eager activation from normal plug-in activation. 
