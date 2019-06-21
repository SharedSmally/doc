#ifndef Viewable_H
#define Viewable_H

#include <string>


/**
 * Superclass that can be managed by the application
 */
class Nameable
{
public:
    Nameable(const std::string & name)
      : name_(name)
    {}
    virtual ~Nameable()
    {}

    const std::string & name() const
    {
        return name_;
    }
    const std::string & name()
    {
        return name_;
    }

protected:
    std::string name_;
};

/**
 * Superclass that can be viewed by the customer
 */
class Viewable : public Nameable
{
public:
    Viewable(const std::string & name)
      : Nameable(name)
    {}
    virtual ~Viewable()
    {}

    virtual std::string get() const = 0;
};


/*
 * Configured by the config files (text,xml,json,...) when application starts.
 */
class Configurable
    : public Viewable
{
public:
    Configurable(const std::string & name)
        : Viewable(name)
    {}
    virtual ~Configurable()
    {}

    virtual bool config( const std::string & val )
    {
        return _config(val);
    }
    virtual bool update( const std::string & val )
    {
        return isUpdateable() ? _config(val) : false;
    }

    virtual bool isUpdateable() const = 0;

protected:
    virtual bool _config( const std::string & val ) = 0;
};


/**
 * superclass of metrics(more counts with statistics info),
 * peg count(incr) and gauge(incr, decr).
 */
class Resetable
    : public Viewable
{
public:
    Resetable(const std::string & name)
        : Viewable(name)
    {}
    virtual ~Resetable()
    {}

    virtual void reset() = 0;
};

#endif
