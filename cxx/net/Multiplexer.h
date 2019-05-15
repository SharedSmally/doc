#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include <vector>
#include <deque>

#include <FdObj.h>


class IOTask
{
public:
	virtual void read(FdObjPtr & obj) = 0;
	virtual void write(FdObjPtr & obj) = 0;
};
typedef std::shared_ptr<IOTask> IOTaskPtr;

class Multiplexer {
public:
    Multiplexer();
    ~Multiplexer();

    virtual bool add(FdObjPtr & ptr) = 0;
    virtual bool remove(FdObjPtr & ptr) = 0;

protected:
    //dissociate/associate from monitoring;
    //bool associate(FdObjPtr & ptr);
    //bool unassociate(FdObjPtr & ptr);
    void notify(); //notify new set of fds to be minitored

    virtual void monitorTask() = 0; // one or more threads to monitor fds
    virtual void ioTask() = 0;  // one or more threads to read/write

protected:
    bool running_;

    typedef std::vector<FdObjPtr> container_type;
    //fds includes one notify fd, such as eventfd, pipe,...
    //to indicate that contents of fds_ changed
    container_type container_;  // fd=>fdObj; managed fdObj

    typedef std::deque<IOTaskPtr> iotasks_type;
    iotasks_type iotasks_;
};

#endif /* end of MULTIPLEXER_H */
