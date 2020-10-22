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
