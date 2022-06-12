# Angular Tutorial
## Books
- Angular development with typescript: https://livebook.manning.com/book/angular-development-with-typescript-second-edition/about-this-book/
- Angular in Action: in pdf

## Angular Components
- Modules: Objects that help to organize dependencies into discrete units
- Components: New elements that will compose the majority of the application’s structure and logic (with html and css for rendering with data/method from the Component)
- Directives: Objects that modify elements to give them new capabilities or change behaviors (tag behavior in html)
    - NgClass —Conditionally apply a class to an element
    - NgStyle —Conditionally apply a set of styles to an element
    - NgIf —Conditionally insert or remove an element from the DOM
    - NgFor —Iterate over a collection of items
    - NgSwitch —Conditionally display an item from a set of options
- Pipes: Functions that format data before it’s rendered
```
{{user.registered_date | date:'shortDate'}}
```
- Services: Reusable objects that fill niche roles such as data access or helper utilities (used by Component to access the model)


## Angular Bootstrap
The application must be bootstrapped at runtime to start the process of rendering. It is specified by _main_ property in angular.json, which points to **main.ts**. The role of main.ts is to bootstrap the Angular application, which use platformBrowserDynamic to load the bootstrap module to render _index.html_. There was a selector of app-root used to identify the component in markup:
```
<body><app-root></app-root></body>
```
Once the app is bootstrapped, Angular will look for the app-root element and replace it with the rendered component (via @Component/selector).

- App Module: @NgModule
The App module is the packaging that helps tell Angular what’s available to render.
It describes the various dependencies that are needed to render the module.
    - declarations: provide a list of any components and directives to make available to the entire application.
    - imports: an array of other modules upon which this module depends
    - providers: a list of services to be created and used by the application
    - bootstrap: defines which components to bootstrap at runtime

- Angular Component: @Component
```
ng generate component component/stcok
```
- Service: @Injectable with Interface
Services are shareable objects that abstract some common logic that can be reused in multiple places.
```
ng generate service services/stocks
```
In StockComponent:
```
imports: [
   BrowserModule,
   HttpClientModule
],

providers: [StocksService],
```
- Add Material CSS and markup:
```
<link rel="stylesheet" href="//storage.googleapis.com/code.getmdl.io/1.0.1/material.indigo-orange.min.css">
<link rel="stylesheet" href="//fonts.googleapis.com/icon?family=Material+Icons">
```


## UI
- Bootstrap (https://getbootstrap.com/)
- ng-bootstrap (https://ng-bootstrap.github.io)
- Angular Material (https://github.com/angular/material2)
- Covalent (https://teradata.github.io/covalent)
- Clarity (https://vmware.github.io/clarity)
- Kendo UI (https://www.telerik.com/kendo-angular-ui/)
- PrimeNG (www.primefaces.org/primeng/)
- Wijmo (http://wijmo.com/angular2/)
- Ionic (http://ionic.io)
- Fuel-UI (http://fuelinteractive.github.io/fuel-ui/)

## Communication between components
- Child from Parent: via Input
- Child to Parent: via event emit

## Communication: use HttpClient for http
https://medium.com/@ZombieCodeKill/angular-fundamentals-communicating-with-the-server-using-http-observables-and-rx-2a1b939cc66b

- Use callback:
```
var bill: number = 20;

Server.request(requestData, function(responseData) {
 // asynchronously handle data
});

//this will be called before the callback
doSomethingElse();
```
- Use Promise: represent a single value which will be returned in the future.
```
var promise = http.get(url, data);
promise.then(function(responseData) {
   // handle response
});

//this will be execute before the then function
doSomethingElse();
return promise;
```

- Use RxJx Observeable: represent 0 or more values, returned either immediately or in the future. They can either be synchronous or asynchronous, and can be closed independently of returning a value. The have improved error handling over promises.
```
var obs= http.get(url, data);
obs.subscribe(function(responseData) {
   // handle response
});

doSomethingElse();
return obs;

this.http.get('/api/user').subscribe(user => {
    // Do something with the user record
  }, (error) => {
    // Handle the error
})

this.keyboardService.keypress().subscribe(key => {
   // Do something with the key record
  }, (error) => {
   // Handle the error
})
```

## Service
- Title Service: https://blog.bitsrc.io/dynamic-page-titles-in-angular-98ce20b5c334
- Sample Service using HttpClient:
```
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

export interface StockInterface {
   symbol: string;
   lastTradePriceOnly: number;
   change: number;
   changeInPercent: number;
}
@Injectable()
export class StocksService {
   constructor(private http: HttpClient) {}
   get() {
     return stocks.slice();
   }
   add(stock) {
     stocks.push(stock);
     return this.get();
   }
   remove(stock) {
    stocks.splice(stocks.indexOf(stock), 1);
    return this.get();
   }
   load(symbols) {
     if (symbols) {
         return this.http.get<Array<StockInterface>>(service + '/stocks/snapshot?symbols=' + symbols.join());
     }
   }
}
```
- Sample in component.html:
```
<div class="mdl-card stock-card mdl-shadow--2dp" [ngClass]="{increase: isPositive(), decrease: isNegative()}" style="width: 100%;">
 <span>
  <div class="mdl-card__title">
    <h4 style="color: #fff; margin: 0">
     {{stock?.symbol?.toUpperCase()}}<br />
     {{stock?.lastTradePriceOnly | currency:'USD':'symbol':'.2'}}<br />
     {{stock?.change | currency:'USD':'symbol':'.2'}} ({{stock?.changeInPercent | percent:'.2'}})
   </h4>
  </div>
 </span>
</div>
```
NgClass directive: add or remove CSS classes to and from the element
NgStyle directive: add or remove CSS styles to and from the element
