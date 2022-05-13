# JFace Text
- [javadoc](https://javadoc.scijava.org/Eclipse/org/eclipse/jface/text/package-summary.html)

| package      | Description |
| ----------- | ----------- |
| org.eclipse.jface.text 	| Provides a framework for creating and manipulating text documents.|
|org.eclipse.jface.text.contentassist 	|Provides a content assist add-on for an ITextViewer.|
|org.eclipse.jface.text.formatter 	|Provides a content formatter add-on for an ITextViewer.|
|org.eclipse.jface.text.hyperlink 	|Provides support for detecting and displaying hyperlinks in ISourceViewers.|
|org.eclipse.jface.text.information 	|Provides an information provider add-on for an ITextViewer.|
|org.eclipse.jface.text.link 	|Application programming interfaces for interaction with the Eclipse text editor's linked position support.|
|org.eclipse.jface.text.presentation 	|Provides a presentation reconciler add-on for an ITextViewer.|
|org.eclipse.jface.text.projection 	|This package provides an implementation of projection documents.|
|org.eclipse.jface.text.quickassist 	|This package provides the quick assist assistant add-on for an ISourceViewer.|
|org.eclipse.jface.text.reconciler 	|Provides a reconciler add-on for an ITextViewer.|
|org.eclipse.jface.text.revisions 	|Provides a revision model and a protocol to display revision information in a vertical ruler column.|
|org.eclipse.jface.text.rules 	|Provides a framework for rule based text scanning and uses the framework to provide rule-driven default implementations of IPresentationDamager, IPresentationRepairer and IDocumentPartitioner.|
|org.eclipse.jface.text.source 	|Provides a framework for connecting document regions with annotations and for displaying those.|
|org.eclipse.jface.text.source.projection 	|This package provides the UI part for projection documents of which the most important part is the projection viewer.|
|org.eclipse.jface.text.templates 	|Application programming interfaces for interaction with the Eclipse text template support.|
|org.eclipse.jface.text.templates.persistence 	|Provides persistence support for templates.|
|org.eclipse.jface.viewers 	|Provides a framework for viewers, which are model-based content adapters for SWT widgets.|
|org.eclipse.jface.viewers.deferred 	|Provides a framework for viewers that handle deferred contents.|


## [Viewer](https://javadoc.scijava.org/Eclipse/org/eclipse/jface/viewers/package-summary.html)
A viewer is a model-based adapter on an SWT widget.  Each viewer has four parts:
- an input - the object that serves as the viewer's model
- a widget - the SWT control through which the viewer's model is displayed
- a content provider - mediates between the model and viewer
- a label provider - maps model objects to displayable labels containing text and/or an image

The framework consists of abstract base classes for viewers (Viewer, StructuredViewer, AbstractTreeViewer) together with concrete viewer classes (ListViewer, TreeViewer, TableViewer, TableTreeViewer, CheckboxTreeViewer, and CheckboxTableViewer), and various lesser support classes. 

In general terms, creating a viewer involves the following steps:
- instantiating a viewer on some pre-existing SWT widget,
- setting the viewer's content provider (an object implementing IContentProvider),
- setting the viewer's label provider (an object implementing ILabelProvider),
- setting the viewer's input.

### Viewer Interface and Class
- [Viewer](https://javadoc.scijava.org/Eclipse/org/eclipse/jface/viewers/Viewer.html)
- [ContentViewer](https://javadoc.scijava.org/Eclipse/org/eclipse/jface/viewers/ContentViewer.html)
- [IContentProvider](https://javadoc.scijava.org/Eclipse/org/eclipse/jface/viewers/IContentProvider.html)
- [IBaseLabelProvider](https://javadoc.scijava.org/Eclipse/org/eclipse/jface/viewers/IBaseLabelProvider.html)
- [ILabelProvider](https://javadoc.scijava.org/Eclipse/org/eclipse/jface/viewers/ILabelProvider.html): provide the text and/or image for the label of a given element.
