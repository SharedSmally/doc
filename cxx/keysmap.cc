# map with multiple keys, keys must be of different types.

#include <map>
#include <string>
#include <exception>

#include <iostream>

template<typename V, typename K, typename... Args>
class KeysMap
{
public:
	V & get(const K & key)
	{
		return values_.get(key);
	}

	template <typename T >
	V & get(const T & key)
	{
		return container_.get(key);
	}

	void insert(V & value, const K & k1, const Args & ... args)
	{
		values_.insert(value, k1);
		container_.insert(value, args...);
	}

protected:
	KeysMap<V, K > values_;
	KeysMap<V, Args... > container_;
};

template<typename V, typename K>
class KeysMap <V, K >
{
public:
	V & get(const K & key)
	{
		auto iter = values_.find(key);
		if ( iter != values_.end())
			return iter->second;
		else
			throw std::runtime_error("No value found in map");
	}

	template <typename T >
	V & get(const T & key)
	{
		std::cout << "call template V & get(const K & key)" << std::endl;
		throw std::runtime_error("No value found");
	}

	void insert( V & value, const K & key)
	{
		values_.insert(std::make_pair(key,value));
	}

protected:
	std::map<K, V > values_;
};

int test2()
{
	KeysMap<int, std::string, int> data;
	std::string k1("key1");
	std::string k2("key2");
	int val=1;
	int val2=100;;
	int intkey=10;

	data.insert(val, k1, intkey);
	data.insert(val2, k2, 20);

	try
	{
		std::cout << " get value from int 1:  value=" << data.get(intkey) << std::endl;
		std::cout << " get value from string: value=" << data.get(k1) << std::endl;

		std::cout << " get value from int 2:  value=" << data.get(20) << std::endl;
		std::cout << " get value from string2: value=" << data.get(k2) << std::endl;
	}
	catch (std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

int test3()
{
	KeysMap<int, std::string, int, short> data;
	std::string k1("key1");
	std::string k2("key2");
	int val=1;
	int val2=100;
	int intkey=10;

	data.insert(val, k1, intkey, (short)2);
	data.insert(val2, k2, 20,  (short)3);

	try
	{
		std::cout << " get value from int 1:  value=" << data.get(intkey) << std::endl;
		std::cout << " get value from string: value=" << data.get(k1) << std::endl;
		std::cout << " get value from short: value=" << data.get((short)2) << std::endl;

		std::cout << " get value from int 2:  value=" << data.get(20) << std::endl;
		std::cout << " get value from string2: value=" << data.get(k2) << std::endl;
		std::cout << " get value from short: value=" << data.get((short)3) << std::endl;
	}
	catch (std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

int main()
{
	//test2();
	test3();
}
