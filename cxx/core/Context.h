#ifndef CONTEXT_H
#define CONTEXT_H

#include <Tree.h>

class ContextItem
{

};

typedef Tree<ContextItem> Context;
typedef std::shared_ptr<Context> ContextPtr;

#endif
