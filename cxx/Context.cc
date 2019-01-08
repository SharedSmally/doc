#include <Context.h>

Context & appContext() {
	static Context appCtx_;
	return appCtx_;
}


ContextPtr Context::getSubContext(const std::string & name, bool create)
{
	contexts_type::locker_type locker(subContexts_.mutex());

	auto it=subContexts_.find(name);
	if (it == subContexts_.end()) {
		if (create) {
			ContextPtr ptr(new Context(this));
			subContexts_.insert(std::make_pair(name,ptr));
			return ptr;
		} else {
			return nullptr;
		}
	} else {
		return it->second;
	}
}
bool Context::destroySubContext(const std::string & name)
{
	contexts_type::locker_type locker(subContexts_.mutex());
	subContexts_.erase(name);
}

bool Context::hasSubContext(const std::string & name)
{
	contexts_type::locker_type locker(subContexts_.mutex());
	return subContexts_.find(name) != subContexts_.end();
}

void Context::subContextNames(names_type & names)
{
	contexts_type::locker_type locker(subContexts_.mutex());
	for (auto it=subContexts_.begin(); it!=subContexts_.end(); ++it)
	    names.push_back(it->first);
}

// contents: consumer portion
bool Context::contains(const std::string & name)
{
	contents_type::locker_type locker(contents_.mutex());
	return contents_.find(name) != contents_.end();
}

MObjectPtr Context::get(const std::string & name)
{
	contents_type::locker_type locker(contents_.mutex());
	auto it=contents_.find(name);
	return (it == contents_.end()) ? nullptr : it->second;
}

void Context::names(std::vector<std::string> & names)
{
	contents_type::locker_type locker(contents_.mutex());
	for (auto it=contents_.begin(); it!=contents_.end(); ++it)
	    names.push_back(it->first);
}

// contents: producer portion
bool Context::bind(const std::string & name, MObjectPtr obj)
{
	contents_type::locker_type locker(contents_.mutex());
	contents_.insert(std::make_pair(name,obj));
}

void Context::unbind(const std::string & name)
{
	contents_type::locker_type locker(contents_.mutex());
	contents_.erase(name);
}
