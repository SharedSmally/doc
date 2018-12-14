# C++ application Platform
Similar to Java Spring platform.

## Context
Similar to IoC in Java Spring with the following interface and parent-children hierarchy relationship:
```
Context & parent()

bool registerFactory<T>(Factory<T> factory);

bool contains(string name);

std::shared_ptr<T> getBean<T>();  # return interface class.
std::shared_ptr<T> getBean<T>(string name, bool createIfNotExist);
```

## Component
The class with auto-wired components based on interface:
```

```

## Component Factory
Register implementaion for the specific interface.
