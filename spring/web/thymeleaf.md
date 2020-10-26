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

### Variables expression: ${...}: 
[OGNL (Object-Graph Navigation Language)](http://commons.apache.org/proper/commons-ognl/) expressions executed on the map of variables contained in the context
```
<p>Today is: <span th:text="${today}">13 february 2011</span>.</p>    =>  ctx.getVariable("today");
<p th:utext="#{home.welcome(${session.user.name})}"> Welcome to our grocery store, Sebastian Pepper! </p>  => ((User) ctx.getVariable("session").get("user")).getName();
```
- Access to properties:  ${person.father.name}; ${person['father']['name']}
- Access map properties: ${countriesByCode.ES}; ${personsByName['Stephen Zucchini'].age}
- Access arrays/collections: ${personsArray[0].name}
- Call Mehtods: ${person.createCompleteName()}; ${person.createCompleteNameWithSeparator('-')}

### Expression Basic Objects: starts with # symbol
- #ctx: the context object.
- #vars: the context variables.
- #locale: the context locale.
- #request: (only in Web Contexts) the HttpServletRequest object.
- #response: (only in Web Contexts) the HttpServletResponse object.
- #session: (only in Web Contexts) the HttpSession object.
- #servletContext: (only in Web Contexts) the ServletContext object.
```
Established locale country: <span th:text="${#locale.country}">US</span>.
```
### Expression Utility Objects
- #execInfo: information about the template being processed.
- #messages: methods for obtaining externalized messages inside variables expressions, in the same way as they would be obtained using #{…} syntax.
- #uris: methods for escaping parts of URLs/URIs
- #conversions: methods for executing the configured conversion service (if any).
- #dates: methods for java.util.Date objects: formatting, component extraction, etc.
- #calendars: analogous to #dates, but for java.util.Calendar objects.
- #numbers: methods for formatting numeric objects.
- #strings: methods for String objects: contains, startsWith, prepending/appending, etc.
- #objects: methods for objects in general.
- #bools: methods for boolean evaluation.
- #arrays: methods for arrays.
- #lists: methods for lists.
- #sets: methods for sets.
- #maps: methods for maps.
- #aggregates: methods for creating aggregates on arrays or collections.
- #ids: methods for dealing with id attributes that might be repeated (for example, as a result of an iteration).
```
Today is: <span th:text="${#calendars.format(today,'dd MMMM yyyy')}">13 May 2011</span>
```

### Expressions on selections: \*{...}
The asterisk syntax evaluates expressions on selected objects rather than on the whole context. That is, as long as there is no selected object, the dollar and the asterisk syntaxes do exactly the same.
```
  <div th:object="${session.user}">
    <p>Name: <span th:text="*{firstName}">Sebastian</span>.</p>
    <p>Surname: <span th:text="*{lastName}">Pepper</span>.</p>
    <p>Nationality: <span th:text="*{nationality}">Saturn</span>.</p>
  </div>
```
Same as
```
<div>
  <p>Name: <span th:text="${session.user.firstName}">Sebastian</span>.</p>
  <p>Surname: <span th:text="${session.user.lastName}">Pepper</span>.</p>
  <p>Nationality: <span th:text="${session.user.nationality}">Saturn</span>.</p>
</div>
```

### Link URLs: \@{...}
- Absolute URLs: http://www.thymeleaf.org
- Relative URLs, which can be:
     - Page-relative: user/login.html
     - Context-relative: /itemdetails?id=3 (context name in server will be added automatically)
     - Server-relative: ~/billing/processInvoice (allows calling URLs in another context (= application) in the same server.
     - Protocol-relative URLs: //code.jquery.com/jquery-2.0.3.min.js
```
<!-- Will produce 'http://localhost:8080/gtvg/order/details?orderId=3' (plus rewriting) -->
<a href="details.html" th:href="@{http://localhost:8080/gtvg/order/details(orderId=${o.id})}">view</a>

<!-- Will produce '/gtvg/order/details?orderId=3' (plus rewriting) -->
<a href="details.html" th:href="@{/order/details(orderId=${o.id})}">view</a>

<!-- Will produce '/gtvg/order/3/details' (plus rewriting) -->
<a href="details.html" th:href="@{/order/{orderId}/details(orderId=${o.id})}">view</a>

<a th:href="@{${url}(orderId=${o.id})}">view</a>
<a th:href="@{'/details/'+${user.login}(orderId=${o.id})}">view</a>

Server root relative URLs: @{~/path/to/something}
```

### Fragments: th:insert or th:replace
```
<div th:insert="~{commons :: main}">...</div>

<div th:with="frag=~{footer :: #main/text()}">
  <p th:insert="${frag}">
</div>
```

### Literals
- Text literals: character strings specified between single quotes, escape any single quotes inside them using \'.
```
Now you are looking at a <span th:text="'working web application'">template file</span>.
```
- Number literals: numbers
```
<p>The year is <span th:text="2013">1492</span>.</p>
<p>In two years, it will be <span th:text="2013 + 2">1494</span>.</p>
```
- Boolean literals: true and false
```
<div th:if="${user.isAdmin()} == false"> ...
```
- null literal
```
<div th:if="${variable.something} == null"> ...
```
- Literal tokens:  no need any quotes surrounding them
```
<div th:class="content">...</div>
```
### Appending texts: using + operator
```
<span th:text="'The name of the user is ' + ${user.name}">
```

### Literal substitutions:  surrounded by vertical bars (|), Only variable/message expressions (\${...}, \*{...}, \#{...}) are allowed inside 
```
<span th:text="|Welcome to our application, ${user.name}!|">
```
### Arithmetic operations: +, -, \*, \/(div) and %(mod)
```
<div th:with="isEven=${prodStat.count % 2 == 0}">
```

### Comparators and Equality: >(gt), <(lt), >=(ge) and <=(le), == (eq) and != (ne/neq) 
```
<div th:if="${prodStat.count} &gt; 1">
<span th:text="'Execution mode is ' + ( (${execMode} == 'dev')? 'Development' : 'Production')">
```

### Conditional expressions:  (condition, then and else)
```
<tr th:class="${row.even}? 'even' : 'odd'">
<tr th:class="${row.even}? (${row.first}? 'first' : 'even') : 'odd'">
<tr th:class="${row.even}? 'alt'">
  ...
</tr>

```

### Default expressions (Elvis operator): ?:  first if not null,else second
```
<div th:object="${session.user}">
  ...
  <p>Age: <span th:text="*{age}?: '(no age specified)'">27</span>.</p>
  <span th:text="*{firstName}?: (*{admin}? 'Admin' : #{default.username})">Sebastian</span>
</div>
```

### No-Operation token: (\_): do nothing
```
<span th:text="${user.name} ?: _">no user authenticated</span>
```

### Data Conversion / Formatting: ${{...}}, \*{{...}}
```
<td th:text="${{user.lastAccessDate}}">...</td>  apply Calendar -> String conversion
```

### Preprocessing: __${expression}__; modife of the expression that will eventually be executed
```
<p th:text="${__#{article.text('textVar')}__}">Some text here...</p>
```


### Control
