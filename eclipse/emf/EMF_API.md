# EMF - Eclipse Modeling Framework
EMF consists of three fundamental pieces:
- EMF - The core EMF framework includes a meta model (Ecore) for describing models and runtime support for 
   the models including change notification, persistence support with default XMI serialization, and a very 
   efficient reflective API for manipulating EMF objects generically.
- EMF.Edit - The EMF.Edit framework includes generic reusable classes for building editors for EMF models. 
   It provides Content and label provider classes, property source support, and other convenience classes that
   allow EMF models to be displayed using standard desktop (JFace) viewers and property sheets.
        A command framework, including a set of generic command implementation classes for building editors 
        that support fully automatic undo and redo.
- EMF.Codegen - The EMF code generation facility is capable of generating everything needed to build a 
   complete editor for an EMF model. It includes a GUI from which generation options can be specified, 
   and generators can be invoked.

## Tutorial
- [Eclipse Help](https://help.eclipse.org/latest/index.jsp)
- [javadoc](https://www.eclipse.org/modeling/emf/javadoc/)

## EMF Tools
- Ecore model
- EMF Generator Model (from Ecore, xsd, Rational Rose, etc) to generate code
- EMF Project
