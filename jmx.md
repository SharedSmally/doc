#JMX

##JMX Client:

### javax.management.remote.JMXServiceURL 
  
  - [API](https://docs.oracle.com/javase/7/docs/api/javax/management/remote/JMXServiceURL.html)
  
  - [Sample](https://stackoverflow.com/questions/2768087/explain-jmx-url): 

  - JMXServiceURL url = new JMXServiceURL("service:jmx:rmi:///jndi/rmi://:9999/jmxrmi");

```
service:jmx:rmi://<TARGET_MACHINE>:<JMX_RMI_SERVER_PORT>/jndi/rmi://<TARGET_MACHINE>:<RMI_REGISTRY_PORT>/jmxrmi
```


