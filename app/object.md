# Objects

## DataObject
See for [parameter pack](https://en.cppreference.com/w/cpp/language/parameter_pack).
```
template <KEY, DATA>
DataObject {
public:
    DataObject(const DataObject & obj) 
       : key_(obj.key_),data_(obj.data_)
    { }    
    DataObject(const KEY && key, const DATA && data) 
       : key_(key),data_(data)
    { }      
    template< typename... Args>
    DataObject(Args... & args) 
       : key_(args...),data_()
    { }
   ~DataObject(){}
   
   const KEY & key() const{ return key_; }   
   DATA & data() { return data_; }
   const DATA & data() const{ return data_; }

protected:
   KEY key_;
   DATA data_;
};

// recursive variadic function
template<typename T, typename... Args>
void func(T t, Args... args) {
    std::cout << t <<std::endl ;
    func(args...) ;
}

//Using reference:
template<class Fun, class... Args>
void foo(Fun f, Args&&... args)
{
    f( std::forward<Args>(args)...);
}
```

## SyncObject

## Manager<KEY, DATA>

## TreeNode

## Context
