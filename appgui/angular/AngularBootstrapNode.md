# Angular + Bootstrap + NodeJS
- bootstrap
```
npm install bootstrap
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
For popper js:
```
npm install @popperjs/core
```
Update **angular.json** file in scripts section:
```
       "./node_modules/@popperjs/core/dist/umd/popper.min.js"
```

- ng -bootstrap: https://ng-bootstrap.github.io/#/home
In an angular project:
```
ng add @ng-bootstrap/ng-bootstrap
ng add @ng-bootstrap/ng-bootstrap --project myProject  # for specific project
```

- ngx-bootstrap: https://valor-software.com/ngx-bootstrap/#/
```
ng add ngx-bootstrap
npm install ngx-bootstrap --save
```
