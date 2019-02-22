#ifndef RESETABLE_H
#define RESETABLE_H

#include <atomic>
#include <string>
#include <limits>
#include <chrono>
#include <sstream>
#include <iomanip>

// c11 clocks: system_clock; steady_clock; high_resolution_clock
// c20 clocks: utc_clock; tai_clock; gps_clock; file_clock
typedef std::chrono::system_clock::time_point Time;
//typedef std::chrono::steady_clock::time_point Time;
typedef Time::duration Duration;
typedef Time::clock Clock;

class Printable
{
	friend std::ostream & operator<<(std::ostream & oss, const Printable & obj) {
		obj.print(oss);
		return oss;
	}

public:
	Printable() {}
	virtual ~Printable() {}
	void print() const { print(std::cout); };
	std::string toString() const
	{
		std::ostringstream oss;
		print(oss);
		return oss.str();
	}

public:  // interface
	virtual void print(std::ostream & oss) const = 0;
};

class NamedObject
{
public:
	NamedObject(const std::string & name)
   	   : name_(name)
	{}
	virtual ~NamedObject()
	{}

	const std::string & name() const
	{
		return name_;
	}

protected:
	std::string name_;
};

// ResetGroup not owns Resetable, just container to refer the Resetable
class Resetable : public NamedObject
{
public:
	Resetable(const std::string & name)
	: NamedObject(name)
	{}

	virtual ~Resetable()
	{}
	virtual void reset() = 0;
};

template<typename T >
class CounterImpl : public Resetable
{
public:
	typedef typename std::atomic<T> value_type;

	CounterImpl(const std::string & name )
	: Resetable(name), value_(0)
	{}
	CounterImpl(const std::string & name, T arg )
	: Resetable(name), value_(arg)
	{}
	~CounterImpl()
	{}

	virtual void reset()
	{
		value_ = 0;
	}

	CounterImpl & operator++() noexcept {
		++value_;
		return *this;
	}
	CounterImpl & operator+=(T arg ) noexcept {
		value_ +=  arg;
		return *this;
	}

	T get() const {
		return (T)value_;
	}
	operator T() const noexcept {
		return (T)value_;
	}

protected:
	value_type value_;

private:
	CounterImpl & operator=( const CounterImpl & ) = delete;
	CounterImpl & operator=( const CounterImpl & ) volatile = delete;
};

template<typename T >
class GaugeImpl : public CounterImpl<T>
{
	using CounterImpl<T>::value_;
public:
	GaugeImpl(const std::string & name  )
	: CounterImpl<T>::CounterImpl(name)
	{}
	GaugeImpl(const std::string & name, T arg)
	: CounterImpl<T>::CounterImpl(name, arg)
	{}
	~GaugeImpl()
	{}

	GaugeImpl & operator--() noexcept {
		--value_;
		return *this;
	}
	GaugeImpl & operator-=(T arg ) noexcept {
		value_ -=  arg;
		return *this;
	}
};

template<typename T >
struct StatisticsInfo : virtual public Printable
{
public:
	StatisticsInfo()
	{
		reset();
	}
	virtual void print(std::ostream & oss) const {
		oss << ", current=" <<  current
			<< ", totalCount=" << totalCount
			<< ", successCount=" << successCount
			<< ", failureCount=" << failureCount
			<< ", total=" << total
			<< ", max=" << max
			<< ", min=" << min;
	}

	void update(T arg, bool success = true)
	{
		++ totalCount;
		if (success) {
			++ successCount;
		} else {
			++ failureCount;
		}

		total += arg;
		current = arg;

		if (totalCount==1)
		{
			min = max = arg;
		}
		else if (arg>max)
		{
			max = arg;
		}
		else if (arg < min)
		{
			min = arg;
		}
	}
	void reset()
	{
		total = 0;
		min = 0;
		max = 0;
		current = 0;
		totalCount = 0;
		successCount = 0;
		failureCount = 0;
	}

	T total;
	T current;
	T min;
	T max;
	uint32_t totalCount;
	uint32_t successCount;
	uint32_t failureCount;
};

template<typename T >
class MetricImpl : public Resetable, virtual public Printable
{
public:
	typedef StatisticsInfo<T> value_type;

	MetricImpl(const std::string & name  )
	: Resetable(name)
	{
		reset();
	}
	~MetricImpl()
	{}

	MetricImpl & update(T arg, bool success = true ) noexcept {
		value_.update(arg, success);
		updateTime = Clock::now();
		return *this;
	}
	virtual void reset()
	{
		value_.reset();
		resetTime = updateTime = Clock::now();
	}
	virtual void print(std::ostream & oss) const {
		std::time_t t1 = Clock::to_time_t(resetTime);
		std::time_t t2 = Clock::to_time_t(updateTime);

		oss << "resetTime=" << std::put_time(gmtime(&t1), "%FT%TZ")
			<< ", updatgeTime=" << std::put_time(gmtime(&t2), "%FT%TZ")
		    << ", " << value_;
	}


protected:
	value_type value_;
	Time resetTime; // last reset time
	Time updateTime;  // last update time
};

template<typename M >
class MetricItemImpl
{
public:
	MetricItemImpl (M & metric, bool status=true)
	: metric_(metric), status_(status)
	{
		startup_ = Clock::now();
	}
	~MetricItemImpl()
	{
		auto int_us = std::chrono::duration_cast<std::chrono::microseconds> ( Clock::now() - startup_);
		metric_.update(int_us.count(), status_); // in unit of microseconds
	}

	void setStatus(bool v) {
		status_ = v;
	}

protected:
	M & metric_;
	Time startup_;
	bool status_;
};

typedef CounterImpl<uint32_t> Counter;
typedef CounterImpl<uint64_t> Counter64;

typedef GaugeImpl<int32_t> Gauge;
typedef GaugeImpl<int64_t> Gauge64;

typedef MetricImpl<uint32_t> Metric;
typedef MetricImpl<uint64_t> Metric64;
typedef MetricItemImpl<Metric> MetricItem;

#endif
