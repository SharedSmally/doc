# Runtime API:  org.eclipse.core.runtime
Provides support for the runtime platform, core utility methods and the extension registry. 

## Classes
- org.eclipse.core.runtime.Platform

|  Method  | 	Description |
|----------|--------------|
|static IProduct getProduct() 	|Returns the product which was selected when running this Eclipse instance or null if none|
|static IPreferencesService 	getPreferencesService() 	|Return the interface into the preference mechanism.|
|static IExtensionRegistry 	getExtensionRegistry() 	|Returns the extension registry for this platform.|

- org.eclipse.core.runtime.IExtensionRegistry

|  Method  | 	Description |
|----------|--------------|
| IConfigurationElement[] 	getConfigurationElementsFor(String extensionPointId) 	| Returns all configuration elements from all extensions configured into the identified extension point.| 
| IConfigurationElement[] 	getConfigurationElementsFor(String namespace, String extensionPointName) 	| Returns all configuration elements from all extensions configured into the identified extension point.| 
| IConfigurationElement[] 	getConfigurationElementsFor(String namespace, String extensionPointName, String extensionId) 	| Returns all configuration elements from the identified extension.| 
| IExtension 	getExtension(String extensionId) 	| Returns the specified extension in this extension registry, or null if there is no such extension.| 
| IExtension 	getExtension(String extensionPointId, String extensionId) 	| Returns the specified extension in this extension registry, or null if there is no such extension.| 
| IExtension 	getExtension(String namespace, String extensionPointName, String extensionId) 	| Returns the specified extension in this extension registry, or null if there is no such extension.| 
| IExtensionPoint 	getExtensionPoint(String extensionPointId) 	| Returns the extension point with the given extension point identifier in this extension registry, or null if there is no such extension point.| 
| IExtensionPoint 	getExtensionPoint(String namespace, String extensionPointName) 	| Returns the extension point in this extension registry with the given namespace and extension point simple identifier, or null if there is no such extension point.| 
| IExtensionPoint[] 	getExtensionPoints() 	| Returns all extension points known to this extension registry.| 
| IExtensionPoint[] 	getExtensionPoints(String namespace) 	| Returns all extension points declared in the given namespace.| 
| IExtensionPoint[] 	getExtensionPoints(IContributor contributor) 	| Returns all extension points supplied by the contributor, or null if there are no such extension points.| 
| IExtension[] 	getExtensions(String namespace) 	| Returns all extensions declared in the given namespace.| 
| IExtension[] 	getExtensions(IContributor contributor) 	| Returns all extensions supplied by the contributor, or null if there are no such extensions.| 


- org.eclipse.core.runtime.Plugin

## runtime Interfaces
|Interface | 	Description |
|----------|--------------|
| IAdaptable 	| An interface for an adaptable object.|
| IAdapterFactory 	| An adapter factory defines behavioral extensions for one or more classes that implements the IAdaptable interface.| 
| IAdapterManager 	| An adapter manager maintains a registry of adapter factories.| 
| IBundleGroup 	| Bundle groups represent a logical collection of plug-ins (aka bundles).| 
| IBundleGroupProvider 	| Bundle group providers define groups of plug-ins which have been installed in the current system.| 
| ICoreRunnable 	| A functional interface for a runnable that can be cancelled and can report progress using the progress monitor passed to the ICoreRunnable.run(IProgressMonitor) method.| 
| ILog 	| A log to which status events can be written.| 
| ILogListener 	| A log listener is notified of entries added to a plug-in's log.| 
| IPath 	| A path is an ordered collection of string segments, separated by a standard separator character, "/".| 
| IProduct 	| Products are the Eclipse unit of branding.| 
| IProductProvider 	| Product providers define products (units of branding) which have been installed in the current system.| 
| IProgressMonitor 	| The IProgressMonitor interface is implemented by objects that monitor the progress of an activity; the methods in this interface are invoked by code that performs the activity.| 
| IRegistryChangeEvent 	| Registry change events describe changes to the extension registry.| 
| IRegistryChangeListener 	| Note: for new implementations consider using IRegistryEventListener.| 
| IRegistryEventListener 	| A registry event listener is notified of changes to extension points.| 
| ISafeRunnable 	| Safe runnables represent blocks of code and associated exception handlers.| 
| ISafeRunnableWithResult<T> 	| Safe runnables represent blocks of code and associated exception handlers.| 
| IStatus 	| A status object represents the outcome of an operation.
| Preferences.IPropertyChangeListener 	| Listener for property changes.| 
  
## Extension Interfaces
|Interface | 	Description |
|----------|--------------|
| IExtensionRegistry 	| The extension registry holds the master list of all discovered namespaces, extension points and extensions.| 
| IExtensionPoint 	| An extension point declared in a plug-in (plugin.xml).| 
| IExtension 	| An extension declared in a plug-in (plugin.xml).| 
| IConfigurationElement 	| A configuration element, with its attributes and children, directly reflects the content and structure of the extension section within the declaring plug-in's manifest (plugin.xml) file.| 
| IContributor 	| This interface describes a registry contributor - an entity that supplies information to the extension registry.| 
| IExecutableExtension 	| Interface for executable extension classes that require access to their configuration element, or implement an extension adapter.| 
| IExtensionDelta 	| An extension delta represents changes to the extension registry.| 
| ExtensionFactory | Factory for the workbench's public extensions. |
| IExecutableExtensionFactory 	| This interface allows extension providers to control how the instances provided to extension-points are being created by referring to the factory instead of referring to a class.| 


  
  
