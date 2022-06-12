# Angular Data Binding
Binding links the result of a property (Component ) with a template (html).

## Component 
The controller (Component) has properties, which might be methods or data:
```
{
  user: {
    name: 'Jeremy',
    img: 'http://example....'
  },
  save: function() {…}
```
## Interpolative Binding:   using  {{ }}, from component to template element
The binding works by taking an expression, evaluating it, and replacing the binding with the result.
```
<p>{{user.name}}</p>

{{10 + 20}}   <!-- 1. Calculates the value of two numbers, adds to 30 -->

{{'Just a simple string'}}   <!-- 2. Outputs a string "Just a simple string" -->

<a href="/users/{{user.user_id}}">View Profile</a>  <!-- 3. Binds into an attribute value, to link to profile -->

{{user.first_name}} {{user.last_name}}   <!-- 4. Outputs first and last name -->

{{getName()}}      <!-- 5. Calls a method in the controller that should return a string -->
```
Interpolations always use the **{{value}}** syntax to bind data into the template. Anything between the double curly braces is evaluated to render some text.

These expressions are evaluated within the context of the component, meaning the component controller should have a property called
user and a getName() method. The expression context is how the view resolves what a particular value refers to, so {{user.name}} is resolved based on the user.name property from the controller


## Property Binding:  using  [ ]; from component to template element
Bind values to properties of an element to modify their behavior or appearance.
This can include properties such as class , disabled , href , or textContent . Property
bindings also allow to bind to custom component properties.
```
<img [src]="user.img" />
<p [textContent]="user.name"></p>
```
The syntax for property bindings is to put the property onto the element wrapped
in brackets ( [] ). The name should match the property, usually in camel case, like
textContent . 

Interpolation is a shortcut for a property binding to the textContent property of an
element. The bindings are evaluated in the component context, so the
binding will reference properties of the controller. The [src]="user.img"
property binding, which does the same thing as src="{{user.img}}"

Using the [] syntax binds to an element’s property, not the attribute. This is an
important distinction, because properties are the DOM element’s property.

There are a couple of special property bindings for setting a class and style property
for an element.
- The class property on an element is a DOMTokenList:
```
<!-- isActive() returns true or false in order to set active class -->
<h1 class="leading" [class.active]="isActive()">Title</h1>
<!-- Renders to the following -->
<h1 class="leading accent">Title</h1>
```
- the style property is a CSSStyleDeclaration object that holds all the CSS properties
```
<!-- getColor() returns a valid color -->
<h1 [style.color]="getColor()">Title</h1>
<h1 [style.line-height.em]="'2'">Title</h1>
<!-- Renders to the following -->
<h1 style="color: blue;">Title</h1>
<h1 style="line-height: 2em;">Title</h1>
```

## Attribute Binding; from component to template element
Some element properties can’t be directly bound, because some HTML elements have
attributes that aren't also made available as properties of the element. The aria (acces-
sibility) attributes are one such example of an attribute.

Similar to property binding, the special attribute binding syntax need to put the name of 
the attribute in the brackets with the prefix attr.:
```
<input id="username" type="text" [attr.aria-required]="isRequired()" />
```


## Event binding: using ()
The syntax for event bindings uses parentheses () to bind to a known event.
It calls a method on the component controller to handle the event:
```
<form style="margin-bottom: 5px;" (submit)="add()">
  <input name="stock" [(ngModel)]="stock" class="mdl-textfield__input" type="text" placeholder="Add Stock" />
</form>
```
The event binding only binds up to the current component, but it triggers events
and those will bubble up to parent elements and components if they’re listening.

The two-way binding approach: using **[()]**, with both the property and event binding syntax together.
It does this by doing a regular property binding and setting up an event binding behind the scenes.
It can only use NgModel with form elements, but can use two-way binding syntax on properties.

