# Eclipse DataBinding

## Tutorial:
- [JFace Data Binding ](https://www.vogella.com/tutorials/EclipseDataBinding/article.html)

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

## IObserverable



The **IObservableValue** interface is the basis for observing properties in JFace. 
The **Properties** API provides factories to create IObservableValue objects. 

| Factory |	Description |
|PojoProperties|Used to create IObservableValue for Java objects. The term Pojo (Plain old Java object) is used to describe a Java object which does not implement a specific framework API.|
|BeanProperties|Used for Java Beans. A Java Bean is a Java object which follows the Java Bean specification. This specification requires that the class implements getter and setter methods for all its attributes. It must also implement property change support via the PropertyChangeSupport class and propagate changes to registered listeners.|
|WidgetProperties|Used for properties of SWT widgets.|
|ViewerProperties|	Used for properties of JFace Viewer.|
|Properties|Used for properties of non specialized types, like Objects, Collections or Maps.|
|Observables|Used for properties of special Objects, Collections, Maps and Entries of an IObservableMap.|


## Binding


## BindContext
