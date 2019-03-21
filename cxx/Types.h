#ifndef CPW_TYPES_H
#define CPW_TYPES_H

#include <inttypes.h>
#include <string>
#include <sstream>

typedef int8_t int8;
typedef uint8_t uint8;

typedef int16_t int16;
typedef uint16_t uint16;

typedef int32_t int32;
typedef uint32_t uint32;

typedef int64_t int64;
typedef uint64_t uint64;

typedef float real32;
typedef double real64;

template <typename T >
std::string toString(const T & obj)
{
       std::ostringstream oss;
       oss << obj;
       return oss.str();
}
template <typename T >
bool fromString(T & object, const std::string & input)
{
       std::istringstream iss(input);
       oss >> obj;
       return !oss.good();
}

class Printable
{
friend std::ostream & operator<<(std::ostream & out, const Printable & obj)
{
    obj.print(out);
    return out;
}
public:
    virtual ~Printable(){};
    virtual void print(std::ostream & out) const = 0;
    std::string toString() const 
    {
       std::ostringstream oss;
       print(oss);
       return oss.str();
    }
};

class Parseable
{
friend std::istream & operator<<(std::istream & out, const Parseable & obj)
{
    obj.input(out);
    return out;
}
public:
    virtual ~Parseable(){};
    virtual bool parse(std::istream & out) const = 0;
    bool fromString(const std::string & in) const 
    {
       std::istringstream iss(in);
       return parse(iss);
    }
};

#endif
