# Text editor: org.eclipse.ui.texteditor
- [javadoc](https://javadoc.scijava.org/Eclipse/org/eclipse/ui/texteditor/package-summary.html): 
Provides a framework for text editors obeying to the desktop rules. 

| package | description |
|---------|-------------|
 |org.eclipse.ui.texteditor 	 |Provides a framework for text editors obeying to the desktop rules. |
 |org.eclipse.ui.texteditor.link 	 |Adds a LinkedModeUI subclass that is aware of workbench editors. |
 |org.eclipse.ui.texteditor.quickdiff 	 |Provides interfaces to for the org.eclipse.ui.editors.quickDiffReferenceProvider extension point and adds an action to enable quick diff display for an editor. |
 |org.eclipse.ui.texteditor.rulers 	 |Provides interfaces and classes for the org.eclipse.ui.workbench.texteditor.rulerColumns. |
 |org.eclipse.ui.texteditor.spelling 	 |Partial infrastructure for spell checking in text editors. |
 |org.eclipse.ui.texteditor.templates 	 |Application programming interfaces for interaction with the Eclipse text editor template support. |


ITextEditor extends IEditorPart with text editor specific functionality. 
Text editors use source viewers (ISourceViewer) for displaying and editing the given editor input. 
In order to translate the editor input into a document and vice versa (e.g., for saving a change), 
a text editor uses document providers (IDocumentProvider). A document provider is responsible not 
just for providing the document for a given editor input but for the complete translation between 
the domain model and the editor's internal document-based model. Document provider can be shared between editors.

The package provides a default implementation of ITextEditor (AbstractTextEditor). 
This default implementation also covers the editor's complete action management and activation. 
The package contains a number of configurable and predefined actions. 
AbstractMarkerAnnotationModel establishs a link between text annotations (Annotation) and desktop markers (IMarker).

- [ITextEditor](https://javadoc.scijava.org/Eclipse/org/eclipse/ui/texteditor/ITextEditor.html): StatusTextEditor, TextEditor
- [IDocumentProvider](https://javadoc.scijava.org/Eclipse/org/eclipse/ui/texteditor/IDocumentProvider.html)
- [IDocument](https://javadoc.scijava.org/Eclipse/org/eclipse/jface/text/IDocument.html): Document
An IDocument represents text providing support for
    - text manipulation
    - positions
    - partitions
    - line information
    - document change listeners
    - document partition change listeners 
- [ISelectionProvider]() 	
