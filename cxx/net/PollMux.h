#ifndef POLLMUX_H
#define POLLMUX_H

#include <Multiplexer.h>

class PollMux
  : public Multiplexer, public IOEventsHandler
{
public:
    PollMux();
    ~PollMux();

    virtual bool add(FdObjPtr & ptr);
    virtual bool remove(FdObjPtr & ptr);
    virtual bool onEvents(FdObjPtr & obj);

    virtual IOEventsHandler & getHandler() { return *this; }

protected:
    virtual void monitorTask();
    bool monitor(FdObjPtr & ptr);

protected:

};

#endif /* end of POLLMUX_H */

