#ifndef CPW_CONFIGOBJ_H
#define CPW_CONFIGOBJ_H

#include <AppMgr.h>
#include <sstream>
#include <atomic>

template <typename T >
class ConfigObj : public Configable
{
public:
	ConfigObj(ConfigGroup & group, const std::string & name,
			const std::string & desc, const T & value,
			Configable::ConfigType type = Configable::ConfigType::CONFIGABLE )
		: Configable(name,desc,type), group_(group), value_(value)
	{
		group_.set(name_, this);
	}
	~ConfigObj()
	{
		group_.unset(name_);
	}
	virtual std::string query() const
	{
		std::ostringstream oss;
		oss << value_;
		return oss.str();
	}

	T & value() { return value_; }
	const T & value() const { return value_; }

protected:
	virtual bool _config(const std::string & value)
	{
		std::istringstream iss(value);
		iss >> value_;
		return iss.good() || iss.eof();
	}

protected:
	T value_;
	ConfigGroup & group_;
};

template <typename T >
class QueryObj : public ConfigObj<T>
{
public:
	QueryObj(ConfigGroup & group, const std::string & name,
			const std::string & desc, const T & value)
		: Config<T>::Config(group,name,desc,value,Configable::ConfigType::QUERYABLE)
	{
	}
	~QueryObj()
	{}
};

template <typename T >
class UpdateObj : public ConfigObj<T>
{
public:
	UpdateObj(ConfigGroup & group, const std::string & name,
			const std::string & desc, const T & value)
		: Config<T>::Config(group,name,desc,value,Configable::ConfigType::UPDATEABLE)
	{
	}
	~UpdateObj()
	{}
};

template <typename T >
class _Count : public Configable
{
public:
	_Count(ConfigGroup & group, const std::string & name,
			const std::string & desc)
		: Configable(name,desc,Configable::ConfigType::RESETABLE),
		  group_(group), value_(0)
	{
		group_.set(name_, this);
	}
	~_Count()
	{
		group_.unset(name_);
	}
	virtual std::string query() const
	{
		std::ostringstream oss;
		oss << value_;
		return oss.str();
	}

	T & value() { return value_; }
	const T & value() const { return value_; }

	T operator++() noexcept { return ++value_; }
	T operator++() volatile noexcept { return ++value_; }

	T operator+=( T arg ) noexcept { return value_+=arg; }
	T operator+=( T arg ) volatile noexcept { return value_+=arg; }

protected:
	virtual bool _reset()
	{
		value_ = 0;
		return true;
	}

protected:
	// lastUpdateTime
	std::atomic<T> value_;
	ConfigGroup & group_;
};
/*
 *struct X
{
    X& operator++()
    {
        // actual increment takes place here
        return *this;
    }
    X operator++(int)
    {
        X tmp(*this); // copy
        operator++(); // pre-increment
        return tmp;   // return old value
    }
};
 */
typedef _Count<uint8_t> Count8;
typedef _Count<uint16_t> Count16;
typedef _Count<uint32_t> Count32;
typedef _Count<uint64_t> Count64;
typedef _Count<uint32_t> Count;



template <typename T >
class _Gauge : public Configable
{
public:
	_Gauge(ConfigGroup & group, const std::string & name,
			const std::string & desc)
		: Configable(name,desc,Configable::ConfigType::RESETABLE),
		  group_(group), value_(0)
	{
		group_.set(name_, this);
	}
	~_Gauge()
	{
		group_.unset(name_);
	}
	virtual std::string query() const
	{
		std::ostringstream oss;
		oss << value_;
		return oss.str();
	}

	T & value() { return value_; }
	const T & value() const { return value_; }

	T operator++() noexcept { return ++value_; }
	T operator++() volatile noexcept { return ++value_; }

	T operator+=( T arg ) noexcept { return value_+=arg; }
	T operator+=( T arg ) volatile noexcept { return value_+=arg; }

	T operator--() noexcept { return --value_; }
	T operator--() volatile noexcept { return --value_; }

	T operator-=( T arg ) noexcept { return value_-=arg; }
	T operator-=( T arg ) volatile noexcept { return value_-=arg; }
protected:
	virtual bool _reset()
	{
		value_ = 0;
		return true;
	}

protected:
	// lastUpdateTime
	std::atomic<T> value_;
	ConfigGroup & group_;
};

typedef _Gauge<int8_t>  Gauge8;
typedef _Gauge<int16_t> Gauge16;
typedef _Gauge<int32_t> Gauge32;
typedef _Gauge<int64_t> Gauge64;
typedef _Gauge<int32_t> Gauge;

#endif
