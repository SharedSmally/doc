# Ecore Resource

## Tutorial:
- [EMF - Persisting models via XMI](https://www.vogella.com/tutorials/EclipseEMFPersistence/article.html)
- [EMF javadoc](https://download.eclipse.org/modeling/emf/emf/javadoc/2.7.0/overview-summary.html)

## Ecore Resource API
| package | description |
|---------|-------------|
|org.eclipse.emf.ecore 	| Provides an API for the Ecore dialect of UML.|
|org.eclipse.emf.ecore.impl |	Provides an implementation of Ecore.|

| interface | description |
|-----------|-------------|
|Resource.Factory.Registry |	A registry of resource factories.|
|EPackage.Registry |	A map from namespace URI to EPackage.|
|EValidator.Registry |	A map from EPackage to EValidator.|

- Interface Resource.Factory.Registry
| interface | description |
|-----------|-------------|
| static Resource.Factory.Registry 	INSTANCE | The global static resource factory registry. |
|Map<String,Object> 	getContentTypeToFactoryMap() |   Returns a map from content type identifier to Resource.Factory or Resource.Factory.Descriptor.|
|Map<String,Object> 	getExtensionToFactoryMap() |     Returns a map from file extension to Resource.Factory or Resource.Factory.Descriptor.|
|Map<String,Object> 	getProtocolToFactoryMap()| Returns a map from protocol to Resource.Factory or Resource.Factory.Descriptor.|
|Resource.Factory 	getFactory(URI uri) |      Returns the resource factory appropriate for the given URI.|
|Resource.Factory 	getFactory(URI uri, String contentType) |    Returns the resource factory appropriate for the given URI with the given content type identifier.|

- Interface Resource.Factory
| method    | description |
|-----------|-------------|
|  Resource 	createResource(URI uri) |  Creates a resource with the given URI and returns it. |

- Interface Resource.Factory
| method    | description |
|-----------|-------------|
| void 	load(InputStream inputStream, Map<?,?> options) | Loads the resource from the input stream using the specified options.|
| void 	load(Map<?,?> options)| Loads the resource using the specified options.|
| void 	save(Map<?,?> options) | Saves the resource using the specified options.|
| void 	save(OutputStream outputStream, java.util.Map<?,?> options)|Saves the resource to the output stream using the specified options.|
| TreeIterator<EObject>	getAllContents() | Returns a tree iterator that iterates over all the direct contents and indirect contents of this resource.|
| EList<EObject> 	getContents() |  Returns the list of the direct content objects; each is of type EObject.|
| EObject	getEObject(String uriFragment) |    Returns the resolved object for the given URI fragment.|
| ResourceSet 	getResourceSet()|  Returns the containing resource set.|
  
          


- Resource Hiarchy (Resource for save/load)
| Resource  | Resource Implementaion | ResourceFactory Implementation|
|-----------|------------------------|-------------------------------|
|Notifier   |BasicNotifierImpl:NotifierImpl |
|Resource   |ResourceImpl:BinaryResourceImpl| Factory; | ResourceFactoryImpl |
|XMLResource |XMLResourceImpl:GenericXMLResourceImpl, XMLTypeResourceImpl|XMLResourceFactoryImpl; GenericXMLResourceFactoryImpl|
|XMIResource |XMIResourceImpl:Ecore2EcoreResourceImpl, EMOFResourceImpl|XMIResourceFactoryImpl:Ecore2EcoreResourceFactoryImpl, , EcoreResourceFactoryImpl, EMOFResourceFactoryImpl|
|Ecore2XMLResource| Ecore2XMLResourceImpl|Ecore2XMLResourceFactoryImpl|
  

      , , , , 
  

 


## Sample
- Save the model
```
import java.io.IOException;
import java.util.Collections;
import java.util.Map;

import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;

import datamodel.*;

public class CreateSaveTester {
    public static void main(String[] args) {
        // Initialize the datamodel for the package
        WebsitePackage.eINSTANCE.eClass();
        // Retrieve the default factory singleton
        WebsiteFactory factory = WebsiteFactory.eINSTANCE;

        // create the content of the model via this program
        MyWeb myWeb = factory.createMyWeb();
        Webpage page = factory.createWebpage();
        page.setXxx("index");
        myWeb.getPages().add(page);

        // As of here we preparing to save the model content
        // Register the XMI resource factory for the .website extension
        Resource.Factory.Registry reg = Resource.Factory.Registry.INSTANCE;
        Map<String, Object> m = reg.getExtensionToFactoryMap();
        m.put("website", new XMIResourceFactoryImpl());

        // Obtain a new resource set
        ResourceSet resSet = new ResourceSetImpl();

        // create a resource via website extension
        Resource resource = resSet.createResource(URI.createURI("website/My2.website"));
        // Get the first model element and cast it to the right type
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
- Load an existing model
```
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
        // Get the first model element and cast it to the right type
        MyWeb myWeb = (MyWeb) resource.getContents().get(0);
        return myWeb;
    }
}
```
- Encryption
```
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.impl.AESCipherImpl;
import org.eclipse.emf.ecore.xmi.XMIResource;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;

public class MyXMIFactoryImpl extends XMIResourceFactoryImpl {
    @Override
    public Resource createResource(URI uri) {
        XMIResourceFactoryImpl resFactory = new XMIResourceFactoryImpl();
        XMIResource resource = (XMIResource) resFactory.createResource(uri);
        try {
            resource.getDefaultLoadOptions().put(Resource.OPTION_CIPHER,new AESCipherImpl("12345"));
            resource.getDefaultSaveOptions().put(Resource.OPTION_CIPHER,new AESCipherImpl("12345"));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return resource;
    }
}
```
