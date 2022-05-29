# EMF ecore
- [javadoc](https://download.eclipse.org/modeling/emf/emf/javadoc/2.7.0/overview-summary.html)
- [Summary](https://download.eclipse.org/modeling/emf/emf/javadoc/2.7.0/org/eclipse/emf/ecore/package-summary.html)
- [Persistence](https://www.vogella.com/tutorials/EclipseEMFPersistence/article.html)

EMF ecore hierarchy:
![components](https://download.eclipse.org/modeling/emf/emf/javadoc/2.7.0/org/eclipse/emf/ecore/doc-files/EcoreHierarchy.gif))

EMF RelationShips

![relationship](https://download.eclipse.org/modeling/emf/emf/javadoc/2.7.0/org/eclipse/emf/ecore/EClassifier.html)

EPackage > EClass > EAttribute > EReference
                  > EOpeartion > EParameter
         > EEnum > EnnumLiteral
         > EDataType
         > EAnnotaion
         > EClassifer
         > EFactory
         > EGenericType
ETypedElement
ETypeParameter
EStructuralFeature
EValidator

EcorePackage > EcoreFactory (EPackage and EFactory for Model)

##
- org.eclipse.emf.ecore.provider: XxxItemProvider for ecore.
- org.eclipse.emf.edit.domain: manage a set of Model and Commands to modify them, EditingDomain/AdapterFactoryEditingDomain
- org.eclipse.emf.edit.provider: xxxItemProvider for Widgets

## Command

## Model Persistence

EMF allows to store the model content via the EMF persistence framework. EMF provides XMI and XML persistence provider. By default EMF uses XMI (XML Metadata Interchange). XMI is a standard for exchanging metadata information via Extensible Markup Language (XML).

If persistent an EMF object all dependent object will automatically be persistent. Objects which do not have a "contains relationship" must be added explicitly to the resource.getContents().add(). If objects are not added and not included in a contains relationship an exception is thrown when calling the resource.save() method.

EMF has the possibility to encrypt the data model before writing it and to decrypt it before loading. 

- Save Model

```
import java.io.IOException;
import java.util.Collections;
import java.util.Map;

import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;

import datamodel.website.MyWeb;
import datamodel.website.Webpage;
import datamodel.website.WebsiteFactory;
import datamodel.website.WebsitePackage;
import datamodel.website.impl.WebsitePackageImpl;

public class CreateSaveTester {
    public static void main(String[] args) {
        // Initialize the model
        WebsitePackage.eINSTANCE.eClass();
        // Retrieve the default factory singleton
        WebsiteFactory factory = WebsiteFactory.eINSTANCE;

        // create the content of the model via this program
        MyWeb myWeb = factory.createMyWeb();
        Webpage page = factory.createWebpage();
        page.setName("index");
        page.setDescription("Main webpage");
        page.setKeywords("Eclipse, EMF");
        page.setTitle("Eclipse EMF");
        myWeb.getPages().add(page);

        // As of here we preparing to save the model content

        // Register the XMI resource factory for the .website extension
        Resource.Factory.Registry reg = Resource.Factory.Registry.INSTANCE;
        Map<String, Object> m = reg.getExtensionToFactoryMap();
        m.put("website", new XMIResourceFactoryImpl());

        // Obtain a new resource set
        ResourceSet resSet = new ResourceSetImpl();

        // create a resource
        Resource resource = resSet.createResource(URI.createURI("website/My2.website"));
        // Get the first model element and cast it to the right type, in my
        // example everything is hierarchical included in this first node
        resource.getContents().add(myWeb);

        // now save the content.
        try {
            resource.save(Collections.EMPTY_MAP);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
```
- Load Model
```
import java.util.Map;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;

import datamodel.website.MyWeb;
import datamodel.website.WebsitePackage;
import datamodel.website.impl.WebsitePackageImpl;

public class EMFModelLoad {
    public MyWeb load() {
        // Initialize the model
        WebsitePackage.eINSTANCE.eClass();

        // Register the XMI resource factory for the .website extension
        Resource.Factory.Registry reg = Resource.Factory.Registry.INSTANCE;
        Map<String, Object> m = reg.getExtensionToFactoryMap();
        m.put("website", new XMIResourceFactoryImpl());

        // Obtain a new resource set
        ResourceSet resSet = new ResourceSetImpl();

        // Get the resource
        Resource resource = resSet.getResource(URI.createURI("website/My.website"), true);
        // Get the first model element and cast it to the right type, in my
        // example everything is hierarchical included in this first node
        MyWeb myWeb = (MyWeb) resource.getContents().get(0);
        return myWeb;
    }
}
```
## EMF Features

### EditingDomain -> MappingDomain

### EMF Listener

### EMF Data Management
First, create an editing domain. An editing domain manages a set of interrelated models and the commands that 
are run to modify them. For example, it contains the stack of all former commands. An editing domain can create 
a resource, which is a container for storing EObjects. Resources can be saved and loaded and contents can be added to them. 
```
@Override
protected void loadContent(IFile file) throws IOException {
  // Load Tournament from file and set it with setTournament
  AdapterFactoryEditingDomain domain = new AdapterFactoryEditingDomain(
      getAdapterFactory(), new BasicCommandStack());
  resource = domain.createResource(file.getFullPath().toString());
  resource.load(null);
  EObject eObject = resource.getContents().get(0);
  setTournament((Tournament) eObject);
}
@Override
protected void save() throws IOException { // save changes in the file
   resource.save(null);
}
@Override
protected void addMatchup() { // add a new Matchup using a Command
 Matchup matchup = BowlingFactory.eINSTANCE.createMatchup();
 EditingDomain editingDomain = AdapterFactoryEditingDomain.getEditingDomainFor(getTournament());
 Command command = AddCommand.create(editingDomain, getTournament(),
             BowlingPackage.eINSTANCE.getTournament_Matchups(), matchup);
 editingDomain.getCommandStack().execute(command);
}
@Override
protected void undo() {  // Undo the last change
  AdapterFactoryEditingDomain.getEditingDomainFor(getTournament()).getCommandStack().undo();
}

@Override
protected void initializeTreeviewer(TreeViewer treeViewer) {
  // initialize a TreeViewer to show the Matchups and Games of the opened Tournament
  AdapterFactoryLabelProvider labelProvider = new AdapterFactoryLabelProvider(getAdapterFactory());
  AdapterFactoryContentProvider contentProvider = new AdapterFactoryContentProvider(getAdapterFactory());
  treeViewer.setLabelProvider(labelProvider);
  treeViewer.setContentProvider(contentProvider);
  treeViewer.setInput(getTournament());
}
```
EMF allows you to generate a maximum of four different plugins for a defined model:
- Model: The model contains all entities, packages and factories to create instances of the model.
- Edit: The edit plugin contains providers to display a model in a UI. For example, the providers offer a label for every model element, which can be used to display an entity showing an icon and a name.
- Editor: The editor plugin is a generated example editor to create and modify instances of a model.
- Test: The test plugin contains templates to write tests for a model.

### AdapterFactories
The basic function of AdapterFactories is to provide you with the interface you need for a certain purpose such as an ILabelProvider needed in the UI. EMF generates a lot of these classes for you. To retrieve the right class, you can use an AdapterFactory implementation of the interface you need, e.g., an AdapterFactoryLabelProvider. The AdapterFactoryLabelProvider will retrieve the generated LabelProviders for all EObjects using an AdapterFactory.

## Mapping: model/edit/editor
- frameworkd
- ecore to ecore mapping
- ecore to xml mapping
```
1. metamodel #1, described by an ecore-file
2. metamodel #2, described by an ecore-file
3. an ecore2ecore mapping-file
```
