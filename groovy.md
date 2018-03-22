# Groovy

### [groovy Document]()

### Groovy-Eclipse Plugin:
[groovy-eclipse plugin](https://github.com/groovy/groovy-eclipse/wiki) - http://dist.springsource.org/release/GRECLIPSE/e4.7

### Script

### Syntax
#### Properties
In Groovy we can set values for properties with a simple assignment using the = operator. Groovy will invoke the set for us. 
At first sight we might think Groovy sets the variable in the class directly, but that is not true, because the set method
is invoked. To get the value of a property we can use dot (.) notation instead of the get method.

```
public class Simple {
    private String text;   
    public Simple() {  super();  }
     public String getMessage() {    return "GET " + text;   }
     public void setMessage(final String text) {   this.text = "SET " + text }

def s1 = new Simple()
s1.setMessage('Old style')
assert 'GET SET Old style' == s1.getMessage()
s1.setMessage 'A bit more Groovy'  // No parenthesis.
assert 'GET SET A bit more Groovy' == s1.getMessage()
 
def s2 = new Simple(message: 'Groovy constructor')  // Named parameter in constructor.
assert 'GET SET Groovy constructor' == s1.getMessage()
 
def s3 = new Simple()
s3.message = 'Groovy style'  // = assigment for property.
assert 'GET SET Groovy style' == s3.message  // get value with . notation.
```

### [Closure](http://docs.groovy-lang.org/latest/html/api/groovy/lang/Closure.html) & [Binding](http://docs.groovy-lang.org/latest/html/api/groovy/lang/Binding.html) & [MetaClass](http://docs.groovy-lang.org/latest/html/api/groovy/lang/MetaClass.html)
Groovy provides a mechanism of binding properties to the closure so the closure can reference properties
that did not exist when it was created.
```
def c = {	println a; }
def a = "Hello"
def binding = new Binding ()
binding.setVariable ("a", a)

c.setBinding (binding)
c.call()
```
