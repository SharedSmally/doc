# [eventfd](http://man7.org/linux/man-pages/man2/eventfd.2.html)
eventfd - create a file descriptor for event notification
```
  #include <sys/eventfd.h>
  int eventfd(unsigned int initval, int flags);
```
eventfd() creates an "eventfd object" that can be used as an event
wait/notify mechanism by user-space applications, and by the kernel
to notify user-space applications of events.  The object contains an
unsigned 64-bit integer (uint64_t) counter that is maintained by the
kernel.  This counter is initialized with the value specified in the
argument initval.

As its return value, eventfd() returns a new file descriptor that can
be used to refer to the eventfd object.

The following values may be bitwise ORed in flags to change the behavior of eventfd():
- EFD_CLOEXEC (since Linux 2.6.27)

  Set the close-on-exec (FD_CLOEXEC) flag on the new file descriptor.
  
- EFD_NONBLOCK (since Linux 2.6.27)

  Set the O_NONBLOCK file status flag on the open file description 
  
- EFD_SEMAPHORE (since Linux 2.6.30)

  Provide semaphore-like semantics for reads from the new file descriptor.
  
Operations:
- read

Each successful read returns an 8-byte integer in host byte order. The operation
depends on whether the eventfd counter currently has a nonzero value and whether
the EFD_SEMAPHORE flag was specified when creating the eventfd file descriptor:

     -  If EFD_SEMAPHORE was not specified and the eventfd counter has a nonzero 
        value, then a read returns 8 bytes containing that value, and the 
        counter's value is reset to zero.
        
     - If EFD_SEMAPHORE was specified and the eventfd counter has a nonzero value,
       then a read returns 8 bytes containing the value 1, and the counter's 
       value is decremented by 1.
       
     - If the eventfd counter is zero at the time of the call to read, then the 
       call either blocks until the counter becomes nonzero or fails with the 
       error EAGAIN if the file descriptor has been made nonblocking.

- write

A write call adds the 8-byte integer value supplied in its buffer to the counter.
The maximum value that may be stored in the counter is the largest unsigned 
64-bit value minus 1 (i.e., 0xfffffffffffffffe). If the addition would cause 
the counter's value to exceed the maximum, then the write
either blocks until a read(2) is performed on the file
descriptor, or fails with the error EAGAIN if the file
descriptor has been made nonblocking.

-  poll, select (and similar)
       


