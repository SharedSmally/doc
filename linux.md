# Linux

## Performance
 - Record perfromance
 - Generate performance svg graph
 
## Network Tunning
  - Cache DNS query (~100ms)
    - update /etc/hosts:    ip hostname
    - install nscd
  - Extend port range
  - Reuse IP port
  - Update resource limits

## Functions
- [inotify](http://man7.org/linux/man-pages/man7/inotify.7.html)
   - [inotify_init](http://man7.org/linux/man-pages/man2/inotify_init.2.html)
     ```
       #include <sys/inotify.h>
       int inotify_init(void);
       int inotify_init1(int flags);
     ```
   - [inotify_add_watch](http://man7.org/linux/man-pages/man2/inotify_add_watch.2.html)
   ```
       #include <sys/inotify.h>
       int inotify_add_watch(int fd, const char *pathname, uint32_t mask);   
   ```
   - [inotify_rm_watch] (http://man7.org/linux/man-pages/man2/inotify_rm_watch.2.html)
   ```
       #include <sys/inotify.h>
       int inotify_rm_watch(int fd, int wd);
   ```
- eventfd](http://man7.org/linux/man-pages/man2/eventfd.2.html)
```
       #include <sys/eventfd.h>
       int eventfd(unsigned int initval, int flags);
```
- (epoll](http://man7.org/linux/man-pages/man7/epoll.7.html)
   - [epoll_create](http://man7.org/linux/man-pages/man2/epoll_create.2.html)
```
      #include <sys/epoll.h>
      int epoll_create(int size);
      int epoll_create1(int flags);
```
   - [epoll_ctl](http://man7.org/linux/man-pages/man2/epoll_ctl.2.html)
```
       #include <sys/epoll.h>
       int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```
   - [epoll_wait](http://man7.org/linux/man-pages/man2/epoll_wait.2.html)
```
       #include <sys/epoll.h>
       int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
       int epoll_pwait(int epfd, struct epoll_event *events, int maxevents, int timeout, const sigset_t *sigmask);
```
- [poll](http://man7.org/linux/man-pages/man2/poll.2.html)
```
       #include <poll.h>
       int poll(struct pollfd *fds, nfds_t nfds, int timeout);

       #include <signal.h>
       #include <poll.h>
       int ppoll(struct pollfd *fds, nfds_t nfds, const struct timespec *tmo_p, const sigset_t *sigmask);
```
- [select](http://man7.org/linux/man-pages/man2/select.2.html): monitor only file descriptors numbers that are less than FD_SETSIZE
```
       #include <sys/select.h>
       int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

       void FD_CLR(int fd, fd_set *set);
       int  FD_ISSET(int fd, fd_set *set);
       void FD_SET(int fd, fd_set *set);
       void FD_ZERO(fd_set *set);

       #include <sys/select.h>
       int pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timespec *timeout,
                   const sigset_t *sigmask);
```
- [event](http://man7.org/linux/man-pages/man3/event.3.html)
