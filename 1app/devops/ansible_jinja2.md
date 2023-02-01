#[Jinja2 template](https://jinja.palletsprojects.com/en/3.1.x/templates/#builtin-filters)

- Statements
```
    {% ... %} for Statements
    {{ ... }} for Expressions to print to the template output
    {# ... #} for Comments not included in the template output
```
- Variable
```
{{ foo.bar }}
{{ foo['bar'] }}
```
- Filters
Variables can be modified by filters. Filters are separated from the variable by a pipe symbol (|) and may have optional arguments 
in parentheses. Multiple filters can be chained. The output of one filter is applied to the next.
```
{{ name|striptags|title }} : output of (title(striptags(name)))
```
- Tests
```
{% if loop.index is divisibleby 3 %}
{% if loop.index is divisibleby(3) %}
{% if True %}yay{% endif %}
{%+ if True %}yay{% endif %}  # for trim
```
- For statements
```
    {% for item in navigation %}
        <li><a href="{{ item.href }}">{{ item.caption }}</a></li>
    {% endfor %}
```
- Template Inheritance

The base.html template defines the skeleton document using {% block head %}
```
<html lang="en">
<head>
    {% block head %}
    <link rel="stylesheet" href="style.css" />
    <title>{% block title %}{% endblock %} - My Webpage</title>
    {% endblock %}
</head>
<body>
    <div id="content">{% block content %}{% endblock %}</div>
    <div id="footer">
        {% block footer %}
        &copy; Copyright 2008 by <a href="http://domain.invalid/">you</a>.
        {% endblock %}
    </div>
</body>
</html>
```
while the child templates to fill the empty blocks with content:
```
{% extends "base.html" %}
{% block title %}Index{% endblock %}
{% block head %}
    {{ super() }}
    <style type="text/css">
        .important { color: #336699; }
    </style>
{% endblock %}
{% block content %}
    <h1>Index</h1>
    <p class="important">
      Welcome to my awesome homepage.
    </p>
{% endblock %}
```
- Include/Import
```
{% include 'header.html' %}
Body goes here.
{% include 'footer.html' %}
```
