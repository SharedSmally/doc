# C++ MetaClass / Reflection
- [Metaclasses and Reflection in C++](http://www.vollmann.com/en/pubs/meta/meta/meta.html)
- [Reflection System in C++](https://preshing.com/20180116/a-primitive-reflection-system-in-cpp-part-1/)

## Reflection
```
Type:


```

## Reflection Sample
```
struct Node {
    std::string key;
    int value;
    std::vector<Node> children;

    REFLECT()      // Enable reflection for this type
};

// Define Node's type descriptor
REFLECT_STRUCT_BEGIN(Node)
REFLECT_STRUCT_MEMBER(key)
REFLECT_STRUCT_MEMBER(value)
REFLECT_STRUCT_MEMBER(children)
REFLECT_STRUCT_END()

// Create an object of type Node
Node node = {"apple", 3, {{"banana", 7, {}}, {"cherry", 11, {}}}};
```
