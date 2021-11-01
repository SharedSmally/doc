# [Spring Framework Integration](https://docs.spring.io/spring-framework/docs/current/reference/html/integration.html)
- REST client
- Remoting
- JMS
- JCA
- JMX
- Jmail
- Tasks
- Scheduling
- Cache

## REST
- [RestTemplate](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/client/RestTemplate.html): The original Spring REST client with a synchronous, template method API.
- [WebClient](): a non-blocking, reactive alternative that supports both synchronous and asynchronous as well as streaming scenarios.

### RestTemplate
#### Initialization: The default uses java.net.HttpURLConnection to perform requests. 
```
RestTemplate template = new RestTemplate(new HttpComponentsClientHttpRequestFactory());
```
It uses [ClientHttpRequestFactory](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/http/client/ClientHttpRequestFactory.html) to create ClientHttpRequest. The Implementations:
```
ClientHttpRequest createRequest(URI uri, HttpMethod httpMethod)
```
-  [BufferingClientHttpRequestFactory](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/http/client/BufferingClientHttpRequestFactory.html)
-  [HttpComponentsAsyncClientHttpRequestFactory](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/http/client/HttpComponentsAsyncClientHttpRequestFactory.html)
-  [HttpComponentsClientHttpRequestFactory](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/http/client/HttpComponentsClientHttpRequestFactory.html)
- [Netty4ClientHttpRequestFactory](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/http/client/Netty4ClientHttpRequestFactory.html)
- [OkHttp3ClientHttpRequestFactory](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/http/client/OkHttp3ClientHttpRequestFactory.html)
- [SimpleClientHttpRequestFactory](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/http/client/SimpleClientHttpRequestFactory.html)
-  InterceptingClientHttpRequestFactory
-  MockMvcClientHttpRequestFactory

#### Common Methods:
| Method group |	Description |
|--------------|--------------|
|getForObject|Retrieves a representation via GET.|
|getForEntity|Retrieves a ResponseEntity (that is, status, headers, and body) by using GET.|
|headForHeaders|Retrieves all headers for a resource by using HEAD.|
|postForLocation|Creates a new resource by using POST and returns the Location header from the response.|
|postForObject|Creates a new resource by using POST and returns the representation from the response.|
|postForEntity|Creates a new resource by using POST and returns the representation from the response.|
|put|Creates or updates a resource by using PUT.|
|patchForObject|Updates a resource by using PATCH and returns the representation from the response. Note that the JDK HttpURLConnection does not support PATCH, but Apache HttpComponents and others do.
|delete|Deletes the resources at the specified URI by using DELETE.|
|optionsForAllow|Retrieves allowed HTTP methods for a resource by using ALLOW.|
|exchange|More generalized (and less opinionated) version of the preceding methods that provides extra flexibility when needed. It accepts a RequestEntity (including HTTP method, URL, headers, and body as input) and returns a ResponseEntity. These methods allow the use of ParameterizedTypeReference instead of Class to specify a response type with generics.|
|execute| The most generalized way to perform a request, with full control over request preparation and response extraction through callback interfaces.|
- Request
```
restTemplate.getForObject("https://example.com/hotel list", String.class);
// Results in request to "https://example.com/hotel%20list"

String result = restTemplate.getForObject("https://example.com/hotels/{hotel}/bookings/{booking}", String.class, "42", "21");

Map<String, String> vars = Collections.singletonMap("hotel", "42");
String result = restTemplate.getForObject("https://example.com/hotels/{hotel}/rooms/{hotel}", String.class, vars);
```
- Headers
```
String uriTemplate = "https://example.com/hotels/{hotel}";
URI uri = UriComponentsBuilder.fromUriString(uriTemplate).build(42);

RequestEntity<Void> requestEntity = RequestEntity.get(uri)
        .header("MyRequestHeader", "MyValue")
        .build();

ResponseEntity<String> response = template.exchange(requestEntity, String.class);

String responseHeader = response.getHeaders().getFirst("MyResponseHeader");
String body = response.getBody();
```

- Body
```
URI location = template.postForLocation("https://example.com/people", person);
Person person = restTemplate.getForObject("https://example.com/people/{id}", Person.class, 42);
```
- Message Converter: JSON view
```
MappingJacksonValue value = new MappingJacksonValue(new User("eric", "7!jd#h23"));
value.setSerializationView(User.WithoutPasswordView.class);

RequestEntity<MappingJacksonValue> requestEntity = RequestEntity.post(new URI("https://example.com/user")).body(value);
ResponseEntity<String> response = template.exchange(requestEntity, String.class);
```
- Multipart
```
MultiValueMap<String, Object> parts = new LinkedMultiValueMap<>();

parts.add("fieldPart", "fieldValue");
parts.add("filePart", new FileSystemResource("...logo.png"));
parts.add("jsonPart", new Person("Jason"));

HttpHeaders headers = new HttpHeaders();
headers.setContentType(MediaType.APPLICATION_XML);
parts.add("xmlPart", new HttpEntity<>(myBean, headers));

template.postForObject("https://example.com/upload", parts, Void.class);
```

## Remoting

## JMS

## JCA

## JMX

## Jmail

## Tasks

## Scheduling

## Cache
