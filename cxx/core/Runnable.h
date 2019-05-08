#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <memory>

#include <Time.h>

#ifdef TEST
#include <iostream>
#endif

class Runnable
{
public:
    virtual ~Runnable() {}
    virtual void run() = 0;
};
typedef std::shared_ptr< Runnable > RunnablePtr;


class Timer
{
public:
	Timer(const Time & time)
      : expireTime_(time)
    {}
	Timer(const Duration & delay)
      : expireTime_(Clock::now() + delay)
    {}
    virtual ~Timer()
    {}
    const Time & expireTime() const
    {
        return expireTime_;
    }
    void expireTime(const Time & time)
    {
        expireTime_ = time;
    }
    virtual void run() = 0;

protected:
    Time expireTime_;
};
typedef std::shared_ptr< Timer> TimerPtr;




template <typename T >
class Callable : public Runnable
{
public:
    Callable() : val_()
    {}

    template <class... Args>
    Callable(Args... args)
      : val_(args...)
    {}

    virtual ~Callable()
    {}

    T & get() { return val_; }
    const T & get() const { return val_; }

    virtual void run()
    {
#ifdef TEST
        std::cout << "Callable:run()" << std::endl;
#endif
    };

protected:
    T val_;
};


template <typename T >
class Callable < T *> : public Runnable
{
public:
    typedef std::shared_ptr< T > type;
    Callable() : val_(std::make_shared< T > ())
    {}

    template <class... Args>
    Callable(Args... args)
       : val_(std::make_shared< T > (args...) )
    {}

    virtual ~Callable()
    {}

    type & get() { return val_; }
    const type & get() const { return val_; }

    virtual void run()
    {
#ifdef TEST
        std::cout << "Callable*:run()" << std::endl;
#endif
    };

protected:
    type val_;
};

#endif
