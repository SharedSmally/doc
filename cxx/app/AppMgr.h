#ifndef CPW_APPMGR_H
#define CPW_APPMGR_H

#include <unordered_map>
#include <iostream>

#include <AppConfig.h>

class ConfigGroup
{
    typedef std::unordered_map<std::string, Configable *> container_type;

public:
    ConfigGroup(const std::string & name) ;
    ~ConfigGroup();

    const std::string & name() const { return name_; }
    bool empty() const { return container_.empty(); }

    bool has(const std::string & key) const
    {
    	return container_.find(key) != container_.end();
    }
    const Configable * get(const std::string & key) const
    {
        auto iter = container_.find(key);
        if (container_.find(key) == container_.end()) // NotFoundException
           return nullptr;

        return iter->second;
    }
    bool set(const std::string & key, Configable * value)
    {
        auto iter = container_.find(key);
        if (iter!= container_.end())  // exist one
            return false;

        // new one
        container_[key] = value;
        return true;
    }
    bool unset(const std::string & key)
    {
        auto iter = container_.find(key);
        if (iter == container_.end() ) return false;

        container_.erase(iter);
        return true;
    }

    void output(std::ostream & out) const
    {
        for (auto iter = container_.begin(); iter != container_.end(); ++iter) {
            out << iter->first << "=" << iter->second->query() << "\n";
        }
    }

protected:
    std::string name_;
    container_type container_;
};

class ConfigMgr
{
    typedef std::unordered_map<std::string, ConfigGroup *> container_type;

public:
    ConfigMgr() { std::cout << " ConfigMgr::ConfigMgr()" << std::endl; }
    ~ConfigMgr() { std::cout << " ConfigMgr::~ConfigMgr()" << std::endl;}

    bool empty() const { return container_.empty(); }

    bool has(const std::string & key) const
    {
    	return container_.find(key) != container_.end();
    }
    const ConfigGroup * get(const std::string & key) const
    {
        auto iter = container_.find(key);
        if (container_.find(key) == container_.end()) // NotFoundException
           return nullptr;

        return iter->second;
    }
    bool set(const std::string & key, ConfigGroup * value)
    {
        auto iter = container_.find(key);
        if (iter!= container_.end())  // exist one
            return false;

        // new one
        container_[key] = value;
        return true;
    }
    bool unset(const std::string & key)
    {
        auto iter = container_.find(key);
        if (iter == container_.end() ) return false;

        container_.erase(iter);
        return true;
    }

    void output(std::ostream & out) const
    {
        for (auto iter = container_.begin(); iter != container_.end(); ++iter) {
            out << "[" << iter->first << "]\n";
            iter->second->output(out);
        }
        out << "\n";
    }

protected:
    container_type container_;
};


ConfigMgr & getConfigMgr()
{
	static ConfigMgr mgr_;
	return mgr_;
}


ConfigGroup::ConfigGroup(const std::string & name)
    : name_(name)
{
	std::cout << " ConfigGroup::ConfigGroup(name):" << name << std::endl;
	::getConfigMgr().set(name, this);
}

ConfigGroup::~ConfigGroup()
{
	std::cout << " ConfigGroup::~ConfigGroup():" << name() << std::endl;
	::getConfigMgr().unset(name());
}

#endif
