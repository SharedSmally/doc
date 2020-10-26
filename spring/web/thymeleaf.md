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


## Setting Attribute Values
- Setting the value of any attribute
```
<form action="subscribe.html" th:attr="action=@{/subscribe}">
  <fieldset>
    <input type="text" name="email" />
    <input type="submit" value="Subscribe!" th:attr="value=#{subscribe.submit}"/>
  </fieldset>
</form>
```
- Setting value to specific attributes
```
<form action="subscribe.html" th:action="@{/subscribe}">
   <input type="submit" value="Subscribe!" th:value="#{subscribe.submit}"/>
```
HTML5 attributes:
```
th:abbr	th:accept	th:accept-charset
th:accesskey	th:action	th:align
th:alt	th:archive	th:audio
th:autocomplete	th:axis	th:background
th:bgcolor	th:border	th:cellpadding
th:cellspacing	th:challenge	th:charset
th:cite	th:class	th:classid
th:codebase	th:codetype	th:cols
th:colspan	th:compact	th:content
th:contenteditable	th:contextmenu	th:data
th:datetime	th:dir	th:draggable
th:dropzone	th:enctype	th:for
th:form	th:formaction	th:formenctype
th:formmethod	th:formtarget	th:fragment
th:frame	th:frameborder	th:headers
th:height	th:high	th:href
th:hreflang	th:hspace	th:http-equiv
th:icon	th:id	th:inline
th:keytype	th:kind	th:label
th:lang	th:list	th:longdesc
th:low	th:manifest	th:marginheight
th:marginwidth	th:max	th:maxlength
th:media	th:method	th:min
th:name	th:onabort	th:onafterprint
th:onbeforeprint	th:onbeforeunload	th:onblur
th:oncanplay	th:oncanplaythrough	th:onchange
th:onclick	th:oncontextmenu	th:ondblclick
th:ondrag	th:ondragend	th:ondragenter
th:ondragleave	th:ondragover	th:ondragstart
th:ondrop	th:ondurationchange	th:onemptied
th:onended	th:onerror	th:onfocus
th:onformchange	th:onforminput	th:onhashchange
th:oninput	th:oninvalid	th:onkeydown
th:onkeypress	th:onkeyup	th:onload
th:onloadeddata	th:onloadedmetadata	th:onloadstart
th:onmessage	th:onmousedown	th:onmousemove
th:onmouseout	th:onmouseover	th:onmouseup
th:onmousewheel	th:onoffline	th:ononline
th:onpause	th:onplay	th:onplaying
th:onpopstate	th:onprogress	th:onratechange
th:onreadystatechange	th:onredo	th:onreset
th:onresize	th:onscroll	th:onseeked
th:onseeking	th:onselect	th:onshow
th:onstalled	th:onstorage	th:onsubmit
th:onsuspend	th:ontimeupdate	th:onundo
th:onunload	th:onvolumechange	th:onwaiting
th:optimum	th:pattern	th:placeholder
th:poster	th:preload	th:radiogroup
th:rel	th:rev	th:rows
th:rowspan	th:rules	th:sandbox
th:scheme	th:scope	th:scrolling
th:size	th:sizes	th:span
th:spellcheck	th:src	th:srclang
th:standby	th:start	th:step
th:style	th:summary	th:tabindex
th:target	th:title	th:type
th:usemap	th:value	th:valuetype
th:vspace	th:width	th:wrap
th:xmlbase	th:xmllang	th:xmlspace
```
- Setting more than one value at a time
    - th:alt-title will set alt and title.
    - th:lang-xmllang will set lang and xml:lang.
```
<img src="../../images/gtvglogo.png" th:src="@{/images/gtvglogo.png}" th:alt-title="#{logo}" />
```

### Appending and prepending
th:attrappend/th:attrprepend: append (suffix) or prepend (prefix) the result of their evaluation to the existing attribute values
```
<input type="button" value="Do it!" class="btn" th:attrappend="class=${' ' + cssStyle}" />
```
two specific appending attributes: th:classappend and th:styleappend
```
<tr th:each="prod : ${prods}" class="row" th:classappend="${prodStat.odd}? 'odd'">
```

