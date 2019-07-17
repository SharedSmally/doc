#include <Context.h>
class ContextMgr
{
public:
    static ContextMgr & instance() { return instance_; }
    Context &  getRoot() { return root_; }

protected:
    ContextMgr()
	: root_()
	{ }
    ~ContextMgr()
    {
    	std::cout << "~ContextMgr()" << std::endl;
    }

private:
    static ContextMgr instance_;
    Context root_;
};

ContextMgr ContextMgr::instance_;

Context & getContext()
{
	ContextMgr::instance().getRoot();
}

ContextPtr getContext(const std::string & fullname)
{
	std::vector<std::string> names;
	split(names, fullname, '/');

	return ContextMgr::instance().getRoot().getNode(names);
}
