#include "Multiplexer.h"

#include <unistd.h>
#include <sys/eventfd.h>

#include <iostream>
using namespace std;

const int Multiplexer::numCPUS = std::thread::hardware_concurrency();

Multiplexer::Multiplexer()
  : running_(true), state_(INIT),
    notifyfd_(eventfd(1, EFD_CLOEXEC|EFD_NONBLOCK))
{
}

Multiplexer::~Multiplexer()
{
    ::close(notifyfd_);

    for ( auto & th : monitorThreads_)
        th.join();

    for ( auto & th : ioThreads_)
        th.join();
}

void Multiplexer::start( int numMonitor, int numIO)
{
    locker_type lock(mtx_);
    if (state_ != INIT) return;

    ioThreads_.reserve(numIO);
    monitorThreads_.reserve(numMonitor);

    for (int i=0; i<numMonitor; i++)
        ioThreads_.emplace_back([=] { monitorTask(); });

    for (int i=0; i<numIO; i++)
        ioThreads_.emplace_back([=] { ioTask(); });

    state_ = RUNNING;
}
void Multiplexer::stop()
{
    locker_type lock(mtx_);
    if (state_!=RUNNING) return;

    running_ = false;

    state_ = STOPPING;
    notify();

    cv_.notify_all();
}

void Multiplexer::ioTask()
{
    INFO( "enter ioTask thread" )
    while (running_) {
        FdObjPtr task(nullptr);
        {
            unilocker_type lk(mtx_);
            cv_.wait(lk, [=]{ return !iotasks_.empty() || !running_; });

            if (!running_) break;

            if (iotasks_.empty()) continue;

            task = iotasks_.front();
            iotasks_.pop_front();
        }

        if (task) {
            INFO( "run ioTask" )
            if (getHandler().onEvents(task))
            {
                monitor(task);
            }
            else
            {
                remove(task);
            }
        }
    }

    state_ = STOPPED;
}
