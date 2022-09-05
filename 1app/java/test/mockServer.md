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
MockServerClient API is used for providing a capability to connect to the MockServer. It models requests and the corresponding responses from the server

## ClientAndServer

## MockServer UI

