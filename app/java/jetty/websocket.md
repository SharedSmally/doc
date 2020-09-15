# jetty WebSocket
- [Document](https://www.eclipse.org/jetty/documentation/current/websocket-jetty.html)
- [java doc](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/websocket/api/package-summary.html)
- 3 Components
    - Web Socket
    - WebSocket Server (via WebServelet)
    - WebSocket Client

##  [WebSocket](https://www.eclipse.org/jetty/documentation/current/websocket-jetty.html)

### Events in [WebSocketConnectionListener](https://www.eclipse.org/jetty/javadoc/9.4.31.v20200723/org/eclipse/jetty/websocket/api/WebSocketConnectionListener.html)
- On Connect Event

An indication to the WebSocket that the Upgrade has succeeded and the WebSocket is now open.
An org.eclipse.jetty.websocket.api.Session object will be passed for this Open Event.
For normal WebSockets,  store and use this Session for communicating with the Remote Endpoint.
For Stateless WebSockets, the Session will be passed into each event as it occurs, allowing to only 
have 1 instance of a WebSocket serving many Remote Endpoints.

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

```
interface WebSocketConnectionListener
void onWebSocketClose(int statusCode, java.lang.String reason)	
void onWebSocketConnect(Session session)	
void onWebSocketError(java.lang.Throwable cause)	

All Known Subinterfaces:
WebSocketFrameListener:
void onWebSocketFrame(Frame frame)

WebSocketListener:
void onWebSocketBinary(byte[] payload, int offset, int len)	
void onWebSocketText(java.lang.String message)

WebSocketPartialListener:
void onWebSocketPartialBinary(java.nio.ByteBuffer payload, boolean fin)	
void onWebSocketPartialText(java.lang.String payload, boolean fin)

WebSocketPingPongListener:
void onWebSocketPing(java.nio.ByteBuffer payload)	
void onWebSocketPong(java.nio.ByteBuffer payload)
```

### [Session](https://www.eclipse.org/jetty/javadoc/9.4.31.v20200723/org/eclipse/jetty/websocket/api/Session.html)

Session represents an active link of communications with a Remote WebSocket Endpoint.
```
RemoteEndpoint getRemote()
UpgradeRequest	getUpgradeRequest()	
UpgradeResponse	getUpgradeResponse()
```

### Send messages via [RemoteEndpoint](https://www.eclipse.org/jetty/javadoc/9.4.31.v20200723/org/eclipse/jetty/websocket/api/RemoteEndpoint.html)
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
RemoteEndpoint remote = session.getRemote();
ByteBuffer buf = ByteBuffer.wrap(new byte[] { 0x11, 0x22, 0x33, 0x44 });
try {
    Future<Void> fut = remote.sendBytesByFuture(buf);
    fut.get(); // wait for completion (forever)
} catch (ExecutionException | InterruptedException e) {
    // Send failed
    e.printStackTrace();
}
```
- interface RemoteEndpoint
```
void sendBytes(java.nio.ByteBuffer data)	
void sendBytes(java.nio.ByteBuffer data, WriteCallback callback)	
java.util.concurrent.Future<java.lang.Void>	sendBytesByFuture​(java.nio.ByteBuffer data)	

void sendPartialBytes(java.nio.ByteBuffer fragment, boolean isLast)	
void sendPartialString(java.lang.String fragment, boolean isLast)	

void sendPing(java.nio.ByteBuffer applicationData)	
void sendPong(java.nio.ByteBuffer applicationData)	

void sendString(java.lang.String text)	
void sendString(java.lang.String text, WriteCallback callback)	
java.util.concurrent.Future<java.lang.Void>	sendStringByFuture(java.lang.String text)	
```

### Using WebSocket Annotations
```
import org.eclipse.jetty.websocket.api.Session;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketMessage;
import org.eclipse.jetty.websocket.api.annotations.WebSocket;

@WebSocket(maxTextMessageSize = 64 * 1024)
public class AnnotatedEchoSocket {
    @OnWebSocketMessage
    public void onText(Session session, String message) {
        if (session.isOpen()) {
            System.out.printf("Echoing back message [%s]%n", message);
            session.getRemote().sendString(message, null);// echo the message back
        }
    }
}
```
- @WebSocket:

A required class level annotation, flags this POJO as being a WebSocket. The class must be not abstract and public.

- @OnWebSocketConnect

An optional method level annotation. Flags one method in the class as receiving the On Connect event. Method must be public, not abstract, return void, and have a single Session parameter.

- @OnWebSocketClose

An optional method level annotation. Flags one method in the class as receiving the On Close event. Method signature must be public, not abstract, and return void.

The method parameters: Session (optional); int closeCode (required);  String closeReason (required)

- @OnWebSocketMessage

An optional method level annotation. Flags up to 2 methods in the class as receiving On Message events. One method for TEXT messages, and 1 method for BINARY messages.

Method signature must be public, not abstract, and return void.

The method parameters for Text messages: Session (optional);  String text (required)

The method parameters for Binary messages: Session (optional);  byte buf[] (required);  int offset (required);  int length (required)

- @OnWebSocketError
An optional method level annotation. Flags one method in the class as receiving Error events from the WebSocket implementation. Method signatures must be public, not abstract, and return void.

The method parameters: Session (optional); Throwable cause (required); 

@OnWebSocketFrame

An optional method level annotation. Flags one method in the class as receiving Frame events from the WebSocket implementation after they have been processed by any extensions declared during the Upgrade handshake. Method signatures must be public, not abstract, and return void.

The method parameters: Session (optional);  Frame (required)

## [WebSocket Server](https://www.eclipse.org/jetty/documentation/current/jetty-websocket-server-api.html)

- [WebSocketServlet](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/websocket/servlet/WebSocketServlet.html) 

Wire up WebSocket endpoints to Servlet Path Specs via a WebSocketServlet bridge servlet.. Internally, Jetty manages the HTTP Upgrade to WebSocket and migration from a HTTP Connection to a WebSocket Connection.
```
import javax.servlet.annotation.WebServlet;
import org.eclipse.jetty.websocket.servlet.WebSocketServlet;
import org.eclipse.jetty.websocket.servlet.WebSocketServletFactory;

@SuppressWarnings("serial")
@WebServlet(name = "MyEcho WebSocket Servlet", urlPatterns = {"/echo"})
public class MyEchoServlet extends WebSocketServlet {
    @Override
    public void configure(WebSocketServletFactory factory) {        
        factory.getPolicy().setIdleTimeout(10000); // set a 10 second timeout
        // register MyEchoSocket as the WebSocket to create on Upgrade
        factory.register(MyEchoSocket.class);
    }
}
```
All WebSocket’s are created via WebSocketCreator for those registered with the WebSocketServletFactory.

-[WebSocketCreator](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/websocket/servlet/WebSocketCreator.html)
Create WebSocket based on UpgradeRequest object
```
import org.eclipse.jetty.websocket.servlet.ServletUpgradeRequest;
import org.eclipse.jetty.websocket.servlet.ServletUpgradeResponse;
import org.eclipse.jetty.websocket.servlet.WebSocketCreator;

public class MyAdvancedEchoCreator implements WebSocketCreator {
    private MyBinaryEchoSocket binaryEcho;
    private MyEchoSocket textEcho;

    public MyAdvancedEchoCreator() {
        this.binaryEcho = new MyBinaryEchoSocket();
        this.textEcho = new MyEchoSocket();
    }

    @Override
    public Object createWebSocket(ServletUpgradeRequest req, ServletUpgradeResponse resp) {
        for (String subprotocol : req.getSubProtocols()) {
            if ("binary".equals(subprotocol)) {
                resp.setAcceptedSubProtocol(subprotocol);
                return binaryEcho;
            }
            if ("text".equals(subprotocol)) {
                resp.setAcceptedSubProtocol(subprotocol);
                return textEcho;
            }
        }
        // No valid subprotocol in request, ignore the request
        return null;
    }
}
```
Register the customized WebSocketCreatorvia WebServlet:
```
import javax.servlet.annotation.WebServlet;
import org.eclipse.jetty.websocket.servlet.WebSocketServlet;
import org.eclipse.jetty.websocket.servlet.WebSocketServletFactory;

@SuppressWarnings("serial")
@WebServlet(name = "MyAdvanced Echo WebSocket Servlet", urlPatterns = {"/advecho"})
public class MyAdvancedEchoServlet extends WebSocketServlet {
    @Override
    public void configure(WebSocketServletFactory factory) {
        factory.getPolicy().setIdleTimeout(10000);

        // set a custom WebSocket creator
        factory.setCreator(new MyAdvancedEchoCreator());
    }
}
```

## [WebSocket Client](https://www.eclipse.org/jetty/documentation/current/jetty-websocket-client-api.html)
- using [WebSocketClient](https://www.eclipse.org/jetty/javadoc/current/org/eclipse/jetty/websocket/client/WebSocketClient.html)
```
void addSessionListener (WebSocketSessionListener listener)	 
java.util.concurrent.Future<Session> connect(java.lang.Object websocket, java.net.URI toUri)	 
java.util.concurrent.Future<Session> connect(java.lang.Object websocket, java.net.URI toUri, ClientUpgradeRequest request)	
java.util.concurrent.Future<Session> connect(java.lang.Object websocket, java.net.URI toUri, ClientUpgradeRequest request, UpgradeListener upgradeListener)

websocket - the websocket object annotated with @WebSocket 
```
Sample:

Client App:
```
import java.net.URI;
import java.util.concurrent.TimeUnit;

import org.eclipse.jetty.websocket.client.ClientUpgradeRequest;
import org.eclipse.jetty.websocket.client.WebSocketClient;

public class SimpleEchoClient {
    public static void main(String[] args)    {
        String destUri = "ws://echo.websocket.org";
        WebSocketClient client = new WebSocketClient();
        SimpleEchoSocket socket = new SimpleEchoSocket();
        try {
            client.start();
            URI echoUri = new URI(destUri);
            ClientUpgradeRequest request = new ClientUpgradeRequest();
            client.connect(socket, echoUri, request);
            System.out.printf("Connecting to : %s%n", echoUri);
            // wait for closed socket connection.
            socket.awaitClose(5, TimeUnit.SECONDS);
        } catch (Throwable t) {
            t.printStackTrace();
        } finally {
            try {
                client.stop();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
```
WebSocket:
```
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

import org.eclipse.jetty.websocket.api.Session;
import org.eclipse.jetty.websocket.api.StatusCode;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketClose;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketConnect;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketError;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketMessage;
import org.eclipse.jetty.websocket.api.annotations.WebSocket;

@WebSocket(maxTextMessageSize = 64 * 1024)
public class SimpleEchoSocket {
    private final CountDownLatch closeLatch;
    @SuppressWarnings("unused")
    private Session session;

    public SimpleEchoSocket() {
        this.closeLatch = new CountDownLatch(1);
    }

    public boolean awaitClose(int duration, TimeUnit unit) throws InterruptedException {
        return this.closeLatch.await(duration, unit);
    }

    @OnWebSocketClose
    public void onClose(int statusCode, String reason) {
        System.out.printf("Connection closed: %d - %s%n", statusCode, reason);
        this.session = null;
        this.closeLatch.countDown(); // trigger latch
    }

    @OnWebSocketConnect
    public void onConnect(Session session) {
        System.out.printf("Got connect: %s%n", session);
        this.session = session;
        try {
            Future<Void> fut;
            fut = session.getRemote().sendStringByFuture("Hello");
            fut.get(2, TimeUnit.SECONDS); // wait for send to complete.

            fut = session.getRemote().sendStringByFuture("Thanks for the conversation.");
            fut.get(2, TimeUnit.SECONDS); // wait for send to complete.
        } catch (Throwable t) {
            t.printStackTrace();
        }
    }

    @OnWebSocketMessage
    public void onMessage(String msg){
        System.out.printf("Got msg: %s%n", msg);
        if (msg.contains("Thanks")) {
            session.close(StatusCode.NORMAL, "I'm done");
        }
    }

    @OnWebSocketError
    public void onError(Throwable cause) {
        System.out.print("WebSocket Error: ");
        cause.printStackTrace(System.out);
    }
}
```
