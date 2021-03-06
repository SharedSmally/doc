# Interfaces
- Xxxable: Interface of the class of the Objects to be Managed 
- XxxObject/Xxxer: The concrete classes that implement the Xxxable interface
- XxxMgr: The Singleton concrete classes that manage the Xxxable managed objects
- XxxService: The Singleton concrete classes that provide Xxxable services, use multiple instances of XxxMgrs on different policies.

## Runnable
- void run(); 

## Taskable : Runnable
- void run(); 
- bool cancel(); 
- TaskStatus status() const; 
TaskStatus: INIT, CANCELLED, RUNNING, SUCESS, ERROR

## Timerable / TimerObject
- const Time & getExpireTime() const; 
- void setExpireTime( const Time &); 
- void onExpired(); 

## Streamable: input/output in binary format
- void input(std::istream & in)
- void output(std::ostream & out) const

## Comparable: order of the object
- CompareResult compare(const Comparable & obj) const
- CompareResult: LT(-1), LE, EQ(0), GE, GT(1)

## Object(Printable, Hashable)
- std::string toString() const ; // Printable
- bool fromString(const std::string &) ; // Parseable; Parser
- uint32_t hashCode() const ;    // Hashable

## Parseable: XmlParser, JsonParser, TextParser, MessageParser
- bool parse(std::istream & in) throws FormatException

## Lockable 
- void lock()
- void unlock()
- bool try_lock();

## Cloneable / Moveable
- T clone()
- T move()

## Singleton / SingletonMgr
- static T & instance() ; //Singleton
- static T & instance() ; //SingletonMgr

## Service : ServiceContext
Manager may

## Manageable / Factory / FactoryService (FactoryMgr)
Manage/create objects by name (Key)
- ManageablePtr get(const std::string & name)     
- T * get<T>(const std::string & name)
- bool put<T>(const std::string & name, ...Args);     
- bool has(const std::string & name);
- ManageablePtr remove(const std::string & name);

## Cacheable / CacheObject / CacheMgr
See for [Java Cache mechanism](https://dzone.com/articles/introducing-amp-assimilating-caching-quick-read-fo)
- Ehcache: Distributed, Level 2
- Hazelcast: Distributed data grid, Level 2
- Redis/Memcached: Distributed in-memory store
- Google Guava: In-process (same process)
- Coherence*: Distributed

## Persistenceable / DataObject / DataService(DataMgr): CRUD
- load()
- save()
- update()
- remove()
- const Key & getKey();
- static Persistenceable getByKey(const Key & key);
- static Persistenceable[] getByCriterion(const Criterion & criterion)

DataMgr implementation:
- SQL/ORM: JDBC, JPA
- NoSQL: Key-value
- Kafka Queue:

## Context: TreeNode
Tree struct to store/retrieve the objects
- Context & root();
- Context & parent();
- Container<Context> & siblings();  
- int index() const;
- Container<Context> & children();

## Event / EventSource / EventListener / EventHandler
- EventSource: the source object that can send out the events (Shareable)
- EventObject: the event objects that the EventSource send out when something happens, include the source
- EventListener: callback function called when the EventSource sends the EventObject
     - bool onEvent(EventObject & obj);
- EventHandler: handle the events,
     - register/deregister the EventListeners
     - bool handle(EventObject & obj); return false if not handled in this Handler.
- EventHandlerMgr: may have the tree- or linear- layout handlers to handle the events, Singleton

## FDObject:SocketObject / NetworkService
- FDObject: EventSource that uses fd to handle the events
- SocketObject: FDObject that uses socket as fd to handle the events
     - IPSocket
     - TCPSocket
     - UDPSOcket
     - SCTPSocket
     - ...
- NetworkService: use NetworkMgr of following subclasses:
    - PollMgr: use poll() function 
    - SelectMgr: use select() function 
    - EpollMgr: use epoll() function 
