#ifndef GROUP_H
#define GROUP_H

#include <map>
#include <string>
#include <iostream>

typedef std::string String;

class Printable
{
    friend std::ostream & operator<<(std::ostream &  out, const Printable & obj)
    {
        obj.output(out);
        return out;
    }
public:
    virtual ~Printable(){}
    virtual void output(std::ostream &  out = std::cout) const = 0;
};

template <typename T >
class Group : virtual public Printable
{
public:
    typedef std::map<String, T> container_type;
    typedef typename container_type::iterator iter_type;
    typedef typename container_type::const_iterator citer_type;
    typedef typename container_type::size_type size_type;

    static const T EMPTY;
    virtual ~Group() { }

    const T & get(const String & name) const
    {
        auto it = container_.find(name);
        return it == container_.end() ? EMPTY : it->second;
    }
    template<typename... Args>
    T & obtain(const String & name, Args... args)
    {
        auto it = container_.find(name);
        if (it != container_.end() )
            return it->second;
        container_[name] = T(args...);
        return container_[name];
    }

    const T & get(const String & name, const T & def) const
    {
        auto it = container_.find(name);
        return it == container_.end() ? def : it->second;
    }
    bool set(const String & name, const T & value, bool override=false)
    {
        if (override)
        {
            container_[name] = value;
            return true;
        }
        return container_.insert( std::make_pair(name, value) ).second;
    }

    bool has(const String & name) const
    {
        return container_.find(name) != container_.end();
    }

    bool erase(const String & name)
    {
        return container_.erase(name) != 0;
    }

    size_type merge(const Group & props)
    {
        size_type size(0);
        for(auto iter = props.container_.begin(); iter != props.container_.end(); ++iter)
        {
            if ( ! container_.insert( std::make_pair(iter->first, iter->second) ).second)
            {
                container_[iter->first] = iter->second;
            }
            ++size;
        }
        return size;
    }

    virtual void output(std::ostream &  out = std::cout) const
    {
        for(auto iter = container_.begin(); iter != container_.end(); ++iter)
        {
            out << iter->first << " = " << iter->second << "\n";
        }
    }

    const container_type & container() const { return container_; }

protected:
    container_type container_;
};

template <typename T >
const T Group<T>::EMPTY("");

template <typename T >
class Group <T *>  : virtual public Printable
{
public:
    typedef std::map<String, const T *> container_type;
    typedef typename container_type::iterator iter_type;
    typedef typename container_type::const_iterator citer_type;
    typedef typename container_type::size_type size_type;

    static const T * EMPTY;
    virtual ~Group() { }

    const T * get(const String & name) const
    {
        auto it = container_.find(name);
        return it == container_.end() ? EMPTY : it->second;
    }

    const T * get(const String & name, const T & def) const
    {
        auto it = container_.find(name);
        return it == container_.end() ? &def : it->second;
    }

    bool set(const String & name, const T & value, bool override=false)
    {
        if (override)
        {
            container_[name] = &value;
            return true;
        }
        return container_.insert( std::make_pair(name, &value) ).second;
    }

    bool has(const String & name) const
    {
        return container_.find(name) != container_.end();
    }

    bool erase(const String & name)
    {
        return container_.erase(name) != 0;
    }

    size_type merge(const Group & props)
    {
        size_type size(0);
        for(auto iter = props.container_.begin(); iter != props.container_.end(); ++iter)
        {
            if ( ! container_.insert( std::make_pair(iter->first, iter->second) ).second)
            {
                container_[iter->first] = iter->second;
            }
            ++size;
        }
        return size;
    }

    virtual void output(std::ostream &  out = std::cout) const
    {
        for(auto iter = container_.begin(); iter != container_.end(); ++iter)
        {
            out <<  iter->first << "=" << *(iter->second) << "\n";
        }
    }

    const container_type & container() const { return container_; }

protected:
    container_type container_;
};

template <typename T >
const T * Group<T *>::EMPTY(nullptr);

typedef Group<String> Properties;

class PropertiesGroup : virtual public Group<Properties>
{
public:
    virtual void output(std::ostream &  out = std::cout) const
    {
        for(auto iter = container_.begin(); iter != container_.end(); ++iter)
        {
            out << "[ " << iter->first << " ]\n";
            out << iter->second << "\n";
        }
    }
};

#endif
