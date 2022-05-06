# Java GUI
- SWT: Eclipse standard Widget Tools, based on JNI using native OS widgets, need native dll
- JFace: based on SWT to provide MVC features (Viewer wraps Control and Data)
- [WindowBuilder](https://help.eclipse.org/latest/index.jsp?topic=%2Forg.eclipse.wb.doc.user%2Fhtml%2Findex.html): Eclipse Plugin
- AWT/Swing/JavaFX: Widget from scratch

# [Eclipse RCP](https://wiki.eclipse.org/Rich_Client_Platform): Rich Client Platform

# [Eclipse RAP](https://www.eclipse.org/rap/): Remote Application Platform, the multi-user, client-server based web framework 

A RAP application does not own the VM. It runs on a server and shares the VM with the servlet container, other applications, maybe even other RAP applications. There are multiple users accessing an application, each one with a separate UI connected via HTTP, but all sharing the same classes. Moreover, a RAP application runs for a very long time. When a user logs in, the application is already running, and it will continue to run when the user leaves. 
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
- UISession
