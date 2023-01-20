# [Angular](https://angular.io/)
- [CLI](https://angular.io/cli)
- [API doc](https://angular.io/api)

## Modules
- [bootstrap](https://ng-bootstrap.github.io/): ng add @ng-bootstrap/ng-bootstrap


## Startup:
- Install angular-CLI: **npm install -g @angular/cli**
- Create a new Project: **ng new *project_name* **
- Run the application: **ng serve** (compiled in memory, not save the compiled ones in disk)
- Build the application: **ng build** (build final html and js files in dist/; **ng build --prod** to build and distribute the app for production)
The generated *dist/index.html* includes *runtime, polyfills, styles, vendor, & main* and the other script files. 

### Bootstrap
The entry point: **main.ts**, specified in *angular.json*.
```
import { enableProdMode } from '@angular/core';
import { platformBrowserDynamic } from '@angular/platform-browser-dynamic';
 
import { AppModule } from './app/app.module';
import { environment } from './environments/environment';
 
if (environment.production) {
  enableProdMode();
}
 
platformBrowserDynamic().bootstrapModule(AppModule)
  .catch(err => console.error(err));
```

**platformBrowserDynamic** is the module to load the Angular application in the desktop browser. It import AppModule, the Root module of the app (load first whe the application is loaded).

#### Root Module - AppModule
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
The root module must have at least one root component(AppComponent). The root component is loaded when the module is loaded by the Angular.
- imports: list of external modules
- declarations: list of components, directives, pipes,services that belong to this module
- providers: register the services created that can be injected by DI
- bootstrap: the component (within this module) that should be loaded when this module is loaded

#### Root Component - AppComponent
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
- templateURL:the HTML template file to be displayed in the browser.
- selector: where the template should be inserted into the HTML
#### Root Template - app.component.html
```
<body>
  <app-root></app-root>
</body>
```

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
