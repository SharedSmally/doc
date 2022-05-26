# Eclipse DataBinding

## Tutorial:
- [JFace Data Binding ](https://www.vogella.com/tutorials/EclipseDataBinding/article.html)
- [Data Binding HOWTO](https://wiki.eclipse.org/Data_Binding_HOWTO)

Originally there are 2 objects, source (model) and target(viewer), Make them IObserverable, and Binding together,
When one side is update, another side will be updated automatically. The binding could be one-side or two-side.
The main purpose for the new package is to provide the Factories to create the IObserverable from the target viewer object.

## Maven
- org.eclipse.core » org.eclipse.core.databinding
- org.eclipse.core » org.eclipse.core.databinding.beans
- org.eclipse.core.databinding » property
- org.eclipse.core.databinding » observable
- org.eclipse.core.databinding » beans
- org.eclipse.jface » org.eclipse.jface.databinding 
- at.bestsolution.efxclipse.rt » org.eclipse.fx.core.databinding

## DataBinding Packages
| Package | Description |
|---------|-------------|
|org.eclipse.core.databinding 	|Provides classes for binding observable objects, for example UI widgets and model objects.|
|org.eclipse.core.databinding.beans 	|Provides classes for observing JavaBeans objects.|
|org.eclipse.core.databinding.conversion 	|Provides interfaces and classes for data type conversion.|
|org.eclipse.core.databinding.observable 	|Provides the core APIs for observing changes in objects.|
|org.eclipse.core.databinding.observable.list 	|Provides classes for observing changes in lists.|
|org.eclipse.core.databinding.observable.map 	|Provides classes that can be used to observe changes in maps.|
|org.eclipse.core.databinding.observable.masterdetail 	|Provides classes that can be used to observe a detail of a master object.|
|org.eclipse.core.databinding.observable.set 	|Provides classes that can be used to observe changes in sets.|
|org.eclipse.core.databinding.observable.value 	|Provides classes that can be used to observe changes in discrete values.|
|org.eclipse.core.databinding.property 	|Interfaces and classes for representing and observing properties of objects.|
|org.eclipse.core.databinding.property.list  ||
|org.eclipse.core.databinding.property.map 	 ||
|org.eclipse.core.databinding.property.set 	 ||
|org.eclipse.core.databinding.property.value ||
|org.eclipse.core.databinding.util 	|Provides general utilities for data binding.|
|org.eclipse.core.databinding.validation 	|Provides the core APIs for validation.|
|org.eclipse.ui.databinding|APIs for Workbench properties and observables for use with data binding Package Specification |


## IObservable 
An object with state that allows to listen for state changes: **add/removeListener(xxxListener)**

Implementations must not manage listeners themselves, listener management must be delegated to a private instance of type ChangeSupport if it is not inherited from AbstractObservable. 

##  IObservable Factories: Create IObservable 

The **IObservableValue** interface is the basis for observing properties in JFace. 
The **Properties** API provides factories to create IObservableValue objects. 

| Factory |	Description |
|---------|-------------|
|PojoProperties|Used to create IObservableValue for Java objects. Pojo is a Java object which does not implement a specific framework API.|
|BeanProperties|Used for Java Beans: the class implements getter and setter methods for all its attributes, implement property change support via the PropertyChangeSupport class and propagate changes to registered listeners.|
|WidgetProperties|Used for properties of SWT widgets.|
|ViewerProperties|	Used for properties of JFace Viewer.|
|Properties|Used for properties of non specialized types, like Objects, Collections, List, Sets, Maps.|
|Observables|Used for properties of special Objects, Collections, Maps and Entries of an IObservableMap.|
|WorkbenchObservables 	|Factory methods for creating observables for Workbench objects|
|WorkbenchProperties 	|Factory methods for creating properties for the Workbench.|

## Binding
This abstract class represents a binding between a model and a target. 

| Factory |	Description |
|---------|-------------|
|Binding(IObservable target, IObservable model) 	|Creates a new binding.|
|void 	dispose() 	|Disposes of this Binding.|
|IObservable 	getModel() 	|Returns the model observable|
|IObservableList<IObservable> 	getModels() 	|Returns an IObservableList containing the model observables (if any) that are being tracked by this validation status provider.|
|IObservable 	getTarget() 	|Returns the target observable|
|IObservableList<IObservable> 	getTargets() 	|Returns an IObservableList containing the target observables (if any) that are being tracked by this validation status provider.|
|void 	init(DataBindingContext context) 	|Initializes this binding with the given context and adds it to the list of bindings of the context.|
|protected abstract void 	postInit() 	|Called by init(DataBindingContext) after adding this binding to the context.|
|protected abstract void 	preInit() 	|Called by init(DataBindingContext) after setting context but before adding this binding to the context.|
|abstract void 	updateModelToTarget() 	|Updates the target's state from the model's state at the next reasonable opportunity.|
|abstract void 	updateTargetToModel() 	|Updates the model's state from the target's state at the next reasonable opportunity.|
|abstract void 	validateModelToTarget() 	|Validates the model's state at the next reasonable opportunity.|
|abstract void 	validateTargetToModel() 	|Validates the target's state at the next reasonable opportunity.|

## DataBindingContext
A DataBindingContext is the point of contact for the creation and management of bindings, and aggregates validation statuses of its bindings, or more generally, its validation status providers. 

 A DataBindingContext provides the following abilities:
- Ability to create bindings between observable values.
- Ability to create bindings between observable lists.
- Access to the bindings created by the instance.
- Access to the list of validation status providers (this includes all bindings). 
  
## Interface IConverter<F,T>
| Method |	Description |
|---------|-------------|
|static <F,T> IConverter<F,T> 	create(Object fromType, Object toType, Function<F,T> conversion) |	Creates a converter which calls the argument conversion function.|
|static <F,T> IConverter<F,T> 	create(Function<F,T> conversion) |	Creates an untyped converter which calls the argument conversion function.  |
|T 	convert(F fromObject) 	|Returns the result of the conversion of the given object.|
|Object 	getFromType() 	|Returns the type whose instances can be converted by this converter.|
|Object 	getToType() 	|Returns the type to which this converter can convert.|
  
## Interface IValidator<T>
A validator is responsible for determining if a given value is valid. Validators can be used on target or model values
| Method |	Description |
|---------|-------------|
|IStatus 	validate(T value) 	|Determines if the given value is valid.  |
IStatus: OK, CANCEL, ERROR, INFO, WARNING 

