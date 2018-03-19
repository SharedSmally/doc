# groovy


### [Template Engine](http://docs.groovy-lang.org/docs/next/html/documentation/template-engines.html)
The template framework consists of a [TemplateEngine](http://docs.groovy-lang.org/2.4.10/html/api/groovy/text/TemplateEngine.html) abstract base class that engines must implement and a [Template](http://docs.groovy-lang.org/2.4.10/html/api/groovy/text/Template.html) interface that the resulting templates they generate must implement.

Included with Groovy are several template engines:

- [SimpleTemplateEngine](http://docs.groovy-lang.org/2.4.10/html/api/groovy/text/SimpleTemplateEngine.html) - for basic templates
- [StreamingTemplateEngine](http://docs.groovy-lang.org/2.4.10/html/api/groovy/text/SimpleTemplateEngine.html) - functionally equivalent to SimpleTemplateEngine, but can handle strings larger than 64k
- [GStringTemplateEngine](http://docs.groovy-lang.org/2.4.10/html/api/groovy/text/StreamingTemplateEngine.html) - stores the template as writeable closures (useful for streaming scenarios)
- [XmlTemplateEngine](http://docs.groovy-lang.org/2.4.10/html/api/groovy/text/XmlTemplateEngine.html) - works well when the template and output are valid XML
- [MarkupTemplateEngine](http://docs.groovy-lang.org/2.4.10/html/api/groovy/text/markup/MarkupTemplateEngine.html) - a very complete, optimized, template engine
```
TemplateConfiguration config = new TemplateConfiguration();         
MarkupTemplateEngine engine = new MarkupTemplateEngine(config);     
Template template = engine.createTemplate(String|File|URL);    
Map<String, Object> model = new HashMap<>();              
Writable output = template.make(model);                             
output.writeTo(writer);                       
```

### builder

### Builder to create Fluent API
- [Builder](http://docs.groovy-lang.org/2.4.10/html/api/groovy/transform/builder/Builder.html)
- Simple Form
```
import groovy.transform.builder.Builder
import groovy.transform.builder.ExternalStrategy
 
// We don't want to change the definition
// of this class to get a fluent API.
class Message {
    String from, to, subject, body
}
 
// New builder class for the Message class.
@Builder(builderStrategy = ExternalStrategy, forClass = Message)
class MessageBuilder {}
 
def message = new MessageBuilder()  // Create new instance.
        .from('mrhaki@mrhaki.com')
        .to('mail@host.nl')
        .subject('Groovy 2.3 is released')
        .body('Groovy rocks!')
        .build()  // Return filled Message instance.
 
assert message.body == 'Groovy rocks!'
assert message.from == 'mrhaki@mrhaki.com'
assert message.subject == 'Groovy 2.3 is released'
```
- Customized Form
```
import groovy.transform.builder.Builder
import groovy.transform.builder.ExternalStrategy
 
class Message {
    String from, to, subject, body
}
 
@Builder(builderStrategy = ExternalStrategy, forClass = Message,
        prefix = 'assign', buildMethodName = 'create',
        includes = 'from,subject')
class MessageBuilder {}
 
def message = new MessageBuilder()
        .assignFrom('mrhaki@mrhaki.com')
        .assignSubject('Groovy 2.3 is released')
        .create()
 
assert message.from == 'mrhaki@mrhaki.com'
assert message.subject == 'Groovy 2.3 is released'
```
