# groovy
### Call Groovy from Java
- add groovy dependency
```
	<dependency>
    	<groupId>org.codehaus.groovy</groupId>
    	<artifactId>groovy-all</artifactId>
    	<version>2.4.14</version>
	</dependency>
```
- src/main/java/xxx/Obj.java:
```
package com.jpw.jgroovy;
public class Obj {
    public int num;

    public Obj(int num) {
        this.num = num;
    }
}
```
- src/main/java/xxx/App.java: use GroovyClassLoader/GroovyObject
```
package com.jpw.jgroovy;

import groovy.lang.GroovyClassLoader;
import groovy.lang.GroovyObject;

import java.io.File;
import java.io.IOException;

public class App {
    static final GroovyClassLoader classLoader = new GroovyClassLoader();
    public static void main(String[] args) throws IllegalAccessException, IOException, InstantiationException {
    	String path  = classLoader.getResource("SampleScript2.groovy").getPath();
        Class<?> groovy = classLoader.parseClass(new File(path));
        GroovyObject groovyObj = (GroovyObject) groovy.newInstance();
        String output = (String) groovyObj.invokeMethod("process", new Object[] { new Obj(10)});
        System.out.println(output);
    }
}
```
- src/main/resources/SampleScript2.groovy
```
import com.jpw.jgroovy.Obj;
class SampleScript2 {
    String process(Obj obj) {
        if(obj.num ==10)
            return "equal";
        else
            return "not-equal"
    }
}
```
### Basic Java+Groovy Integration: use GroovyShell
```
// call groovy expressions from Java code
Binding binding = new Binding();
binding.setVariable("foo", new Integer(2));
GroovyShell shell = new GroovyShell(binding);

Object value = shell.evaluate(groovyScript);
```
See [examples](https://github.com/framis/exec-groovy-in-java/blob/master/src/test/java/ExecGroovyTest.java) to run script expression, script file, data binding, etc. 

### Template engine + MarkupBuilder
Developping a template engine relying on the Groovy MarkupBuilder. 
- [Example](http://mrhaki.blogspot.com/2014/08/groovy-goodness-use-custom-template.html)
    - Define Template inherits from [BaseTemplate](http://docs.groovy-lang.org/2.4.10/html/api/groovy/text/markup/BaseTemplate.html)
```
import groovy.text.markup.*
import groovy.text.*
 
abstract class FontAwesomeTemplate extends BaseTemplate { 
    FontAwesomeTemplate(final MarkupTemplateEngine templateEngine,
        final Map model, final Map<String,String> modelTypes,
        final TemplateConfiguration configuration) {
        super(templateEngine, model, modelTypes, configuration)
    }
 
    String icon(final String icon, final String[] attributes = []) {
        // Prefix attribute names with fa-.
        final faAttributes = attributes.collect { "fa-$it" }
 
        // Create markup.
        $/<span class="fa fa-${icon} ${faAttributes.join(' ')}"></span>/$
    }
 
}
```
    - Use the new Defined Template
```
import groovy.text.*
import groovy.text.markup.*
 
// Create configuration and set base template class to FontAwesomeTemplate.
TemplateConfiguration config = new TemplateConfiguration(
    baseTemplateClass: FontAwesomeTemplate
)
 
// Create engine with configuration.
MarkupTemplateEngine engine = new MarkupTemplateEngine(config)    
 
// Create template with text using the icon method.
Template template = engine.createTemplate('''
    ul {
        // Use the name of the icon as argument for the icon method.
        li icon('cloud')
 
        // Any extra arguments are assumed to be FontAwesome attributes.
        li icon('pencil', 'large', 'rotate-90')
    }
 
    // If we want to use the icon method in between text we must use the ${stringOf notation}.
    p "This is a ${stringOf {icon('home')}} home icon."
 
    // Or use yieldUnescaped method.
    p {
        yield "This is a "
        yieldUnescaped icon('cog')
        yield " settings icon."
    }
''')   
 
// Render output for template.
Writer writer = new StringWriter()                         
Writable output = template.make([:]) 
output.writeTo(writer)  
String result = writer.toString()
```

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

### Builder with Closures
- Use pre-defined builders like the [JsonBuilder](http://docs.groovy-lang.org/2.4.10/html/api/groovy/json/JsonBuilder.html) or [MarkupBuilder](http://docs.groovy-lang.org/2.4.10/html/api/groovy/xml/MarkupBuilder.html) to create data or text structures
   - JsonBuilder
```
       def builder = new groovy.json.JsonBuilder()
       def root = builder.people {
           person {
               firstName 'Guillame'
               lastName 'Laforge'
               // Named arguments are valid values for objects too
               address(
                       city: 'Paris',
                       country: 'France',
                       zip: 12345,
               )
               married true
               // a list of values
               conferences 'JavaOne', 'Gr8conf'
           }
       }

       // creates a data structure made of maps (Json object) and lists (Json array)
       assert root instanceof Map

       assert builder.toString() == '{"people":{"person":{"firstName":"Guillame","lastName":"Laforge","address":{"city":"Paris","country":"France","zip":12345},"married":true,"conferences":["JavaOne","Gr8conf"]}}}'
```
   - create JSON string using JsonBuilder
```
def message = new MessageBuilder()
        .assignFrom('mrhaki@mrhaki.com')
        .assignSubject('Groovy 2.3 is released')
        .create()

def builder = new groovy.json.JsonBuilder(message)
print "message json="+builder.toString()
```
   - create XML string using [DomBuilder](http://docs.groovy-lang.org/2.4.10/html/api/groovy/xml/DOMBuilder.html) and [DocumentBuilder](https://docs.oracle.com/javase/8/docs/api/javax/xml/parsers/DocumentBuilder.html)
   
   - create XML string using [SAXBuilder](http://docs.groovy-lang.org/2.4.10/html/api/groovy/xml/SAXBuilder.html)
   
   - create XML/HTML string using [MarkupBuilder](http://docs.groovy-lang.org/2.4.10/html/api/groovy/xml/MarkupBuilder.html)
```
new MarkupBuilder().root {
   a( a1:'one' ) {
     b { mkp.yield( '3 < 5' ) }
     c( a2:'two', 'blah' )
   }
 }
 ``` 
Will print the following to System.out:
```
<root>
   <a a1='one'>
     <b>3 &lt; 5</b>
     <c a2='two'>blah</c>
   </a>
 </root>
```

- Simple Builders with Closures
     - A node in the builder is a method and use a closure as the argument of the method to create a new level in the builder hierarchy.
     - Use pre-defined method names in the builder syntax
     - Use dynamic or unkown method names by implementing the methodMissing method.
     - The same goes for properties with real property methods or by implementing the propertyMissing method.
```
// Builder syntax to create a reservation with passengers,
// departing and destination airport and make it a 2-way flight.
def reservation = new ReservationBuilder().make {
    passengers {
        name 'mrhaki'
        name 'Hubert A. Klein Ikkink'
    }
    from 'Schiphol, Amsterdam'
    to 'Kastrup, Copenhagen'
    retourFlight
}
 
assert reservation.flight.from == new Airport(name: 'Schiphol', city: 'Amsterdam')
assert reservation.flight.to == new Airport(name: 'Kastrup', city: 'Copenhagen')
assert reservation.passengers.size() == 2
assert reservation.passengers == [new Person(name: 'mrhaki'), new Person(name: 'Hubert A. Klein Ikkink')]
assert reservation.retourFlight
  
// ----------------------------------------------
// Builder implementation and supporting classes.
// ----------------------------------------------
import groovy.transform.*
@Canonical
class Reservation {
    Flight flight = new Flight()
    List<Person> passengers = []
    Boolean retourFlight = false
}
 
@Canonical
class Person { String name }
 
@Canonical
class Airport { String name, city }
 
@Canonical
class Flight { Airport from, to }
 
// The actual builder for reservations.
class ReservationBuilder {
    // Reservation to make and fill with property values.
    Reservation reservation
 
    private Boolean passengersMode = false
 
    Reservation make(Closure definition) {
        reservation = new Reservation()

        runClosure definition
 
        reservation
    }
 
    void passengers(Closure names) {
        passengersMode = true
 
        runClosure names
 
        passengersMode = false
    }
 
    void name(String personName) {
        if (passengersMode) {
            reservation.passengers << new Person(name: personName)
        } else {
            throw new IllegalStateException("name() only allowed in passengers context.")
        }
    }
 
    def methodMissing(String name, arguments) {
        // to and from method calls will set flight properties
        // with Airport objects.
        if (name in ['to', 'from']) {
            def airport = arguments[0].split(',')
            def airPortname = airport[0].trim()
            def city = airport[1].trim()
            reservation.flight."$name" = new Airport(name: airPortname, city: city)
        }
    }
 
    def propertyMissing(String name) {
        // Property access of retourFlight sets reservation
        // property retourFlight to true.
        if (name == 'retourFlight') {
            reservation.retourFlight = true
        }
    }
 
    private runClosure(Closure runClosure) {
        // Create clone of closure for threading access.
        Closure runClone = runClosure.clone()
 
        // Set delegate of closure to this builder.
        runClone.delegate = this
 
        // And only use this builder as the closure delegate.
        runClone.resolveStrategy = Closure.DELEGATE_ONLY
 
        // Run closure code.
        runClone()
    }
}
```

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
