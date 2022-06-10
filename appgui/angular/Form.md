# Angular Form
- Template Driven Forms:  the form's construction is performed inside the view.
    -  NgModel
    -  NgModelGroup
    -  NgForm
- Reactive Forms: form is created when the view is being built, for complex form
    - FormControlDirective/FormControlName/FormControl: a class that tracks the value and validation status of an individual form control. 
    - FormGroupDirective/FormGroupName/FormGroup: A list of FormControl with Validator
    - FormArrayName; FormArray: Array of FormControl, FormGroup, or FormArray instances.
    - FormBuilder: create FormControl, FormGroup, and FormArray.

## Template Driven Forms in html
```
<form> <!-- `NgForm` - automatically bound to `<form>` -->
  <input type="text" ngModel name="companyName"/>

  <div ngModelGroup="personal">
    <input type="text" ngModel name="name"/>

    <div ngModelGroup="address">
      <input type="text" ngModel name="city"/>
      <input type="text" ngModel name="street" />
    </div>
  </div>
</form>
```

## Reactive Forms in ts
```
<form [formGroup]="myFormGroup">
  <!-- path: 'name' -->
  <input formControlName="name" type="text">

  <!-- path: 'address' -->
  <ng-container formGroupName="address">
    <!-- path: ['address', 'city'] -->
    <input formControlName="city" type="text">

    <!-- path: ['address', 'street'] -->
    <input formControlName="street" type="text">
  </ng-container>
</form>
```

### FormControl

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
  
### FormGroup

FormGroup is used with FormControl to track the value and validate the state of form control. It aggregates the values of each child FormControl into a single object, using each control name as the key. It calculates its status by reducing the status values of its children so that if one control in a group is invalid, the entire group is rendered invalid.

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

The Angular reactive forms API makes it possible to nest a form group inside another form group.

### FormArray
  
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

In app.component.html:
```
<form [formGroup] = "angForm" (ngSubmit)="onFormSubmit()">
  <div formArrayName="names">
    <div *ngFor="let name of names.controls; index as idx">
      <input [formControlName]="idx" placeholder="Enter a Name">
      <label *ngIf="name.invalid" [ngClass] = "'error'"> Name is required. </label>
      <button (click)="deleteNameField(idx)">Delete</button>
    </div>
  </div> 
  <div>
    <button type="submit">Send</button>
    <button type="button" (click)="addNameField()">Add More Names</button>
  </div>
</form>
```

## FormBuilder

```
import { Component } from '@angular/core';
import { FormBuilder } from '@angular/forms';
@Component({
  selector: 'app-employeeDetails-editor',
  templateUrl: './employeeDetails-editor.component.html',
  styleUrls: ['./employeeDetails-editor.component.css']
})

export class EmployeeDetailsEditorComponent {
  employeeDetailsForm = this.fb.group({
    firstName: ['', Validators.required],
    lastName: [''],
    address: this.fb.group({
      street: [''],
      city: [''],
      state: [''],
      zip: ['']
    }),
  });

  constructor(private fb: FormBuilder) { }
}
```

## Validators
Angular comes with a small set of pre-built validators to match the ones we can define via standard HTML5 attributes, namely required, minlegth, maxlength and pattern which we can access from the Validators module.
```
    // user details form validations
    this.userDetailsForm = this.fb.group({
      pseudo: new FormControl('', Validators.required),
      email: new FormControl(
        '',
        Validators.compose([
          Validators.required,
          Validators.pattern('^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+.[a-zA-Z0-9-.]+$')
        ])
      ),
      matching_passwords: this.matching_passwords_group,
      terms: new FormControl(false, Validators.pattern('true'))
    });
```

##  Model Driven Template Reactive forms
