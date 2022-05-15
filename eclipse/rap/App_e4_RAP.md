# RAP e4 on Application Model

## Eclipse IDE Setup
- Eclipse RCP/RAP IDE
- WindowBuilder 
- e4 Tools Developer Resources 
- RAP e4 Tooling 
- RAP Target Components
- RAP e4 Target Components

## Build RAP App
- [RAP App Sample](https://o7planning.org/10183/eclipse-rap-tutorial-for-beginners-workbench-application)

## Create Project: 
- [Tutorial](https://o7planning.org/10183/eclipse-rap-tutorial-for-beginners-workbench-application)
- [e4 tutorial](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwivj-mLpt33AhVHnHIEHZd2B84QFnoECB4QAQ&url=https%3A%2F%2Ftomsondev.files.wordpress.com%2F2010%2F07%2Ftutorial.pdf&usg=AOvVaw0JxTDRD0WsRADGS1Z37TJa)
File/New/Other... >Plugin Project (No for create a rich cleint application) > RAP e4 Application

- list of built-in command of the RAP framework at:

http://help.eclipse.org/mars/topic/org.eclipse.platform.doc.isv/reference/api/org/eclipse/ui/actions/ActionFactory.html


## Run the application
- Run directly
Right click the project and select:
    Run As/RAP Application

- Configure the port and the default browser to run RAP e4 application:
Right-click the RAPe4Tutorial project and select:
    Run As/Run Configurations... to set the port and browser

## Application Model: Application.e4xmi (e4>Model>new Application Model)
- Addons: Objects instantiated by Eclipse 4's dependency injection framework. They are global and are contained under the application.
- Binding Contexts
- Binding Tables
- Handlers: handling for the commands of Menu or Toolbar by clicking MenuItem or ToolItem
- Commands: Associate Handler to Item (MenuItem and ToolbarItem)
- Command Categories: group of commands
- Windows and Dialogs: TrimmedWindow - A Windows with trimmed MenuBar,and StatusBar
    - Handlers
    - Windows and Dialogs
    - Controls: Windows as parent
    - Shared Elements
    - TrimBars
- Part Contributions
- Menu Contributions
- Toolbar Contributions
- Trim Contributions
- Snippets

## Depoly as WAR
- Use an ApplicationConfiguration to bind different entrypoints to different url-patterns.
```
application.addEntryPoint("/start", MyEntryPoint.class, properties);
application.addEntryPoint("/admin", MyAdminEntryPoint.class, properties);
```
-  bind the RapServlet to all used url-patterns in the web.xml
```
<servlet>
    <servlet-name>RAPServlet</servlet-name>
    <servlet-class>org.eclipse.rwt.internal.engine.RWTDelegate</servlet-class>
</servlet>
<servlet-mapping>
    <servlet-name>RAPServlet</servlet-name>
    <url-pattern>/start</url-pattern>
</servlet-mapping>
<servlet-mapping>
    <servlet-name>RAPServlet</servlet-name>
    <url-pattern>/admin</url-pattern>
</servlet-mapping>
```


### [Command and Handler](https://www.vogella.com/tutorials/EclipseCommands/article.html)
