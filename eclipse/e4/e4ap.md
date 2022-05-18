
# E4AP - Eclipse 4 Application Platform
- [javadoc](https://www.ibm.com/docs/tr/rational-soft-arch/9.6.1?topic=r-api-reference)

|  package | Description |
|----------|-------------|
|org.eclipse.e4.core.contexts 	|APIs for Eclipse contexts.|
|org.eclipse.e4.core.di.annotations 	|APIs for annotations used by the dependency injection.|
|org.eclipse.e4.core.services.events 	 ||
|org.eclipse.e4.ui.di 	|APIsdescribing the Eclipse 4 dependency injection annotations.
|org.eclipse.e4.ui.model.application 	|APIs describing the Eclipse 4 application model elements.|
|org.eclipse.e4.ui.model.application.commands 	 ||
|org.eclipse.e4.ui.model.application.descriptor.basic 	|APIs describing the Eclipse 4 descriptor model elements.|
|org.eclipse.e4.ui.model.application.ui 	|APIs describing the Eclipse 4 state and container model elements.|
|org.eclipse.e4.ui.model.application.ui.advanced 	|APIs describing the advanced Eclipse 4 user interface model elements.|
|org.eclipse.e4.ui.model.application.ui.basic 	|APIs describing the basic Eclipse 4 user interface model elements.|
|org.eclipse.e4.ui.model.application.ui.menu 	|APIs describing the Eclipse 4 menu and toolbar model elements.|
|org.eclipse.e4.ui.model.fragment 	|APIs describing the Eclipse 4 fragment model elements.|
|org.eclipse.e4.ui.services 	|APIsdescribing the Eclipse 4 context service.|
|org.eclipse.e4.ui.workbench 	|APIs describing Eclipse 4 handlers and the workbench.|
|org.eclipse.e4.ui.workbench.modeling 	|AAPIs describing the Eclipse 4 model services.|

## Package org.eclipse.e4.core.contexts
### Interface
|Interface |	Description|
|----------|-------------|
|IContextFunction 	|A context function encapsulates evaluation of some code within an IEclipseContext.|
|IEclipseContext 	|A context is used to isolate application code from its dependencies on an application framework or container.|
### Class Summary 
| Class |	Description|
|----------|-------------|
|ContextFunction 	|The base class for all computed value implementations.|
|ContextInjectionFactory 	|An injection factory is used to inject data and services from a context into a domain object.|
|EclipseContextFactory 	|This factory is used to create new context instances.|
|RunAndTrack 	|Instances of this class contain behavior that is executed within an IEclipseContext.|

### Annotation Summary 
|Annotation Type 	|Description|
|----------|-------------|
|Active 	|This annotation can be added to injectable fields ands methods to indicate that the injected value should come from the active context.|
