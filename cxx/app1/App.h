#ifndef CPW_APP_H
#define CPW_APP_H

#include <unistd.h>

#include <future>
#include <string>

#include <AppContext.h>

/**
 * App: base class for all Applications.
 * Subclasses: ConsoleApp; GuiApp; ServerApp
 * main.cc:
 *
 * int main(int argc, char* argv[]) {
 *    MyApp app(argc, argv);
 *    if (app.start())
 *       return app.getRetCode(); //blocked
 *    else
 *       return EXIT_FAILURE;
 * }
 *
 * int main()
 * int main(int argc, char* argv[], char **envp)
 *
 */

class App
{
public:
    static std::string getEnv( std::string const & env );
    App(int argc, char * argv[]);
    virtual ~App(){}

    virtual void setRetCode( int code ) = 0;
    virtual int getRetCode() = 0;

    void print() const;
    // command name: first argument
    const char * cmd() const;
    int argc() const { return argc_; }
    char ** argv() const { return argv_; }

    // getAppInfo:  (unsigned long) getpid()
private:
    App() = delete;
    App(const App &) = delete;
    App & operator=(const App &) = delete;

protected:
    int argc_;  // including cmd, min=1
    char ** argv_;
};


/**
 * Short-lived command-line-application
 * using AppArgs to parse command-line-args and AppTask to do the work.
 *
 * class MyAppArgs : pubic AppArgs {
 *    virtual void parse(int argc, char ** argv) {
 *       .......
 *    }
 * }
 * template < >
 * class AppTask<MyAppArgs> {
 *     void run(App & app, const MyAppArgs & args) {
 *        .......;
 *     }
 * }
 *
 * main.cc:
 * int main(int argc, char* argv[]) {
 *    App<MyAppArgs> app(argc, argv);
 *    app.run();
 *    return app.getRetCode();
 * }
 *
 */
class AppArgs  // command line arguments/parameters
{
public:
    AppArgs(){};
    virtual ~AppArgs(){}
    virtual bool parse(int argc, char ** argv) = 0;
};

template <typename ARGS>
class AppTask
{
public:
    AppTask(){};
    virtual ~AppTask(){}
    // as interface or virtual method for individual class to impl it
    virtual void run(App & app, const ARGS & args) = 0;
};

template <typename ARGS>
class CLIApp : public App
{
public:
    typedef ARGS args_type;

    CLIApp(int argc, char **argv)
    : App(argc, argv), args_(),
      retCode_(EXIT_SUCCESS)
    {}
    virtual ~CLIApp() {};

    virtual void setRetCode( int code ) { retCode_ = code; };
    virtual int getRetCode() { return retCode_; }

    virtual void run() noexcept
    {
        if (!args_.parse(argc_, argv_))
        {
            retCode_ = EXIT_FAILURE;
            return;
        }

        AppTask<ARGS> task;
        task.run(*this, args_);
    }

    //ARGS & args() { return args_; }
    const ARGS & args() const { return args_; }

protected:
    ARGS args_;
    int retCode_;
};


/**
 * Long-lived Daemon application with signal handler
 */
//
class CApp : public App
{
protected:
    enum AppState {
        INIT = 0,
        CONFIG = 1,
        STARTING = 2,
        RUNNING = 3,
        STOPPING = 4,
        STOPPED = 5
    };

public:
    CApp(int argc, char **argv);
    virtual ~CApp() {}

    void setRetCode(int code)
    {
        return retCodeProm_.set_value(code);
    }
    int getRetCode()
    {
        return retCodeProm_.get_future().get();
    }

    virtual bool start() noexcept = 0;
    virtual void stop() noexcept = 0;

protected:
    virtual void _signal(); // register signal handler

protected:
    AppState state_;
    std::promise<int> retCodeProm_;
};

/**
 * SApp: The Server App with IPC/Network:
 *    app name:port list-of-config files
 *  Use AppContext to handle components;
 *     Info/Config/Update/ResetMgr for Application status and configs
 *
 * class MyApp : public SApp {
 *
 * }
 *
 * main.cc:
 * int main(int argc, char* argv[]) {
 *    MyApp app(argc, argv);
 *    if (app.start())
 *       return app.getRetCode(); //blocked
 *    else
 *       return EXIT_FAILURE;
 * }
 */
//class AppContext;

class SApp : public CApp
{
public:
    SApp(int argc, char **argv)
     : CApp(argc, argv),
       ctx_(*this), name_(), port_(0)
    {}
    virtual ~SApp() {};

    AppContext & context() { return ctx_; }
    const AppContext & context() const { return ctx_; }

    virtual bool start() noexcept;
    virtual void stop() noexcept;

    int16_t port() const { return port_; }
    const std::string & name() const { return name_; }

protected:
    static const int MIN_CLI_ARGS = 4; // cmd name port cfgs
    static const int MAX_PORT = 65536;

    static const char FILE_PATH_SEPARATOR = '/';
    static const std::string ENV_PROJ_NAME;
    static const std::string ENV_PROJ_HOME;
    static const std::string CONFIG_FILE_DIR;
    static const std::string CONFIG_FILE_SUFFIX;

    AppContext ctx_;   // for components and properties
    int16_t port_;     // for IPC
    std::string name_; // for ID


    static bool exitsFile(const std::string & filename) {
        return access( filename.c_str(), F_OK ) == 0;
    }
    static std::string fullPathFileName(const std::string & dir, const std::string & filename) {
        if (dir.empty()) return filename;
        if (dir.back()==FILE_PATH_SEPARATOR) {
            return dir+filename;
        } else {
            return dir+FILE_PATH_SEPARATOR+filename;
        }
    }
};

#endif
