# CORE Resources

## Resource
```
public interface Resource extends InputStreamSource {
    boolean exists();
    boolean isOpen();
    URL getURL() throws IOException;
    File getFile() throws IOException;
    Resource createRelative(String relativePath) throws IOException;
    String getFilename();
    String getDescription();
}

public interface InputStreamSource {
    InputStream getInputStream() throws IOException;
}
```
Resource is used to access to low-level resources. The Built-in implementations:
- UrlResource: accessible with a URL, such as files(file:), an HTTP target(http:), an FTP target(ftp:), relative in classpath(classpath:), and others
- ClassPathResource
- FileSystemResource
- ServletContextResource
- InputStreamResource
- ByteArrayResource

## ResourceLoader
```
public interface ResourceLoader {
    Resource getResource(String location);
}
```
All application contexts implement the ResourceLoader interface, so it may be used to obtain Resource instances.
- ClassPathXmlApplicationContext returns a ClassPathResource
- FileSystemXmlApplicationContext returns a FileSystemResource
- WebApplicationContext returns a ServletContextResource. 

The strategy for converting String objects to Resource objects:

| Prefix |	Example | 	Explanation |
| :------------- | :----------: | -----------: |
| classpath: | classpath:com/myapp/config.xml | Loaded from the classpath.|
| file: |  file:///data/config.xml | Loaded as a URL from the filesystem.|
| http: | https://myserver/logo.png | Loaded as a URL. |
| (none) | /data/config.xml | Depends on the underlying ApplicationContext.|
