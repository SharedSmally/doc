#ifndef CPW_APPCONTEXT_H
#define CPW_APPCONTEXT_H

#include <map>
#include <memory>

#include <Properties.h>

class Manageable
{
public:
    virtual ~Manageable() {}
    virtual bool config(const Properties & props) = 0;
};
typedef std::shared_ptr<Manageable> ManageablePtr;

class App;

class AppContext : public PropertiesGroup
{
public:
    AppContext(App & app);
    ~AppContext() {};

    App & app();

    /////////////////////// Components
    ManageablePtr get(const std::string & name);

    template<typename T>
    std::shared_ptr<T> get(const std::string & name);

    template<typename T, typename... Args>
    bool put(const std::string & name, Args & ... args);

    template<typename T, typename... Args>
    bool put(const std::string & name, Args && ... args);

private:
    AppContext(const AppContext &) = delete;
    AppContext & operator=(const AppContext &) = delete;

protected:
    typedef std::map<std::string, ManageablePtr> manageable_container;

    App & app_;
    manageable_container container_;
};

////////////////////////////////////////////impl
template<typename T>
std::shared_ptr<T> AppContext::get(const std::string & name)
{
    auto it = container_.find(name);
    return ( it == container_.end() ) ?
            std::shared_ptr<T>(nullptr) :
            std::dynamic_pointer_cast<T>(it->second);
}

template<typename T, typename... Args>
bool AppContext::put(const std::string & name, Args & ... args)
{
    const Properties * props = getProperties(name);
    if (props == nullptr) return false;

    ManageablePtr ptr = std::static_pointer_cast<Manageable>(std::make_shared<T> (args...));

    if (ptr && !props->empty())
    {
        if (!ptr->config(*props))
            return false;
    }

    auto ret = container_.insert(std::make_pair(name, ptr));

    return ret.second;
}

template<typename T, typename... Args>
bool AppContext::put(const std::string & name, Args && ... args)
{
    const Properties * props = getProperties(name);
    //if (props == nullptr || ) return false;

    ManageablePtr ptr = std::static_pointer_cast<Manageable>(std::make_shared<T> (args...));

    if (ptr && !props->empty())
    {
        if (!ptr->config(*props))
            return false;
    }
    auto ret = container_.insert(std::make_pair(name, ptr));

    return ret.second;
}

#endif
