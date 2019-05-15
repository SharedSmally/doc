# [epoll](http://man7.org/linux/man-pages/man2/epoll_ctl.2.html)
```
#include <sys/epoll.h>

int epoll_create(int size);
int epoll_create1(int flags);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
int epoll_pwait(int epfd, struct epoll_event *events, int maxevents, int timeout, const sigset_t *sigmask);

epoll_wait can be called by multithread, each with a separated events.

struct epoll_event {
    uint32_t     events;      /* Epoll events */
    epoll_data_t data;        /* User data variable */
};
typedef union epoll_data {
    void        *ptr;
    int          fd;
    uint32_t     u32;
    uint64_t     u64;
} epoll_data_t;
```

### epoll_create op:
Valid values for the op argument are:
```
EPOLL_CTL_ADD
      Add fd to the interest list and associate the settings specified in event with the internal file linked to fd.

EPOLL_CTL_MOD
      Change the settings associated with fd in the interest list to the new settings specified in event.

EPOLL_CTL_DEL
       Remove (deregister) the target file descriptor fd from the interest list.  The event argument is ignored and can be NULL
```
## events:
```
EPOLLET
     Sets the Edge Triggered behavior for the associated file descriptor( default behavior).

EPOLLONESHOT (since Linux 2.6.2)
     Sets the one-shot behavior for the associated file descriptor.
     This means that after an event is pulled out with epoll_wait(2) the associated file 
     descriptor is internally disabled and no other events will be reported by the epoll
     interface.  The user must call epoll_ctl() with EPOLL_CTL_MOD to rearm the file 
     descriptor with a new event mask.

EPOLLIN
    The associated file is available for read(2) operations.
EPOLLOUT
    The associated file is available for write(2) operations.
EPOLLPRI
    There is an exceptional condition on the file descriptor.

EPOLLRDHUP (since Linux 2.6.17)
    Stream socket peer closed connection, or shut down writing half of connection.  
    (This flag is especially useful for writing simple code to detect peer shutdown 
    when using Edge Triggered monitoring.)
EPOLLERR
    Error condition happened on the associated file descriptor.
    This event is also reported for the write end of a pipe when
    the read end has been closed.  epoll_wait(2) will always
    report for this event; it is not necessary to set it in events.

EPOLLHUP
     Hang up happened on the associated file descriptor. epoll_wait(2) 
     will always wait for this event; it is not necessary to set it in events.            
```
