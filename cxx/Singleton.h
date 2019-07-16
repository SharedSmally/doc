#ifndef SINGLETON_H
#define SINGLETON_H

#include <mutex>
#include <memory>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

class ISingleton
{
public:
	virtual ~ISingleton(){};

protected:
	ISingleton() {};

protected: //no copy and assign
	ISingleton(ISingleton &) = delete;
	ISingleton(ISingleton &&) = delete;
	ISingleton & operator=(ISingleton &) = delete;
	ISingleton & operator=(ISingleton &&) = delete;
};

template <typename R >
class Singleton
{
public:
	static R & instance() { return instance_; }

protected:
	Singleton(){};
	~Singleton(){};
	static R instance_;

protected:
	Singleton(Singleton &) = delete;
	Singleton(Singleton &&) = delete;
	Singleton & operator=(Singleton &) = delete;
	Singleton & operator=(Singleton &&) = delete;
};

template <typename R >
R Singleton<R>::instance_;

template <typename R >
inline R & getSingleton()
{
	return Singleton<R>::instance();
}

class SingletonMgr
{
public:
	typedef std::mutex mutex_type;
	typedef std::lock_guard<mutex_type> Guarder;
	typedef std::shared_ptr<ISingleton> ISingletonPtr;
	typedef std::unordered_map<std::type_index, ISingletonPtr> container_type;

	static SingletonMgr & instance() { return instance_; }

	template <typename T >
	std::shared_ptr<T> get()
	{
		std::type_index index(typeid(T));
		auto it = container_.find(index);
		if (it!= container_.end()) return std::dynamic_pointer_cast<T>(it->second);

		Guarder guarder(mtx_);
		it = container_.find( index );
		if (it!= container_.end()) return std::dynamic_pointer_cast<T>(it->second);

		std::shared_ptr<T> ptr = std::make_shared<T>();
		container_.insert(std::make_pair(index, std::static_pointer_cast<ISingleton>(ptr)));
		return ptr;
	}

	template <typename T, class ...Args>
	std::shared_ptr<T> put(Args... args)
	{
		std::shared_ptr<T> ptr = std::make_shared<T>(args...);
		Guarder guarder(mtx_);
		container_[std::type_index(typeid(T))] = std::static_pointer_cast<ISingleton> (ptr);
		return ptr;
	}

	template <typename Interface, typename IMPL, class ...Args>
	std::shared_ptr<Interface> put(Args... args)
	{
		std::shared_ptr<InterfaceT> ptr = std::make_shared<IMPL>(args...);
		Guarder guarder(mtx_);
		container_[std::type_index(typeid(Interface))] = std::static_pointer_cast<ISingleton> (ptr);
		return ptr;
	}

protected:
	SingletonMgr()	{}
	~SingletonMgr()	{}

protected:
	static SingletonMgr instance_;
	mutex_type mtx_;
	container_type container_;
};

SingletonMgr SingletonMgr::instance_;

inline SingletonMgr & singletonMgr()
{
	return SingletonMgr::instance();
}


#endif
