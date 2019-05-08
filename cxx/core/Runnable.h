#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <memory>

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

class Cancellable : public Runnable
{
public:
	enum State {
		READY,
		RUNNING,
		CANCELLED,
		FINISHED
	};

	Cancellable() : state_(READY) { }
	virtual ~Cancellable() {}
    virtual void run()
    {
    	if (state_ != READY) return;
    	state_ = RUNNING;
    	_run();
    	state_ = FINISHED;
    }
    bool cancel()
    {
    	if (state_ == READY)
    	{
    		state_ = CANCELLED;
    		return true;
    	}
    	else
    	{
    		return false;
    	}
    }
    State state()
    {
    	return state_;
    }

protected:
    virtual void _run() = 0;

protected:
    State state_;
    //std::mutex mtx_;
};


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

