#ifndef STREAMABLE_H
#define STREAMABLE_H

#include <iostream>
#include <sstream>

class Serializable
{
	friend std::ostream & operator<<(std::ostream & out, const Serializable & obj)
	{
		obj.output(out);
		return out;
	}
public:
	virtual ~Serializable()
	{}
	virtual void output(std::ostream & out) const = 0;
};

class Deserializable
{
	friend std::istream & operator<<(std::istream & in, Deserializable & obj)
	{
		obj.input(in);
		return in;
	}
public:
	virtual ~Deserializable()
	{}
	virtual void input(std::istream & in) = 0;
};

class Streamable : virtual public Serializable, virtual public Deserializable
{
public:
	virtual ~Streamable()
	{}
};


class Printable : virtual public Serializable
{
public:
	virtual ~Printable()
	{}
	virtual std::string toString() const
	{
		std::ostringstream oss;
		output(oss);
		return oss.str();
	}
	virtual void print(std::ostream & out = std::cout) const
	{
		output(out);
	}
};

class Parseable : virtual public Deserializable
{
public:
	virtual ~Parseable()
	{}
	virtual bool parse(const std::string & str)
	{
		std::istringstream iss(str);
		input(iss);
		return iss.good();
	}
};

class Stringable : virtual public Printable, virtual public Parseable
{
public:
	virtual ~Stringable()
	{}
};

class Formatter
{
public:
	virtual ~Formatter()
	{}
};

class DateFormatter : public Formatter
{
public:
	virtual ~DateFormatter()
	{}
};

// strftime (buffer,80,"Now it's %I:%M%p.",timeinfo);
class TimeFormatter : public Formatter
{
public:
	virtual ~TimeFormatter()
	{}
};

class NumericFormatter : public Formatter
{
public:
	virtual ~NumericFormatter()
	{}
};

class JsonFormatter : public Formatter
{
public:
	virtual ~JsonFormatter()
	{}
};

// JSON streamable
// getFormatter()

#endif
