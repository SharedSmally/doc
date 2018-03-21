## [Groovy Closure](http://groovy-lang.org/closures.html)
 A closure in Groovy is an open, anonymous, block of code that can take arguments, return a value and be assigned to a variable. A closure may reference variables declared in its surrounding scope. In opposition to the formal definition of a closure, Closure in the Groovy language can also contain free variables which are defined outside of its surrounding scope.
 
### Syntax
```
{ [closureParameters -> ] statements }
```
Where [closureParameters->] is an optional comma-delimited list of parameters, and statements are 0 or more Groovy statements. 
The parameters look similar to a method parameter list, and these parameters may be typed or untyped.

When a parameter list is specified, the -> character is required and serves to separate the arguments from the closure body. 
The statements portion consists of 0, 1, or many Groovy statements

### Method Call
Groovy allows to omit the parentheses for top-level expressions, like with the println command:
```
println "Hello"
method a, b

println("Hello")
method(a, b)
```
When a closure is the last parameter of a method call, like when using Groovy’s each{} iteration mechanism, you can put the closure outside the closing parentheses, and even omit the parentheses:
```
list.each( { println it } )
list.each(){ println it }
list.each  { println it }
```

### [Closure Object](http://docs.groovy-lang.org/latest/html/api/groovy/lang/Closure.html)
- A closure is an instance of the groovy.lang.Closure class, making it assignable to a variable or a field as any other 
variable, despite being a block of code:
```
def listener = { e -> println "Clicked on $e.source" }      # listener instanceof Closure
Closure callback = { println 'Done!' }                      
Closure<Boolean> isTextFile = {   
    File it -> it.name.endsWith('.txt')                     
}
```
- Closure can be called by (args) or call(args).
```
V	call()
V	call(java.lang.Object... args) 
V	call(java.lang.Object arguments)
```

### Parameters
Parameters of closures follow the same principle as parameters of regular methods:
- an optional type
- a name
- an optional default value
Parameters are separated with commas:

#### Implicit parameter
When a closure does not explicitly define a parameter list (using ->), a closure always defines an implicit parameter, named *it*.

#### Varargs
It is possible for a closure to declare variable arguments like any other method. Vargs methods are methods that can accept a variable number of arguments if the last parameter is of variable length (or an array) like in the next examples:
```
def concat1 = { String... args -> args.join('') }           
def concat2 = { String[] args -> args.join('') }            
def multiConcat = { int n, String... args ->  args.join('')*n }
```

## Closure Delegate
A closure actually defines 3 distinct things:
- *this* corresponds to the enclosing class where the closure is defined
- *owner* corresponds to the enclosing object where the closure is defined, which may be either a class or a closure. Similar to this, but returns the direct enclosing object, be it a closure or a class
- *delegate* corresponds to a third party object where methods calls or properties are resolved whenever the receiver of the message is not defined
- Closure main methods
    - java.lang.Object	getDelegate() 
    - java.lang.Object	getOwner() 
    - int	getResolveStrategy()
    - java.lang.Object	getThisObject() 
    - void	setDelegate(java.lang.Object delegate)
    - void	setDirective(int directive) 
    - void	setProperty(java.lang.String property, java.lang.Object newValue)
    - void	setResolveStrategy(int resolveStrategy)

The delegate of a closure can be accessed by using the delegate property or calling the getDelegate method. It is a powerful 
concept for building domain specific languages in Groovy. While closure-this and closure-owner refer to the lexical scope 
of a closure, the delegate is a user defined object that a closure will use. By default, the delegate is set to owner:

### Delegation strategy
Whenever, in a closure, a property is accessed without explicitly setting a receiver object, then a delegation strategy is involved:
```
class Person {
    String name
}
def p = new Person(name:'Igor')
def cl = { name.toUpperCase() }                 
cl.delegate = p                                 
assert cl() == 'IGOR'                           
```
name is not referencing a variable in the lexical scope of the closure.  we can change the delegate of the closure to be an instance of Person and the method call will succeed
The name property will be resolved transparently on the delegate object! This is a very powerful way to resolve properties or method calls inside closures. There’s no need to set an explicit delegate. receiver: the call will be made because the default delegation strategy of the closure makes it so. 

A closure defines multiple resolution strategies to resolve the methods and properties for the object:
- Closure.OWNER_FIRST is the default strategy. If a property/method exists on the owner, then it will be called on the owner. If not, then the delegate is used.
- Closure.DELEGATE_FIRST reverses the logic: the delegate is used first, then the owner
- Closure.OWNER_ONLY will only resolve the property/method lookup on the owner: the delegate will be ignored.
- Closure.DELEGATE_ONLY will only resolve the property/method lookup on the delegate: the owner will be ignored.
- Closure.TO_SELF can be used by developers who need advanced meta-programming techniques and wish to implement a custom resolution strategy: the resolution will not be made on the owner or the delegate but only on the closure class itself. It makes only sense to use this if you implement your own subclass of Closure.

### Currying
In Groovy, currying refers to the concept of partial application. Currying in Groovy will let you set the value of one parameter of a closure, and it will return a new closure accepting one less argument.

- Left curring
```
def nCopies = { int n, String str -> str*n }    
def twice = nCopies.curry(2)                    
assert twice('bla') == 'blabla'                 
assert twice('bla') == nCopies(2, 'bla') 
```
- Right curring
```
def nCopies = { int n, String str -> str*n }    
def blah = nCopies.rcurry('bla')                
assert blah(2) == 'blabla'                      
assert blah(2) == nCopies(2, 'bla')   
```
- Index based currying
In case a closure accepts more than 2 parameters, it is possible to set an arbitrary parameter using ncurry:
```
def volume = { double l, double w, double h -> l*w*h }      
def fixedWidthVolume = volume.ncurry(1, 2d)                 
assert volume(3d, 2d, 4d) == fixedWidthVolume(3d, 4d)       
def fixedWidthAndHeight = volume.ncurry(1, 2d, 4d)          
assert volume(3d, 2d, 4d) == fixedWidthAndHeight(3d)  
```

### Additionals
- Memoization
Memoization allows the result of the call of a closure to be cached.
```
def fib
fib = { long n -> n<2?n:fib(n-1)+fib(n-2) }
assert fib(15) == 610 // slow!
fib = { long n -> n<2?n:fib(n-1)+fib(n-2) }.memoize()
assert fib(25) == 75025 // fast! 
```
The behavior of the cache can be tweaked using alternate methods:
     - memoizeAtMost will generate a new closure which caches at most n values
     - memoizeAtLeast will generate a new closure which caches at least n values
     - memoizeBetween will generate a new closure which caches at least n values and at most n values
The cache used in all memoize variants is a LRU cache.

- Composition
Closure composition corresponds to the concept of function composition, that is to say creating a new function by composing two or more functions (chaining calls).
```
def plus2  = { it + 2 }
def times3 = { it * 3 }

def times3plus2 = plus2 << times3
assert times3plus2(3) == 11
assert times3plus2(4) == plus2(times3(4))

def plus2times3 = times3 << plus2
assert plus2times3(3) == 15
assert plus2times3(5) == times3(plus2(5))

// reverse composition
assert times3plus2(3) == (times3 >> plus2)(3)
```

