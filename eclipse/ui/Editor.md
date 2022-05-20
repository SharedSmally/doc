# JFace Editor
- [Creating a Text Editor with JFace Text](https://flylib.com/books/en/1.70.1/creating_a_text_editor_with_jface_text.html)
- [JFace javadoc](https://www.ibm.com/docs/en/rsar/9.5?topic=SS5JSH_9.5.0/org.eclipse.platform.doc.isv/reference/api/org/eclipse/e4/core/contexts/class-use/RunAndTrack.html)

## JFace Text Framework
### Customized Editor
- Custom Editor extends from TextEditor/Source
- Custom DocumentProvider extends from FileDocumentProvider, ...
- Custom PartitionScanner extends from RuleBasedPartitionScanner, ..., 
- Custom Rule extends from MultiLineRule(IRule) 
- Advance Features
    - Syntax highlighting: Custom ViewerConfiguration extends from SourceViewerConfiguration
    - Content Assistance: usign IContentAssistantProcessor and ContentAssistant

### Models, Views, and Controllers in JFace Text Framework
The JFace text framework is model-view-controller based: 
- a text document is modeled as an IDocument (model)
- an ITextViewer (controller) to view or edit an IDocument document
- ITextViewer turns a StyledText widget (view) into a documentbased text component

Usually no need to implement the IDocument and ITextViewer interfaces from scratch because the framework provides many abstract as well as concrete implementations of these interfaces. Built on ITextViewer and its descendant classes, many editor-related classes in the org.eclipse.ui.texteditor and org.eclipse.ui.editors.text packages also act in the controller role. Such classes include AbstractTextEditor and TextEditor, which act as the controller and manage the view (through ITextViewer) and the model.

![MVC](https://flylib.com/books/1/70/1/html/2/images/fig20-1.jpg)

### IDocument, AbstractDocument, Document
The IDocument interface represents text providing support for text manipulation, partition, search, and document change event notification.
```
public void set(String text)
```
 A partition is a certain part of the document. The whole document can be viewed as a sequence of non-overlapping partitions.One of the advantages of document partitioning is that you can manipulate partitions in different ways according to their types.
 
The process of dividing a document into non-overlapping partitions is called document partitioning. Usually, you need a document partitioner to perform the task.
```
public void setDocumentPartitioner(IDocumentPartitioner partitioner)
```
An IDocumentPartitioner is capable of dividing a document into a set of disjointed partitions. A partition is represented by the ITypedRegion interface. The ITypedRegion interface defines the content type, offset (to the beginning of the document), and the length of a partition. Once the document changes, the document partitioner is invoked to update the partition.

In most cases, a document partitioner uses a scanner to scan the document from the beginning to the end to perform partitioning. Such a scanner is represented by the IPartitionTokenScanner interface. A partition token scanner returns tokens representing partitions. The RuleBasedPartitionScanner class is a concrete implementation of the IPartitionTokenScanner interface. A rule-based partition scanner performs document partitioning according to the specified predicate rules.

### ITextViewer, TextViewer
An ITextViewer enables a text widget to support model documents mentioned in the preceding subsection. You can register various listeners on a text viewer to listen for text change events. A text viewer supports a set of plugins: undo manager, double-click behavior, auto indentation, and text hover. Implementing the ITextViewer is complicated and error prone; usually, you should use or extend classes implementing the ITextViewer class in the framework. The TextViewer class is a concrete implementation of the ITextViewer interface.

#### ISourceViewer, SourceViewer, SourceViewerConfiguration
An AbstractTextEditor controls and manages the source viewer and the document.
The source viewer (represented by SourceViewer) is created and maintained by an AbstractTextEditor.  You cannot set the source viewer for the text editor. However, with the SourceViewerConfiguration class, you can configure the source viewer wrapped by the text editor with the following method:
```
 protected void setSourceViewerConfiguration(SourceViewerConfiguration configuration)
```

The setSourceViewerConfiguration method is protected; you need to call it in a subclass of the AbstractTextEditor class.

An AbstractTextEditor requests a document through a document provider. A document provider is represented by the IDocumentProvider interface, which maps between domain elements and documents. A text editor employs document providers to bridge the gap between input elements and documents. 


## JFace Text Framework
The org.eclipse.jface.text package is the main package, which provides a framework for creating, displaying, and manipulating text documents. The org.eclipse.jface.text.contentassist, org.eclipse.jface.text.formatter, org.eclipse.jface.text.information, org.eclipse.jface.text.presentation, and org.eclipse.jface.text.reconciler packages provide various add-ons for a text viewer. The org.eclipse.jface.text.rules package contains classes that handle rule-based text scanning. The org.eclipse.jface.text.source package provides utility classes handling text annotations. Finally, the two subpackages of the org.eclipse.ui package provide many ready-to-use text editors.

| Package | Description |
|---------|-------------|
| org.eclipse.jface.text 	|Provides a framework for creating and manipulating text documents.|
| org.eclipse.jface.text.contentassist 	| Provides a content assist add-on for an ITextViewer.| 
| org.eclipse.jface.text.formatter 	| Provides a content formatter add-on for an ITextViewer.| 
| org.eclipse.jface.text.hyperlink 	| Provides support for detecting and displaying hyperlinks in ISourceViewers.| 
| org.eclipse.jface.text.information 	| Provides an information provider add-on for an ITextViewer.| 
| org.eclipse.jface.text.link 	| Application programming interfaces for interaction with the Eclipse text editor's linked position support.| 
| org.eclipse.jface.text.presentation 	| Provides a presentation reconciler add-on for an ITextViewer.| 
| org.eclipse.jface.text.projection 	| This package provides an implementation of projection documents.| 
| org.eclipse.jface.text.quickassist 	| This package provides the quick assist assistant add-on for an ISourceViewer.| 
| org.eclipse.jface.text.reconciler 	| Provides a reconciler add-on for an ITextViewer.| 
| org.eclipse.jface.text.revisions 	| Provides a revision model and a protocol to display revision information in a vertical ruler column.| 
| org.eclipse.jface.text.rules 	| Provides a framework for rule based text scanning and uses the framework to provide rule-driven default implementations of IPresentationDamager, IPresentationRepairer and IDocumentPartitioner.| 
| org.eclipse.jface.text.source 	| Provides a framework for connecting document regions with annotations and for displaying those.| 
| org.eclipse.jface.text.source.projection 	| This package provides the UI part for projection documents of which the most important part is the projection viewer.| 
| org.eclipse.jface.text.templates 	| Application programming interfaces for interaction with the Eclipse text template support.| 
| org.eclipse.jface.text.templates.persistence 	| Provides persistence support for templates.| 
| org.eclipse.jface.util 	| Provides useful building blocks used throughout JFace, including property change events, a listener list implementation, and runtime checked assertions.| 
| org.eclipse.jface.viewers 	| Provides a framework for viewers, which are model-based content adapters for SWT widgets.| 
| org.eclipse.jface.viewers.deferred 	| Provides a framework for viewers that handle deferred contents.| 
| org.eclipse.jface.window 	| Provides a general framework for creating and managing windows.| 
| org.eclipse.jface.wizard 	| Provides a framework for wizards.| 
