## Eclipse
- Eclipse 4
     - Classes
         - New Addon Class
         - New Handler Class
         - New Part Class
         - New Tool Control Class
     - Model
         - New Application Model
         - New Model Fragment

FAQ: https://stackoverflow.com/questions/27919913/how-to-create-view-via-fragment-that-is-linked-to-applicatio-model-eclipse-plugi

### Application

In order to have an application model to contribute to, we first need an Eclipse4 application project. 
Create one by selecting File -> New -> Other from the Eclipse main menu. Choose the wizard Eclipse 4 Application Project 
in the Eclipse 4 category. Name your project as you wish, choose Equinox as OSGI framework, and check the Generate an Activator... option. 
The newly created project will contain a file Application.e4xmi (your application model) and a \*.product file (product definition). 
Open the latter in and make sure org.eclipse.e4.ui.workbench.swt.E4Application is set as Application in the Overview tab.

Open Application.e4xmi and append a Part Stack somewhere in the model tree.

### Model fragment

Create a new plugin for the model fragment. Letting it have an Activator class won't harm. It is important, however, 
that the options Activate this plug-in when one of its classes is loaded and This plug-in is a singleton are both checked in the 
Overview tab of its plugin.xml editor. Next, create a model fragment with New -> Other... -> Eclipse 4 -> Model -> New Model Fragment 
in the plugin's Package Explorer context menu. The wizard will automatically create an extension of org.bbaw.bts.ui.pdr.fragment 
specifying your model fragment file. The plugin's dependencies should include:
- org.eclipse.swt
- org.eclipse.jface
- org.eclipse.e4.core.di
- org.eclipse.e4.ui.workbench
- javax.inject
- org.eclipse.e4.ui.di

Open the model fragment file (fragment.e4xmi by default) and attach a Model Fragment to the Model Fragments node. Your new Model 
Fragment element needs to specify both an Element ID and a Featurename in order to correctly address the Application Model's element 
that you want to contribute to. Thus, copy the ID of the Part Stack previously created in the Application Model into the Element ID 
field of the Model Fragment you've just created. In the Featurename field, type children, as this is the Part stack's attribute we 
want to contribute to. Then, append a Part to the Model Fragment element and specify the Class URI of the Part's implementation. 
This class is basically a POJO, no implementation of ViewPart is necessary! It creates its GUI in a method annotated with the 
@PostConstruct annotation, e.g.
```
@PostConstruct
public final void createComposite(final Composite parent)
```
That should be it. When running the application project's product, the Part should appear like expected (given the plugin containing 
that Part is included in the run configuration...). 

## Window Builder
- Project Pallette
- Swing Designer
- SWT Designer
    -  SWT/JFace Java Project
    -  Databinding
         -  JFace Automatic Databinding
    -  Eclipse 4
         - ViewPart  
    -  Forms
         - Composite 
         - DetailsPage
         - FormPage
         - MasterDetailsBlock
         - SectionPart
         - ViewPart
    -  JFace
         - ApplicationWindows
         - Dialog
         - TitleAreaDialog
         - Wizard
         - WizardPage
    -  RCP
         - ActionBarAdvisor
         - EditorPart
         - MultiPageEditorPart
         - PageBookViewOage
         - Perspective
         - PerferencePage
         - PropertyPage
         - ViewPart
    -  SWT
         - Application Window
         - Composite
         - Dialog
         - Shell

## User Assistance
- Cheat Sheet
- Context Help
- Help Table of Contents
