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

## Angular CLI

