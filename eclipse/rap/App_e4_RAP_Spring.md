# Eclipse e4 RAP Spring Boot
Eclipse e4 RAP Application:
- With OSGi for multiple Bunndles
- Without OSGi - RWT Standalone Application

## Tutorial
- [Eclipse RAP with Spring Boot](https://www.javacodegeeks.com/2018/11/eclipse-rap-spring-boot.html)
- [example project](https://github.com/bwolff/rwt-on-spring-boot)
- [Eclipse RAP Developer's Guide](https://www.eclipse.org/rap/developers-guide/)
- [RWT Standalone](https://www.eclipse.org/rap/developers-guide/devguide.php?topic=rwt-standalone.html&version=3.20)
- [RWT Application Configuration](https://www.eclipse.org/rap/developers-guide/devguide.php?topic=application-configuration.html&version=3.20)
- Run in Debug: 
*./gradlew bootRoot -Dlogging.level.root=DEBUG*

![RCP vs RAP](http://file.itpub.net/forum/itpub/attachment/day_090706/20090706_62f02d78bd33e0c81efdo3T6I3wMso7j.jpg)

- Code Samples: https://github.com/eclipsesource/tabris-demos/tree/master/com.eclipsesource.tabris.demos
- Eclipse 4 (e4) Tutorial Part 1-7: https://eclipsesource.com/blogs/2012/05/10/eclipse-4-final-sprint-part-1-the-e4-application-model/
- Eclipse 4 (e4) Tutorial Part 2: https://eclipsesource.com/blogs/2012/06/12/eclipse-4-e4-tutorial-part-2/
- Eclipse 4 (e4) FAQ: https://wiki.eclipse.org/Eclipse4/RCP/FAQ

Main
```
public static void main(String[] args) {
   Display display = new Display();
   Shell shell = new Shell(display);
   shell.setLayout(new FillLayout());
   new ExampleView(shell);
   shell.open();
   while( !shell.isDisposed() ) {
      if( ! display.readAndDispatch() ) {
         display.sleep();
      }
   }
}
```
View:
```
public class ExampleView {
   @Inject
   public ExampleView(Composite parent) {
      Label label = new Label(parent, SWT.NONE);
      label.setText("Hello World!");
   }
}
```
Handler:
```
public class MyHandler {
   @Execute
   public static void execute(Shell shell){
      MessageDialog.openInformation(shell, "", "Hello World!");
   }
}
```
For Plugin e4 application with EntryPoint:
```
public class BasicApplication implements ApplicationConfiguration {
    public void configure(Application application) {
        Map<String, String> properties = new HashMap<String, String>();
        properties.put(WebClient.PAGE_TITLE, "My RAP Application");
        Bundle bundle = FrameworkUtil.getBundle(my.package.E4LifeCycle.class);
        String symbolicName = bundle.getSymbolicName();
        String appXmiLocation = "platform:/plugin/" + symbolicName + "/Application.e4xmi";
        String lifeCycleLocation = "bundleclass://" + symbolicName + "/" + my.package.E4LifeCycle.class.getName();
        E4ApplicationConfig applicationConfig = E4ApplicationConfig.create(appXmiLocation, lifeCycleLocation);
        E4EntryPointFactory entryPointFactory = new E4EntryPointFactory(applicationConfig);
        application.addEntryPoint("/myapp", entryPointFactory, properties);
        application.setOperationMode(OperationMode.SWT_COMPATIBILITY);
    }
}
```
![Handle-Command-Item](https://eclipsesource.com/wp-content/uploads/2012/06/image09.png)

## E4Application ->IApplication; create E4Workbench (with created IEclipseContext appctx; MApplication appModel)
Source code:
- RAP : https://github.com/eclipse-rap/org.eclipse.rap and https://github.com/eclipse-rap
- E4: https://git.eclipse.org
- E4book: https://github.com/vogellacompany/eclipse4book
- E4Application.java: https://git.eclipse.org/c/platform/eclipse.platform.ui.git/tree/bundles/org.eclipse.e4.ui.workbench.swt/src/org/eclipse/e4/ui/internal/workbench/swt/E4Application.java

XMI URL: private final static String E4XMI = "platform:/plugin/RAPe4Tutorial/Application.e4xmi"; 
- schema: platform:/  or bundleclass://
- segment: plugin/ or fragment/
- Bundle SymbolicName: in MANIFEST.MF - Bundle-SymbolicName
- filename: Application.e4xmi

## RWT standalone Application embedded in Spring Boot
- Gradle project Sample: https://github.com/bwolff/rwt-on-spring-boot

## RWT standalone Application 
- Create gradle project
