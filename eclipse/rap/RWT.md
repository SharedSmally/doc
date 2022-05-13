# RWT - RAP Widget Toolkit
- [Overview](https://wiki.eclipse.org/RAP/RWT):  org.eclipse.rap.rwt
- [javadoc](https://download.eclipse.org/rt/rap/doc/3.6/guide/reference/api/index.html)
- RWT

| Method | Description |
|--------|-------------|
| static Client 	getClient()| Returns a representation of the client that is connected with the server in the current UI session.| 
| static ApplicationContext 	getApplicationContext() | Returns the ApplicationContext instance that represents the web context's global data storage area.|
| static ResourceManager 	getResourceManager()| Returns the instance of the resource manager for the current application context.| 
| static ServiceManager 	getServiceManager()| Returns the instance of the service manager for the current application context.| 
| static SettingStore 	getSettingStore()| Returns the setting store instance for the current UI session.| 
| static UISession 	getUISession()| Returns the current UI session.| 
| static UISession 	getUISession(Display display)| Returns the UI session that is associated with the given display.| 
| static HttpServletRequest 	getRequest()| Returns the HttpServletRequest that is currently processed.| 
| static HttpServletResponse 	getResponse()| Returns the HttpServletResponse that will be sent to the client after processing the current request.| 
| static void 	requestThreadExec(java.lang.Runnable runnable)| Executes the run method of the given runnable on the request thread.| 
| static java.util.Locale 	getLocale()| Returns the preferred Locale for the current UI session.| 
| static void 	setLocale(java.util.Locale locale)| Sets the preferred Locale for the current UI session.| 

- Client  : WebClient

| Method | Description |
|--------|-------------|
| <T extends ClientService> T 	getService(java.lang.Class<T> type) | Returns this client's implementation of a given service, if available.|

- ClientService
  - All Known Subinterfaces: BrowserNavigation, ClientFileLoader, ClientFileUploader, ClientInfo, ExitConfirmation, JavaScriptExecutor, JavaScriptLoader, StartupParameters, UrlLauncher
  - All Known Implementing Classes: AbstractEntryPoint 
  
- ApplicationContext
  
| Method | Description |
|--------|-------------|
| ResourceManager 	getResourceManager()| Returns the instance of the resource manager for this application context.| 
| ServiceManager 	getServiceManager()| Returns the instance of the service manager for this application context.| 
| boolean 	addApplicationContextListener(ApplicationContextListener listener)| Adds an ApplicationContextListener to this application context.| 
| boolean 	removeApplicationContextListener(ApplicationContextListener listener)| Removes an ApplicationContextListener from this application context.| 
| void 	addUIThreadListener(UIThreadListener listener)| Adds a UIThreadListener to this application context.| 
| void 	removeUIThreadListener(UIThreadListener listener)| Removes a UIThreadListener from this application context.| 
| java.lang.Object 	getAttribute(java.lang.String name)| Returns the value which is stored under the given name in this application context.| 
| void 	removeAttribute(java.lang.String name)| Removes the object which is stored under the given name in this application context.| 
| void 	setAttribute(java.lang.String name, java.lang.Object value)| Stores the given value in this application context, associated with the given name.| 

- ResourceManager
  
| Method | Description |
|--------|-------------|
| java.lang.String 	getLocation(java.lang.String name)| Returns the location within the web-applications context where the resource will be available for download.| 
| java.io.InputStream 	getRegisteredContent(java.lang.String name)| Returns the content of the registered resource with the given name.| 
| boolean 	isRegistered(java.lang.String name)| Determines whether the resource with the given name has been registered.| 
| void 	register(java.lang.String name, java.io.InputStream inputStream)| Registers a given resource and makes it available for download.| 
| boolean 	unregister(java.lang.String name)| Unregisters the resource with the given name.| 
   
- ServiceManager
  
| Method | Description |
|--------|-------------|
| java.lang.String 	getServiceHandlerUrl(java.lang.String id)|Returns the URL to access a service handler.|
|void 	registerServiceHandler(java.lang.String id, ServiceHandler serviceHandler)|Registers a new service handler with the given unique id.|
|void 	unregisterServiceHandler(java.lang.String id)|Unregisters the service handler with the given id.  |
  
- SettingStore : FileSettingStore
  
| Method | Description |
|--------|-------------|
| java.lang.String 	getId()| Returns the unique identifier of this setting store.| 
| void 	loadById(java.lang.String id)| Replaces the contents of this setting store with the persisted contents associated with the given ID.| 
| void 	addSettingStoreListener(SettingStoreListener listener)| Attaches the given listener to this setting store.| 
| void 	removeSettingStoreListener(SettingStoreListener listener)| Removes the given listener from this setting store.| 
| java.lang.String 	getAttribute(java.lang.String name)| Returns the attribute stored under the specified name in this setting store.| 
| java.util.Enumeration<java.lang.String> 	getAttributeNames()| Returns an Enumeration of strings with the names of all attributes in this setting store.| 
| void 	removeAttribute(java.lang.String name)| Removes the attribute stored under the specified name from this setting store.| 
| void 	setAttribute(java.lang.String name, java.lang.String value)| Stores a given attribute in this setting store, using the name specified.| 

- UISession
  
| Method | Description |
|--------|-------------|
| ApplicationContext 	getApplicationContext()| Returns the ApplicationContext this UISession belongs to.| 
| void 	exec(java.lang.Runnable runnable)| Executes the given runnable in the context of this UI session.| 
| Client 	getClient()| Returns a representation of the client that is connected with the server in this UI session.| 
| Connection 	getConnection()| Returns the connection used to communicate with the client that is connected to this UI session.| 
| HttpSession 	getHttpSession()| Returns the underlying HttpSession instance.| 
| java.lang.String 	getId()| Returns a unique identifier for this UI session.| 
| boolean 	isBound()| Returns whether this UI session is bound to the underlying HttpSession or not.|   
| boolean 	addUISessionListener(UISessionListener listener)| Adds a UISessionListener to this UI session.| 
| boolean 	removeUISessionListener(UISessionListener listener)| Removes a UISessionListener from this UI session.| 
| java.lang.Object 	getAttribute(java.lang.String name)| Returns the object bound with the specified name in this UI session, or null if no object is bound under the name.| 
| java.util.Enumeration<java.lang.String> 	getAttributeNames()| Returns an Enumeration of the names of all objects bound to this UI session.| 
| boolean 	removeAttribute(java.lang.String name)| Removes the object bound with the specified name from this UI session.| 
| boolean 	setAttribute(java.lang.String name, java.lang.Object value)| Binds an object to this UI Session, using the name specified.| 
| java.util.Locale 	getLocale()| Returns the preferred Locale for this UI session.| 
| void 	setLocale(java.util.Locale locale)| Sets the preferred Locale for this UI session.| 
  
  