### Fixed-value boolean attributes: HTML boolean attributes that have no value and the presence means true.
```
<input type="checkbox" name="option2" checked /> <!-- HTML -->
<input type="checkbox" name="option1" checked="checked" /> <!-- XHTML -->

<input type="checkbox" name="active" th:checked="${user.active}" />
```
The fixed-value boolean attributes exist in the Standard Dialect:
```
th:async	        th:autofocus	  th:autoplay
th:checked	      th:controls	    th:declare
th:default	      th:defer	      th:disabled
th:formnovalidate	th:hidden	      th:ismap
th:loop	          th:multiple	    th:novalidate
th:nowrap	        th:open	        th:pubdate
th:readonly	      th:required	    th:reversed
th:scoped	        th:seamless	    th:selected
```
### Setting the value of any attribute
Set the value of any attribute, even if no specific th:* processor has been defined for it at the Standard Dialect
```
<span th:whatever="${user.name}">...</span>   => <span whatever="John Apricot">...</span>
```

### Support for HTML5-friendly attribute and element names

The data-{prefix}-{name} syntax is the standard way to write custom attributes in HTML5, without requiring developers to use any namespaced names like th:\*. There is also a syntax to specify custom tags: {prefix}-{name}, that follows the W3C Custom Elements.
```
    <tr data-th-each="user : ${users}">
        <td data-th-text="${user.login}">...</td>
        <td data-th-text="${user.name}">...</td>
    </tr>
```

## Iteration
- use th:each
```
      <tr th:each="prod : ${prods}">
        <td th:text="${prod.name}">Onions</td>
        <td th:text="${prod.price}">2.41</td>
        <td th:text="${prod.inStock}? #{true} : #{false}">yes</td>
      </tr>
```
- Keeping iteration status: always create one with suffix Stat to iteration variable name if not set explicitly
Status variables are defined within a th:each attribute and contain the following data:
    - The current iteration index, starting with 0. This is the index property.
    - The current iteration index, starting with 1. This is the count property.
    - The total amount of elements in the iterated variable. This is the size property.
    - The iter variable for each iteration. This is the current property.
    - Whether the current iteration is even or odd. These are the even/odd boolean properties.
    - Whether the current iteration is the first one. This is the first boolean property.
    - Whether the current iteration is the last one. This is the last boolean property.
```
  <tr th:each="prod,iterStat : ${prods}" th:class="${iterStat.odd}? 'odd'">
    <td th:text="${prod.name}">Onions</td>
    <td th:text="${prod.price}">2.41</td>
    <td th:text="${prod.inStock}? #{true} : #{false}">yes</td>
  </tr>
```
- Optimizing through lazy retrieval of data
```
<li th:each="u : ${users}" th:text="${u.name}">user name</li>
```

### Conditional Evaluation
- Simple if conditionals: th:if, th:unless
```
<a href="comments.html" th:href="@{/product/comments(prodId=${prod.id})}"  th:if="${not #lists.isEmpty(prod.comments)}">view</a>
<a href="comments.html" th:href="@{/comments(prodId=${prod.id})}" th:unless="${#lists.isEmpty(prod.comments)}">view</a>
```

- Switch statements: default option is specified as th:case="*":
```
<div th:switch="${user.role}">
  <p th:case="'admin'">User is an administrator</p>
  <p th:case="#{roles.manager}">User is a manager</p>
  <p th:case="*">User is some other thing</p>
</div>
```

## Template Layout
- define fragments: th.fragment: copy fragment in /WEB-INF/templates/footer.html
```
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
  <body> 
    <div th:fragment="copy"> &copy; 2011 The Good Thymes Virtual Grocery </div>
    <div id="copy-section"> &copy; 2011 The Good Thymes Virtual Grocery </div>
  </body>  
</html>
```

- refer fragments: th.include or th:replace or th:include
```
<body>
  ...
  <div th:insert="~{footer :: copy}"></div> 
  <div th:insert="~{footer :: #copy-section}"></div>
</body>
```
or
```
<div th:insert="footer :: copy"></div>
<div th:insert="footer :: (${user.isAdmin}? #{footer.admin} : #{footer.normaluser})"></div>
```
- Fragment specification syntax
    - ~{templatename::selector}: Includes the fragment resulting from applying the specified Markup Selector on the template named templatename. 
    - ~{templatename}: Includes the complete template named templatename.
    - ~{::selector} / ~{this::selector}: Inserts a fragment from the same template, matching selector

