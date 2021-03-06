#JMX

##JMX Client:

### javax.management.remote.JMXServiceURL 
  
  - [API](https://docs.oracle.com/javase/7/docs/api/javax/management/remote/JMXServiceURL.html)
  
  - [Sample](https://stackoverflow.com/questions/2768087/explain-jmx-url): 

  - JMXServiceURL url = new JMXServiceURL("service:jmx:rmi:///jndi/rmi://:9999/jmxrmi");

```
service:jmx:rmi://<TARGET_MACHINE>:<JMX_RMI_SERVER_PORT>/jndi/rmi://<TARGET_MACHINE>:<RMI_REGISTRY_PORT>/jmxrmi
```

Config:
- JMX/RMI doesn't need to open all these ports. You can force them to be same :

```
-Dcom.sun.management.jmxremote 
-Dcom.sun.management.jmxremote.port = 
-Dcom.sun.management.jmxremote.rmi.port = 
-Dcom.sun.management.jmxremote.authenticate=false 
-Dcom.sun.management.jmxremote.ssl=false  
-Dcom.sun.management.jmxremote.local.only
-Djava.rmi.server.hostname=${DOCKER_HOST_IP}
```

Explicitly setting these will stop RMI from picking random ports. Setting them to the same value will make sure it opens less ports to listen on.

The third port is used by the Java Attach API. It is what JConsole uses for connecting to "Local Process".

```
%	java -cp ./  \
	-Dcom.sun.management.jmxremote \
	-Dcom.sun.management.jmxremote.port=9999 \
	-Dcom.sun.management.jmxremote.rmi.port=9999 \
	-Dcom.sun.management.jmxremote.authenticate=false \
	-Dcom.sun.management.jmxremote.ssl=false  \
	com.example.ThreadMonitor
```

Application class name must be the **last one**.


- Enable password
```
% java -Dcom.sun.management.jmxremote.port=3000 \
     -Dcom.sun.management.jmxremote.password.file=password.properties \
     -Dcom.sun.management.jmxremote.access.file=access.properties \
     -Djavax.net.ssl.keyStore=keystore \
     -Djavax.net.ssl.keyStorePassword=password \
     com.example.MyApp
```

- [Enable auth](http://www.journaldev.com/1359/java-jmx-client-example-authentication):


### MBean
The "standard" set of JMX MBeans is Standard MBean, Dynamic MBean, Model MBean, Open MBean, and MXBean(simple Standard MBean). 
 
An MXBean is a type of MBean that references only a predefined set of data types. The MBean is usable by any client, including remote clients, without any requirement that the client have access to model-specific classes representing the types of your MBeans. MXBeans provide a convenient way to bundle related values together, without requiring clients to be specially configured to handle the bundles.

- The issue with Standard MBeans is that all classes defined in the interface must be Serializable and available to the client JVM.  That is, if your MBean interface returns a class named Dog, that class must be available to the remote client JVM (however, the JConsole does not know about Dogs).

- In the same way as for standard MBeans, an MXBean is defined by writing a Java interface called SomethingMXBean and a Java class that implements that interface. However, unlike standard MBeans, MXBeans do not require the Java class to be called Something. Every method in the interface defines either an attribute or an operation in the MXBean. The annotation @MXBean can be also used to annotate the Java interface, instead of requiring the interface's name to be followed by the MXBean suffix.

- See [MXBean returns Customized types implements *MBean](https://stackoverflow.com/questions/14939335/java-mxbean-custom-types)

- ManagementFactory.getPlatformMBeanServer(); is used to access the MBeanServer in the same JVM( One JVM owns one PlatformMBeanServer; not shared by multiple JVM). While JMXConnectorFactory is for accessing remote MBeanServers (i.e. in a different JVM, and/or on a different host).

