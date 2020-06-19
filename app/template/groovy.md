# [groovy template](https://docs.groovy-lang.org/docs/next/html/documentation/template-engines.html)
The template framework in Groovy consists of a TemplateEngine abstract base class that engines must implement and a Template interface that the resulting templates they generate must implement.

Included with Groovy are several template engines:
- SimpleTemplateEngine - for basic templates
- StreamingTemplateEngine - functionally equivalent to SimpleTemplateEngine, but can handle strings larger than 64k
- GStringTemplateEngine - stores the template as writeable closures (useful for streaming scenarios)
- XmlTemplateEngine - works well when the template and output are valid XML
- MarkupTemplateEngine - a very complete, optimized, template engine

```
def text = 'Dear "$firstname $lastname",\nSo nice to meet you in <% print city %>.\nSee you in ${month},\n${signed}'
def binding = ["firstname":"Sam", "lastname":"Pullara", "city":"San Francisco", "month":"December", "signed":"Groovy-Dev"]
def engine = new groovy.text.SimpleTemplateEngine()
def template = engine.createTemplate(text).make(binding)
def result = 'Dear "Sam Pullara",\nSo nice to meet you in San Francisco.\nSee you in December,\nGroovy-Dev'
assert result == template.toString()
```

There are other templating solutions that can be used along with Groovy, such as FreeMarker, Velocity, StringTemplate.
