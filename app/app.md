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

- ServiceContext: Organize Services within an application
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
