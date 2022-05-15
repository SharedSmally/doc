# EMF - Eclipse Modeling Framework
EMF is a Java framework and code generation facility for building tools and other applications based on a structured model. 
It uses XMI (XML Metadata Interchange) as its canonical form of a model definition. 

EMF consists of two fundamental frameworks: the core framework and EMF.Edit. The core framework provides basic generation 
and runtime support to create Java implementation classes for a model. EMF.Edit extends and builds on the core framework, 
adding support for generating adapter classes that enable viewing and command-based (undoable) editing of a model, and 
even a basic working model editor. 

Get the model into that form:
- Use a modeling tool that works with EMF
- Create the XMI document directly, using an XML or text editor
- Export the XMI document from a modeling tool such as Rational Rose
- Annotate Java interfaces with model properties
- Use XML Schema to describe the form of a serialization of the model

The model interface (inherits from EObject) and implementation can be generated from the model.

## Relationship
- One-way references

![one-way](http://help.eclipse.org/latest/topic/org.eclipse.emf.doc/references/overview/images/EMF/image002.gif)

In interface Book:
```
  Writer getAuthor();
  void setAuthor(Writer value);
```

- Two-way references

![two-way](http://help.eclipse.org/latest/topic/org.eclipse.emf.doc/references/overview/images/EMF/image003.gif)


- Multiplicity-many references
```
  public interface Writer extends EObject
  {
    ...
    EList getBooks();
  }
```

- Containment references
A class, Library act as the container for Books:

![containment](http://help.eclipse.org/latest/topic/org.eclipse.emf.doc/references/overview/images/EMF/image004.gif)

The containment reference is indicated by the black diamond on the Library end of the association. 
In full, the association indicates that a Library aggregates, by value, 0 or more Books. 
By-value aggregation (containment) associations are particularly important because they identify 
the parent or owner of a target instance, which implies the physical location of the object when persisted. 

If you want to avoid the downcast, you can change the association to be explicitly two-way instead: 

![downcast](http://help.eclipse.org/latest/topic/org.eclipse.emf.doc/references/overview/images/EMF/image005.gif)

- Enumeration attributes

![enum](http://help.eclipse.org/latest/topic/org.eclipse.emf.doc/references/overview/images/EMF/image006.gif)

- Factories and packages
```
public interface LibraryFactory extends EFactory {
    LibraryFactory eINSTANCE = new LibraryFactoryImpl();
    Book createBook();
    Writer createWriter();
    Library createLibrary();
    LibraryPackage getLibraryPackage();
}
```

- Generating classes with super classes

![inheraritance](http://help.eclipse.org/latest/topic/org.eclipse.emf.doc/references/overview/images/EMF/image007.gif)

Multiple interface inheritance is supported, but each EMF class can only extend one implementation base class.

![multipleInheritance](http://help.eclipse.org/latest/topic/org.eclipse.emf.doc/references/overview/images/EMF/image008.gif)
```
  public interface SchoolBook extends Book, Asset
```
or
```
  public class SchoolBookImpl extends BookImpl implements SchoolBook
```

- Operations in EMF models

In addition to attributes and references, you can add operations to your model classes. The EMF generator will generate 
their signature into the interface and a method skeleton into the implementation class. EMF does not model behavior, 
so the implementation must be provided by user-written Java code. 

- Observing (adapting) EMF objects

In the set methods in generated EMF classes, the notifications are always sent when an attribute or reference is changed. 
```
  eNotify(newENotificationImpl(this, ..., oldPages, pages));
```

- Data types
All the classes defined in a model implicitly derive from the EMF base class EObject. However, all the classes that a model 
uses are not necessarily EObjects. We need to define an EMF DataType to represent the external type (import datatype).

![Data types](http://help.eclipse.org/latest/topic/org.eclipse.emf.doc/references/overview/images/EMF/image009.gif)

## Ecore Model

![Ecore Model](http://help.eclipse.org/latest/topic/org.eclipse.emf.doc/references/overview/images/EMF/image011.gif)
