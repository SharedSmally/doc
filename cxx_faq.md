
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
–
