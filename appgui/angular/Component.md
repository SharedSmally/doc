# Component
An Angular application is a tree of components. The tree shows the relationship between 
the components, where a line points to a child component.

Components have a lifecycle that begins with their initial instantiation, and contin-
ues with their rendering until they’re destroyed and removed from the application.

## Component conposition
Required pieces
- **Component Metadata Decorator** : All components must be annotated with the
@Component() decorator to properly register the component with Angular. The
metadata contains numerous properties to help modify the way the component
behaves or is rendered.
- **Controller** : The controller is the class that is decorated with @Component() , and
it contains all the properties and methods for the component. Most of the logic
exists in the controller.
- **Template** : A component isn’t a component without a template. The markup for
a component defines the layout and content of the UI that a user can see, and the
rendered version of the template will look at the values from the controller to
bind any data.

Optional pieces:
- **Providers and hosts** : Services can be injected directly into a component if they’re
not already provided at the root module level. You also have some control over
how these services are discovered and where they are made available.

- **Inputs** L Components can accept data being passed to them using the component 
 inputs, which make it possible for a parent component to bind data directly
into a child component, which is a way to pass data down the component tree.
- **Styles and encapsulation** : Optionally, components can include a set of CSS styles
that are meant to apply only to the component. This provides a layer of encapsu-
lation for the design of components, because component styles don’t have to be
injected globally. Components can configure the way that styles are injected and
encapsulated into the application.
- **Animations** : Angular provides an animation library that makes it easy to style
component transitions and animations that plug into the template, and can
define keyframes or animation states to toggle between.
- **Outputs** : Outputs are properties that are linked to events that can be used to
listen for data changes or other events that a parent component might be inter-
ested in, and can also be used to share data up the component tree.
- **Lifecycle hooks** : During the rendering and lifecycle of a component, you can
use various hooks to trigger application logic to execute. Such as run initialization 
logic once during the instantiation of the component and tear
down logic during the destruction. You can also use these hooks to bring data
into the component, so lifecycle hooks work well with both inputs and outputs.
