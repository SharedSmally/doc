# [Mock Server](https://www.mock-server.com/)
- [javadoc API]()

Via HTTP or HTTPS, MockServer can be used as 
- a mock configured to return specific responses for different requests
- a proxy recording and optionally modifying requests and responses
- both a proxy for some requests and a mock for other requests at the same time

MockServer supports the follow actions:
- Mock response:![Mock Response](https://www.mock-server.com/images/expectation_response_action.png)
- Forward a request: ![proxy](https://www.mock-server.com/images/expectation_forward_action.png)
- Return an invalid response 
- Verify requests
- Retrieve logs and requests

Maven Dependencies(mockserver):
- mockserver-client: class MockServerClient (when(HttpRequest),verify(HttpRequest);clear(HttpRequest);reset
- mockserver-client-java
- mockserver-core: model: Http\*/\*Body; 
- mockserver-junit-jupiter: class MockServerExtension and annotation MockServerSettings
- mockserver-junit-rule: class MockServerRule
- mockserver-netty: ClientAndServer(extends MockServerClient with UI)

```
<dependency>
    <groupId>org.mock-server</groupId>
    <artifactId>mockserver-netty</artifactId>
    <version>3.10.8</version>
</dependency>
<dependency>
    <groupId>org.mock-server</groupId>
    <artifactId>mockserver-client-java</artifactId>
    <version>3.10.8</version>
</dependency>
```
In the test class
```
import org.junit.*;
import static junit.framework.Assert.assertEquals;

import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.HttpClientBuilder;

import org.mockserver.client.server.MockServerClient;
import org.mockserver.integration.ClientAndProxy;
import org.mockserver.integration.ClientAndServer;
import org.mockserver.model.Header;
import org.mockserver.model.HttpForward;
import org.mockserver.verify.VerificationTimes;

import static org.mockserver.integration.ClientAndProxy.startClientAndProxy;
import static org.mockserver.integration.ClientAndServer.startClientAndServer;
import static org.mockserver.matchers.Times.exactly;
import static org.mockserver.model.HttpClassCallback.callback;
import static org.mockserver.model.HttpForward.forward;
import static org.mockserver.model.HttpRequest.request;
import static org.mockserver.model.HttpResponse.response;
import static org.mockserver.model.StringBody.exact;
```
## [MockServerClient](https://www.baeldung.com/mockserver)
**MockServerClient** API is used for providing a capability to connect to the MockServer. It models requests and the corresponding responses from the server
- when: ForwardChainExpectation	when(HttpRequest httpRequest[, Times times])
- verify: MockServerClient verify(HttpRequest httpRequest, Times times)
- retrieve: Expectation[] retrieveAsExpectations(HttpRequest httpRequest)
- retrieve: String 	retrieveAsJSON(HttpRequest httpRequest)

**HttpRequest**/**HttpResponse** API: 
- withBody
- withClientCertificateChain
- withContentType
- withCookie(s)
- withHeader(s)
- withMethod
- withPath
- withPathParameter
- withQueryStringParameter

- static HttpRequest 	request() 
- static HttpRequest 	request(String path) 
- static HttpResponse 	response()
- static HttpResponse 	response(String body)

**HttpForward** API
- static HttpForward 	forward()
- HttpForward 	withHost(String host)
- HttpForward 	withPort(Integer port)
- HttpForward 	withScheme(HttpForward.Scheme scheme)

**ForwardChainExpectation** API:
- void 	forward(HttpForward httpForward)
- void 	respond(HttpResponse httpResponse)

### Creating Expectations by request matcherand returns With Mock Responses
Requests can be matched using plain text or regular expressions for:
   - path – URL path
   - query string – URL parameters
   - headers – request headers
   - cookies – client side cookies
   -  body – POST request body with XPATH, JSON, JSON schema, regular expression, exact matching plain text or body parameters
And a response action will contain:
   - status codes – valid HTTP status codes e.g. 200, 400 etc.
   - body – it is the sequence of bytes containing any content
   - headers – response headers with name and one or more values
   - cookies – response cookies with name and one or more values
```
public class TestMockServer {
    private void createExpectationForInvalidAuth() {
        new MockServerClient("127.0.0.1", 1080)
          .when(
            request()  // static HttpRequest.request()
              .withMethod("POST")
              .withPath("/validate")
              .withHeader("\"Content-type\", \"application/json\"")
              .withBody(exact("{username: 'foo', password: 'bar'}")),
            exactly(1))
          .respond(
            response() // static HttpResponse.response()
              .withStatusCode(401)
              .withHeaders(
                   new Header("Content-Type", "application/json; charset=utf-8"),
                   new Header("Cache-Control", "public, max-age=86400"))
              .withBody("{ message: 'incorrect username and password combination' }")
              .withDelay(TimeUnit.SECONDS,1)
          );
    }
```

### Forwarding a Request
Expectation can be set up to forward the request. 
    - host – the host to forward to 
    - port – the port where the request to be forwarded, the default port is 80
    - scheme – protocol to use e.g. HTTP or HTTPS
```
private void createExpectationForForward(){
    new MockServerClient("127.0.0.1", 1080)
      .when(
        request()
          .withMethod("GET")
          .withPath("/index.html"),
        exactly(1))
      .forward(
        forward()
          .withHost("www.mock-server.com")
          .withPort(80)
          .withScheme(HttpForward.Scheme.HTTP)
      );
}
```
### Executing a Callback
The server can be set to execute a callback when receiving a particular request.Callback action can define callback class that implements org.mockserver.mock.action.ExpectationCallback interface:
```
private void createExpectationForCallBack() {
    mockServer
      .when(
        request().withPath("/callback"))
      .callback(
        callback().withCallbackClass("com.jpw.mock.server.TestExpectationCallback")
    );
}

public class TestExpectationCallback implements ExpectationCallback {
    public HttpResponse handle(HttpRequest httpRequest) {
        if (httpRequest.getPath().getValue().endsWith("/callback")) {
            return httpResponse;
        } else {
            return notFoundResponse();
        }
    }

    public static HttpResponse httpResponse = response()
      .withStatusCode(200);
}
```
### Verifying Requests
```
private void verifyPostRequest() {
    new MockServerClient("localhost", 1080).verify(
      request()
        .withMethod("POST")
        .withPath("/validate")
        .withBody(exact("{username: 'foo', password: 'bar'}")),
      VerificationTimes.exactly(1)
    );
}
```

## ClientAndServer

## MockServer UI

