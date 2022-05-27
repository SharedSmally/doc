# Eclipse Application
https://eclipsesource.com/blogs/tutorials/your-first-application-based-on-eclipse-faq/amp/

In OSGi, the bundles are managed by the OSGi framework:
![OSGi Application](https://eclipsesource.com/wp-content/uploads/2016/04/image05.png)

## Application Architecture
- Product: Product Definition; Target Platform
    - Project: Feature
        - Package: Plugin (OSGi bundle/MANIFEST.MF + plugin.xml/extension point/extension)
            - Module (api; module; ui; database; json; xml; ...)
            

## Plugin/Bundle
Technically, an OSGi bundle is either a Jar file or an unpacked Jar file (directory). The only difference to a plain Jar is the existence of a file called “MANIFEST.MF” located in a folder “META-INF”. It contains all additional meta-information about a bundle, which is processed by the OSGi runtime. This is mainly: an ID, a version, the dependencies, and packages a bundle is providing to other bundles as API.

“plugin” and “bundle” today actually means the same thing. There is one differentiation: A plugin is something, which extends the Eclipse IDE, while a bundle is part of a general purpose application. There are two artefacts in typical Eclipse “plugins”, the “MANIFEST.MF” as defined by OSGi and the “plugin.xml”, which was the former artifact to define all plugin information such as dependencies. Today, the “plugin.xml” only contains extension points, all other information has moved to the “MANIFEST.MF”. In the Eclipse IDE, select “New” => “Plugin project” to create a new plugin or bundle.

## Feature
Features are a way to organize bundles by grouping them. In a typical Eclipse application, you deal with up to 1000 bundles, it would be hard to manage on that level of granularity. Therefore, bundles are grouped into features which provide a consistent set of functionalities. Features can be further grouped again into other features.

## Product
product, is an artefact to configure a complete application. It is basically a collection of bundles or features, so it defines what is in the final application. Products can be setup with bundles or features. The definition of a product is contained in a file called “Product Definition”, which can be created within Eclipse IDE. Beside the list of bundles or features, a product also contains information about the branding of the final application such as a logo, the splash screen, etc.

## Category: catergory.xml
Create a category definition file (catergory.xml, includes a list of features) for the update site:  File > New > Other ... > Plug-in Development > Category Definition

## Target Platform
Every Eclipse Application project uses a target platform. The custom bundles are located as sources in the workspace, they have some dependencies to other bundles. Those target bundles are needed for compiling and application running. So there needs to be a location to retrieve those “target bundles” from. This location is called “Target Platform” as is defined with a “Target Definition”.

![target platform](https://eclipsesource.com/wp-content/uploads/2016/04/image06.png)

A target definition is basically a collection of locations, where bundles can be retrieved from. All those locations sum up to the target platform.
- The simplest type of location is a plain directory containing the target bundles.
- The second type of location is an update site, that is, a location reachable over HTTP containing the bundles. The update site can be hosted internally, or the official update sites at eclipse.org can be used. 
- The third type of location is an Eclipse installation. This type is very similar to the directory type, it points to the installation directory of an existing Eclipse IDE installation and retrieves the bundles from it.

The Eclipse IDE ships with a default target platform. This is of type “Eclipse Installation” and points to the running IDE itself. That is the IDE you use for development as all Eclipse IDEs contain the most common Eclipse frameworks. 

May use **Oomph** for further project build, it can manage a list of Target Platforms.

![target platform](https://eclipsesource.com/wp-content/uploads/2016/04/image07-768x442.png)


## Platform
- Tool Platform: extensible platform with OSGi + IDE + Extension Point + SDKs
- Application Platform: RCP/RAP;  (OSGi plugin project/select OSGi framework can be converted to Maven project/add pom.xml)
![PLatform](https://eclipsesource.com/wp-content/uploads/2016/04/image09.png) 


## OSGi dependencies

- Bundle-based: managed by “**Required bundles**”. The bundle has a dependency on the other bundle including all its packages.
- Package-based: managed by “**Imported packages**”. The bundle has a dependency on the Java package, only. Therefore, “package imports” are more fine-grained than “required bundles”.

## Set-up a build - Maven Tycho
Tycho is a plugin for maven, which enables two things:
- Building Eclipse-specific artefacts, such as bundles or features
- It uses the informations stored in MANIFEST.MF files, e.g. the dependencies.

Maven has its own way of specifying dependencies in pom.xml. Tycho enables a “Manifest first” approach,
so no need to duplicate the information of the Manifest file in the pom.xml.

These are typically three different types: 
- bundles
- features
- products
![Tycho](https://eclipsesource.com/wp-content/uploads/2016/04/image08.png)
