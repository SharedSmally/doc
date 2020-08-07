# [Netty](https://netty.io/)

##mvn
```
<property>
    <netty.version>4.1.51.Final</netty.version>
</property>

<dependency>
    <groupId>io.netty</groupId>
    <artifactId>netty-all</artifactId>
    <version>${netty.version}</version>
</dependency>
```

## Channels (socket,sctp for NIO, OIO-deprecated)
- ChannelGroup / ChannelPool
- TCP/IP: 
    - io.netty.channel.socket interfaces
        - DatagramChannel/DatagramChannelConfig : DatagramPacket
        - SocketChannel/SocketChannelConfig
        - ServerSocketChannel / ServerSocketChannelConfig
    - io.netty.channel.socket.nio classes:
         - NioDatagramChannel
         - NioSocketChannel
         - NioServerSocketChannel
    - io.netty.channel.socket.oio classes: deprecated
         - OioDatagramChannel
         - OioSocketChannel
         - OioServerSocketChannel
- SCTP/IP:
    - io.netty.channel.sctp interfaces
         - SctpChannel / SctpChannelConfig
         - SctpServerChannel / SctpServerChannelConfig : SctpMessage
    - io.netty.channel.sctp.nio classes:
         - NioSctpChannel
         - NioSctpServerChannel
    - io.netty.channel.sctp.oio classes: deprecated
         - OioSctpChannel
         - OioSctpServerChannel
- unix
      - DatagramSocketAddress / DomainSocketAddress
      - UnixChannel / ServerDomainSocketChannel
      - DomainSocketChannel / DomainSocketChannelConfig
- local
      - LocalEventLoopGroup / LocalAddress
      - LocalChannel / LocalServerChannel
- rxtx
      - RxtxDeviceAddress / RxtxChannelOption<T> / RxtxChannelConfig
      - RxtxChannel

## Transprots
- OIO: old blocking IO: n<1000; OioEventLoopGroup (deprecated)
- NIO : NIO based nonblocking: n>1000: 
      - NioEventLoop; NioEventLoopGroup
- epoll: 
      - EpollEventLoopGroup / Epoll / EpollTcpInfo / EpollMode	 
      - EpollChannelConfig / / EpollServerChannelConfig / EpollChannelOption<T>	
      - EpollDatagramChannel / EpollDatagramChannelConfig 	 
      - EpollDomainSocketChannel / EpollDomainSocketChannelConfig  
      - EpollServerDomainSocketChannel / EpollServerChannelConfig  
      - EpollServerSocketChannel / EpollServerSocketChannelConfig       
      - EpollSocketChannel / EpollSocketChannelConfig        
- kqueue

- ndt: Deprecated 

## Codecs:  io.netty.handler.codec
- base64
- bytes
- compression
- dns
- haproxy
- http / http2
- json / xml/protobuf
- ssl
- ......

