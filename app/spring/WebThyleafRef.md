# Thymeleaf
- [Reference](https://www.thymeleaf.org/doc/tutorials/3.0/usingthymeleaf.html)

## Standard Expression Syntax
- Simple expressions:
``` 
        Variable Expressions: ${...}
        Selection Variable Expressions: *{...}
        Message Expressions: #{...}
        Link URL Expressions: @{...}
        Fragment Expressions: ~{...}
```
- Literals
``` 
        Text literals: 'one text', 'Another one!',…
        Number literals: 0, 34, 3.0, 12.3,…
        Boolean literals: true, false
        Null literal: null
        Literal tokens: one, sometext, main,…
```        
- Text operations:
``` 
        String concatenation: +
        Literal substitutions: |The name is ${name}|
```
- Arithmetic operations:
```
        Binary operators: +, -, *, /, %
        Minus sign (unary operator): -
```        
- Boolean operations:
``` 
        Binary operators: and, or
        Boolean negation (unary operator): !, not
```        
- Comparisons and equality:
``` 
        Comparators: >, <, >=, <= (gt, lt, ge, le)
        Equality operators: ==, != (eq, ne)
```        
- Conditional operators:
``` 
        If-then: (if) ? (then)
        If-then-else: (if) ? (then) : (else)
        Default: (value) ?: (defaultvalue)
```        
- Special tokens:
``` 
        No-Operation: _
```

## Syntax
### Variables
 ${...} expressions are OGNL expressions executed on the map of variables contained in the context. 
```
<p>Today is: <span th:text="${today}">13 february 2011</span>.</p>  :  ctx.getVariable("today"); 
```

### Selection Variable Expressions: *{...}

the asterisk syntax evaluates expressions on selected objects rather than on the whole context. That is, as long as there is no selected object, the dollar and the asterisk syntaxes do exactly the same.
```
  <div th:object="${session.user}">
    <p>Name: <span th:text="*{firstName}">Sebastian</span>.</p>
    <p>Surname: <span th:text="*{lastName}">Pepper</span>.</p>
    <p>Nationality: <span th:text="*{nationality}">Saturn</span>.</p>
  </div>
```

### Message Expressions: #{...}:
```
<p th:utext="#{home.welcome}">Welcome to our grocery store!</p>
<p th:utext="#{home.welcome(${session.user.name})}">    :  ((User) ctx.getVariable("session").get("user")).getName();
      Welcome to our grocery store, Sebastian Pepper!
</p>
```
These objects will be referenced (per OGNL standard) starting with the # symbol:

- #ctx: the context object.
- #vars: the context variables.
- #locale: the context locale.
- #request: (only in Web Contexts) the HttpServletRequest object.
- #response: (only in Web Contexts) the HttpServletResponse object.
- #session: (only in Web Contexts) the HttpSession object.
- #servletContext: (only in Web Contexts) the ServletContext object.

Utilities Objects
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
<p>
  Today is: <span th:text="${#calendars.format(today,'dd MMMM yyyy')}">13 May 2011</span>
</p>
```

### Link URLs: @{...}
```
<!-- Will produce 'http://localhost:8080/gtvg/order/details?orderId=3' (plus rewriting) -->
<a href="details.html" th:href="@{http://localhost:8080/gtvg/order/details(orderId=${o.id})}">view</a>

<!-- Will produce '/gtvg/order/details?orderId=3' (plus rewriting) -->
<a href="details.html" th:href="@{/order/details(orderId=${o.id})}">view</a>

<!-- Will produce '/gtvg/order/3/details' (plus rewriting) -->
<a href="details.html" th:href="@{/order/{orderId}/details(orderId=${o.id})}">view</a>
```

### Fragments
Fragment expressions are an easy way to represent fragments of markup and move them around templates. This allows us to replicate them, pass them to other templates as arguments, and so on.

The most common use is for fragment insertion using th:insert or th:replace (more on these in a later section):
```
<div th:insert="~{commons :: main}">...</div>
<div th:with="frag=~{footer :: #main/text()}">
  <p th:insert="${frag}">
</div>
```
