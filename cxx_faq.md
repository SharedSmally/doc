
## C++
```
  template<typename... Args>
  void doSomething(Args  ... args);   -> doSomething(int, double) [int a=10; double f=20.0; doSomething(a,f);]

  template<typename... Args>
  void doSomething(Args & ... args); -> doSomething(int &, double &)  [int a=10; double f=20.0; doSomething(a,f);]

  template<typename... Args>
  void doSomething(Args && ... args);  -> doSomething(int&&, double&&) [doSomething(10,20.0)]

```
## [C++ reference 4-value: &&](https://stackoverflow.com/questions/5481539/what-does-t-double-ampersand-mean-in-c11)
- Move semantics.
```
foo(foo const& other)
{
    this->length = other.length;
    this->ptr = new int[other.length];
    copy(other.ptr, other.ptr + other.length, this->ptr);
}
```
can be optimized as for temporary object:
```
foo(foo&& other)
{
   this->length = other.length;
   this->ptr = other.ptr;
   other.length = 0;
   other.ptr = nullptr;
}
```
- Perfect forwarding
```
template <typename T, typename A1>
std::unique_ptr<T> factory(A1& a1)
{
    return std::unique_ptr<T>(new T(a1));
}
```
not work for factory<foo>(5).
```
template <typename T, typename A1>
std::unique_ptr<T> factory(A1&& a1)
{
    return std::unique_ptr<T>(new T(std::forward<A1>(a1)));
}
  
auto p1 = factory<foo>(foo()); // calls foo(foo&&)
auto p2 = factory<foo>(*p1);   // calls foo(foo const&)
```
  When the function parameter type is of the form T&& where T is a template parameter, and the function argument is an lvalue of type A, the type A& is used for template argument deduction.
```
foo f1((foo())); // Move a temporary into f1; temporary becomes "empty"
foo f2 = std::move(f1); // Move f1 into f2; f1 is now "empty"
```
  
## C++ template
- virtual method cannot be a template. If the generic form is not implemented, the individual one will be found and used. and will cause compile error if it is not implemented. The inherited virtual is still virtual.
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

## [C++ Operators](https://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading)
