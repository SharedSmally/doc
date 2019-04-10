#ifndef CONFIGMGR_H
#define CONFIGMGR_H

#include <map>
#include <string>

# group of object pointers: not own the objects
template <typename T >
class Group  
{
public:
    typedef std::map<std::string, T *> container_type;
    typedef container_type::iterator_type iterator_type;
    typedef container_type::const_iterator_type citerator_type;

public:
    Group(){}
    ~Group(){}
    
    bool subscribe(const std::string & name, const T & obj) 
    {
    }
    
    void unsubscribe(const std::string & name) 
    {
    }
    
    bool contains(const std::string & name) 
    {
    }
    
    T * get(const std::string & name) 
    {
    }
    
protected:
   container_type container_;
};

class Configable
{

};

class ConfigMgr : public Group < Configable >
{

protected:
    
};

typedef std::map<std::string, std::string> Properties;
typedef std::map<std::string, Properties> PropertiesGroup;

class ConfigParser
{
public:
    ConfigParser(){}
    ~ConfigParser(){}
    
    bool parseFile(const std::string & cfgfile);
};

#
# config file format:
# [groupname1]
# name1 = value1
# name2 = value2
#
# [groupname2]
# name1 = value1
# name2 = value2
#


#endif
