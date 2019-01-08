#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>
#include <string>

#include <map>
#include <vector>

#include <Lockable.h>

class MObject
{
public:
    MObject(){}
    virtual ~MObject(){}

    size_t hashCode() const {
        return (size_t)(this);
    }
};
typedef std::shared_ptr<MObject> MObjectPtr;

class Context
{
public:
    typedef std::shared_ptr<Context> ContextPtr;
    typedef std::vector<std::string> names_type;
    typedef LockableObject< std::map< std::string, ContextPtr > > contexts_type;
    typedef LockableObject< std::map< std::string, MObjectPtr > > contents_type;

public:
    Context() : parent_(nullptr){};
    virtual ~Context(){};

    //parent
    Context * parent() { return parent_; }
    const Context * parent() const { return parent_; }
    bool isRoot() const    {return parent_ == nullptr;    }

    //subcontexts
    ContextPtr getSubContext(const std::string & name, bool create=true);
    bool destroySubContext(const std::string & name);

    bool hasSubContext(const std::string & name);
    void subContextNames(names_type & names);
    contexts_type & subContexts() { return subContexts_;}
    const contexts_type & subContexts() const { return subContexts_;}

    // contents: consumer portion
    bool contains(const std::string & name);
    MObjectPtr get(const std::string & name);
    void names(std::vector<std::string> & names);

    // contents: producer portion
    // template <typename... Args>   void log(Args&&... args);
    template <typename T, typename... Args >
    bool bind(const std::string & name, Args&&... args)
    {
        return bind(name, std::static_pointer_cast<MObject>( std::make_shared<T>() ) );
    }
    bool bind(const std::string & name, MObjectPtr obj);
    void unbind(const std::string & name);

    // bind factory with interface and implementation, maybe in Factory
    /*
    template <typename I, typename IMPL >
    bool bind(const std::string & name);
    template <typename I >
    std::unique_ptr<I> create<I>();
    */

protected:
    Context(Context * parent) : parent_(parent){};

protected:
    Context * parent_;
    contexts_type subContexts_;
    contents_type contents_;
};


typedef std::shared_ptr<Context> ContextPtr;

Context & appContext();

/*
 ContextPtr ctx;
 while (ctx) {
     ctx.xxx;
     ctx = ctx->parent();
 }
 */

#endif
