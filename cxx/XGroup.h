#ifndef GROUP_H
#define GROUP_H

#include <Lockable.h>

#include <string>
#include <map>
#include <unordered_map>

typedef std::string String;
//typedef std::map<String, String> StringGroup;
typedef std::unordered_map<String, String> StringGroup;

typedef std::basic_string<uint8_t> Bytes;

template <typename T >
class Group
	: public LockObject< std::unordered_map<String, T> , MutexType::NORMAL, false>
{
	typedef typename std::unordered_map<String, T> container_type;
	typedef LockObject< container_type, MutexType::NORMAL, false> parent_class;
	typedef typename parent_class::guard_type guard_type;

	using  parent_class::value_;
	using  parent_class::mutex_;

public:
	Group()
	{}
	~Group()
	{}

	// CRUD operations:
	// no check whether it exists: C
	void set(const String & name, const T & value)
	{
		guard_type guard(mutex_);
		value_[name] = value;
	}

	// check whether it exists: C
	bool put(const String & name, const T & value)
	{
		auto it = value_.find(name);
		if (it != value_.end()) return false;

		guard_type guard(mutex_);
		it = value_.find(name);
		if (it != value_.end()) return false;

		value_[name] = value;
		return true;
	}

	// R/U
	T & find(const String & name)
	{
		auto it = value_.find(name);
		if (it != value_.end()) return it->second;

		guard_type guard(mutex_);
		it = value_.find(name);
		if (it != value_.end()) return it->second;

		//  throw not found exception
	}

	bool exist(const String & name)
	{
		guard_type guard(mutex_);
		return value_.find(name) != value_.end();
	}

	// D
	bool erase(const String & name)
	{
		guard_type guard(mutex_);
		return value_.erase(name) > 0;
	}
};


template <typename T >
class Group<T *>
	: public LockObject< std::unordered_map<String, T*> , MutexType::NORMAL, false>
{
	typedef typename std::unordered_map<String, T*> container_type;
	typedef LockObject< container_type, MutexType::NORMAL, false> parent_class;
	typedef typename parent_class::guard_type guard_type;

	using  parent_class::value_;
	using  parent_class::mutex_;

public:
	Group()
	{}
	~Group()
	{}

	// CRUD operations:
	// no check whether it exists: C
	void set(const String & name, const T & value)
	{
		guard_type guard(mutex_);
		value_[name] = &value;
	}

	// check whether it exists: C
	bool put(const String & name, const T & value)
	{
		auto it = value_.find(name);
		if (it != value_.end()) return false;

		guard_type guard(mutex_);
		it = value_.find(name);
		if (it != value_.end()) return false;

		value_[name] = &value;
		return true;
	}

	// R/U
	T * find(const String & name)
	{
		auto it = value_.find(name);
		if (it != value_.end()) return it->second;

		guard_type guard(mutex_);
		it = value_.find(name);
		if (it != value_.end()) return it->second;

		//  throw not found exception
	}

	bool exist(const String & name)
	{
		guard_type guard(mutex_);
		return value_.find(name) != value_.end();
	}

	// D
	bool erase(const String & name)
	{
		guard_type guard(mutex_);
		return value_.erase(name) > 0;
	}
};


template <typename T >
class PtrGroup
	: public LockObject< std::unordered_map<String, std::shared_ptr<T> > , MutexType::NORMAL, false>
{
	typedef std::shared_ptr<T> ptr_type;
	typedef typename std::unordered_map<String, ptr_type> container_type;
	typedef LockObject< container_type, MutexType::NORMAL, false> parent_class;
	typedef typename parent_class::guard_type guard_type;

	using  parent_class::value_;
	using  parent_class::mutex_;

public:
	PtrGroup()
	{}
	~PtrGroup()
	{}

	// CRUD operations:
	// no check whether it exists: C
	template <typename... Args>
	void set(const String & name, Args...args)
	{
		guard_type guard(mutex_);
		value_[name] = std::make_shared<T>(args...);
	}

	// check whether it exists: C
	template <typename... Args>
	bool put(const String & name, Args...args)
	{
		auto it = value_.find(name);
		if (it != value_.end()) return false;

		guard_type guard(mutex_);
		it = value_.find(name);
		if (it != value_.end()) return false;

		value_[name] = std::make_shared<T>(args...);
		return true;
	}

	// R/U
	T * find(const String & name)
	{
		auto it = value_.find(name);
		if (it != value_.end()) return it->second;

		guard_type guard(mutex_);
		it = value_.find(name);
		if (it != value_.end()) return it->second;

		//  throw not found exception
	}

	bool exist(const String & name)
	{
		guard_type guard(mutex_);
		return value_.find(name) != value_.end();
	}

	// D
	bool erase(const String & name)
	{
		guard_type guard(mutex_);
		return value_.erase(name) > 0;
	}
};

#endif
