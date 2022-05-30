# Angular

- Angular as front-end: using HttpClient to connect to Spring Boot REST API (app.module.ts: import HttpClient)
     - Service:
```   
export class UserService {
    private baseUrl="http://localhost:8080/api/users";  // Spring Boot
    constructor(private http:HttpClient) {}
    
    getUsers(): Observerable<User[]>  {
         return this.http.get<User[]>(`${this.baseUri}`)[
    }
```     
- Spring Boot REST API as backend

## Document
- [Angular: Angular-2;new version](https://angular.io/)/React
The Typescript framework developing web applications for front-end developers use frameworks using Components and directive. 

- [AngularJS: Angular-1](https://angularjs.org/)/Reactjs
A Javascript open-source front-end framework that is mainly used to develop single-page web applications(SPAs) using MVC.

- [Angular Tutorial](https://www.tektutorialshub.com/angular/angular-dependency-injection/)

Can use Bootstrap in in \*.html.

## Environment Setup for FrontEnd
- Install nodejs
- Install npm
- Install Angular CLI: ng command
- Visual Code for JS

Angular is based on TypeScript while AngularJS is based on JavaScript. TypeScript is a superset of ES6 with new features: 
lambda operators, iterators or reflection’s mechanism.

AngularJS uses terms of scope and controller. To scope a variable you can add many variables that will be visible in View as 
well as in Controller. AngularJS has also a concept of rootScope. Variables in rootScope are available on all throughout application. 
Angular does not have a concept of scope or controllers. Instead of them it uses a hierarchy of components as its main 
architectural concept. Component is a directive with a template. That is a similar approach as in ReactJS – another 
library used for building user interfaces.

AngularJS has many directives and every developer can also specify custom new directive. Angular also has standard directives,
but they are used in a bit different way. For example: ng-model in AngularJS means that you want to create two-way binding. 
If you want to create one-way binding, you should use ng-bind. Angular occurs only ngModel, but if you would write it only 
in: “[ ]”, you’ll get one-way binding.  If you want to create two-way binding you must write it in: “[( )]”. We have to write 
it this way because of the fact that “[ ]” is used to property binding and “( )” is used to event binding. In Angular,
some directives have changed their names like ng-repeat to ngFor.

## [Angular DI](https://www.tektutorialshub.com/angular/angular-dependency-injection/)
The Angular creates two Injector trees when the Application bootstraps. One is the ModuleInjector tree for the Modules and the other one is the ElementInjector tree which is for the Elements (Components & Directives etc).

The Angular loads the Root Module (named as AppModule) when the application bootstraps. It creates RootModule Injector for the Root Module. This Injector has an application-wide scope. The RootModule Injector becomes part of the ModuleInjector Tree.

Angular Root Module loads the AppComponent, which is the root component of our app. The AppComponent gets its own Injector. We call this root Injector. This Injector becomes the root of the ElementInjector tree.

The Root Component contains all other components. Angular App will create child components under the Root Component. All these child component can have their own child components creating a tree of components. The Angular also creates an Injector for all those components creating an Injector tree closely mimicking the component tree. These Injectors become part of the ElementInjector tree.

The Every Injector gets its own copy of Providers.

### Angular Dependency Injection Framework

Angular Dependency Injection framework implements the Dependency Injection in Angular. It creates & maintains the Dependencies and injects them into the Components, Directives, or Services.

There are five main players in the Angular Dependency injection Framework.
- **Consumer**:  The Consumer is the class (Component, Directive, or Service) that needs the Dependency. In the above example, the AppComponent is the Consumer.
- **Dependency**:  The Service that we want to in our consumer. In the above example the ProductService is the Dependency
- **Injection Token (DI Token)**:  The Injection Token (DI Token) uniquely identifies a Dependency. We use DI Token when we register dependency
- **Provider**:  The Providers Maintain the list of Dependencies along with their Injection Token. It uses the Injection Token is to identify the Dependency.  
- **Injector**:  Injector holds the Providers and is responsible for resolving the dependencies and injecting the instance of the Dependency to the Consumer. The Injector uses Injection Token to search for Dependency in the Providers. It then creates an instance of the dependency and injects it into the consumer.

### Registering the Dependency with the Injector

Angular Provides an instance of Injector & Provider to every component & directive in the application ( Consumers). It also creates an Injector instance at the module level and also at the root of the application. Basically, it creates a Tree of Injectors with parent-child relationship 

The dependencies are registered with the Provider. This is done in the Providers metadata of the Injector.
```
@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  providers: [ProductService] 
})
export class AppComponent
{
```
We can also add the Services to Providers array of the @NgModule. Then they will be available for use in all the components & Services of the application.
```
@NgModule({
  declarations: [...],
  imports: [...],
  providers: [ProductService],
  bootstrap: []
})
```

Next, need to tell angular that our component needs dependency injection. This is done by using the @Injectable() decorator.

@Injectable() decorator is not needed if the class already has other Angular decorators like @Component, @pipe or @directive etc. Because all these are a subtype of Injectible.

Since our AppComponent is already decorated with @Component, we do not need to decorate with the @Injectable

There are two ways register the services participating in the dependency injections in the Providers metadata:
- Register directly in the Providers array of the @NgModule or @Component or in @Directive.  
- Use the providedIn property of the @Injectable decorator.

There are four ways to create the dependency: 
- Class Provider (useClass)
- Value Provider (useValue )
- Factory Provider ( useFactory )
- Aliased Class Provider ( useExisting).

![Provider](https://www.tektutorialshub.com/wp-content/uploads/2017/01/Angular-Provider.png)
```
 {provide:'PRODUCT_SERVICE', useClass: ProductService }, 
 {provide:'USE_FAKE', useValue: true },   
 {provide:'APIURL', useValue: 'http://SomeEndPoint.com/api' },    
```

### Asking for Dependency in the Constructor
The Components, Directives & Services (Consumers) declare the dependencies that they need in their constructor.
	
``` 
constructor(private productService:ProductService) { 
}
```

Injector reads the dependencies from the constructor of the Consumer. It then looks for that dependency in the provider. 
The Provider provides the instance and injector, then injects it into the consumer.

If the instance of the Dependency already exists, then it will reuse it. This will make the dependency singleton.


### Injecting Service into Another Service
Create a sevice class using @Injectible metadata to decorate it. Technically,do not have to do that if it not have any external dependencies.

```
import { Injectable } from '@angular/core';
 
//@Injectable()
@Injectable({
  providedIn:'root'   # where to get the dependencies
})
export class LoggerService {
  log(message:any) {
    console.log(message);
  }
} 
```

The ProductService needs loggerService to be injected. Hence the class requires @Injectible metadata
```	

@Injectable()
export class ProductService{
  constructor(private loggerService: LoggerService) {
    this.loggerService.log("Product Service Constructed");
  }
}
```

- @Injectable

The Injectable is a decorator, which you need to add to the consumer of the dependency. This decorator tells angular that it must Inject the constructor arguments via the Angular DI system

The injectable decorator also has the ProvidedIn property using which you can specify how Angular should provide the dependency.

- @Inject

The @Inject() is a constructor parameter decorator, which tells angular to Inject the parameter with the dependency provided in the given token. It is a manual way of injecting the dependency

The @Inject takes the Injector token as the parameter. The token is used to locate the dependency in the Providers.
``` 
export class ProductService{
    constructor(@Inject(LoggerService) private loggerService) {
        this.loggerService.log("Product Service Constructed");
    }
}
``` 
 
