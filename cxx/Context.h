#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>
#include <string>

#include <Lockable.h>

class MObject {
public:
	virtual ~MObject()
	{}

	virtual size_t hashcode() const {
		return (size_t)(this);
	}
};
typedef std::shared<MObject> MObjectPtr;

class Context
{
public:
	typedef std::vector<Context *> subcontext_container_type;
	typedef std::vector<MObjectPtr>  content_container_type;
	typedef std::vector<std::string> name_container_type;
	
	Context() : parent(nullptr);
	~Context() {}

	//parent
	Context * parent() { return parent_; }
	const Context * parent() const { return parent_; }
	bool isRoot() const { return nullptr=parent; }
	
	// subcontexs
	Context * getSubContext(const std::string & name, bool create=true);
        bool destroySubContext(const std::string & name);
	
	bool hasSubContext(const std::string & name);
	void subContextNames(std::vector<std::string> & names);
	std::vector<Context *> & subContexts() { return subContexts_;}
	std::vector<Context *> & subContexts() const { return subContexts_;}	

	// contents: consumer portion
	bool contains(const std::string & name);
	MObjectPtr get(const std::string & name);
	void names(std::vector<std::string> & names);

	// contents: producer portion
	template <typename T >
	bool bind(const std::string & name);
	bool bind(const std::string & name, MObjectPtr obj);
	bool unbind(const std::string & name);

	// bind factory with interface and implementation, maybe in
	template <typename I, typename IMPL >
	bool bind(const std::string & name);	
	template <typename I >
	std::unique_ptr<I> create<I>();
	
protected:
	Context(Context * parent) : parent_(parent)();
	
protected:
	Context * parent_;
	subcontext_container_type subContexts_;
	content_container_type contents_;
};

Context & appContext();

typedef std::shared<Context> ContextPtr;

#endif

/*
 ContextPtr ctx;
 while (ctx) {
     ctx.xxx;
     ctx = ctx->parent();
 }
 */
