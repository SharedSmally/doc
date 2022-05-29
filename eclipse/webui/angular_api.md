# Angular API

## Document
- [API Reference](https://angular.io/api)
- [Tutorial](https://www.tektutorialshub.com/angular-tutorial/)

## API
- core
    - global
    - test
- common
    - http
- animations
- elements
- forms
- router
- service-worker
- platform-browser
- platform-server

## Angular Architecture

The  Architecture of an Angular Application is based on the idea of Components.  An Angular application starts with a Top-level component called the Root Component. We then add child components forming a tree of loosely coupled components.

![Architecture](https://www.tektutorialshub.com/wp-content/uploads/2016/08/Angular-2-Architecture-Overview-and-Concepts.png)

The application consists of three components, Services that gets injected into the components and directives that help to manipulate the DOM.

The application has three Components. At the top we have rootComponent. Under the rootComponent, we have two other components. One is TaskComponent, which displays the list of Tasks and TaskAddComponent, which allows us to create new tasks.

The Angular Components are plain javaScript classes and defined using @component Decorator. This Decorator provides the component with the View to display ( known as Template) & Metadata about the class

The Components uses data binding to get the data from the Component to our View (Template). We use the special HTML markup knows as the Angular Template Syntax to achieve this.

At the right side, we have an Angular Services. The Angular Services provides services to our Component, like fetching data from database using Task Service, logging application events using logger Services and making an HTTP request to the back-end server using HTTP service.

The Responsibility to provide the instance of the Service to the Components falls on Angular Injector. It injects services into the components using Dependency Injection

We also have Directives, which help us to manipulate the structure (structural directives) or style (attribute directive) our application. The directives help us to transform the DOM as per our needs.

## Modules
We will create components, services, and directivesand put them inside the Angular Modules. We use the special directive to create the Modules. The Angular Module also called as ngModule

Use Angular Module ( or ngModule) to organize of the Angular code within a bigger Angular Application. The Application is made up of several Angular Modules acting together. Each Module implementing a specific feature or functionality of the application. 

Angular Application mainly build Components, Services & Directives. They are defined inside a JavaScript Module:
```
import { Component } from '@angular/core';
 
@Component({   
})
export class AppComponent{    
    SomeObject : any;    
    Title : string ="Hello Angular";    
     getSomeObject(): any {        
       return this.SomeObject;    
    }
}
```

## Class
The Class contains the logic of the application. It can contain methods & properties just like c# or java classes. The class must be defined with the export keyword if you want to use the class in another module.
- The class Decorator
AppComponent is just a class. There is nothing Angular about it. It is the decorator, which tells angular how to treat the class.

For Example, @Component decorator tells the Angular that the Class is a Component. Similarly, a @Directive tells the Angular that the class is a Directive. Angular currently has the following class decorators
- @Component
- @Directive
- @Injectable
- @NgModule
- @Pipe
 
## Application:
An Angular Application is composed of
-    Component
-    Templates
-    Metadata
-    Data Binding
-    Directives
-    Services
-    Dependency Injection
 

## [Decorators](https://angular.io/api/core#decorators)
- [@Directive](https://angular.io/api/core/Directive)
- [@Component](https://angular.io/api/core/Component): inherit from Directive
- [@NgModule](https://angular.io/api/core/NgModule)
- [@Inject](https://angular.io/api/core/Inject)
- [@Injectable](https://angular.io/api/core/Injectable)
- [@Input](https://angular.io/api/core/Input)
- [@Output](https://angular.io/api/core/output)

## core Ng Directive
- NgClass
- NgComponentOutlet / NgTemplateOutlet 
- NgForOf/NgForOfContext
- NgIf/ NgIfContext
- NgLocaleLocalization/NgLocalization
- NgPlural/NgPluralCase
- NgStyle
- NgSwitch/NgSwitchCase/NgSwitchDefault

## Directives

The Angular directive helps us to manipulate the DOM. You can change the appearance, behavior, or layout of a DOM element 
using the directives. They help you to extend HTML. The Angular directives are classified into three categories based on 
how they behave.  They are Component, Structural and Attribute Directives

The ngFor is an Angular structural directive, which repeats a portion of the HTML template once per each item from an iterable list (Collection).
The ngSwitch allows us to Add/Remove DOM Element. It is similar to the switch statement of Javascript.  The ngIf allows us to Add/Remove DOM Element. 

The ngClass Directive is an Angular Attribute Directive, which allows us to add or remove CSS classes to an HTML element. 
The ngStyle directive allows you to modify the style of an HTML element using the expression.  Using the ngStyle you can dynamically 
change the style of your HTML element.


The Angular has directives, with a * before the directive name indicating it as a structural directive
``` 
<ul>     
    <li *ngFor =#customer of customers>         
        {{customer.name}}     
    </li> 
</ul> 
<div *ngIf=”vm.isVIP”> 
    <h3> VIP Customer </h3> 
</div>
``` 

The style directives like ng-style, ng-src & ng-href are all gone. These are now replaced by property binding HTML elements to the class properties

The creation of Custom Directives is simplified as:
``` 
@Directive({     
   selector: '[MyDirective]' 
}) 
class MyDirective { }
```

## Component
The Angular Component is a class decorated by @Component class decorator

The Component controls the part of the user interface (or view). The Task List application listed above has three components. The TaskComponent displays the list of Tasks The TaskAddComponent helps us to create new tasks. The rootComponent is the Parent component of these components and it only displays the name of the application.

```
import { Component } from '@angular/core';
 
@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'GettingStarted';
}
``` 

The Component has four important parts
- Import Statement
-  Class
-  Template
-  Metadata

The Import statement imports the dependencies required by this component. The class contains the application logic. It is decorated by the @Component class decorator.


## Template

The Component needs a View to display. The Template defines that View.

The Template is just a subset of HTML, that tells Angular how to display the view. It is a normal HTML page using tags like h1, h2, etc. It also uses the Angular-specific markup like {} (for interpolation), [] (for Property binding) etc.

## DataBinding
Angular uses the Data Binding to get the data from the Component to our View (Template). This is done using the special HTML Angular-specific markup known as the Template Syntax

- Interpolation: Data is bind from component to View
```
//AngularJS   
<h3> {{vm.customer.Name}}</h3>  
 
//Angular 
<h3> {{customer.Name}}</h3>
```

- One-way binding: can bind to any property of the HTML element.
```
//AngularJS 
<h3> ng-bind=vm.customer.name></h3> 
 
//Angular 
<h3 [innerText]=”customer.name” ></h3>
```
- Two- way binding: The data flow in both directions from view to component or from component to view
``` 
//AngularJS 
<input ng-model=”vm.customer.name”>  
 
//Angular 
<input [(ng-model)]=”customer.name”> 
```

- Event Binding: bind directly to the DOM events; The DOM Events are bind from View to a method in the Component
```
//AngularJS 
<button ng-click=”vm.save()”>Save<button>  
 
//Angular 
<button (click)=”save()”>Save<button> 
```
- Property Binding: Data is bind from component to the property of an HTML control in the view like

## Directive

The Directives help us to manipulate the view.

A directive is a class, which we create using the @Directive class decorator. It contains the metadata and logic to manipulate the DOM

The Views are created by Angular using the Templates defined in the Components. These templates are dynamic and are transformed as per the Directives.

Angular supports two types of directives. One is structural directives which change the structure of the View and the other one is attribute directive, which alters the style of our view.


## Services
The Services provide service to the Components or to the other Services.

Angular does not have any specific definition for Services. just create a class, export a method, that does some specific task and it becomes a service. ```
export class MyLogger {
    AddTolog(msg: any)  {
        console.log(msg);
    }
}
``` 
And in any of the controllers, just invoke it using
```	
log :MyLogger = new MyLogger();
constructor() {
    this.log.AddTolog("Component Created");
}
``` 
## Dependency Injection

Dependency injection is a method by which, a new instance of a service is injected into the component (or pipe, directive, services, etc), which requires it. A Component, Directive, Pipe, or Service that requires service is called the consumer of the service.

Consumers declare the dependencies that they need in their constructor. Injector reads the dependencies from the constructor of the Consumer. It then looks for that dependency in the Angular Provider. The Provider provides the instance and injector, then injects it into the consumer.

The Injectable is a decorator, which you need to add to the consumer of the dependency. This decorator tells angular that it must Inject the constructor arguments via the Angular DI system. But @Injectable() decorator is not needed if the class already has other Angular decorators like @Component, @pipe or @directive etc. Because all these are a subtype of Injectible.

## Pipes

The Angular pipes are used to Transform the Data. For Example, the Date pipe formats the date according to locale rules. 
We can pass arguments to pipe and chain pipes. The Angular also allows us to create the Custom Pipe
-    Angular Pipes
-    Angular Custom Pipes
-    Date Pipe
-    Async Pipe
-    KeyValue Pipe
-    Using Pipes in Components & Services
```
<td>{{customer.name | uppercase}}</td>
```

## Root Module

Angular organizes the application code as Angular modules. The Modules are closely related blocks of code in functionality. Every application must have at least one module.

The Module, which loads first is the root Module. This Module is our root module.

The root module is called app.module.ts. (under src/app folder). It contains the following code
``` 
import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
 
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
 
@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
``` 

The structure of the Angular module is similar to the component class. Like Component, it consists of three parts. A class, class decorator and import statement


## Components

The Component is the main building block of an Angular Application. A Component contains the definition of the View and the 
data that defines how the View looks and behaves.  The Angular Components are plain javascript classes and defined using 
@component Decorator. This Decorator provides the component with the View to display & Metadata about the class

The Component passes the data to the view using a process called Data Binding. This is done by Binding the DOM Elements to 
component properties. Binding can be used to display component class property values to the user, change element styles, 
respond to a user event, etc.

In Angular, Components is used for Controller and View:
```	
import { Component } from '@angular/core'; 

@Component({     
    selector: 'app',     
    template: '<h1>{{message}} </h1>' 
}) 
export class AppComponent  {
      message: string=’Hello Angular’; 
}
``` 

In Angular, a component represents a UI element. You can have many such components on a single web page. Each component is 
independent of each other and manages a section of the page. The components can have child components and parent components.

## Forms

## Modules

