# [Thymeleaf](https://www.thymeleaf.org/)
Thymeleaf is a modern server-side Java template engine for both web and standalone environments.
- [Home](https://www.thymeleaf.org/)
- [Document](https://www.thymeleaf.org/documentation.html)
- [Migration](https://www.thymeleaf.org/doc/articles/thymeleaf3migration.html): viewResolver => templateEngine -> templateResolver

## template file
```
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
  <head>
    <title>Good Thymes Virtual Grocery</title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <link rel="stylesheet" type="text/css" media="all" href="../../css/gtvg.css" th:href="@{/css/gtvg.css}" />
  </head>
  <body>
    <p th:text="#{home.welcome}">Welcome to our grocery store!</p>
  </body>
</html>
```
For HTML5-valid template file, using the data- prefix for attribute names and hyphen (-) separators instead of semi-colons (:):
```
<!DOCTYPE html>
<html>
  <head>
    <title>Good Thymes Virtual Grocery</title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <link rel="stylesheet" type="text/css" media="all" href="../../css/gtvg.css" data-th-href="@{/css/gtvg.css}" />
  </head>
  <body>
    <p data-th-text="#{home.welcome}">Welcome to our grocery store!</p> 
  </body>
</html>
```

## Standard Expression Syntax
- Simple expressions:
    - Variable Expressions: ${...}
    - Selection Variable Expressions: *{...}
    - Message Expressions: #{...}
    - Link URL Expressions: @{...}
    - Fragment Expressions: ~{...}
- Literals
    - Text literals: 'one text', 'Another one!',…
    - Number literals: 0, 34, 3.0, 12.3,…
    - Boolean literals: true, false
    - Null literal: null
    - Literal tokens: one, sometext, main,…
- Text operations:
    - String concatenation: +
    - Literal substitutions: |The name is ${name}|
- Arithmetic operations:
    - Binary operators: +, -, *, /, %
    - Minus sign (unary operator): -
- Boolean operations:
    - Binary operators: and, or
    - Boolean negation (unary operator): !, not
- Comparisons and equality:
    - Comparators: >, <, >=, <= (gt, lt, ge, le)
    - Equality operators: ==, != (eq, ne)
- Conditional operators:
    - If-then: (if) ? (then)
    - If-then-else: (if) ? (then) : (else)
    - Default: (value) ?: (defaultvalue)
- Special tokens:
    - No-Operation: _
    
All these features can be combined and nested:
```
'User is of type ' + (${user.isAdmin()} ? 'Administrator' : (${user.type} ?: 'Unknown'))
```

### Message expression: #{...} for static/dynamic message:
 ```
 <p th:utext="#{home.welcome}">Welcome to our grocery store!</p>
 ```
 to
 ```
 home.welcome=¡Bienvenido a nuestra tienda de comestibles!
 ```
If the message is dynamic(pass parameters to message):
```
home.welcome=¡Bienvenido a nuestra tienda de comestibles, {0}!

<p th:utext="#{home.welcome(${session.user.name})}"> Welcome to our grocery store, Sebastian Pepper! </p>
```
 The use of th:utext here means that the formatted message will not be escaped.

### Variables expression: ${...}: [OGNL (Object-Graph Navigation Language)](http://commons.apache.org/proper/commons-ognl/) expressions executed on the map of variables contained in the context


### Control
