#ifndef CPW_PROPERTIES_H
#define CPW_PROPERTIES_H

#include <map>
#include <list>
#include <vector>
#include <string>

#include <iostream>

typedef std::string String;

// 2 levels properties file in format of
// [groupname]
// propname=propvalue
// propname=propvalue

class Properties
{
    static const String EMPTY_STRING;
    friend std::ostream & operator>>(std::ostream & out, const Properties & properties)
    {
        properties.output(out);
        return out;
    }

public:
    Properties(const String & name) : name_(name) {}
    ~Properties() { std::cout << " delete properties name=" << name_ << std::endl; }

    const String & name(const String & name) const { return name_; }
    const std::vector<String> & names() const { return names_; };
    bool empty() const { return properties_.empty(); }

    bool hasProperty(const String & key) const ;
    const String & getProperty(const String & key) const;
    const String & getProperty(const String & key, const String & defaultValue) const;
    void setProperty(const String & key, const String & value);

    void output(std::ostream & out) const;

protected:
    String name_;
    std::vector<String> names_;
    std::map<String, String> properties_;
};

class PropertiesGroup
{
    friend std::ostream & operator>>(std::ostream & out, const PropertiesGroup & props)
    {
        props.output(out);
        return out;
    }

public:
    PropertiesGroup(){}
    ~PropertiesGroup();

    const std::list<String> & names() const { return names_; };

    bool hasProperties(const String & name) const ;
    const Properties * getProperties(const String & name) const;

    void removeProperties(const String & name);

    bool load(const String & cfgfile);
    bool store(const String & cfgfile) const;
    bool empty() const { return groups_.empty(); }

    void output(std::ostream & out = std::cout) const;

protected:
    Properties * getProperties(const String & name);

    //std::vector<String> names_;
    std::list<String> names_;
    std::map<String, Properties *> groups_;
};

#endif /* end of PROPERTIES_H */
