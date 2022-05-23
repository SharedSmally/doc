# EMF ecore
- [javadoc](https://download.eclipse.org/modeling/emf/emf/javadoc/2.7.0/overview-summary.html)
- [Summary](https://download.eclipse.org/modeling/emf/emf/javadoc/2.7.0/org/eclipse/emf/ecore/package-summary.html)

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

## EditingDomain -> MappingDomain

## EMF Data Management via AdapterFactories
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
