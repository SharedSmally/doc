# JSON Forms
The JSON Form Library is a client-side JavaScript library that takes a structured data form defined using the JSON schema 
as input and returns an easy-to-run Bootstrap 3 HTML form that matches the schema.

## Document
- [Json Forms](https://jsonforms.io/)
- [Json Github](https://github.com/jsonform/jsonform)
- [Bootstrap 4 JSON Form](https://ambersnow.github.io/bs-jsonform/list.html)

## Angular vs Reactjs - Frontend JS framework
Angular is a Javascript framework built using Typescript, while Reactjs is a Javascript library and built using JSX. 
Angular is mostly used to build complex enterprise-grade apps like single-page apps and progressive web apps, 
while React is used to build UI components in any app with frequently variable data.

These are the steps of our tutorial:
- Installing Angular CLI v13
- Installing Bootstrap 5 in Your Angular 13 Project
- Method 1 : Adding Bootstrap 5 to Angular 13 Usingangular.json
- Method 2 : Adding Bootstrap 5 to Angular 13 Usingindex.html
- Method 3 : Adding Bootstrap 5 to Angular 13 Using ng-bootstrap and ngx-bootstrap

## Tutorial

JSON Forms utilizes the capabilities of JSON and JSON schema and provides a simple and declarative way of describing forms. 
Forms are then rendered with a UI library or framework, e.g. React or Angular.

Any UI is defined by using two schemata:
- the data/JSON schema defines the underlying data to be shown in the UI (objects, properties, and their types);
- the UI schema defines how this data is rendered as a form, e.g. the order of controls, their visibility, and the layout.

## UI Controls

## Samples
Here's the JSON schema, which defines a simple task entity:
```
{
  "type":"object",
  "properties":{
    "name":{
      "type":"string"
    },
    "description":{
      "type":"string"
    },
    "done":{
      "type":"boolean"
    },
    "rating":{
      "type":"integer"
    }
  },
  "required":[
    "name"
  ]
}
```
And here's the respective UI schema:
```
{
  "type":"VerticalLayout",
  "elements":[
    {
      "type":"Control",
      "scope":"#/properties/name"
    },
    {
      "type":"Control",
      "scope":"#/properties/description",
      "options":{
        "multi":true
      }
    },
    {
      "type":"Control",
      "label":"Rating",
      "scope":"#/properties/rating"
    },
    {
      "type":"Control",
      "label":"Done?",
      "scope":"#/properties/done"
    }
  ]
}
```

