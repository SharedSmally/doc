```
Disable to use new:
You can just declare operator new = delete, similar to how you'd disable some constructors. Like

struct Foo {
    void* operator new(std::size_t) = delete;
    void* operator new[](std::size_t) = delete;
};

That'll give you compiler errors when you try to use new with this class. See https://godbolt.org/z/RToOcf

```

basic components for c++ application
- core: 
    Object; Wrapper; Traits; 
    Parseable/Printable/Streamable
    Mutex Lockable
    Runnable ThreadPool Executor
    Time Timer Scheduler

- cfg
    Monitorable
    Configurable (static configs from config files or sys-env) - Updateable (dynamic configs)
    Resetable: Metric<N>; Count; Gauge; Reportable (Auto report in interval)
    ConfigMgr/ResetMgr
    ConfigParser/Properties/PropertiesGroup: read config files  

- app
    Manageable  AppContext Application Factory  Service

- event
    EventSource EventHandler EventObject EventListener

- net
    Address: IPAddress/IPv4Address/IPv6Address; UnixAddress
    FDObject - FDObjOptions; FDObjListener; FDObjHandler 
    Socket: CSocket; DSocket; Connection  : SocketOptions
    TcpSocket-SslSocket; UdpSocket; McastSocket; SctpSocket; DsctpSocket; RawSocket
    Server; Client; Proxy

-ssl
    
-crypto
    
- regex

- logger
  Logger; FileLogger; CerrorLogger; CoutLogger; SyslogLogger; UdpLogger; KafkaLogger

- db: on unixODBC

- nosql
   redis:  XmlParser; JsonParser; ProtoBufferParser

- producer:
   Kafka

- utils:
    Files; Strings; 
