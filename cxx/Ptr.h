
#ifndef CPW_PTR_H
#define CPW_PTR_H

#include <memory>

class Ptr : public std::enable_shared_from_this<Ptr>
{
public:
	// factory function that perfect-forwards args to a private ctor
	template<typename ... T>
	static std::shared_ptr<Ptr> create(T&& ... t) {
	    return std::shared_ptr<Ptr>(new Thingy(std::forward<T>(t)...));
	}

	//Requires a shared_ptr to be created before use
	std::shared_ptr<Ptr> getPtr() {
	     return shared_from_this();
	}

private:
     //We make constructor private - shared_from_this() breaks if a shared
     //ptr has never been created before.  (It looks for the control block)
     Ptr() : name_("Nameless Ptr") {}
     Ptr(std::string name) : name_(name) {}

     std::string name_;
};

void test()
{
	auto ptr = Ptr::create("Thing 1"); // to hold the shared object
	auto t = ptr->getPtr();  // via shared_ptr<Ptr> to get a new shared_ptr<Ptr>
	std::cout << "ptr.use_count() = " << t.use_count() << '\n';  //2
}

#endif
