## Context
Similar to IoC in Java Spring with the following interface and parent-children hierarchy relationship:
```
Context & parent()

bool registerFactory<T>(Factory<T> factory);

bool contains(string name);

std::shared_ptr<T> getBean<T>();
std::shared_ptr<T> getBean<T>(string name, bool createIfNotExist);
```
