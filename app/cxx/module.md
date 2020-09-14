 C++ Module

## Tutorials
- [cppreference](https://en.cppreference.com/w/cpp/language/modules)

## Syntax
```
export(optional) module module-name module-partition(optional) attr(optional) ;	 # Module declaration
export declaration	                     # Export declaration
export { declaration-seq(optional) }	   # Export declaration	
export(optional) import module-name attr(optional) ;	    # Import declaration 
export(optional) import module-partition attr(optional) ;	# Import declaration 	
export(optional) import header-name attr(optional) ;	   # Import declaration 
module ;	          # Starts a global module fragment.
module : private ;	# Starts a private module fragment.
```

## Samples
helloworld.cpp
```
export module helloworld;  // module declaration
import <iostream>;         // import declaration
 
export void hello() {      // export declaration
    std::cout << "Hello world!\n";
}
```

main.cpp
```
import helloworld;  // import declaration
 
int main() {
    hello();
}
```
