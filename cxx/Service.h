#ifndef SERVICE_H
#define SERVICE_H

template <CONTEXT>
class Service
{
public:
    typedef std::shared_ptr< CONTEXT > ContextPtr;
    Service(ContextPtr ctx) : ctx_(ctx){}
    
    template typename... Args>
    Service(Args... args)
    : ctx_(std::make_shared<CONTEXT>(args...)
    {}   
    
    virtual ~Service() { ctx_ = nullptr; }
    
    void setContext(ContextPtr ctx) {
       ctx_ = ctx;
    }
    ContextPtr getContext() {
       return ctx_;
    }
    const ContextPtr getContext() const {
       return ctx_;
    }
    
    // operations for the service
    
protected:
   ContextPtr ctx_;
};

template <KEY, OBJECT>
class ObjectManager
{
public:
    typedef std::shared_ptr< OBJECT > ObjectPtr;
    ObjectManager(){}
    virtual ~ObjectManager() { objs_.clear(); }    
    
    //interfaces: CRUD
    // C: return false and no register if already exists
    bool register(const KEY & key, ObjectPtr & obj)
    {    
    }  
    // R: get 
    ObjectPtr get(const KEY & key)
    {    
    }
    // U: replace
    void replace(const KEY & key, ObjectPtr & obj)
    {    
    }
    // D:  remove
    bool unregister(const KEY & key)
    {   
    }
    // check status
    bool has(const KEY & key)
    {
    
    }
    
protected:
    std::map<KEY, ObjectPtr> objs_;
};



#endif
