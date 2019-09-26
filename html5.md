# HTML
## [html tutorial](https://www.tutorialrepublic.com/html-tutorial/)

### [Html5 canvas](https://www.tutorialrepublic.com/html-tutorial/html5-canvas.php)
```
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Drawing on Canvas</title>
<script>
    window.onload = function() {
        var canvas = document.getElementById("myCanvas");
        var context = canvas.getContext("2d");
        // draw stuff here
    };
</script>
</head>
<body>
    <canvas id="myCanvas" width="300" height="200"></canvas>
</body>
</html>
```

## [Form](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/form)
```
<form action="" method="post">
  <label for="POST-name">Name:</label>
  <input id="POST-name" type="text" name="name">
  <input type="submit" value="Save">
</form>
```

## [select](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/select)
```
<select name="text"> <!--Supplement an id here instead of using 'text'-->
  <option value="first">First Value</option> 
  <option value="second" selected>Second Value</option>
  <option value="third">Third Value</option>
</select>
```

## [fieldset](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/fieldset)
Used to group several controls as well as labels (<label>) within a web form.
```
<form action="test.php" method="post">
  <fieldset>
    <legend>Title</legend>
    <input type="radio" id="radio">
    <label for="radio">Click me</label>
  </fieldset>
</form>
```
  
##[datalist](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/datalist)
 contains a set of <option> elements that represent the values available for other controls.
```
<label for="myBrowser">Choose a browser from this list:</label>
<input list="browsers" id="myBrowser" name="myBrowser" />
<datalist id="browsers">
  <option value="Chrome">
  <option value="Firefox">
  <option value="Internet Explorer">
  <option value="Opera">
  <option value="Safari">
  <option value="Microsoft Edge">
</datalist>
```

## [input types](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/input)
```
<input id="input1" type="text">
<input id="input2" type="text">
```
- button: A push button with no default behavior.
- submit: A button that submits the form.
- reset: A button that resets the contents of the form to default values.
- image: A graphical submit button. You must use the src attribute to define the source of the image and the alt attribute to define alternative text. You can use the height and width attributes to define the size of the image in pixels.
- checkbox: A check box allowing single values to be selected/deselected.
- radio: A radio button, allowing a single value to be selected out of multiple choices.
- text: A single-line text field. Line-breaks are automatically removed from the input value.
- file: A control that lets the user select a file. Use the accept attribute to define the types of files that the control can select.
- hidden: A control that is not displayed but whose value is submitted to the server.
- password: A single-line text field whose value is obscured. Use the maxlength and minlength attributes to specify the maximum length of the value that can be entered.

### HTML5 inputs:
- search: A single-line text field for entering search strings. Line-breaks are automatically removed from the input value.
- email:  A field for editing an e-mail address.
- tel:  A control for entering a telephone number.
- url:  A field for entering a URL.
- number: A control for entering a number.
- range:  A control for entering a number whose exact value is not important.
- color:  A control for specifying a color. A color picker's UI has no required features other than accepting simple colors as text.
- date:   A control for entering a date (year, month, and day, with no time).
- time:   A control for entering a time value with no time zone.
- datetime-local:  A control for entering a date and time, with no time zone.
- month:  A control for entering a month and year, with no time zone.
- week:   A control for entering a date consisting of a week-year number and a week number with no time zone.
- datetime*: Obsoleted. A control for entering a date and time (hour, minute, second, and fraction of a second) based on UTC time zone. This feature has been removed from WHATWG HTML.  

```
type=button: link, menuitem, menuitemcheckbox, menuitemradio, radio, switch, tab
type=checkbox: button, menuitemcheckbox, option, switch
type=image: link, menuitem, menuitemcheckbox, menuitemradio, radio, switch
type=radio: menuitemradio
type=color|date|datetime|datetime-local|email|file: None
type=hidden|month|number|password|range|reset: None
type=search|submit|tel|text|url|week: None

search:  <input type="search" name="search">
email:   <input type="email" name="email" required>
url:     <input type="url" name="url" required>
tel:     <input type="tel" name="tel" id="tel" required>
number:  <input type="text" pattern="[0-9]*" name="shoe-size">
    <input type="number" min="5" max="18" step="0.5" value="9" name="shoe-size">
range:   <input id="skill" type="range" min="1" max="100" value="0">
date:    <input id="startdate" name="startdate" min="2012-01-01" max="2013-01-01" type="date">
month:   <input id="expiry" name="expiry" type="month" required>
week:    <input id="vacation" name="vacation" type="week">
time:    <input id="exit-time" name="exit-time" type="time">
datetime: <input id="entry-day-time" name="entry-day-time" type="datetime">
datetime-local:  <input id="arrival-time" name="arrival-time " type="datetime-local">
color:    <input id="color" name="color" type="color">
```

## [SpringBoot + Bootstrap + jQuery](https://dzone.com/articles/spring-boot-integrating-with-bootstrap-and-jquery)
- (Webjar)[https://www.webjars.org/]
```
<dependency>
    <groupId>org.webjars</groupId>
    <artifactId>bootstrap</artifactId>
    <version>4.1.2</version>
</dependency>
<dependency>
    <groupId>org.webjars</groupId>
    <artifactId>bootstrap-datepicker</artifactId>
    <version>1.0.1</version>
</dependency>
<dependency>
    <groupId>org.webjars</groupId>
    <artifactId>jquery</artifactId>
    <version>3.3.1-1</version>
</dependency>
```
