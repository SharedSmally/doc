#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <memory>
#include <mutex>

#include <map>
#include <unordered_map>

template <typename T >
class Container
{
public:
	typedef std::mutex mutex_type;
	typedef std::lock_guard<mutex_type> guard_type;
	typedef std::shared_ptr<T> ptr_type;
	typedef std::unordered_map<std::string, ptr_type> container_type;

	//CRUD operations
	// C: Create
	bool put(const std::string & name, ptr_type ptr)
	{
		if (!ptr) return false;
		guard_type lock(mtx_);
		return container_.insert(std::make_pair(name, ptr)).second;
	}
	template < typename T0 >
	bool put(const std::string & name, std::shared_ptr<T0> ptr)
	{
		return put(name, std::static_pointer_cast<T>(ptr));
	}
	template <typename... Args>
	bool putT(const std::string & name, Args... args)
	{
		return put(name, std::make_shared<T>(args...));
	}
	template <typename T0, typename... Args>
	bool putT0(const std::string & name, Args... args)
	{
		return put(name,std::make_shared<T0>(args...));
	}

	//R: Retrieve
	ptr_type get(const std::string & name)
	{
		guard_type lock(mtx_);
		auto iter = container_.find(name);
		return (iter==container_.end()) ? ptr_type(nullptr) : iter->second;
	}

	//Update
	bool set(const std::string & name, ptr_type ptr)
	{
		if (!ptr) return false;
		guard_type lock(mtx_);
		container_[name]=ptr;
		return true;
	}
	template < typename T0 >
	bool set(const std::string & name, std::shared_ptr<T0> ptr)
	{
		return set(name, std::static_pointer_cast<T>(ptr));
	}
	bool replace(const std::string & name, ptr_type ptr)
	{
		if (!ptr) return false;
		guard_type lock(mtx_);
		if (container_.find(name)==container_.end()) return false;
		container_[name]=ptr;
		return true;
	}
	template < typename T0 >
	bool replace(const std::string & name, std::shared_ptr<T0> ptr)
	{
		return replace(name, std::static_pointer_cast<T>(ptr));
	}

	//D
	bool remove(const std::string & name)
	{
		guard_type lock(mtx_);
		return container_.erase(name);
	}
	void clear()
	{
		guard_type lock(mtx_);
		container_.clear();
	}

	bool exist(const std::string & name)
	{
		guard_type lock(mtx_);
		return container_.find(name) != container_.end();
	}

protected:
	mutable mutex_type mtx_;
	container_type container_;
};



template <typename T >
class SContainer
{
public:
	typedef std::shared_ptr<T> ptr_type;
	typedef std::unordered_map<std::string, ptr_type> container_type;

	//CRUD operations
	// C: Create
	bool put(const std::string & name, ptr_type ptr)
	{
		if (!ptr) return false;
		return container_.insert(std::make_pair(name, ptr)).second;
	}
	template < typename T0 >
	bool put(const std::string & name, std::shared_ptr<T0> ptr)
	{
		return put(name, std::static_pointer_cast<T>(ptr));
	}
	template <typename... Args>
	bool putT(const std::string & name, Args... args)
	{
		return put(name, std::make_shared<T>(args...));
	}
	template <typename T0, typename... Args>
	bool putT0(const std::string & name, Args... args)
	{
		return put(name,std::make_shared<T0>(args...));
	}

	//R: Retrieve
	ptr_type get(const std::string & name)
	{
		auto iter = container_.find(name);
		return (iter==container_.end()) ? ptr_type(nullptr) : iter->second;
	}

	//Update
	bool set(const std::string & name, ptr_type ptr)
	{
		if (!ptr) return false;
		container_[name]=ptr;
		return true;
	}
	template < typename T0 >
	bool set(const std::string & name, std::shared_ptr<T0> ptr)
	{
		return set(name, std::static_pointer_cast<T>(ptr));
	}
	bool replace(const std::string & name, ptr_type ptr)
	{
		if (!ptr) return false;
		if (container_.find(name)==container_.end()) return false;
		container_[name]=ptr;
		return true;
	}
	template < typename T0 >
	bool replace(const std::string & name, std::shared_ptr<T0> ptr)
	{
		return replace(name, std::static_pointer_cast<T>(ptr));
	}

	//D
	bool remove(const std::string & name)
	{
		return container_.erase(name);
	}
	void clear()
	{
		container_.clear();
	}

	bool exist(const std::string & name)
	{
		return container_.find(name) != container_.end();
	}

protected:
	container_type container_;
};
