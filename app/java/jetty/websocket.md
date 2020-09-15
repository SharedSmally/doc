# jetty WebSocket
- [Document](https://www.eclipse.org/jetty/documentation/current/websocket-jetty.html)

##

### Events
- On Connect Event

An indication to the WebSocket that the Upgrade has succeeded and the WebSocket is now open.
An org.eclipse.jetty.websocket.api.Session object will be passed for this Open Event.
For normal WebSockets,  store and use this Session for communicating with the Remote Endpoint.
For Stateless WebSockets, the Session will be passed into each event as it occurs, allowing to only have 1 instance of a WebSocket serving many Remote Endpoints.

- On Close Event
An indication that the WebSocket is now closed.
Every Close Event will have a Status Code (and an optional Closure Reason Message)
A normal WebSocket closure will go through a Close Handshake where both the Local Endpoint and the Remote 
Endpoint both send a Close frame to indicate that the connection is closed.

It is possible for the Local WebSocket to indicate its desire to Close by issuing a Close frame to the Remote Endpoint,
but the Remote Endpoint can continue to send messages until it sends a Close Frame. This is known as a Half-Open connection, 
and it is important to note that once the Local Endpoint has send the Close Frame it cannot write anymore WebSocket traffic.

On an abnormal closure, such as a connection disconnect or a connection timeout, the low level connection will be terminated 
without going through a Close Handshake, this will still result in an On Close Event (and likely a corresponding On Error Event).

- On Error Event
If an error occurred, during the implementation, the WebSocket will be notified via this event handler.

- On Message Event
An indication that a complete message has been received and is ready for handling by your WebSocket.
This can be a (UTF8) TEXT message or a raw BINARY message.

### Session

### Send messages
- Blocking Sending
```
RemoteEndpoint remote = session.getRemote();

ByteBuffer buf = ByteBuffer.wrap(new byte[] { 0x11, 0x22, 0x33, 0x44 });
try {
    remote.sendBytes(buf); //binary
    remote.sendString("Hello World"); //string
} catch (IOException e) {
    e.printStackTrace(System.err);
}
```
- Blocking Sending partial
```
RemoteEndpoint remote = session.getRemote();

ByteBuffer buf1 = ByteBuffer.wrap(new byte[] { 0x11, 0x22 });
ByteBuffer buf2 = ByteBuffer.wrap(new byte[] { 0x33, 0x44 });
try {
    remote.sendPartialBytes(buf1,false);
    remote.sendPartialBytes(buf2,true); // isLast is true
    
    remote.sendPartialString("hello",false);
    remote.sendPartialString("world",true); // last part
} catch (IOException e) {
    e.printStackTrace(System.err);
}
```
- Async Sending
```

```
