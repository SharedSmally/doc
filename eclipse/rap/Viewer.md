

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
