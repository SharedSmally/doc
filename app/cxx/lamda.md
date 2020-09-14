# C++ Lamda

## Tutorial
- [cpp reference](https://en.cppreference.com/w/cpp/language/lambda)

## Syntax
```
[ captures ] <tparams>(optional) ( params ) specifiers exception attr -> ret requires(optional) { body }
[ captures ] ( params ) -> ret { body }
[ captures ] ( params ) { body }
[ captures ] { body }
```

### Lambda capture
The capture defaults are
- &: implicitly capture the used automatic variables by reference
- =: implicitly capture the used automatic variables by copy

The syntax of an individual capture in captures:
- identifier: 

simple by-copy capture

- identifier ...	
simple by-copy capture that is a pack expansion

- identifier initializer
by-copy capture with an initializer

- & identifier
simple by-reference capture

- & identifier ...
simple by-reference capture that is a pack expansion

- & identifier initializer
by-reference capture with an initializer

- this
simple by-reference capture of the current object

- * this
simple by-copy capture of the current object

- ... identifier initializer	
 by-copy capture with an initializer that is a pack expansion
 
- & ... identifier initializer	
 by-reference capture with an initializer that is a pack expansion
 
 Samples
 ```
struct S2 { void f(int i); };
void S2::f(int i) {
    [&]{};          // OK: by-reference capture default
    [&, i]{};       // OK: by-reference capture, except i is captured by copy
    [&, &i] {};     // Error: by-reference capture when by-reference is the default
    [&, this] {};   // OK, equivalent to [&]
    [&, this, i]{}; // OK, equivalent to [&, i]
}

struct S2 { void f(int i); };
void S2::f(int i) {
    [=]{};          // OK: by-copy capture default
    [=, &i]{};      // OK: by-copy capture, except i is captured by reference
    [=, *this]{};   // until C++17: Error: invalid syntax;  since c++17: OK: captures the enclosing S2 by copy
    [=, this] {};   // until C++20: Error: this when = is the default; since C++20: OK, same as [=]
}

    auto func1 = [](int i = 6) { return i + 4; };
    std::cout << "func1: " << func1() << '\n';
    
    std::vector<int> c = {1, 2, 3, 4, 5, 6, 7};
    std::for_each(c.begin(), c.end(), [](int i){ std::cout << i << ' '; });
 ```

