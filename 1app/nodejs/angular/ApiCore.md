# [ API core: @angular/core ](https://angular.io/api/core)

## Decorators
- **NgModule**:	Decorator that marks a class as an NgModule and supplies configuration metadata.
- **Component**: Decorator that marks a class as an Angular component and provides configuration metadata that determines how the component should be processed, instantiated, and used at runtime.
- **Directive**: Decorator that marks a class as an Angular directive. You can define your own directives to attach custom behavior to elements in the DOM.
- **Pipe**:	Decorator that marks a class as pipe and supplies configuration metadata.
- **Injectable**: Decorator that marks a class as available to be provided and injected as a dependency.

- **Attribute**: Parameter decorator for a directive constructor that designates a host-element attribute whose value is injected as a constant string literal.
- **Host**:	Parameter decorator on a view-provider parameter of a class constructor that tells the DI framework to resolve the view by checking injectors of child elements, and stop when reaching the host element of the current component.
- **Inject**:	Parameter decorator on a dependency parameter of a class constructor that specifies a custom provider of the dependency.
- **Optional**:	Parameter decorator to be used on constructor parameters, which marks the parameter as being an optional dependency. The DI framework provides null if the dependency is not found.
- **Self**:	Parameter decorator to be used on constructor parameters, which tells the DI framework to start dependency resolution from the local injector.
- **SkipSelf**:	Parameter decorator to be used on constructor parameters, which tells the DI framework to start dependency resolution from the parent injector. Resolution works upward through the injector hierarchy, so the local injector is not checked for a provider.
  
- **ContentChild**:	Property decorator that configures a content query.
- **ContentChildren**: Property decorator that configures a content query.
- **ViewChild**: Property decorator that configures a view query. The change detector looks for the first element or the directive matching the selector in the view DOM. If the view DOM changes, and a new child matches the selector, the property is updated.
- **ViewChildren**:	Property decorator that configures a view query.

- **HostBinding**:	Decorator that marks a DOM property as a host-binding property and supplies configuration metadata. Angular automatically checks host property bindings during change detection, and if a binding changes it updates the host element of the directive.
- **HostListener**:	Decorator that declares a DOM event to listen for, and provides a handler method to run when that event occurs.
- **Input**: Decorator that marks a class field as an input property and supplies configuration metadata. The input property is bound to a DOM property in the template. During change detection, Angular automatically updates the data property with the DOM property's value.
- **Output**:	Decorator that marks a class field as an output property and supplies configuration metadata. The DOM property bound to the output property is automatically updated during change detection.

