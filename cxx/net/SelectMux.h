#ifndef SELECTMUX_H
#define SELECTMUX_H

#include <Multiplexer.h>

class SelectMux
  : public Multiplexer, public IOEventsHandler
{
public:
    SelectMux();
    ~SelectMux();

    virtual bool add(FdObjPtr & ptr);
    virtual bool remove(FdObjPtr & ptr);
    virtual bool onEvents(FdObjPtr & obj);

    virtual IOEventsHandler & getHandler() { return *this; }

protected:
    virtual void monitorTask();
    bool monitor(FdObjPtr & ptr);
};

#endif /* end of SELECTMUX_H */
