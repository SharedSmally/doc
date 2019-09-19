#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include <string.h>

#include <AppContext.h>
#include <App.h>

#include <iostream>
using namespace std;

static App * app_ = nullptr;

void setApp(App * app) {
	app_ = app;
}
App * getApp() {
	return app_;
}

// handler should use global variable for context:
// see  man 7 signal for signal values (middle is x86)
// defined in /usr/include/asm-generic/signal.h
// SIGKILL	9	Kill signal
// SIGUSR1   30,10,16    Term    User-defined signal 1(10)
// SIGUSR2   31,12,17    Term    User-defined signal 2(12)
// SIGTERM	15	Termination signal
// SIGSTOP	17,19,23	Stop the process
static void sighandler (int sig)
{
    cout << "App Received signal " << sig << "\n";
    App * app = getApp();
    if (app == nullptr)
    {
    	cout << "App is null \n";
    	return;
    }

    switch (sig)
    {
    case SIGUSR1:
    case SIGQUIT:
    //case SIGUSR2:
       app->setRetCode( EXIT_SUCCESS );
       break;

    default:
       app->setRetCode( EXIT_FAILURE );
       break;
    }
}

static void signalhandler(int signum, siginfo_t *info, void *ptr)
{
    cout << "Received signal " << signum << " from process " <<  (unsigned long)info->si_pid << "\n";
    sighandler(signum);
}

std::string App::getEnv( std::string const & key )
{
    char * val = getenv( key.c_str() );
    return val == nullptr ? std::string("") : std::string(val);
}

///////////////////  App
App::App(int argc, char ** argv)
: argc_(argc), argv_(argv)
{
}

const char * App::cmd() const
{
    return argv_[0];
}

void App::print() const
{
    if (argc_==0) return;

    cout << "App name: " << argv_[0];
    for(int i=0; i<argc_; i++)
       cout << "\nargv[" << i << "]:" << argv_[i];
    cout << endl;
}

///////////////////  CApp
CApp::CApp(int argc, char **argv)
   : App(argc, argv),
	 retCodeProm_(), state_(INIT)
{
	::close(STDIN_FILENO); //close Standard input
	// 0	Standard input	STDIN_FILENO	stdin
	// 1	Standard output	STDOUT_FILENO	stdout
	// 2	Standard error	STDERR_FILENO	stderr

	_signal();
}


void CApp::_signal()
{
    ::setApp(this);

	// register signal handler: 1-31
	struct sigaction act_;
	memset(&act_, 0, sizeof(act_));

	//act.sa_handler = sighandler; //SIG_IGN; ignore
	act_.sa_flags = SA_SIGINFO;
	act_.sa_sigaction = signalhandler;

	// 9(SIGKILL) and 19(SIGSTOP) cannot be caught or ignored
	sigaddset(&act_.sa_mask, SIGUSR1); //10
	sigaddset(&act_.sa_mask, SIGUSR2); //12
	sigaddset(&act_.sa_mask, SIGQUIT); //3
	sigaddset(&act_.sa_mask, SIGTERM); //15

	sigaction(SIGUSR1, &act_, NULL);
	sigaction(SIGUSR2, &act_, NULL);
	sigaction(SIGQUIT, &act_, NULL);
	sigaction(SIGTERM, &act_, NULL);

	// Install a signal handler using signal
	//signal(SIGUSR1, sighandler);
}

const std::string SApp::ENV_PROJ_NAME("PROJECT_NAME");
const std::string SApp::ENV_PROJ_HOME("PROJECT_HOME");
const std::string SApp::CONFIG_FILE_DIR("cfg/");
const std::string SApp::CONFIG_FILE_SUFFIX(".cfg");

bool SApp::start() noexcept
{
    if (argc_ < MIN_CLI_ARGS)
    {
        std::cout << "Usage: " << cmd() << " name port cfgs" << std::endl;
        return false;
    }

    name_ = argv_[1];
    port_ = atoi(argv_[2]);  // port_=0 if not number of > 65536

    if (port_ == 0)
    {
        std::cout << "input port should be number in [0. 65535] " << std::endl;
        std::cout << "Usage: " << cmd() << " name port cfgs " << std::endl;
        return false;
    }

    std::cout << "App ID Name=" << name_ << std::endl;
    std::cout << "PROJECT NAME=" << App::getEnv(ENV_PROJ_NAME) << std::endl;
    std::cout << "PROJECT HOME=" << App::getEnv(ENV_PROJ_HOME) << std::endl;

    //parse the properties from config files
    std::string projHome = App::getEnv(ENV_PROJ_HOME);
    for (int i = MIN_CLI_ARGS-1; i< argc_; ++i)
    {
        std::string cfgfile = fullPathFileName(projHome, CONFIG_FILE_DIR+argv_[i]);

        if (exitsFile(cfgfile))
        {
        	std::cout << " parsing config file: " << cfgfile << std::endl;
        	//ctx_.loadProperties(cfgfile);
        }
        else
        {
        	std::string cfg2file = cfgfile+CONFIG_FILE_SUFFIX;
        	if (exitsFile(cfg2file)) {
        		std::cout << " parsing config file: " << cfg2file << std::endl;
        		//ctx_.loadProperties(cfg2file);
        	} else {
        		std::cout << " not find config file: " << cfgfile << " or " << cfg2file << std::endl;
        	}
        }
    }

    return true;
}

void SApp::stop() noexcept
{

}

/*
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
struct sigaction {
    void (*sa_handler)(int signum);
    void (*sa_sigaction)(int signum, siginfo_t *siginfo, void *uctx);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};
typedef struct {
	int si_signo;
	int si_code;
	union sigval si_value;
	int si_errno;
	pid_t si_pid;
	uid_t si_uid;
	void *si_addr;
	int si_status;
	int si_band;
} siginfo_t;
union sigval {
	int sival_int;
	void *sival_ptr;
};

int sigemptyset(sigset_t *); to clear the mask.
int sigfillset(sigset_t *); to set all bits in the mask.
int sigaddset(sigset_t *, int signum); to set bit that represents certain signal.
int sigdelset(sigset_t *, int signum); to clear bit that represents certain signal.
int sigismember(sigset_t *, int signum); to check status of certain signal in a mask.
 */
