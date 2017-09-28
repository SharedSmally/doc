
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
- [Exector proposal:C++14 ](https://github.com/chriskohlhoff/executors):A C++14 library for executors

- [R6 Executors](https://github.com/ccmysen/executors_r6): Revision 6 of the C++ executor standards proposal follow-on to N4414

- [Executor proposal: 2016](https://github.com/executors/issaquah_2016): A proposal for a minimal executor model for the Issaquah 2016 ISO C++ committee meeting
