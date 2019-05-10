#include <AppContext.h>

#include <iostream>
using namespace std;

static const std::string EMPTY_STRING("");
static const Properties EMPTY_PROPERTIES;

void AppContext::start()
{
	cout << "AppContext::start()" << endl;
}
void AppContext::stop()
{
	cout << "AppContext::stop()" << endl;
}

ManageablePtr AppContext::get(const std::string & name)
{
	auto it = container_.find(name);
	return (it == container_.end() ) ? ManageablePtr(nullptr) : it->second;
}

bool AppContext::hasProperties(const std::string & group) const
{
	return propsgroup_.find(group) != propsgroup_.end();
}
const Properties & AppContext::getProperties(const std::string & group) const
{
	auto it = propsgroup_.find(group);
	return it == propsgroup_.end() ? EMPTY_PROPERTIES : it->second;
}

bool AppContext::hasProperty(const std::string & group, const std::string & name) const
{
	auto it = propsgroup_.find(group);
	if ( it == propsgroup_.end() ) return false;

	return it->second.find(name) != it->second.end();
}
const std::string & AppContext::getProperty(const std::string & group, const std::string & name) const
{
	auto it = propsgroup_.find(group);
	if ( it == propsgroup_.end() ) return EMPTY_STRING;

	auto prop = it->second.find(name);
	return prop == it->second.end() ? EMPTY_STRING : prop->second;
}

void AppContext::loadProperties(const std::string & filename)
{

}
void AppContext::saveProperties(const std::string & filename)
{

}
