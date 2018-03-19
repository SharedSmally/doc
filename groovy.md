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

### Builder with Closures
- Use pre-defined builders like the JsonBuilder or MarkupBuilder to create data or text structures
- Simple Builders with Closures
     - A node in the builder is a method and use a closure as the argument of the method to create a new level in the builder hierarchy.
     - use pre-defined method names in our builder syntax, but can also use dynamic or unkown method names by implementing the methodMissing method. The same goes for properties we can implement with real property methods or by implementing the propertyMissing method.
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
