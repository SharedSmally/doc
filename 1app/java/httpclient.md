# httpClient
Added after java 11.
- [httpclient](https://www.baeldung.com/java-9-http-client)
- [Multipart Upload](https://www.baeldung.com/httpclient-multipart-upload)
- [Multipart](https://www.springcloud.io/post/2022-04/httpclient-multipart/#gsc.tab=0)


HTTP Client packages:
- java 11 HttpClient: http and http2; sync and async; with apache http mime for multipart supporting
- Apache HTTP Client
- OK Http Client

## Java Http client
- HttpClient class, java.net.http.HttpClient
- HttpRequest class, java.net.http.HttpRequest
- HttpResponse<T> interface, java.net.http.HttpResponse
- WebSocket interface, java.net.http.WebSocket

### Multipart
```
public class MultipartRequest {
    public static void main(String[] args) throws Exception {
        // Create a Multipart request body with MultipartEntityBuilder.
                HttpEntity httpEntity = MultipartEntityBuilder.create()
                // FORM
                .addPart("name", new StringBody("<Spring Cloud>", ContentType.create("application/x-www-form-urlencoded", StandardCharsets.UTF_8)))
                // JSON
                .addPart("info", new StringBody("{\"site\": \"https://www.springcloud.io\"}", ContentType.APPLICATION_JSON))
                // FILE
                .addBinaryBody("logo", new File("C:\\Users\\KevinBlandy\\Desktop\\logo.png"), ContentType.IMAGE_PNG,"logo.png")
                .build();
        /**
        * Use pipeline streams to write the encoded data directly to the network instead of caching it in memory. 
        * Because Multipart request bodies contain files, they can cause memory overflows if cached in memory.
        */
        Pipe pipe = Pipe.open();

        // Pipeline streams must be used in a multi-threaded environment. Using one
        // thread for simultaneous reads and writes can lead to deadlocks.
        new Thread(() -> {
            try (OutputStream outputStream = Channels.newOutputStream(pipe.sink())) {
                // Write the encoded data to the pipeline.
                httpEntity.writeTo(outputStream);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();

        HttpClient httpClient = HttpClient.newHttpClient();

        HttpRequest request = HttpRequest.newBuilder(new URI("http://localhost/upload"))
                // The Content-Type header is important, don't forget to set it.
                .header("Content-Type", httpEntity.getContentType().getValue())
                // Reads data from a pipeline stream.
                .POST(BodyPublishers.ofInputStream(() -> Channels.newInputStream(pipe.source()))).build();

        HttpResponse<String> responseBody = httpClient.send(request, BodyHandlers.ofString(StandardCharsets.UTF_8));

        System.out.println(responseBody.body());
    }  
```  
  
### Get Request  
```
  HttpRequest request = HttpRequest.newBuilder()
     .uri(new URI("https://postman-echo.com/get"))
     .version(HttpClient.Version.HTTP_2)
     .headers("key1", "value1", "key2", "value2")
     .header("key1", "value1")
     .header("key2", "value2")  
     .timeout(Duration.of(10, SECONDS))  
     .GET()
     .build();  
```

#### Request Body
BodyPublisher with the implmenting for the request body:
- StringProcessor – reads body from a String, created with HttpRequest.BodyPublishers.ofString
- InputStreamProcessor – reads body from an InputStream, created with HttpRequest.BodyPublishers.ofInputStream
- ByteArrayProcessor – reads body from a byte array, created with HttpRequest.BodyPublishers.ofByteArray
- FileProcessor – reads body from a file at the given path, created with HttpRequest.BodyPublishers.ofFile
```
HttpRequest request = HttpRequest.newBuilder()
  .uri(new URI("https://postman-echo.com/post"))
  .headers("Content-Type", "text/plain;charset=UTF-8")
  .POST(HttpRequest.BodyPublishers.ofString("Sample request body"))
  .build();

byte[] sampleData = "Sample request body".getBytes();
HttpRequest request = HttpRequest.newBuilder()
  .uri(new URI("https://postman-echo.com/post"))
  .headers("Content-Type", "text/plain;charset=UTF-8")
  .POST(HttpRequest.BodyPublishers
   .ofInputStream(() -> new ByteArrayInputStream(sampleData)))
  .build();

byte[] sampleData = "Sample request body".getBytes();
HttpRequest request = HttpRequest.newBuilder()
  .uri(new URI("https://postman-echo.com/post"))
  .headers("Content-Type", "text/plain;charset=UTF-8")
  .POST(HttpRequest.BodyPublishers.ofByteArray(sampleData))
  .build();
  
HttpRequest request = HttpRequest.newBuilder()
  .uri(new URI("https://postman-echo.com/post"))
  .headers("Content-Type", "text/plain;charset=UTF-8")
  .POST(HttpRequest.BodyPublishers.fromFile(Paths.get("src/test/resources/sample.txt")))  
  .followRedirects(HttpClient.Redirect.ALWAYS)
  .proxy(ProxySelector.getDefault())
  .build();  
```

### HttpClient
All requests are sent using HttpClient by HttpClient.newBuilder() method or by calling HttpClient.newHttpClient().  

##### Handling Response Body
methods dedicated to creating handlers for common body types:
- BodyHandlers.ofByteArray
- BodyHandlers.ofString
- BodyHandlers.ofFile
- BodyHandlers.discarding
- BodyHandlers.replacing
- BodyHandlers.ofLines
- BodyHandlers.fromLineSubscriber  

New HttpClient provides two possibilities for sending a request to a server:
- send(…) – synchronously (blocks until the response comes)
- sendAsync(…) – asynchronously (doesn't wait for the response, non-blocking)
  
```
HttpResponse<String> response = client.send(request, BodyHandlers.ofString());
  
HttpResponse<String> response = HttpClient
  .newBuilder()
  .proxy(ProxySelector.getDefault())
  .build()
  .send(request, BodyHandlers.ofString());

  
HttpResponse<String> response = HttpClient.newBuilder()
  .followRedirects(HttpClient.Redirect.ALWAYS)
  .build()
  .send(request, BodyHandlers.ofString());
  
HttpResponse<String> response = HttpClient.newBuilder()
  .authenticator(new Authenticator() {
    @Override
    protected PasswordAuthentication getPasswordAuthentication() {
      return new PasswordAuthentication(
        "username", "password".toCharArray());
    }
}).build()
  .send(request, BodyHandlers.ofString());  

  HttpHeaders responseHeaders = response.headers();

CompletableFuture<HttpResponse<String>> response = HttpClient.newBuilder()
  .build()
  .sendAsync(request, HttpResponse.BodyHandlers.ofString());  
  
List<URI> targets = Arrays.asList(
  new URI("https://postman-echo.com/get?foo1=bar1"),
  new URI("https://postman-echo.com/get?foo2=bar2"));
HttpClient client = HttpClient.newHttpClient();
List<CompletableFuture<String>> futures = targets.stream()
  .map(target -> client
    .sendAsync(
      HttpRequest.newBuilder(target).GET().build(),
      HttpResponse.BodyHandlers.ofString())
    .thenApply(response -> response.body()))
  .collect(Collectors.toList());
  
ExecutorService executorService = Executors.newFixedThreadPool(2);

CompletableFuture<HttpResponse<String>> response1 = HttpClient.newBuilder()
  .executor(executorService)
  .build()
  .sendAsync(request, HttpResponse.BodyHandlers.ofString());

CompletableFuture<HttpResponse<String>> response2 = HttpClient.newBuilder()
  .executor(executorService)
  .build()
  .sendAsync(request, HttpResponse.BodyHandlers.ofString());  
```

```
  HttpClient.newBuilder()
  .cookieHandler(new CookieManager(null, CookiePolicy.ACCEPT_NONE))
  .build();
```
### Multipart Body  
```
File file = new File(textFileName);
HttpPost post = new HttpPost("http://echo.200please.com");
FileBody fileBody = new FileBody(file, ContentType.DEFAULT_BINARY);
StringBody stringBody1 = new StringBody("Message 1", ContentType.MULTIPART_FORM_DATA);
StringBody stringBody2 = new StringBody("Message 2", ContentType.MULTIPART_FORM_DATA);
// 
MultipartEntityBuilder builder = MultipartEntityBuilder.create();
builder.setMode(HttpMultipartMode.BROWSER_COMPATIBLE);
builder.addPart("upfile", fileBody);
builder.addPart("text1", stringBody1);
builder.addPart("text2", stringBody2);
HttpEntity entity = builder.build();
//
post.setEntity(entity);
HttpResponse response = client.execute(post);  
```
  
