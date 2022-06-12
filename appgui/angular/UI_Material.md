# Material

## Tutorial
- https://material.angular.io/


## Setup
- Install module
```
ng add @angular/material
```
- import the MatSliderModule in app.module.ts file.
```
import { MatSliderModule } from '@angular/material/slider';

@NgModule ({
  imports: [
    MatSliderModule,
  ]
})
class AppModule {}
```
- Add the tag to the html file: app.component.html
```
<mat-slider min="1" max="100" step="1" value="50"></mat-slider>
```
