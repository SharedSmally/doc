# Data Binding
- [javadoc](https://javadoc.scijava.org/Eclipse/index.html)
Provides classes for binding observable objects, for example UI widgets and model objects. It can be used to synchronize state between pairs of observable objects with optional data type conversion and validation.

A DataBindingContext is used to manage a list of Bindings with their validation results. 

| package | description |
|---------|-------------|
|org.eclipse.core.databinding 	|Provides classes for binding observable objects, for example UI widgets and model objects.|
|org.eclipse.core.databinding.beans 	|Provides classes for observing JavaBeans(tm) objects.|
|org.eclipse.core.databinding.conversion 	|Provides interfaces and classes for data type conversion.|
|org.eclipse.core.databinding.observable 	|Provides the core APIs for observing changes in objects.|
|org.eclipse.core.databinding.observable.list 	|Provides classes for observing changes in lists.|
|org.eclipse.core.databinding.observable.map 	|Provides classes that can be used to observe changes in maps.|
|org.eclipse.core.databinding.observable.masterdetail 	|Provides classes that can be used to observe a detail of a master object.|
|org.eclipse.core.databinding.observable.set 	|Provides classes that can be used to observe changes in sets.|
|org.eclipse.core.databinding.observable.value 	|Provides classes that can be used to observe changes in discrete values.|
|org.eclipse.core.databinding.property 	|Interfaces and classes for representing and observing properties of objects.|
|org.eclipse.core.databinding.property.list ||
|org.eclipse.core.databinding.property.map 	 ||
|org.eclipse.core.databinding.property.set 	 | |
|org.eclipse.core.databinding.property.value 	|| 
|org.eclipse.core.databinding.util 	|Provides general utilities for data binding.|
|org.eclipse.core.databinding.validation 	|Provides the core APIs for validation.|

- [Binding](https://javadoc.scijava.org/Eclipse/org/eclipse/core/databinding/Binding.html):  a binding between a model and a target.
- [DataBindingContext](https://javadoc.scijava.org/Eclipse/org/eclipse/core/databinding/DataBindingContext.html)
- [IObservable](https://javadoc.scijava.org/Eclipse/org/eclipse/core/databinding/observable/IObservable.html)
- [IChangeListener](https://javadoc.scijava.org/Eclipse/org/eclipse/core/databinding/observable/IChangeListener.html)
