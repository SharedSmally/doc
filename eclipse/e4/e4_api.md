# Eclipse e4

## Document
- [Help](https://help.eclipse.org/latest/index.jsp): e4

## Tools
- e4 Tools Developer Resources
- RCP/RAP SDKs

## e4: MApplication > MContext > IEclipseContext 	

| Package | Description |
|---------|-------------|
|org.eclipse.e4.core.contexts 	|Application programming interfaces for Eclipse contexts.|
|org.eclipse.e4.core.di 	|Application programming interfaces describing dependency injection framework.|
|org.eclipse.e4.core.di.annotations 	|Application programming interfaces for annotations used by the dependency injection.|
|org.eclipse.e4.core.di.suppliers 	|Application programming interfaces for dependency injection object suppliers.|
|org.eclipse.e4.core.services.events 	 ||
|org.eclipse.e4.ui.di 	|Application programming interfaces describing the Eclipse 4 dependency injection annotations.|
|org.eclipse.e4.ui.model.application 	|Application programming interfaces describing the Eclipse 4 application model elements.|
|org.eclipse.e4.ui.model.application.commands 	 ||
|org.eclipse.e4.ui.model.application.descriptor.basic 	|Application programming interfaces describing the Eclipse 4 descriptor model elements.|
|org.eclipse.e4.ui.model.application.ui 	|Application programming interfaces describing the Eclipse 4 state and container model elements.|
|org.eclipse.e4.ui.model.application.ui.advanced 	|Application programming interfaces describing the advanced Eclipse 4 user interface model elements.|
|org.eclipse.e4.ui.model.application.ui.basic 	|Application programming interfaces describing the basic Eclipse 4 user interface model elements.|
|org.eclipse.e4.ui.model.application.ui.menu 	|Application programming interfaces describing the Eclipse 4 menu and toolbar model elements.|
|org.eclipse.e4.ui.model.fragment 	|Application programming interfaces describing the Eclipse 4 fragment model elements.|
|org.eclipse.e4.ui.services 	|Application programming interfaces describing the Eclipse 4 context service.|
|org.eclipse.e4.ui.workbench 	|Application programming interfaces describing Eclipse 4 handlers and the workbench.|
|org.eclipse.e4.ui.workbench.lifecycle 	|Application programming interfaces describing the Eclipse 4 lifecycle annotations.|
|org.eclipse.e4.ui.workbench.modeling 	|Application programming interfaces describing the Eclipse 4 model services.|

## org.eclipse.e4.core.contexts 	

| Interface |	Description |
|---------|-------------|
|IContextFunction 	|A context function encapsulates evaluation of some code within an IEclipseContext.|
|IEclipseContext 	|A context is used to isolate application code from its dependencies on an application framework or container.|

| Class |Description |
|---------|-------------|
|ContextFunction 	|The base class for all computed value implementations.|
|ContextInjectionFactory 	|An injection factory is used to inject data and services from a context into a domain object.|
|EclipseContextFactory 	|This factory is used to create new context instances.|
|RunAndTrack 	|Instances of this class contain behavior that is executed within an IEclipseContext.|

|Annotation Type |	Description|
|---------|-------------|
|Active 	|This annotation can be added to injectable fields ands methods to indicate that the injected value should come from the active context.|

## org.eclipse.e4.core.di

| Interface | 	Description| 
|---------|-------------|
| IBinding 	| Describes binding between object description and its implementation to be used by the dependency injection.| 
| IInjector 	| An injector is used to inject data from the object supplier into a domain object.| 

| Class | 	Description| 
|---------|-------------|
| InjectorFactory 	| Use this class to obtain an instance of the dependency injector.| 

## org.eclipse.e4.core.di.annotations 

|Annotation Type |	Description|
|---------|-------------|
|CanExecute 	|Use this annotation to tag methods that determine if this object's Execute method can be called.|
|Creatable 	|Specifies that the target class can be created by an injector as needed.|
|Evaluate 	|Use this annotation to tag methods that determine if MUIElements (e.g., MMenu, MToolbar and it's items etc.) should be visible or not.|
|Execute 	|Use this annotation to tag methods that need to be executed.|
|GroupUpdates 	|This annotation indicates that injection field or method supports batching of updates.|
|Optional 	|This annotation can be applied to methods, fields, and parameters to mark them as optional for the dependency injection.|

## org.eclipse.e4.core.di.suppliers 	

|Interface |	Description|
|---------|-------------|
|IObjectDescriptor 	|This interface describes objects created by the dependency injection.|
|IRequestor 	|Requestor represents an atomary operation performed during the injection.|

|Class |	Description|
|---------|-------------|
|ExtendedObjectSupplier 	|The base class for an "object supplier" - something that knows how to instantiate objects corresponding to the object descriptor.|
|PrimaryObjectSupplier 	|The base class for an "object supplier" - something that knows how to instantiate objects corresponding to the object descriptor.|

## org.eclipse.e4.core.services.events 	

|Interface |	Description|
|---------|-------------|
|IEventBroker 	|To obtain an instance of the event broker service from the IEclipseContext context, use|

## org.eclipse.e4.ui.di 	

|Class |	Description|
|---------|-------------|
|UISynchronize 	|Widget toolkit abstract to synchronize back into the UI-Thread from other threads|

|Annotation Type |	Description|
|---------|-------------|
|AboutToHide 	|Use this annotation to act on to the list of dynamically shown entries within a DynamicMenuContributionItem.|
|AboutToShow 	|Use this annotation to provide MMenuElements to the list of dynamically shown entries within a DynamicMenuContributionItem.|
|Focus 	|Parts can specify this annotation on one of its methods to tag it as the method to be invoked when it has been granted focus.|
|Persist 	|Parts can specify this annotation on one of the methods to tag it as the method that performs "save" operation.|
|PersistState 	|Parts can specify this annotation on one of the methods to tag it as the method that performs the "visual state persit" operation|
|UIEventTopic 	|This annotation can be applied to arguments and fields that want to receive notifications on the specified event topic.|

## org.eclipse.e4.ui.model.application 	

|Interface |	Description|
|---------|-------------|
|MAddon 	|A representation of the model object 'Addon'.|
|MApplication 	|A representation of the model object 'Application'.|
|MApplicationElement 	|A representation of the model object 'Element'.|
|MApplicationFactory 	|The Factory for the model.|
|MContribution 	|A representation of the model object 'Contribution'.|

## org.eclipse.e4.ui.model.application.commands 	 
|Interface 	|Description|
|---------|-------------|
|MBindingContext 	|A representation of the model object 'Binding Context'.|
|MBindings 	|A representation of the model object 'Bindings'.|
|MBindingTable 	|A representation of the model object 'Binding Table'.|
|MBindingTableContainer 	|A representation of the model object 'Binding Table Container'.|
|MCategory 	|A representation of the model object 'Category'.|
|MCommand 	|A representation of the model object 'Command'.|
|MCommandParameter 	|A representation of the model object 'Command Parameter'.|
|MCommandsFactory 	|The Factory for the model.|
|MHandler 	|A representation of the model object 'Handler'.|
|MHandlerContainer 	|A representation of the model object 'Handler Container'.|
|MKeyBinding 	|A representation of the model object 'Key Binding'.|
|MKeySequence 	|A representation of the model object 'Key Sequence'.|
|MParameter 	|A representation of the model object 'Parameter'.|

## org.eclipse.e4.ui.model.application.descriptor.basic 	

|Interface |	Description|
|---------|-------------|
|MBasicFactory 	|The Factory for the model.|
|MPartDescriptor 	|A representation of the model object 'Part Descriptor'.|
|MPartDescriptorContainer 	|A representation of the model object 'Part Descriptor Container'.|

## org.eclipse.e4.ui.model.application.ui 	

|Interface |	Description|
|---------|-------------|
|MContext 	|A representation of the model object 'Context'.|
|MCoreExpression 	|A representation of the model object 'Core Expression'.|
|MDirtyable 	|A representation of the model object 'Dirtyable'.|
|MElementContainer<T extends MUIElement> 	|A representation of the model object 'Element Container'.|
|MExpression 	|A representation of the model object 'Expression'.|
|MGenericStack<T extends MUIElement> 	|A representation of the model object 'Generic Stack'.|
|MGenericTile<T extends MUIElement> 	|A representation of the model object 'Generic Tile'.|
|MGenericTrimContainer<T extends MUIElement> 	|A representation of the model object 'Generic Trim Container'.|
|MImperativeExpression 	|A representation of the model object 'Imperative Expression'.|
|MLocalizable 	|A representation of the model object 'Localizable'.|
|MSnippetContainer 	|A representation of the model object 'Snippet Container'.|
|MUIElement 	|A representation of the model object 'UI Element'.|
|MUiFactory 	|The Factory for the model.|
|MUILabel 	|A representation of the model object 'UI Label'.|

|Enum |	Description|
|---------|-------------|
|SideValue 	|A representation of the literals of the enumeration 'Side Value', and utility methods for working with them.|

## org.eclipse.e4.ui.model.application.ui.advanced 	

|Interface |	Description|
|---------|-------------|
|MAdvancedFactory 	|The Factory for the model.|
|MArea 	|A representation of the model object 'Area'.|
|MPerspective 	|A representation of the model object 'Perspective'.|
|MPerspectiveStack 	|A representation of the model object 'Perspective Stack'.|
|MPlaceholder 	|A representation of the model object 'Placeholder'.|

## org.eclipse.e4.ui.model.application.ui.basic 	

|Interface |	Description|
|---------|-------------|
|MBasicFactory 	|The Factory for the model.|
|MCompositePart 	|A representation of the model object 'Composite Part'.|
|MDialog 	Deprecated. ||
|MPart 	|A representation of the model object 'Part'.|
|MPartSashContainer 	|A representation of the model object 'Part Sash Container'.|
|MPartSashContainerElement 	|A representation of the model object 'Part Sash Container Element'.|
|MPartStack 	|A representation of the model object 'Part Stack'.|
|MStackElement 	|A representation of the model object 'Stack Element'.|
|MTrimBar 	|A representation of the model object 'Trim Bar'.|
|MTrimElement 	|A representation of the model object 'Trim Element'.|
|MTrimmedWindow 	|A representation of the model object 'Trimmed Window'.|
|MWindow 	|A representation of the model object 'Window'.|
|MWindowElement 	|A representation of the model object 'Window Element'.|
|MWizardDialog 	|Deprecated. |

## org.eclipse.e4.ui.model.application.ui.menu 	

| Interface |	Description|
|---------|-------------|
|MDirectMenuItem 	|A representation of the model object 'Direct Menu Item'.|
|MDirectToolItem 	|A representation of the model object 'Direct Tool Item'.|
|MDynamicMenuContribution 	|A representation of the model object 'Dynamic Menu Contribution'.|
|MHandledItem 	|A representation of the model object 'Handled Item'.|
|MHandledMenuItem 	|A representation of the model object 'Handled Menu Item'.|
|MHandledToolItem 	|A representation of the model object 'Handled Tool Item'.|
|MItem 	|A representation of the model object 'Item'.|
|MMenu 	|A representation of the model object 'Menu'.|
|MMenuContribution 	|A representation of the model object 'Contribution'.|
|MMenuContributions 	|A representation of the model object 'Contributions'.|
|MMenuElement 	|A representation of the model object 'Element'.|
|MMenuFactory 	|The Factory for the model.|
|MMenuItem 	|A representation of the model object 'Item'.|
|MMenuSeparator 	|A representation of the model object 'Separator'.|
|MPopupMenu 	|A representation of the model object 'Popup Menu'.|
|MToolBar 	|A representation of the model object 'Tool Bar'.|
|MToolBarContribution 	|A representation of the model object 'Tool Bar Contribution'.|
|MToolBarContributions 	|A representation of the model object 'Tool Bar Contributions'.|
|MToolBarElement 	|A representation of the model object 'Tool Bar Element'.|
|MToolBarSeparator 	|A representation of the model object 'Tool Bar Separator'.|
|MToolControl 	|A representation of the model object 'Tool Control'.|
|MToolItem 	|A representation of the model object 'Tool Item'.|
|MTrimContribution 	|A representation of the model object 'Trim Contribution'.|
|MTrimContributions 	|A representation of the model object 'Trim Contributions'.|

| Enum |	Description|
|---------|-------------|
|ItemType 	|A representation of the literals of the enumeration 'Item Type', and utility methods for working with them.|

## org.eclipse.e4.ui.model.fragment 	

|Interface |	Description|
|---------|-------------|
|MFragmentFactory 	|The Factory for the model.|
|MModelFragment 	|A representation of the model object 'Model Fragment'.|
|MModelFragments 	|A representation of the model object 'Model Fragments'.|
|MStringModelFragment 	|A representation of the model object 'String Model Fragment'.|

## org.eclipse.e4.ui.services 	

|Interface |	Description|
|---------|-------------|
|EContextService 	| |
|EMenuService 	|Provide for management of different menus.|
|IServiceConstants 	 ||
|IStylingEngine 	 ||

|Class |	Description|
|---------|-------------|
|ContextServiceAddon||


## org.eclipse.e4.ui.workbench 	

|Interface |	Description|
|---------|-------------|
|IExceptionHandler 	|This handler allows clients to be notified when an exception occurs|
|IModelResourceHandler 	|This handler allows clients load, create and save model resources|
|IPresentationEngine 	|The presentation engine is used to translate the generic workbench model into widgets.|
|IResourceUtilities<ImageDesc> 	|This interface describes a utility that is used to load ImageDesc's from URIs|
|IWorkbench 	|A running instance of the workbench.|
|Selector 	|Selector to find element|
|UIEvents.Application(*) 	 ||
|UIEvents 	|E4 UI events and event topic definitions.|

## org.eclipse.e4.ui.workbench.lifecycle 	

|Annotation Type| 	Description|
|---------|-------------|
|PostContextCreate 	|Use this annotation to describe methods that will participate in the application lifecycle.|
|PostWorkbenchClose 	|Use this annotation to describe methods that will participate in the application lifecycle.|
|PreSave 	|Use this annotation to describe methods that will participate in the application lifecycle.|
|ProcessAdditions 	|Use this annotation to describe methods that will participate in the application lifecycle.|
|ProcessRemovals 	|Use this annotation to describe methods that will participate in the application lifecycle.|

## org.eclipse.e4.ui.workbench.modeling 	

|Interface |	Description|
|---------|-------------|
|EModelService 	|This service is used to find, create and handle model elements|
|EPartService 	|The part service provides clients with the functionalities of showing and hiding parts.|
|EPlaceholderResolver 	|This service is used to resolve references from MPlaceholders.|
|ESelectionService 	|This interface describes the workbench selection service|
|IModelProcessorContribution 	|Service component interface to be able to register model processors via OSGi services.|
|IPartListener||
|ISaveHandler||
|ISelectionListener 	 ||
|IWindowCloseHandler 	|A handler that can be inserted into the context of the application or a particular window to determine whether the window should be closed or not.|

|Class |	Description|
|---------|-------------|
|ElementMatcher 	|This is an implementation of a Selector that implements the existing 'findElements'.|
|EObjModelHandler 	 ||
|IModelProcessorContribution.ModelElement 	||A model element to be added to the context used to invoke the processor.|
|ModelHandlerBase 	 ||

|Enum |	Description|
|---------|-------------|
|EPartService.PartState 	|Applicable states that a part can be in.|
|ISaveHandler.Save 	 ||

