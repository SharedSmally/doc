# Internal Process Communication

- Pipe: between parent-child processes
```
#define ReadEnd  0
#define WriteEnd 1
int pipe(int fildes[2]);  # one for read, one for write.
```

- FIFO: named pipe
```
int mkfifo(const char *pathname, mode_t mode);
```

- Message Queue
```
#include <mqueue.h>
mqd_t mq_open(const char *name, int oflag);
mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);

int mq_notify(mqd_t mqdes, const struct sigevent *sevp);

int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio);
int mq_timedsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio, const struct timespec *abs_timeout);

ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio);
ssize_t mq_timedreceive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio, const struct timespec *abs_timeout);
```
- Sempaphore
```
#include <sys/sem.h>

int semget(key_t key, int nsems, int semflg);
int semctl(int semid, int semnum, int cmd, ...);
int semop(int semid, struct sembuf *sops, unsigned nsops);
int semtimedop(int semid, struct sembuf *sops, unsigned nsops, struct timespec *timeout);
```
- Shared-Memory
```
#include <sys/shm.h>
int shmget(key_t key, size_t size, int shmflg);
iqnt shmctl(int shmid, int cmd, struct shmid_ds *buf);
int shmdt(const void *shmaddr);
```
- Futex: 
fast user-space locking, provides a method for waiting until a certain condition becomes true. 
```
#include <linux/futex.h>
int futex(int *uaddr, int op, int val, const struct timespec *timeout, int *uaddr2, int val3);
uaddr could be shared memory.
```
- Socket

- SocketPair (only for PF-UNIX)

