
#[signal](https://en.cppreference.com/w/cpp/utility/program/signal)
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

#
