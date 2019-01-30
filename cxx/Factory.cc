#include <map>
#include <tuple>
#include <typeinfo>

#include <string>
#include <memory>

#include <iostream>

using namespace std;

class Manageable
{
public:
	virtual ~Manageable() {};
};

class Factory
{
public:
	typedef std::shared_ptr<Manageable> ManageablePtr;

	template <typename T >
	std::shared_ptr<T> get()
	{
		std::string name(typeid(T).name());
		auto iter = container_.find(name);
		if ( iter != container_.end())
		{
			return std::dynamic_pointer_cast<T>(iter->second);
		}

		std::shared_ptr<T> ptr = std::make_shared<T>();
		container_.insert(std::make_pair(name, ptr));
		return ptr;
	}

	template <typename T >
	std::shared_ptr<T> get(const std::string & name)
	{
		auto iter = container_.find(name);
		if ( iter != container_.end())
		{
			return std::dynamic_pointer_cast<T>(iter->second);
		}

		std::shared_ptr<T> ptr = std::make_shared<T>();
		container_.insert(std::make_pair(name, ptr));
		return ptr;
	}

	//register impl
	template <typename I, typename IMPL, typename ...Args >
	void link(Args... args)
	{
		std::string name(typeid(I).name());
		std::string implName(typeid(IMPL).name());
		if ( container_.find(name) == container_.end())
		{
			std::shared_ptr<Manageable> ptr = std::dynamic_pointer_cast<Manageable>(std::make_shared<IMPL>(args...));
			container_.insert(std::make_pair(name, ptr));
			container_.insert(std::make_pair(implName, ptr));
		}
	}

protected:
	std::map<std::string, ManageablePtr> container_;
};


Factory & factory()
{
	static Factory factory;
	return factory;
}


class T1 : public Manageable
{
public:
	T1() { cout << "T1" << endl; };
	virtual ~T1() { cout << "~T1" << endl; };
	virtual void print() { cout << "T1::print(): addr=" << (size_t)(this) << endl; };
};

class T2 : public Manageable
{
public:
	T2() { cout << "T2()" << endl; };
	virtual ~T2() { cout << "~T2()" << endl; };
	void hello() { cout << "T2::hello()" << endl; };
};

class T3 : public T1
{
public:
	T3() { cout << "T3()" << endl; };
	virtual ~T3() { cout << "~T3()" << endl; };
	virtual void print() { cout << "T3::print(): addr=" << (size_t)(this) << endl; };
};

void test1()
{
   cout << "test1" << endl;
   {
	   auto f1 = factory().get<T1>();
	   f1->print();
   }

   {
	   auto f2 = factory().get<T2>();
	   f2->hello();
   }
}

void test2()
{
   cout << "test2" << endl;
   {
	   auto f1 = factory().get<T1>("t1");
	   f1->print();
   }

   {
	   auto f2 = factory().get<T1>("t1");
	   f2->print();
   }
}

void test3()
{
   cout << "test3" << endl;
   factory().link<T1, T3>();

   {
	   auto f1 = factory().get<T1>();
	   f1->print();
   }

   {
	   auto f2 = factory().get<T3>();
	   f2->print();
   }
}

int main()
{
	//test2();
	test3();
}
