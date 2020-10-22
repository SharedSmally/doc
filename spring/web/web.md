# SpringIteb Frsamework
Spring web framework is built on the MVC (Model-View-Controller) pattern, it needs to define a ViewResolver bean corresponding 
for each technology to render each view type, so returning the view names from @Controller mapping methods in the same way as returning JSP files.

Template engines: [Configuration](https://www.baeldung.com/spring-template-engines) and [Comparison](https://springhow.com/spring-boot-template-engines-comparison/)
- Thymeleaf: HTML files should be placed in the resources/templates location
- FreeMarker: placing template files (*.ftl) in the resources/templates folder
- Java Server Pages (JSP): not good
- Groovy: slower; placing template files (*.groovy) in the resources/templates folder using html
- Jade
- Mustache (faster), smiliar to FreeMarker
- Pebble
- jasper: for docs or PDF


## Controllers
- Normal controller: method() return view name, and the corresponding view page is rendered via template engine (template file name without .html suffix)
    - [Pass parameters from Controller to View] (https://www.baeldung.com/spring-mvc-model-model-map-model-view) via Model, ModelMap and ModelView
    - [Config thymeleaf](http://zetcode.com/springboot/thymeleafconfig/): Not needed in autoconfig.
    
- RestController: method() return model object, and the corresponding json string is rendered



## Tips
- th:tag should be in <>:
```
working:  <div>Web Application. Passed spring parameter : <div th:text="${spring}"/></div>
Not work: <div>Web Application. Passed spring parameter : th:text="${spring}"</div>
```
