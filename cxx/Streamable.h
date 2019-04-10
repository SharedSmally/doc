#ifndef STREAMABLE_H
#define STREAMABLE_H

#include <iostream>
#include <sstream>

class IStreamable
{
    friend std::istream & operator>>(std::istream & in, IStreamable & obj)
    {
        obj.input(in);
        return in;
    }

public:
    IStreamable(){};
    virtual ~IStreamable(){};
    
    bool input() { input(std::cint);  return std::cint.bad(); };
    
    virtual void input(std::istream & in) = 0;    
};

class OStreamable
{
    friend std::ostream & operator<<(std::ostream & out, OStreamable & obj)
    {
        obj.output(out);
        return out;
    }

public:
    OStreamable(){};
    virtual ~OStreamable(){};
    
    bool output() { output(std::cout); return std::cout.bad(); };
    
    virtual void output(std::ostream & out) = 0;    
};

class Streamable 
   : public IStreamable,  public OStreamable
{
public:
    Streamable(){};
    virtual ~Streamable(){};
}


class Parseble : public IStreamable
{
public:
    Parseble() {}
    virtual ~Parseble() {}
    
    virtual parse() const  { print(std::cin); }
    virtual parse(const std::stream & content) 
    { 
        std::isstream iss(content);
        parse(iss);
        //check iss    
    };
    
    virtual void input(std::istream & in) { parse(in); };    
    
    virtual fromString(const std::string & content) const = 0;
    
protected:    
};

class Printable : public OStreamable
{
public:
    Printable() {}
    virtual ~Printable() {}
    
    void print() const  { print(std::cout); }
    void print(std::ostream & out) const { out << toString(); };
    
    virtual output(std::ostream & out) const { print(out); };
    
    virtual std::string() toString() const = 0;
};

class Serializable 
   : public Parseable, public Printable
{
public:
    Serializable() {}
    virtual ~Serializable() {}
};

#endif
