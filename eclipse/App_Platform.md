# Eclipse 
- [Help](https://help.eclipse.org/latest/index.jsp)
- [Eclipse Platform Maven](https://mvnrepository.com/artifact/org.eclipse.platform)

## Eclipse Platform
- core
  - runtime
  - resources
  - filesystem; filebuffer
  - expression
  - commands; jobs
  - databinding
  - help
  - team
- equinox: OSGi implementation
  - p2
- emf: core
- e4: Application Plaform
-   Application Model
-   DI container
-   CSS
- ui
  - rap/rcp:
    - jface: High level Widgets
    - rwt/swt: Widget Toolkits

![Architecture](https://wiki.eclipse.org/images/thumb/8/80/Eclipse_4_Architecture.png/640px-Eclipse_4_Architecture.png)


![rcp vs rap](https://owenou.com/assets/images/posts/rap_archi.png)


## [contributorURI vs contributionURI](https://tomsondev.bestsolution.at/2015/09/25/eclipse-4-application-platform-contributoruri-vs-contributionuri/)
All Eclipse 4 applications leverage the Eclipse 4 application model who is a representation of the whole application in a well defined and typesafe 
EMF-Model (similar browsers DOM).

The model itself is not static but a so called live model and you can interact with it through your preferred VM-Language eg to add new elements. 
One of the things done most often is to programmatically add MPart instances to represent your UI-Component.
```
public static class DefaultEditorOpener implements EditorOpener {
  @Inject
  EModelService modelService;
 
  @Inject
  @Service
  List<FileIconProvider> fileIconProvider;
 
  @Override
  public boolean openEditor(String uri) {
    // .....
    MPart part = modelService.createModelElement(MPart.class);
    part.setCloseable(true);
    part.setLabel(URI.create(uri).lastSegment());
    part.setContributionURI("bundleclass://org.eclipse.fx.code.editor.fx/org.eclipse.fx.code.editor.fx.TextEditor");
    part.setContributorURI("platform:/plugin/org.eclipse.fx.code.editor.fx.e4");
 
    String iconUri = fileIconProvider
      .stream()
      .filter( f -> f.test(uri))
      .findFirst()
      .map( f -> f.getFileIconUri(uri))
      .orElse("platform:/plugin/org.eclipse.fx.code.editor.fx.e4/icons/file_16.png");
    part.setIconURI(iconUri);
    part.getPersistedState().put(Constants.DOCUMENT_URL, uri);
    part.getTags().add(EPartService.REMOVE_ON_HIDE_TAG);
    // .....
  }
}
```
2 very similar MPart attributes:
- contributionURI: URI to identify the class that is responsible to create the MParts UI
- contributorURI: URI to identify the bundle who create the model element, used to retrieve the ResourceBundle through the BundleLocalization-Service.

