# Application:

## Application: standalone application
- Application: process
    - TaskApp: , short-lived; run and then completed.
         - Configed with command line arguments
    - ServiceApp: long-lived application; run and waits for the services to be completed
         - Config with configuration file 
         - Contains a list of Services (organized by Tree as ServiceContext)
         
- Service: A single task run within the application.
    - May run in a single thread or threadgroup/threadpool, to handle the incoming messages.
    - Include Configurable Parameters, Resetable Parameters, Session Records
    - Configurable parameters: Configurations (Configurable from config file, Updateable from messages) and Metrics 
    - Resetable Parameters: includes Counts (only value, ++), Gauges(one value, ++,--) and Metrics)
    - Session Records: records for each transaction, may collect Session data from differernt services.
    - Session Data: data related to the session for the specific service
    - Session Context: Context for the session, including SessionID, Timeout, ...,

- ServiceContext: Organize Services within an application, the root is AppContext (one App has one AppContext)
    - Contains a list of services, and organized by parent-children relationship.

- Message/Serializable: Serializable object passing between services; could be xml,json,rawbytes,... (Format)
- DAO/Persistable: Data Access Object for Persistence; could be sql,redis,queue,mongodb,...; querying by key 
- Cacheable: part of Persistable; expired after the given time

## Basic Services
- ExecutorService: execute task
    - Task: One time work
- SchedulerService: schedule the tasks running in the future
    - Timer: Work to be done when timer expired    
- NetworkMgr: handle incoming/outgoing messages from network
- ModuleMgr: Manage the Module(library with the Services) dynamically
    - Handler: Specialized Service to handle the specific message
- Dispathcer: Dispatch the incoming messages to the specific Services
- DaoManager: Service interfaces for DAO data persistence:  CRUD
- CacheMgr: manage the Cacheable

## net
### Address: socket address
  - IPv4Addr/IPv6Addr/IPAddr/UnixAddr
### Socket: subclass of FDObject (subclass of EventObject), can be configured by SocketOptions
  - TCPSocket(connection-based unicast socket )
      - SslSocket
  - UDPSocket(connectionless-based unicast socket)
  - BcastSocket(BroadCast)
  - SctpSocket(Unicast Sctp socket)
  - BsctpSocket(Broadcast Sctp socket)
  - IPSocket(raw IP socket)
### SocketOptions; 
   managed by OptionMgr:  [xxx/Tcp/...Options]
### SocketHandler: 
   handle message from the socket, subclass of EventHandler, read/write raw binary data
### Channel: 
   combine SocketHandler (EventHandler) and Socket (EventObject)
### Socket/FD-based Multiplexer: EventMgr
   - PollMulplex: based on poll
   - SelectMulplex: based on select
   - EPollMulplex: based on epoll
### NetApp 
   - Server
   - Client
   - Proxy
### Session/SessionMgr:
associated by message; including a sequence of message via a Channel (TimedObject), may be separated into to 2 parts
- lower level handler: read/write data(binary)
- application level handler: convert raw binary data into application message, and handle it.

## Class
- public static Meta & getMeta(): MetaData about the class, static infomation; read only; class traits

```
template <typename META>
class MetaClass {
public:
static META & getMeta() { return meta_; }

private:
static META meta_;
};

class MyClass : MetaClass<String> {

};

String MetaClass<String>::meta_("String");
```

