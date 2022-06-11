# Angular + Bootstrap + NodeJS

## setup bootstrap:
npm install packages in node_modules/. --save: Package will appear in the dependencies. 
- Install bootstrap
```
npm install bootstrap --save
```
Update **angular.json** file:
```
        "styles": [
          "node_modules/bootstrap/dist/css/bootstrap.min.css",
          "src/styles.css"
        ],
        "scripts": [
          "node_modules/bootstrap/dist/js/bootstrap.bundle.min.js"
        ]
```
- Install popper js:
```
npm install @popperjs/core --save
```
Update **angular.json** file in scripts section:
```
        "scripts": [
          "node_modules/bootstrap/dist/js/bootstrap.bundle.min.js",
          "node_modules/@popperjs/core/dist/umd/popper.min.js"
        ]       
```
- Install jquery:
```
npm install jquery --save
```
In **src/app/app.component.html**:
```
<div class="container">
  <h1>Install Bootstrap 5 in Angular 13 - ItSolutionStuff.com</h1> 
  <div class="card">
    <div class="card-header">
      Featured
    </div>

    <div class="card-body">
      <h5 class="card-title">Special title treatment</h5>
      <p class="card-text">With supporting text below as a natural lead-in to additional content.</p>
      <a href="#" class="btn btn-primary">Go somewhere</a>
    </div>
  </div>
</div>
```
- run the project
```
ng serve
```

## ng -bootstrap: https://ng-bootstrap.github.io/#/home

In an angular project:
```
ng add @ng-bootstrap/ng-bootstrap
ng add @ng-bootstrap/ng-bootstrap --project myProject  # for specific project
```
It provides some directives for the components.

## ngx-bootstrap: https://valor-software.com/ngx-bootstrap/#/
```
ng add ngx-bootstrap
npm install ngx-bootstrap --save
```