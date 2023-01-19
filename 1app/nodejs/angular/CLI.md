# Angular CLI
- [Tutorial](https://www.tektutorialshub.com/angular/angular-cli-tutorial/)
 
## Tutorial
- Setup
```
npm install -g @angular/cli
```
- Create a workspace
```
ng new project   # select to use Typescript and css
```
- Run the application
```
cd workspace/; ng serve
```
- Add new components, such as components, module, class, pipes & directives, etc
```
ng generate <schematic> [options]
ng g <schematic> [options]
```
- Add Componet,Pipe, Directive to a module
```
ng g module account
ng g component --module=account account/hello
ng g directive --module=account --flat=false account/Some
ng g service --module=account --flat=false account/Data
ng g pipe --module=account --flat=false account/Date
```

## Commands
$ ng help
```
  new (n) Creates a new workspace and an initial Angular application. One workspace can have mutliple apps.  ng new [name]   
  generate (g) Generates and/or modifies files based on a schematic.                                         ng generate <schematic>    
  config  Retrieves or sets Angular configuration values in the angular.json file for the workspace.         ng config [json-path] [value]
  add     Adds support for an external library to the project:       ng add <collection>   
  update  Updates the application and its dependencies.                                                      ng update [packages..]
  build (b) Compiles an Angular app into an output directory named dist/ at the given output path.           ng build [project]    
  serve (s) Builds and serves your app, rebuilding on file changes.                                          ng serve         // or npm start  
  deploy  Invokes the deploy builder for a specified project or for the default project in the workspace.    ng deploy [project]  
  
  run Runs an Architect target with an optional custom builder configuration defined in the project.         ng run <target>
  test (t) Runs unit tests in a project.
  e2e (e) Builds and serves an Angular app, then runs end-to-end tests.
  
  lint (l) Runs linting tools on Angular app code in a given project folder.  
  extract-i18n (i18n-extract, xi18n) Extracts i18n messages from source code.

  analytics Configures the gathering of Angular CLI usage metrics.
  doc (d) Opens the official Angular documentation in a browser, and searches for a given keyword.  ng doc <keyword>    
  help Lists available commands and their short descriptions.
  version (v) Outputs Angular CLI version.
```  

### [ng generate](https://angular.io/cli/generate)
```    
ng generate <schematic>  [options] 
ng g <schematic>  [options]
  
This command has the following sub-commands:
    app-shell       App shell
    application     Application
    class
    component
    directive
    enum    
    guard
    interceptor
    interface
    pipe
    resolver
    service
    service-worker
    web-worker

    library
    module

    config
    environments
```

### Generate component
```
ng g component Hello   
```
- Creates the Hello folder under the src/app folder
- Create the HelloComponent along with CSS, Spec & Template file under the Hello folder
- Imports the HelloComponent in the root module and adds it to the declarations array
- The CSS selector use the format app-<name>. i.e app-hello
    

### npm install name:
Basically there are two types of modules on npm, they are -
- Global modules - these are modules that follow the naming convention that exists today. You require('foo') and there is much rejoicing. They are owned by one or more people through the npm install XYZ command.
- Scoped modules - these are new modules that are "scoped" under an organization name that begins with an @ the organisation's name, a slash and finally the package name, e.g. @someOrgScope/packagename. Scopes are a way of grouping related packages together, and also affect a few things about the way npm treats the package.

A scoped package is installed by referencing it by name, preceded by an @-symbol, in npm install:
```
npm install @myorg/mypackage
```

### Generate Direactive
```
  ng g directive Some
```
Generate Some.Directive.ts and some.directive.spec.ts:
``
import { Directive } from '@angular/core';
@Directive({
  selector: '[appSome]'
})
export class SomeDirective { 
  constructor() { }
}  
```  

### Generate Pipe
```
  ng g pipe Date 
```
Generates the date.pipe.ts, and date.pipe.ts.spec.ts:
```
import { Pipe, PipeTransform } from '@angular/core';
@Pipe({
  name: 'date'
})
export class DatePipe implements PipeTransform { 
  transform(value: any, args?: any): any {
    return null;
  }
}  
```  

### Generate Service
```
  ng g service Data 
```
Generates the data.service.ts, and date.service.ts.spec.ts:
```
import { Injectable } from '@angular/core'; 
@Injectable({
  providedIn: 'root'
})
export class DataService { 
  constructor() { }
} 
```   

### Generate class
```
  ng g class customer
```
Generates the customer.ts:
```
export class Customer {   
} 
```  

### Generate Module
```
  ng g class account
```
Generate modeule under src/app/account:
```
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
 
@NgModule({
  declarations: [],
  imports: [
    CommonModule
  ]
})
export class AccountModule { }
```   
  
