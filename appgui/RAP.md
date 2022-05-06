# [Eclipse RAP](https://www.eclipse.org/rap/): Remote Application Platform

RAP is the multi-user, client-server based web framework. A RAP application does not own the VM. It runs on a server and shares the VM with the servlet container, other applications, maybe even other RAP applications. There are multiple users accessing an application, each one with a separate UI connected via HTTP, but all sharing the same classes. Moreover, a RAP application runs for a very long time. When a user logs in, the application is already running, and it will continue to run when the user leaves. 
- [RAP Widget Toolkit (RWT)](), implements the same API as the Standard Widget Toolkit (SWT).
  - [RWT](https://download.eclipse.org/rt/rap/doc/3.2/guide/reference/api/org/eclipse/rap/rwt/RWT.html):  
```
static ApplicationContext 	getApplicationContext()
static Client 	getClient()
static java.util.Locale 	getLocale()
static HttpServletRequest 	getRequest()
static ResourceManager 	getResourceManager()
static HttpServletResponse 	getResponse()
static ServiceManager 	getServiceManager()
static SettingStore 	getSettingStore()
static UISession 	getUISession()
static UISession 	getUISession(Display display)
static void 	requestThreadExec(java.lang.Runnable runnable)
static void 	setLocale(java.util.Locale locale)
```
- ApplicationContext: 
```
ResourceManager 	getResourceManager()
ServiceManager 	getServiceManager()

boolean 	addApplicationContextListener(ApplicationContextListener listener)
boolean 	removeApplicationContextListener(ApplicationContextListener listener)

void 	addUIThreadListener(UIThreadListener listener)
void 	removeUIThreadListener(UIThreadListener listener)

java.lang.Object 	getAttribute(java.lang.String name)
void 	removeAttribute(java.lang.String name)
void 	setAttribute(java.lang.String name, java.lang.Object value)
```
- UISession
```
void 	exec(java.lang.Runnable runnable)

ApplicationContext 	getApplicationContext()
Client 	getClient()
Connection 	getConnection()
HttpSession 	getHttpSession()
java.lang.String 	getId()
boolean 	isBound()

java.lang.Object 	getAttribute(java.lang.String name)
java.util.Enumeration<java.lang.String> 	getAttributeNames()
boolean 	removeAttribute(java.lang.String name)
boolean 	setAttribute(java.lang.String name, java.lang.Object value)

boolean 	addUISessionListener(UISessionListener listener)
boolean 	removeUISessionListener(UISessionListener listener)

java.util.Locale 	getLocale()
void 	setLocale(java.util.Locale locale)
```
- Client
```
<T extends ClientService> T 	getService(java.lang.Class<T> type)
```
- ClientService
```
Superinterfaces: java.io.Serializable
Subinterfaces:  BrowserNavigation, ClientFileLoader, ClientFileUploader, ClientInfo, ExitConfirmation, JavaScriptExecutor, JavaScriptLoader, StartupParameters, UrlLauncher
Known Implementing Classes: AbstractEntryPoint 
```
- ResourceManager
```
java.lang.String 	getLocation(java.lang.String name)
java.io.InputStream 	getRegisteredContent(java.lang.String name)
boolean 	isRegistered(java.lang.String name)
void 	register(java.lang.String name, java.io.InputStream inputStream)
boolean 	unregister(java.lang.String name)
```
- ServiceManager
```
java.lang.String 	getServiceHandlerUrl(java.lang.String id)
void 	registerServiceHandler(java.lang.String id, ServiceHandler serviceHandler)
void 	unregisterServiceHandler(java.lang.String id)
```
- SettingStore
