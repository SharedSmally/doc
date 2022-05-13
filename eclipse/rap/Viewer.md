# JFace Viewer
- [javadoc](https://javadoc.scijava.org/Eclipse/org/eclipse/jface/text/package-summary.html)

| package      | Description |
| ----------- | ----------- |
|org.eclipse.jface.viewers 	|Provides a framework for viewers, which are model-based content adapters for SWT widgets.|
|org.eclipse.jface.viewers.deferred 	|Provides a framework for viewers that handle deferred contents.|
| org.eclipse.ui.themes 	| Application programming interfaces for interaction with and extension of the Eclipse Platform User Interface.| 
| org.eclipse.ui.views 	| Application programming interfaces for interaction with and extension of the Eclipse Platform User Interface.| 
| org.eclipse.ui.views.bookmarkexplorer 	| Provides the standard Bookmarks view which displays bookmarks on resources.| 
| org.eclipse.ui.views.contentoutline 	| Provides the standard Content Outline view which can show the active editor's custom outline for the document being edited.| 
| org.eclipse.ui.views.framelist 	| Provides support for a web-browser style of navigation within a view by maintaining a list of frames.| 
| org.eclipse.ui.views.markers 	| Utility classes for working with markers in views| 
 | org.eclipse.ui.views.navigator 	| Provides the standard Resource Navigator view which presents the tree of resources in the workspace.| 
| org.eclipse.ui.views.properties 	| Provides the standard Property Sheet view which displays custom properties of the active workbench part's current selection.| 
| org.eclipse.ui.views.properties.tabbed 	| Provides the Tabbed Properties framework.| 
| org.eclipse.ui.views.tasklist 	| Provides the standard Task List view for displaying tasks and problem annotations on resources.| 


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
