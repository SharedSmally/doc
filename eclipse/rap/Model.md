# Application Model

##  e4 Notes
https://www.vogella.com/tutorials/Eclipse4Notes/article.html
https://www.codeaffine.com/2011/08/26/raprwt-osgi-integration/

### Workbench XMI file
The base workbench model for the Eclipse IDE is defined in the "org.eclipse.ui.workbench" plug-in in the "LegacyIDE.e4xmi" file. In the org.eclipse.platform plug-in you find the LegacyIDE.e4xmi file which defines the initial window and some model Add-ons.

If Eclipse is started in the compatibility mode, this file is read via the E4Workbench class. This class is part of the org.eclipse.e4.workbench.ui.internal package. E4Workbench will then convert the relevant extension points into elements of the application model.


### Eclipse 4 application - E4Application

The org.eclipse.e4.ui.workbench.swt.E4Application application is defined in the extension point org.eclipse.core.runtime.applications in the org.eclipse.e4.ui.workbench.swt plug-in.

It points to the org.eclipse.e4.ui.internal.workbench.swt.E4Application class which implements the IApplication interface.

The E4Application class, reads the parameter passed to the application, evaluates the model and builds up the context. The loadApplicationModel(IApplicationContext appContext, IEclipseContext eclipseContex) method will load the initial application. The createE4Workbench IApplicationContext applicationContext, Display display) method will process the whole model.

### Model Resource Handler
The org.eclipse.e4.ui.internal.workbench.ResourceHandler class is responsible for loading and saving the model. The loadBaseModel() method will load the Application.e4xmi model.

### ModelAssembler
- ModelAssembler class processes the model fragments and processors in its methods.
- ContributionsAnalyzer class is a class with lots of static method to analyse things like the visibility of MenuItems.

## Classes

| package | description |
|---------|-------------|
| org.eclipse.e4.ui.di 	| Application programming interfaces describing the Eclipse 4 dependency injection annotations.| 
| org.eclipse.e4.ui.model.application 	| Application programming interfaces describing the Eclipse 4 application model elements.| 
| org.eclipse.e4.ui.model.application.commands 	 | Application commands |
| org.eclipse.e4.ui.model.application.descriptor.basic 	| Application programming interfaces describing the Eclipse 4 descriptor model elements.
| org.eclipse.e4.ui.model.application.ui 	| Application programming interfaces describing the Eclipse 4 state and container model elements.| 
| org.eclipse.e4.ui.model.application.ui.advanced 	| Application programming interfaces describing the advanced Eclipse 4 user interface model elements.| 
| org.eclipse.e4.ui.model.application.ui.basic 	| Application programming interfaces describing the basic Eclipse 4 user interface model elements.| 
| org.eclipse.e4.ui.model.application.ui.menu 	| Application programming interfaces describing the Eclipse 4 menu and toolbar model elements.| 
| org.eclipse.e4.ui.model.fragment 	| Application programming interfaces describing the Eclipse 4 fragment model elements.| 
| org.eclipse.e4.ui.services 	| Application programming interfaces describing the Eclipse 4 context service.|

## org.eclipse.e4.ui.model.application.commands
| Interface | 	Description | 
| --------------|---------|
| MBindingContext 	| A representation of the model object 'Binding Context'.| 
| MBindings 	| A representation of the model object 'Bindings'.| 
| MBindingTable 	| A representation of the model object 'Binding Table'.| 
| MBindingTableContainer 	| A representation of the model object 'Binding Table Container'.| 
| MCategory 	| A representation of the model object 'Category'.| 
| MCommand 	| A representation of the model object 'Command'.| 
| MCommandParameter 	| A representation of the model object 'Command Parameter'.| 
| MCommandsFactory 	| The Factory for the model.| 
| MHandler 	| A representation of the model object 'Handler'.| 
| MHandlerContainer 	| A representation of the model object 'Handler Container'.| 
| MKeyBinding 	| A representation of the model object 'Key Binding'.| 
| MKeySequence 	| A representation of the model object 'Key Sequence'.| 
| MParameter 	| A representation of the model object 'Parameter'.| 
