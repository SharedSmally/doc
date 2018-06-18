
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

HTML5 inputs:
-search: A single-line text field for entering search strings. Line-breaks are automatically removed from the input value.
-email:  A field for editing an e-mail address.
-tel:  A control for entering a telephone number.
-url:  A field for entering a URL.
-number: A control for entering a number.
-range:  A control for entering a number whose exact value is not important.
-color:  A control for specifying a color. A color picker's UI has no required features other than accepting simple colors as text (more info).
-date:   A control for entering a date (year, month, and day, with no time).
-time:   A control for entering a time value with no time zone.
-datetime-local:  A control for entering a date and time, with no time zone.
-month:  A control for entering a month and year, with no time zone.
-week:   A control for entering a date consisting of a week-year number and a week number with no time zone.
-datetime*: Obsoleted. A control for entering a date and time (hour, minute, second, and fraction of a second) based on UTC time zone. This feature has been removed from WHATWG HTML.  
