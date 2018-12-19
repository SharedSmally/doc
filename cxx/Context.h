#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>

class MObject {
public:
	virtual ~MObject()
	{}

	virtual size_t hashcode() const = 0;
};
typedef std::shared<MObject> MObjectPtr;

class Context
{
public:
	typedef std::shared<Context> ptr_type;

	Context(const std::string & name);
	virtual ~Context() {}

	virtual ptr_type parent() = 0;
	virtual bool hasChild(const std::string & name);
	virtual Context & child(const std::string & name);

	virtual std::vector<std::string> childNames();
	virtual void childNames(std::vector<std::string> & names);

	virtual const std::string & name();

	virtual bool contains(const std::string & name);
	virtual MObjectPtr get(const std::string & name);
};

Context & context();

typedef std::shared<Context> ContextPtr;

#endif

/*
 ContextPtr ctx;
 while (ctx) {
     ctx.xxx;
     ctx = ctx->parent();
 }
 */
