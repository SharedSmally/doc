# groovy
=====

## [Template Engine](http://docs.groovy-lang.org/docs/next/html/documentation/template-engines.html)
The template framework consists of a TemplateEngine abstract base class that engines must implement and a Template interface that the resulting templates they generate must implement.

Included with Groovy are several template engines:

- SimpleTemplateEngine - for basic templates
- StreamingTemplateEngine - functionally equivalent to SimpleTemplateEngine, but can handle strings larger than 64k
- GStringTemplateEngine - stores the template as writeable closures (useful for streaming scenarios)
- XmlTemplateEngine - works well when the template and output are valid XML
- MarkupTemplateEngine - a very complete, optimized, template engine
```
TemplateConfiguration config = new TemplateConfiguration();         
MarkupTemplateEngine engine = new MarkupTemplateEngine(config);     
Template template = engine.createTemplate(String|File|URL);    
Map<String, Object> model = new HashMap<>();              
Writable output = template.make(model);                             
output.writeTo(writer);                       
```
