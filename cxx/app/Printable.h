#ifndef CPW_PRINTABLE_H
#define CPW_PRINTABLE_H

#include <string>
#include <sstream>
#include <exception>

#include <iostream>

#include <array>
#include <vector>
#include <deque>
#include <list>

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

class Serializable
{
	friend std::ostream & operator<<(std::ostream & os, Serializable & obj)
	{
		obj.output(os);
		return os;
	}

public:
	virtual ~Serializable(){};
	virtual void output(std::ostream & oss) const { };
};

class Deserializable
{
	friend std::istream & operator>>(std::istream & is, Deserializable & obj)
	{
		obj.input(is);
		return is;
	}
public:
	virtual ~Deserializable(){};
	virtual void input(std::istream & is) {};
};

class Streamable : public Serializable, public Deserializable
{
public:
	virtual ~Streamable(){};
/*
 * virtual void input(std::istream & is);
 * virtual void output(std::ostream & oss) const;
 */
};

///////////////////////////////////////////////////////////////////////////////
class Formatter
{
public:
	virtual ~Formatter();
	virtual std::string format() const = 0;
};

class FormatException : std::runtime_error
{
public:
	FormatException(const std::string & msg)
	: runtime_error(msg)
	{};
	virtual ~FormatException(){};
};

class Printable : public Serializable
{
public:
	virtual ~Printable(){};

	// using sprintf(char* buffer, const char* format, ... )
	virtual std::string print() const {
		std::ostringstream oss;
		output(oss);
		return oss.str();
	}
};

class Parseable : public Deserializable
{
public:
	virtual ~Parseable(){};

	//int sscanf ( const char * s, const char * format, ...);
	virtual bool parse(const std::string & value) throw ( FormatException )
	{
		std::istringstream iss(value);
		input(iss);
		return iss.good();
	}
};

class Stringable : public Parseable, public Printable
{
public:
	virtual ~Stringable(){};
	/*
	virtual void output(std::ostring & oss) const = 0;
	virtual void input(std::istream & is) = 0;

	virtual std::string print() const;
	virtual bool parse(const std::string & str);
	*/
};

///////////////////////////////////////////////////////////////////////////////
template <typename T >
std::string toString(const T & obj)
{
	std::ostringstream oss;
	oss << obj;
	return oss.str();
}

template <typename T >
bool fromString(T & obj, const std::string & str) throw ( FormatException )
//  noexcept;
{
	std::istringstream iss(str);
	iss >> obj;
	return iss.good() || iss.eof();
}
template < >
std::string toString(const std::string & obj)
{
	return obj;
}

template < >
bool fromString(std::string & obj, const std::string & str) throw ( FormatException )
{
	obj=str;  return true;
}
//////////////////////////////
template < >
std::string toString(const Printable & obj)
{
	return obj.print();
}

template < >
bool fromString(Parseable & obj, const std::string & str) throw ( FormatException )
{
	return obj.parse(str);
}

//////////////////////////////

template <typename T, size_t N >
std::string toString(const std::array<T, N> & obj)
{
	std::ostringstream oss;
	for (auto & val : obj)
		oss << val << " ";
	return oss.str();
}

/*
template <typename T >
bool fromString(T & obj, const std::string & str) throw ( FormatException )
//  noexcept;
{
	std::istringstream iss;
	iss >> obj;
	return iss.good();
}*/

template <typename T >
std::string toString(const std::vector<T> & obj)
{
	std::ostringstream oss;
	for (auto & val : obj)
		oss << val << " ";
	return oss.str();
}

template <typename T >
bool fromString(std::vector<T> & obj, const std::string & str) throw ( FormatException )
{
	T val;
	std::istringstream iss(str);
	while (!iss.eof() && iss.good()) {
		iss >> val;
		obj.push_back(val);
	}
	return iss.good();
}

template <typename T >
std::string toString(const std::list<T> & obj)
{
	std::ostringstream oss;
	for (auto & val : obj)
		oss << val << " ";
	return oss.str();
}

template <typename T >
bool fromString(std::list<T> & obj, const std::string & str) throw ( FormatException )
{
	T val;
	std::istringstream iss(str);
	while (!iss.eof() && iss.good()) {
		iss >> val;
		obj.push_back(val);
	}
	return iss.good();
}

template <typename T >
std::string toString(const std::deque<T> & obj)
{
	std::ostringstream oss;
	for (auto & val : obj)
		oss << val << " ";
	return oss.str();
}

template <typename T >
bool fromString(std::deque<T> & obj, const std::string & str) throw ( FormatException )
{
	T val;
	std::istringstream iss(str);
	while (!iss.eof() && iss.good()) {
		iss >> val;
		obj.push_back(val);
	}
	return iss.good();
}

///////////////////////////////////////////////////
template <typename T >
std::string toString(const std::set<T> & obj)
{
	std::ostringstream oss;
	for (auto & val : obj)
		oss << val << " ";
	return oss.str();
}

template <typename T >
bool fromString(std::set<T> & obj, const std::string & str) throw ( FormatException )
{
	T val;
	std::istringstream iss(str);
	while (!iss.eof() && iss.good()) {
		iss >> val;
		obj.insert(val);
	}
	return iss.good();
}
template <typename T >
std::string toString(const std::unordered_set<T> & obj)
{
	std::ostringstream oss;
	for (auto & val : obj)
		oss << val << " ";
	return oss.str();
}

template <typename T >
bool fromString(std::unordered_set<T> & obj, const std::string & str) throw ( FormatException )
{
	T val;
	std::istringstream iss(str);
	while (!iss.eof() && iss.good()) {
		iss >> val;
		obj.insert(val);
	}
	return iss.good();
}

template <typename K, typename V >
std::string toString(const std::map<K,V> & obj)
{
	std::ostringstream oss;
	for (auto iter = obj.begin(); iter != obj.end(); ++iter)
		oss << iter->first << "=" << iter->second << ";";
	return oss.str();
}

template <typename K, typename V >
bool fromString(std::map<K,V> & obj, const std::string & str) throw ( FormatException )
{
	K key; V val;
	size_t pos = 0, ind = 0, valpos=0;
	std::string s0;
	while ( (ind=str.find(';',pos)) != std::string::npos && (ind > pos) ) {
		valpos = str.find('=', pos);
		if (valpos != std::string::npos) {
			if (!fromString(key,str.substr(pos, valpos-pos))) return false;
			if (!fromString(val,str.substr(valpos+1, ind-valpos-1))) return false;
			obj.insert(std::make_pair(key,val));
		}
		pos = ind+1;
	}
	return true;
}

template <typename K, typename V >
std::string toString(const std::unordered_map<K,V> & obj)
{
	std::ostringstream oss;
	for (auto iter = obj.begin(); iter != obj.end(); ++iter)
		oss << iter->first << "=" << iter->second << ";";
	return oss.str();
}

template <typename K, typename V >
bool fromString(std::unordered_map<K,V> & obj, const std::string & str) throw ( FormatException )
{
	K key; V val;
	size_t pos = 0, ind = 0, valpos=0;
	std::string s0;
	while ( (ind=str.find(';',pos)) != std::string::npos && (ind > pos) ) {
		valpos = str.find('=', pos);
		if (valpos != std::string::npos) {
			if (!fromString(key,str.substr(pos, valpos-pos))) return false;
			if (!fromString(val,str.substr(valpos+1, ind-valpos-1))) return false;
			obj.insert(std::make_pair(key,val));
		}
		pos = ind+1;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////

#endif
