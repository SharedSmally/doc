# Route
Can route between components, but not tetween applications.

## Add Route: https://angular.io/guide/router
- Create an application with Routing
```
ng new routing-app --routing --defaults
```
- Adding components for routing
```
ng generate component first
ng generate component second
```
- Export AppRoutingModule in **app.module.ts**:
```
import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { AppRoutingModule } from './app-routing.module'; // CLI imports AppRoutingModule
import { AppComponent } from './app.component';

@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule // CLI adds AppRoutingModule to the AppModule's imports array
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
```
- Defining a basic route in app-routing.module.ts
```
import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router'; // CLI imports router

// sets up routes constant where you define your routes
const routes: Routes = [
  { path: 'first-component', component: FirstComponent },
  { path: 'second-component', component: SecondComponent },
  { path: '',   redirectTo: '/first-component', pathMatch: 'full' }, // redirect to `first-component`
  { path: '**', component: PageNotFoundComponent },  // Wildcard route for a 404 page
]; 

// configures NgModule imports and exports
@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
```
- Add routes in the application using **routerLink** and **\<router-outlet\>**:
```
<h1>Angular Router App</h1>
<!--  nav gives the links to click, which tells the router which route to use (defined in the routes constant in  AppRoutingModule) -->
<nav>
  <ul>
    <li><a routerLink="/first-component" routerLinkActive="active" ariaCurrentWhenActive="page">First Component</a></li>
    <li><a routerLink="/second-component" routerLinkActive="active" ariaCurrentWhenActive="page">Second Component</a></li>
  </ul>
</nav>
<!-- The routed views render in the <router-outlet>-->
<router-outlet></router-outlet>
```
In first-component.html:
```
<h2>First Component</h2>

<nav>
  <ul>
    <li><a routerLink="../second-component">Relative Route to second component</a></li>
  </ul>
</nav>
<router-outlet></router-outlet>
```
- Route order
The order of routes is important because the Router uses a first-match wins strategy when matching routes, so more specific routes should be placed above less specific routes. List routes with a static path first, followed by an empty path route, which matches the default route. The wildcard route comes last because it matches every URL and the Router selects it only if no other routes match first.

## Getting route information
https://angular.io/guide/router#query-parameters-and-fragments

- Import Router, ActivatedRoute and ParamMap to the component:
```
import { Router, ActivatedRoute, ParamMap } from '@angular/router';

export class FirstComponent implements OnInit {
  constructor( private route: ActivatedRoute,) {}
  ngOnInit() {
    this.route.queryParams.subscribe(params => {
      this.name = params['name'];
      console.log("name="+this.name);
    });
  }
}
```
- Add link with query parameters:
```
<nav>
    <ul>
      <li><a [routerLink]="['../first']" [queryParams]="{name: 'second component'}">Hi, First Relative Route to second component</a></li>
    </ul>
</nav>
```
- queryParams: queryParams is another input of routerLink where they can be passed like
```
<a [routerLink]="['../']" [queryParams]="{prop: 'xxx'}">Somewhere</a>
```

- fragment
```    
<a [routerLink]="['../']" [queryParams]="{prop: 'xxx'}" [fragment]="yyy">Somewhere</a>

a [routerLink]="['../']" [queryParams]="{name: 'ferret'}" [fragment]="nose">Ferret Nose</a>

foo://example.com:8042/over/there?name=ferret#nose
\_/   \______________/\_________/ \_________/ \__/
 |           |            |            |        |
scheme    authority      path        query   fragment
```

- routerLinkActiveOptions:

To get routes active class set on parent routes:
```
[routerLinkActiveOptions]="{ exact: false }"
```
To pass query parameters to this.router.navigate(...) use
```
let navigationExtras: NavigationExtras = {
  queryParams: { 'session_id': sessionId },
  fragment: 'anchor'
};

// Navigate to the login page with extras
this.router.navigate(['/login'], navigationExtras);
```