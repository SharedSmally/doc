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
### 
```
<p>Today is: <span th:text="${today}">13 february 2011</span>.</p>  :  ctx.getVariable("today"); 
```

### Selection Variable Expressions: *{...}

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

