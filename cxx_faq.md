
## C++
```
  template<typename... Args>
  void doSomething(Args  ... args);   -> doSomething(int, double) [int a=10; double f=20.0; doSomething(a,f);]

  template<typename... Args>
  void doSomething(Args & ... args); -> doSomething(int &, double &)  [int a=10; double f=20.0; doSomething(a,f);]

  template<typename... Args>
  void doSomething(Args && ... args);  -> doSomething(int&&, double&&) [doSomething(10,20.0)]

```

## C++ template
- virtual method cannot be a template. 

– To call a base template class function , need to use this:
```
this->f();
B<T>::f(); //If f and g were both static:
```

## C++ executors
- [A C++14 library for executors](https://github.com/chriskohlhoff/executors):

- [R6 Executors](https://github.com/ccmysen/executors_r6): Revision 6 of the C++ executor standards proposal follow-on to N4414
