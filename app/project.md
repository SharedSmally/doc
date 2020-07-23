# Java/C++ project

multiple modules:

project metadata/:
   module/: Java classes
   svc/: Java Service: com.jpw.xxx.svc, implement the Interfaces
      Manageable:
         Updateable:
            configurations: read-only; read-writable
         Resetable:
            counts/gauges: increment/decrement values
            metrics: counts/gauges with statistics info
      Has ServiceContext, whose root is AppContext

app/: Java Applications: com.jpw.xxx.app
      CommandLineArgs besides of svc, 
      No ServiceContext
      Has AppContext
      
dao/: Data object for database: com.jpw.xxx.dao: xxx.dao.jar
entdata/: enterprise data record(external record): com.jpw.xxx.entdata: xxx.entdata.jar
protocol/: message definition (internal message): com.jpw.xxx.protocol: xxx.api.jar
           and interfaces
dashboard/:  web-UI:    xxx.dashboard.jar

 -->
