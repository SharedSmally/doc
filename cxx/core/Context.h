#ifndef CONTEXT_H
#define CONTEXT_H

#include <Tree.h>

class Manageable
{
public:
	virtual ~Manageable()
	{}
};

class ContextItem
{
public:
	~ContextItem()
	{
		clear();
	}

public:
    typedef std::mutex mutex_type;
    typedef std::lock_guard<mutex_type> Guarder;
    typedef std::shared_ptr<Manageable> pointer_type;
    typedef std::unordered_map<std::string, pointer_type> content_type;

    template <typename T >
    std::shared_ptr<T> get()
    {
        return get<T>(typeid(T).name());
    }
    template <typename T >
    std::shared_ptr<T> get(const char* name)
    {
        std::string strname(name);
        return get<T>(strname);
    }

    template <typename T >
    std::shared_ptr<T> get(const std::string & name)
    {
        auto it = content_.find(name);
        if (it!= content_.end()) return std::dynamic_pointer_cast<T>(it->second);

        Guarder guarder(content_mtx_);
        it = content_.find( name );
        if (it!= content_.end()) return std::dynamic_pointer_cast<T>(it->second);

        return nullptr;
    }

    template <typename T, class ...Args>
    std::shared_ptr<T> put(Args... args)
    {
        std::shared_ptr<T> ptr = std::make_shared<T>(args...);
        Guarder guarder(content_mtx_);
        content_[typeid(T).name()] = std::static_pointer_cast<Manageable> (ptr);
        return ptr;
    }

    template <typename Interface, typename IMPL, class ...Args>
    std::shared_ptr<Interface> put(Args... args)
    {
        std::shared_ptr<Interface> ptr = std::make_shared<IMPL>(args...);
        Guarder guarder(content_mtx_);
        content_[typeid(Interface).name()] = std::static_pointer_cast<Manageable> (ptr);
        return ptr;
    }

    template <typename T, class ...Args>
    std::shared_ptr<T> put(const std::string & name, Args... args)
    {
        std::shared_ptr<T> ptr = std::make_shared<T>(args...);
        Guarder guarder(content_mtx_);
        content_[name] = std::static_pointer_cast<Manageable> (ptr);
        return ptr;
    }
    template <typename T, class ...Args>
    std::shared_ptr<T> put(std::string && name, Args... args)
    {
        std::shared_ptr<T> ptr = std::make_shared<T>(args...);
        Guarder guarder(content_mtx_);
        content_[name] = std::static_pointer_cast<Manageable> (ptr);
        return ptr;
    }
    template <typename T, class ...Args>
    std::shared_ptr<T> put(const char * name, Args... args)
    {
        return put<T>(std::string(name), args...);
    }

    template <typename Interface, typename IMPL, class ...Args>
    std::shared_ptr<Interface> put(const std::string & name, Args... args)
    {
        std::shared_ptr<Interface> ptr = std::make_shared<IMPL>(args...);
        Guarder guarder(content_mtx_);
        content_[name] = std::static_pointer_cast<Manageable> (ptr);
        return ptr;
    }
    template <typename Interface, typename IMPL, class ...Args>
    std::shared_ptr<Interface> put(std::string && name, Args... args)
    {
        std::shared_ptr<Interface> ptr = std::make_shared<IMPL>(args...);
        Guarder guarder(content_mtx_);
        content_[name] = std::static_pointer_cast<Manageable> (ptr);
        return ptr;
    }
    template <typename Interface, typename IMPL, class ...Args>
    std::shared_ptr<Interface> put(const char * name, Args... args)
    {
    	return put<Interface,IMPL>(std::string(name), args...);
    }

    template <typename T >
    bool exist()
    {
        //Guarder guarder(content_mtx_);
        return content_.find( typeid(T).name() ) != content_.end();
    }
    bool exist( const std::string & name)
    {
        //Guarder guarder(content_mtx_);
        return content_.find(name) != content_.end();
    }
    template <typename T >
    bool erase()
    {
        Guarder guarder(content_mtx_);
        return content_.erase( typeid(T).name() ) != 0;
    }
    bool erase( const std::string & name)
    {
        Guarder guarder(content_mtx_);
        return content_.erase(name) != 0;
    }
    void clear()
    {
        Guarder guarder(content_mtx_);
        return content_.clear();
    }

protected:
    content_type content_;
    mutex_type content_mtx_;
};

typedef Tree<ContextItem> Context;
typedef std::shared_ptr<Context> ContextPtr;

Context & getContext();

ContextPtr getContext(const std::string & fullname);

#endif
