# Eclipse Application
https://eclipsesource.com/blogs/tutorials/your-first-application-based-on-eclipse-faq/amp/

In OSGi, the bundles are managed by the OSGi framework:
![OSGi Application](https://eclipsesource.com/wp-content/uploads/2016/04/image05.png)

## Application Architecture
- Product: Product Definition; Target Platform
    - Project: Feature
        - Package: Plugin (OSGi bundle/MANIFEST.MF + plugin.xml/extension point/extension)
            - Module (api; module; ui; database; json; xml; ...)
            

## OSGi
Technically, an OSGi bundle is either a Jar file or an unpacked Jar file (directory). The only difference to a plain Jar is the existence of a file called “MANIFEST.MF” located in a folder “META-INF”. It contains all additional meta-information about a bundle, which is processed by the OSGi runtime. This is mainly: an ID, a version, the dependencies, and packages a bundle is providing to other bundles as API.

“plugin” and “bundle” today actually means the same thing. There is one differentiation: A plugin is something, which extends the Eclipse IDE, while a bundle is part of a general purpose application. There are two artefacts in typical Eclipse “plugins”, the “MANIFEST.MF” as defined by OSGi and the “plugin.xml”, which was the former artifact to define all plugin information such as dependencies. Today, the “plugin.xml” only contains extension points, all other information has moved to the “MANIFEST.MF”. In the Eclipse IDE, select “New” => “Plugin project” to create a new plugin or bundle.

Features are a way to organize bundles by grouping them. In a typical Eclipse application, you deal with up to 1000 bundles, it would be hard to manage on that level of granularity. Therefore, bundles are grouped into features which provide a consistent set of functionalities. Features can be further grouped again into other features.


- Tool Platform: extensible platform with OSGi + IDE + Extension Point + SDKs
- Application Platform: RCP/RAP
![PLatform](https://eclipsesource.com/wp-content/uploads/2016/04/image09.png) 
