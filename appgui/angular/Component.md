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


## Lifecycle hooks
- OnChanges
- On Init
- OnDestroy
- DoCheck
- AfterContentInit
- AfterContentChecked
- AfterViewInit
- AfterViewChecked

The OnInit , OnChanges , and OnDestroy hooks are the most commonly used lifecycle
hooks. The DoCheck , AfterContentChecked , and AfterViewChecked hooks are most
useful to keep track of logic that needs to run during any change detection process, and
respond if necessary. The OnInit , AfterContentInit , and AfterViewInit hooks are
primarily useful to run logic during the component’s initial rendering to set it up, and
each one ensures a different level of component integrity

Angular is a tree of components, the component can be nested inside one another.

- **View Child**: Most often, components are nested by being declared in the template of another component.
    A View Child is declared inside the component template.
- **Content Child**: a component accepts content to be inserted into its template. The components are inserted as content
inside the component rather than being directly declared in the template. A Content
Child is declared between the opening and closing tags when a component is used.
Any component passed in through NgContent would be considered a Content Child.
```
<user-avatar [avatar]="avatar"></user-avatar>
<ng-content></ng-content>
```

## Component Types
- **App component**: This is the root app component, and you only get one of these per application.
- **Display component**: This is a stateless component that reflects the values passed into it, making it highly reusable.
- **Data component** : This is a component that helps get data into the application by loading it from external sources.
- **Route component** : When using the router, each route will render a component, and this makes the component intrinsically linked to the route.

```
import { Component, Input } from '@angular/core';

interface Metric {  // interface as data type
  used: number,
  available: number
};
interface Node {
  name: string,
  cpu: Metric,
  mem: Metric
};

export class DashboardComponent implements OnInit, OnDestroy {
  cpu: Metric;
  mem: Metric;
  cluster1: Node[];
  cluster2: Node[];
  interval: any;
  
  ngOnInit(): void { }
}

<p>{{cluster1 | json}}</p>
```

## Inputs: from parent to children
Component can define properties that can accept input through property bindings. Any default HTML element properties can also be
bound to a component, but you can define additional properties that the component can use to manage its lifecycle or display.
```
<summary [stock]="stock"></summary>
```
The inputs declared means that all the properties of this component are made available for binding
```
@Component({
  selector: 'app-metric',
  templateUrl: './metric.component.html',
  styleUrls: ['./metric.component.css']
})
export class MetricComponent {
  @Input() title: string = '';
  @Input() description: string = '';
  @Input('used') value: number = 0;
  @Input('available') max: number = 100;
  
  @Input('used')  //intercept inputs using set/put keyword
  set value(value: number) {
    if (isNaN(value)) value = 0;
    this._value = value;
  }
  get value(): number { return this._value; }

  isDanger() {
    return this.value / this.max > 0.7;
  }
}
```

## Change detection
```
import { Component, Input, ChangeDetectionStrategy } from '@angular/core';
@Component({
  selector: '[app-nodes-row]',
  templateUrl: './nodes-row.component.html',
  styleUrls: ['./nodes-row.component.css'],
  changeDetection: ChangeDetectionStrategy.OnPush
})

export class MetricComponent implements OnChanges {
  @Input('used') value: number = 0;
  @Input('available') max: number = 100;
  ngOnChanges(changes) {
    if (changes.value && isNaN(changes.value.currentValue)) this.value = 0;
    if (changes.max && isNaN(changes.max.currentValue)) this.max = 0;
  }
}
```

## Output events: from child to parent or descendent
```
import { Component, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'app-navbar',
  templateUrl: './navbar.component.html',
  styleUrls: ['./navbar.component.css']
})
export class NavbarComponent {
  @Output() onRefresh: EventEmitter<null> = new EventEmitter<null>();
  refresh() {
    this.onRefresh.emit();
  }
}
```
In component.html:
```
<button class="btn btn-success" type="button" (click)="refresh()">Reload</button>
```
In app.component.html:
```
<app-navbar (onRefresh)="dashboard.generateData()"></app-navbar>
<app-dashboard #dashboard></app-dashboard>
```
## View Child
In order to access a child component’s controller inside a parent controller, we can
leverage ViewChild to inject that controller into our component.

ViewChild is a decorator for a controller property, like Inject or Output , which tells
Angular to fill in that property with a reference to a specific child component control-
ler. It’s limited to injecting only children, so if you try to inject a component that isn’t a
direct descendent, it will provide you with an undefined value.
```
export class AppComponent {
  @ViewChild(DashboardComponent) dashboard: DashboardComponent;
  refresh() {
    this.dashboard.generateData();
  }
}
```


