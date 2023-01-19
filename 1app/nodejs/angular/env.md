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

File **angular.json** tells angular which files to use for each environment in node *projects/name/architect/build*.

## Create new configuration
- Add a new environment file environment.test.ts in app->environments/  
- Create a test node under the build->configurations  in angular.json
- run ng serve --configuration="test"   

## [Angular Runtime Configuration using the APP_INITIALIZER](https://www.tektutorialshub.com/angular/angular-runtime-configuration/)
Store the configuration information in a config file in a secured location(src/app/assets/config). It is deployed with the App. The App can load the configuration from it when the application loads. The Angular provides the injection token named APP_INITIALIZER, which it executes when the application starts.
- Create the IAppConfig in src/app/app-config.service.ts
```
export interface IAppConfig {
    env: {
        name: string
    }
    apiServer: {
        link1:string,
        link2:string,
    }
}
```
- Create config file: appConfig.json:
```
{
   "appTitle": "APP_INITIALIZER Example App",
        
   "apiServer" : {
        "link1" :"http://amazon.com",
        "link2" :"http://ebay.com"
    },
 
   "appSetting"             : {
        "config1"    : "Value1",
        "config2"    : "Value2",
        "config3"    : "Value3",
        "config3"    : "Value4"
    }
}
```
- import APP_INITIALIZER in Root Module.
```
import { NgModule, APP_INITIALIZER } from '@angular/core';
```
-  create a service, AppConfigService, responsible for reading the configuration file.
```
@Injectable()
export class AppConfigService { 
   constructor(private http: HttpClient) {}
   load() {
       //Read Configuration
        const jsonFile = `assets/config/config.json`;
        return new Promise<void>((resolve, reject) => {
            this.http.get(jsonFile).toPromise().then((response : IAppConfig) => {
               AppConfigService.settings = <IAppConfig>response;
               console.log( AppConfigService.settings);
               resolve();   //Return Sucess
            }).catch((response: any) => {
               reject(`Failed to load the config file`);
            });
        });
   }
}
//create a factory method to call the load method of AppConfigService
export function initializeApp(appConfigService: AppConfigService) {
  return () => appConfigService.load();
}
  
```
-  use the APP_INITIALIZER token to provide the initializeApp using the useFactory
```
providers: [ 
  AppConfigService,
  { provide: APP_INITIALIZER,useFactory: initializeApp, deps:  [AppConfigService], multi: true}
],
```
