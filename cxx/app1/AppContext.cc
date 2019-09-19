#include <AppContext.h>

#include <iostream>
using namespace std;

static const std::string EMPTY_STRING("");
//static const Properties EMPTY_PROPERTIES;

AppContext::AppContext(App & app)
: app_(app)
{
}

App & AppContext::app()
{
    return app_;
}

ManageablePtr AppContext::get(const std::string & name)
{
    auto it = container_.find(name);
    return (it == container_.end() ) ? ManageablePtr(nullptr) : it->second;
}
