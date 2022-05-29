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

## Pipes

The Angular pipes are used to Transform the Data. For Example, the Date pipe formats the date according to locale rules. 
We can pass arguments to pipe and chain pipes. The Angular also allows us to create the Custom Pipe
-    Angular Pipes
-    Angular Custom Pipes
-    Date Pipe
-    Async Pipe
-    KeyValue Pipe
-    Using Pipes in Components & Services
    

## Components

The Component is the main building block of an Angular Application. A Component contains the definition of the View and the 
data that defines how the View looks and behaves.  The Angular Components are plain javascript classes and defined using 
@component Decorator. This Decorator provides the component with the View to display & Metadata about the class

The Component passes the data to the view using a process called Data Binding. This is done by Binding the DOM Elements to 
component properties. Binding can be used to display component class property values to the user, change element styles, 
respond to a user event, etc.

## Forms

## Modules

