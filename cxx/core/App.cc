#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include <string.h>

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
// SIGUSR1   30,10,16    Term    User-defined signal 1
// SIGUSR2   31,12,17    Term    User-defined signal 2
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
    case SIGUSR2:
       app->setCode( EXIT_SUCCESS );
       break;

    default:
       app->setCode( EXIT_FAILURE );
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
App::App(int argc, char ** argv, char ** env)
: argc_(argc), argv_(argv),
  envc_(0), env_(env),
  retCode_(EXIT_SUCCESS)
{
    if (env_ != nullptr)
    {
        char ** ptr = env_;
        while ( *ptr != nullptr ) {
                ++ptr; ++ envc_;
        }
    }
}

const char * App::name() const
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

    for(int i=0; i<envc_; i++)
       cout << "\nenv[" << i << "]:" << env_[i];
    cout << endl;
}

///////////////////  CApp
CApp::CApp(int argc, char **argv, char ** env)
   : App(argc, argv, env),
	 retCodeProm_(),
	 retCodeFut_(retCodeProm_.get_future())
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

	//act.sa_handler = SIG_IGN; ignore
	act_.sa_flags = SA_SIGINFO;
	act_.sa_sigaction = signalhandler;

	// 9(SIGKILL) and 19(SIGSTOP) cannot be caught or ignored
	sigaddset(&act_.sa_mask, SIGUSR1);
	sigaddset(&act_.sa_mask, SIGUSR2);

	sigaction(SIGUSR1, &act_, NULL);
	sigaction(SIGUSR2, &act_, NULL);

	// Install a signal handler
	//signal(SIGUSR1, sighandler);
}

void CApp::setCode(int code)
{
	return retCodeProm_.set_value(code);
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

int sigemptyset(sigset_t *) – to clear the mask.
int sigfillset(sigset_t *) – to set all bits in the mask.
int sigaddset(sigset_t *, int signum) – to set bit that represents certain signal.
int sigdelset(sigset_t *, int signum) – to clear bit that represents certain signal.
int sigismember(sigset_t *, int signum) – to check status of certain signal in a mask.
 */

