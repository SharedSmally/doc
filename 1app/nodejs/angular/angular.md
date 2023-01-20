# [Angular](https://angular.io/)
- [CLI](https://angular.io/cli)
- [API doc](https://angular.io/api)

## Startup:
- Install angular-CLI: npm install -g @angular/cli
- Create a new Project: ng new *project_name*
- Run the application: ng serve (compiled in memory, not save the compiled ones in disk)
- Build the application: ng build (build final html and js files in dist/; ng build --prod to build and distribute the app for production)

## Samples
### Components
```
import { Component } from '@angular/core'; 
 
@Component({     
    selector: 'app',     
    template: '<h1>{{message}} </h1>' 
}) 
export class AppComponent  {
      message: string=’Hello Angular’; 
}
```
### Directives
```
<ul>     
    <li ng-repeat =customer in vm.customers> 
        {{customer.name}}     
    </li> 
</ul> 
<div ng-if=”vm.isVIP”>     <h3> VIP Customer </h3> </div>
```
directives starts with \*:
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
Customized directives
```
@Directive({     
   selector: '[MyDirective]' 
}) 
class MyDirective { }
```
### Data Bindings
- Interpolation
```
<h3> {{customer.Name}}</h3>
```
- One way Binding
```
<h3 [innerText]=”customer.name” ></h3>
```
- Event Binding
```
<button (click)=”save()”>Save<button> 
```
- Two-way binding
```
<input [(ng-model)]=”customer.name”> 
```
- Using Pipe
```
<td>{{customer.name | uppercase}}</td>
```

## Bootstrapping Angular Application
- Index.html loads
- Angular, Third-party libraries & Application loads
- Main.ts the application entry point
- Root Module
- Root Component
- Template

### index.html
```
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>GettingStarted</title>
  <base href="/">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" type="image/x-icon" href="favicon.ico">
</head>
<body>
  <app-root></app-root>
</body>
</html>
```


An Angular application is based on Components, it starts with a Top-level component(Root Component),then add child components forming a tree of loosely coupled components.

Application
    - Components: View (Template) and the Metadata, using databind to get the data
    - Services: reusable without view, injected to Components
    - Directives: manipulate the structure/style of the application, transform the DOM
    - Pipe: Data transformation
Module
   Collection of Components, Services, Directives, etc

Components:
- Shell Application
- Application
- Component
- Directive
- Pipe
- Service
- Class