- difference between th:insert and th:replace (and th:include, not recommended)
    - th:insert is the simplest: it will simply insert the specified fragment as the body of its host tag. keep the host tag
    - th:replace actually replaces its host tag with the specified fragment. remove the host tag
    - th:include is similar to th:insert, but instead of inserting the fragment it only inserts the contents of this fragment. keep the host tag, remove fragment tag.

- Parameterizable fragment signatures: functional-like fragments
```
<div th:fragment="frag (onevar,twovar)">
    <p th:text="${onevar} + ' - ' + ${twovar}">...</p>
</div>
```
```
<div th:replace="::frag (${value1},${value2})">...</div>
<div th:replace="::frag (onevar=${value1},twovar=${value2})">...</div>
<div th:replace="::frag (twovar=${value2},onevar=${value1})">...</div>
```
 th:assert attribute can specify a comma-separated list of expressions which should be evaluated and produce true for every evaluation, raising an exception if not.
 ```
 <div th:assert="${onevar},(${twovar} != 43)">...</div>
 ```
 
 - th:remove:
 ```
   <tr th:remove="all">
    <td>Mild Cinnamon</td>
    <td>1.99</td>
    <td>yes</td>
    <td>
      <span>3</span> comment/s
      <a href="comments.html">view</a>
    </td>
  </tr>
 ```
    - all: Remove both the containing tag and all its children.
    - body: Do not remove the containing tag, but remove all its children.
    - tag: Remove the containing tag, but do not remove its children.
    - all-but-first: Remove all children of the containing tag except the first one.
    - none : Do nothing. This value is useful for dynamic evaluation.

- Layout Inheritance
```
<!DOCTYPE html>
<html th:replace="~{layoutFile :: layout(~{::title}, ~{::section})}">
<head>
    <title>Page Title</title>
</head>
<body>
<section>
    <p>Page content</p>
    <div>Included on page</div>
</section>
</body>
</html>
```
## Local Variables

Thymeleaf calls local variables the variables that are defined for a specific fragment of a template, and are only available for evaluation inside that fragment.
```
<div th:with="firstPer=${persons[0]},secondPer=${persons[1]}">
  <p>
    The name of the first person is <span th:text="${firstPer.name}">Julius Caesar</span>.
  </p>
  <p>
    But the name of the second person is <span th:text="${secondPer.name}">Marcus Antonius</span>.
  </p>
</div>
```

## Attribute Precedence
```
Order	Feature	Attributes
1	Fragment inclusion	              th:insert, th:replace
2	Fragment iteration	              th:each
3	Conditional evaluation	          th:if,th:unless,th:switch,th:case
4	Local variable definition	        th:object,th:with
5	General attribute modification	  th:attr,th:attrprepend,th:attrappend
6	Specific attribute modification	  th:value,th:href,th:src,...
7	Text (tag body modification)	    th:text,th:utext
8	Fragment specification	          th:fragment
9	Fragment removal	                th:remove
```

## Blocks
- Comments:
```
<!-- User info follows -->
<!--/* This code will be removed at Thymeleaf parsing time! */-->
```
- Synthetic th:block tag
```
<table>
  <th:block th:each="user : ${users}">
    <tr>
        <td th:text="${user.login}">...</td>
        <td th:text="${user.name}">...</td>
    </tr>
    <tr>
        <td colspan="2" th:text="${user.address}">...</td>
    </tr>
  </th:block>
</table>
```
- Inlining
```
<p>Hello, [[${session.user.name}]]!</p> 
```
instead of
```
<p>Hello, <span th:text="${session.user.name}">Sebastian</span>!</p>
```
- Disabling inlining:
```
<p th:inline="none">A double array looks like this: [[1, 2, 3], [4, 5]]!</p>
```
- JavaScript inlining
```
<script th:inline="javascript">
    ...
    var username = [[${session.user.name}]];
    ...
</script>
```
- CSS inlining
```
<style th:inline="css">
    .[[${classname}]] { text-align: [[${align}]]; }
</style>
```

## [Expression Basic Objects](https://www.thymeleaf.org/doc/tutorials/3.0/usingthymeleaf.html#base-objects)
