#include <App.h>

#include <cstdlib>
#include <string.h>

#include <iostream>
using namespace std;

static App * app_ = nullptr;

void setApp(App & app) {
	app_ = &app;
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

    switch (sig)
    {
    case SIGUSR1:
    case SIGUSR2:
    {
        App * app = getApp();
        if (app != nullptr)
        {
            app->setReturnCode( EXIT_SUCCESS ); //EXIT_FAILURE
        }
    }
    break;

    default:
    break;
    }
}

static void signalhandler(int signum, siginfo_t *info, void *ptr)
{
    cout << "Received signal " << signum << "\n";
    cout << "Signal originates from process " <<  (unsigned long)info->si_pid << "\n";
}

App::App()
   : retCodeProm_(), retCodeFut_(retCodeProm_.get_future())
{
}

void App::_init()
{
    // register signal handler
	memset(&act_, 0, sizeof(act_));

	act_.sa_flags = SA_SIGINFO;
	act_.sa_sigaction = signalhandler;

	sigaddset(&act_.sa_mask, SIGUSR1);
	sigaddset(&act_.sa_mask, SIGUSR2);

	sigaction(SIGUSR1, &act_, NULL);
	sigaction(SIGUSR2, &act_, NULL);

	// Install a signal handler
	//signal(SIGUSR1, sighandler);
}
/*
void App::print() const
{
	args_.print();
}
*/
void App::run()
{

}

int App::getReturnCode()
{
	return retCodeFut_.get();
}
void App::setReturnCode(int code)
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
