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


## Command

## EditingDomain -> MappingDomain

## EMF Data Management
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
