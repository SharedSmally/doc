# Angular Form
- FormControl: the basic
- FormGroup: A list of FormControl with Validator
- FormArray: Array of FormControl, FormGroup, or FormArray instances.
- FormBuilder: create FormControl, FormGroup, and FormArray.

## FormControl

Angular FormControl is an inbuilt class that is used to get and set values and validation of the form control fields like \<input\> 
or \<select\>. The FormControl tracks the value and validation status of an individual form control. It can be used standalone 
  as well as with a parent form.

In app.component.ts: 
  
```
import { Component } from '@angular/core';
import { FormControl, Validators } from '@angular/forms';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  name = new FormControl('default', [Validators.required]); //value: name.value
}  
```  

  In app.component.html
  
```
<div>
  <input [formControl]="name">
  <label *ngIf="name.invalid" [ngClass] = "'error'"> Name is required </label>
</div>  
```
  
## FormGroup
  
```
import { Component } from '@angular/core';
import { FormControl, Validators, FormGroup } from '@angular/forms';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  angForm = new FormGroup({
    name: new FormControl('Krunal', Validators.maxLength(10)),
    age: new FormControl(26, Validators.required),
    college: new FormControl('VVP College'),
  });
  
  onFormSubmit(): void {
    console.log('Name:' + this.angForm.get('name').value);
    console.log('Age:' + this.angForm.get('age').value);
    console.log('College:' + this.angForm.get('college').value);
  } 
}  
```  
  
## FormArray
  
```
import { Component } from '@angular/core';
import { FormControl, FormGroup, FormArray, Validators } from '@angular/forms';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  angForm = new FormGroup({
    names: new FormArray([
      new FormControl('', Validators.required),
      new FormControl('', Validators.required),
    ])
  });
  
  get names(): FormArray { 
    return this.angForm.get('names') as FormArray; 
 }

  addNameField() { 
    this.names.push(new FormControl('', Validators.required)); 
  }
  
  deleteNameField(index: number) {
    this.names.removeAt(index);
  }

  onFormSubmit(): void {
    for(let i = 0; i < this.names.length; i++) {
      console.log(this.names.at(i).value);
    } 
  }
}  
```  
