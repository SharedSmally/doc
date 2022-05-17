# Eclipse Plugin
- [Plugin components](https://www.euclideanspace.com/software/development/eclipse/plugin/index.htm)


An Eclipse project consists of a hierarchy of files in a workspace.

In order to have an active running program we need to translate these files to resources in memory. 

There are 2 types of URI:
- Identify resources.
- Identify java classes.

Eclipse Application Model
- Perspectives
- Parts (views + Editors)
- Menus
- Toolbars
- Handlers
- Commands
- Key Bindings

URIs which identify resources (associated with a file) have the form:

"platform:/plugin/"+Bundle-SymbolicName+/path to file/filename.

Where Bundle-SymbolicName is from MANIFEST.MF file. 

## OSGi Bundle
Eclipse bundles together extension points into XML file(s) using an OSGi standard.

The files involved are: 
- META-INF/MANIFEST.MF:
```
Manifest-Version: 1.0
Bundle-ManifestVersion: 2
Bundle-Name: %Bundle-Name
Bundle-SymbolicName: com.euclideanspace.spad.builder;singleton:=true
Bundle-Version: 1.0.0.qualifier
Bundle-Activator: com.euclideanspace.spad.builder.Activator
Bundle-Vendor: %Bundle-Vendor
Require-Bundle: org.eclipse.ui,
	   org.eclipse.core.runtime,
	   org.eclipse.ui.ide;bundle-version="3.8.0",
	   org.eclipse.core.resources;bundle-version="3.8.0"
Bundle-RequiredExecutionEnvironment: JavaSE-1.6
Bundle-ActivationPolicy: lazy
```

- OSGI-INF/l10n/bundle.properties

A '.properties' file contains key-value pairs. For instance the MANIFEST.MF file above references 'Bundle-Name' and 'Bundle-Vendor' from this file. 
```
#Properties file for com.euclideanspace.spad.builder
category.name = SPAD
wizard.name = SPAD project
Bundle-Vendor = EUCLIDEANSPACE
Bundle-Name = SPAD Builder
```

- build.properties
```
source.. = src/
output.. = bin/
bin.includes = META-INF/,\
               .,\
               plugin.xml,\
               OSGI-INF/l10n/bundle.properties
```

- plugin.xml
```
<?xml version="1.0" encoding="UTF-8"?>
 <?eclipse version="3.4"?>
<plugin>
  <extension
          point="org.eclipse.ui.newWizards">
  <category
          id="com.euclideanspace.spad.builder.category.wizards"
          name="%category.name">
  </category>
  <wizard
          category="com.euclideanspace.spad.builder.category.wizards"
          class="com.euclideanspace.spad.builder.BuilderNewWizard"
          id="builder.wizard.new.custom"
          name="%wizard.name">
  </wizard>
  </extension>
        </plugin>
```
## Read Bundle Resource
```
ResourceBundle rb = ResourceBundle.getBundle("test.bundletest.mybundle");
		Enumeration  keys = rb.getKeys();
		while (keys.hasMoreElements()) {
			String key = keys.nextElement();
			String value = rb.getString(key);
			System.out.println(key + ": " + value);
		}
```
