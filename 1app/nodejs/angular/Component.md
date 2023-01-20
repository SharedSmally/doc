# Component
- [API doc](https://angular.io/api/core/Component)

A Component is a class with **@Component**, contains the View (via Template) and the data for the View.
```
import { Component } from '@angular/core';
@Component({    
  selector: 'app-root',
  templateUrl: './app.component.html',  //template defining the view
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'GettingStarted';
}
```

The Template is just a subset of HTML on how to display the view. It is a normal HTML page using tags like h1, h2, etc. 
It also uses the Angular-specific markup like {} (for interpolation), [] (for Property binding) etc.

The Angular supports four types of Data binding
- Interpolation: Data is bind from component to View
- Property Binding:  Data is bind from component to the property of an HTML control in the view like
- Event Binding: The DOM Events are bind from View to a method in the Component
- Two-way Binding/Model Binding: The data flow in both directions from view to component or from component to view
