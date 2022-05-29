# JSON Forms
The JSON Form Library is a client-side JavaScript library that takes a structured data form defined using the JSON schema 
as input and returns an easy-to-run Bootstrap 3 HTML form that matches the schema.

## Document
- [Json Forms](https://jsonforms.io/)
- [Bootstrap 4 JSON Form](https://ambersnow.github.io/bs-jsonform/list.html)

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

