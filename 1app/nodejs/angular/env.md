# Angular Environments
- [Tutorial](https://www.tektutorialshub.com/angular/angular-environment-variables/)

The Environment Variable are those variables, whose value changes as per the running environment (development, testing, staging, production stages).
The environment configuration under the folder *src/environments/* folder.
- The default is the development and uses the **environment.ts** 
- The production environment uses the **environment.prod.ts** file.

## Create Environment Variable
Add the new environment variable to all the environment files.
```
export const environment = {
  production: false,
  apiEndPoint:"https://api.development.example.com"
};
```
## Read Environment Variable
```
import { environment } from '../environments/environment';  #only the default environment file

apiEndPoint:string="";
  constructor() {
    this.apiEndPoint = environment.apiEndPoint;
  }
```

## Testing the Environment Variable
```
ng serve   # use the default or development
ng serve --configuration="production"   #force to use environment.prod
```
The same for ng build:
- ng build: uses the default environment i.e. development environment.
- ng build --prod or (ng build --configuration="production"): uses the production environment.

File **angular.json** tells angular which files to use for each environment in node *projects -> <name> -> architect -> build*.
