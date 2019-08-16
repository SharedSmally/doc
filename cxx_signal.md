
# [signal](https://en.cppreference.com/w/cpp/utility/program/signal)
```
#include <signal.h>
void signalHandlerFunc (int sig);

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sig_handler(int signo) {
    if (signo == SIGUSR1)    printf("received SIGUSR1\n");
    else if (signo == SIGKILL)   printf("received SIGKILL\n");
    else if (signo == SIGSTOP)   printf("received SIGSTOP\n");
}

int main() {
    if (signal(SIGUSR1, sig_handler) == SIG_ERR)  printf("\ncan't catch SIGUSR1\n");
    if (signal(SIGKILL, sig_handler) == SIG_ERR)  printf("\ncan't catch SIGKILL\n");
    if (signal(SIGSTOP, sig_handler) == SIG_ERR)  printf("\ncan't catch SIGSTOP\n");

    while(1) sleep(1);       
    return 0;
}
```
# [signal number](http://www.yolinux.com/TUTORIALS/C++Signals.html)
# [signal manual](http://man7.org/linux/man-pages/man7/signal.7.html)

# [sigaction] [manual](http://man7.org/linux/man-pages/man2/sigaction.2.html)
```
int sigaction (int signum, const struct sigaction *act, struct sigaction *oldact);
struct sigaction {
        void     (*sa_handler)(int);
        void     (*sa_sigaction)(int, siginfo_t *, void *);
        sigset_t   sa_mask;
        int        sa_flags;
        void     (*sa_restorer)(void);
};

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
 
static int exit_flag = 0;
static void hdl (int sig) {
	exit_flag = 1;
}
 
int main (int argc, char *argv[]) {
	struct sigaction act;
 	memset (&act, '\0', sizeof(act));
	act.sa_handler = &hdl;
	if (sigaction(SIGTERM, &act, NULL) < 0) {
		perror ("sigaction"); return 1;
	}
 	while (!exit_flag) ;
 	return 0;
}

void  handle_prof_signal(int signal, siginfo_t * info, void * context)
{
}

// install signal handler
struct sigaction sig_action;
struct sigaction old_action;

memset(&sig_action, 0, sizeof(sig_action));

sig_action.sa_sigaction = handle_prof_signal;
sig_action.sa_flags = SA_RESTART | SA_SIGINFO;
sigemptyset(&sig_action.sa_mask);

sigaction(SIGPROF, &sig_action, &old_action);

```

## Timer
```
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ucontext.h>
#include <sys/time.h>

struct itimerval timeout={0};

static void handle_prof_signal(int sig_no, siginfo_t* info, void *vcontext) {
  char output[100];
  ucontext_t *context = (ucontext_t*)vcontext;
  unsigned long pc = context->uc_mcontext.gregs[REG_PC];
  
  snprintf(output,100,"Sample at %lx\n",pc);
  write(1,output,strlen(output)+1);
  setitimer(ITIMER_PROF, &timeout, 0);
}

int main() {
  struct sigaction sig_action;
  memset(&sig_action, 0, sizeof(sig_action));
  sig_action.sa_sigaction = handle_prof_signal;
  sig_action.sa_flags = SA_RESTART | SA_SIGINFO;
  sigemptyset(&sig_action.sa_mask);
  sigaction(SIGPROF, &sig_action, 0);

  timeout.it_value.tv_sec=1;
  setitimer(ITIMER_PROF, &timeout, 0);
  volatile int i=0;
  do { i++; } while(1);
}
```
