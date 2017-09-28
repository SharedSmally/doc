
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
- [Executor Open STD] (http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0443r0.html)
- [P0443 Rev 1 proposal](http://open-std.org/JTC1/SC22/WG21/docs/papers/2017/p0443r1.html)
- [Exector proposal:C++14 ](https://github.com/chriskohlhoff/executors):A C++14 library for executors(Chris Kohlhoff's executor model for the Networking TS N4370)

- [R6 Executors](https://github.com/ccmysen/executors_r6): Revision 6 of the C++ executor standards proposal follow-on to N4414(Google's executor model for interfacing with thread pool)

- [Executor proposal: 2016](https://github.com/executors/issaquah_2016): A proposal for a minimal executor model for the Issaquah 2016 ISO C++ committee meeting(NVIDIA's executor model for the Parallelism TS P0058.)

## (C++ Operators](https://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading)
