#ifndef APP_H
#define APP_H

#include <signal.h>
#include <future>

#include <AppArgs.h>
#include <AppContext.h>

class App
{
public:
	App();
	~App(){}

	int getReturnCode();
	void setReturnCode(int reccode);

	virtual void run();
	void print() const;
	// getAppInfo:  (unsigned long)getpid()

private:
	App(const App &) = delete;
	App & operator=(const App &) = delete;

protected:
	void _init();
	std::promise<int> retCodeProm_;
	std::future<int> retCodeFut_;
	struct sigaction act_; // signal handler
};

template <typename ARGS>
class TApp : public App
{
public:
	typedef ARGS args_type;
	typedef AppContext<TApp<ARGS>, ARGS> context_type;

    TApp(int argc, char **argv)
    : args_(argc, argv), ctx_(*this, args_)
    {
    }
    TApp(int argc, char **argv, char ** env)
    : args_(argc, argv, env), ctx_(*this, args_)
    {}
    ~TApp()
    {};

    context_type & context() { return ctx_; }
	args_type & args() { return args_; }

private:
	TApp() = delete;
	TApp(const TApp &) = delete;
	TApp & operator=(const TApp &) = delete;

protected:
	context_type ctx_;
	args_type args_;
};


#endif
