#ifndef APP_H
#define APP_H

#include <future>
#include <string>

class AppArgs  //parse command line arguments
{
public:
	AppArgs(int argc, char ** argv, char ** env = nullptr);
	virtual ~AppArgs(){}

protected:
	virtual void parse(int argc, char ** argv, char ** env = nullptr) = 0;
};

class App
{
public:
	static std::string getEnv( std::string const & env );
	App(int argc, char ** argv, char ** env = nullptr);
	virtual ~App(){}

	virtual void run() noexcept = 0;
	virtual void setCode( int code ) = 0;

	virtual int getCode() { return retCode_; }

	void print() const;
	const char * name() const;
	// getAppInfo:  (unsigned long)getpid()

private:
	App() = delete;
	App(const App &) = delete;
	App & operator=(const App &) = delete;

protected:
    int argc_;
    char ** argv_;
    int envc_;
    char ** env_;
    int retCode_;
};

// command-line-application; not need AppContext
template <typename ARGS>
class CLIApp : public App
{
public:
	typedef ARGS args_type;

	CLIApp(int argc, char **argv, char **env = nullptr);
    virtual ~CLIApp() {};

    virtual void setCode(int retCode) {  retCode_ = retCode; }

    ARGS & args() { return args_; }
    const ARGS & args() const { return args_; }

protected:
	ARGS args_;

};


//daemon application: main thread bolcked in getCode()
class CApp : public App
{
public:
	CApp(int argc, char **argv, char ** env = nullptr);
	virtual ~CApp() {}

	virtual void setCode(int retcode);

protected:
	virtual void _signal(); // register signal handler

protected:
	std::promise<int> retCodeProm_;
	std::future<int> retCodeFut_;
};


template <typename CONTEXT>
class TApp : public CApp
{
public:
	typedef CONTEXT context_type;
    TApp(int argc, char **argv, char ** env = nullptr);
    virtual ~TApp() {};

    context_type & context() { return ctx_; }
    const context_type & context() const { return ctx_; }

    virtual void run() noexcept;

protected:
	CONTEXT ctx_;
};


///////////////////////////////////// impl
template <typename ARGS>
CLIApp<ARGS>::CLIApp(int argc, char **argv, char **env)
: App(argc, argv, env), args_(argc, argv, env)
{
}

template <typename CONTEXT>
TApp<CONTEXT>::TApp(int argc, char **argv, char ** env)
: CApp(argc, argv, env), ctx_(*this, argc, argv, env)
{
}

template <typename CONTEXT>
void TApp<CONTEXT>::run() noexcept
{
	//start tasks in main thread
	try {
		ctx_.start();
	} catch (std::exception & ex) {
		retCode_ = EXIT_FAILURE;
		return;
	} catch (...) {
		retCode_ = EXIT_FAILURE;
		return;
	}

	// blocked to waiting for signal
	retCode_ = retCodeFut_.get();

	//stop tasks in main thread
	try {
		ctx_.stop();
	} catch (std::exception & ex) {
		retCode_ = EXIT_FAILURE;
		return;
	} catch (...) {
		retCode_ = EXIT_FAILURE;
		return;
	}
}


#endif

