# Eclipse RCP
IoC for OSGi and Application; based on EMF for MVC.
- https://www.vogella.com/tutorials/EclipseRCP/article.html

E4RCP Architecture
![Architecture](https://wiki.eclipse.org/images/thumb/8/80/Eclipse_4_Architecture.png/640px-Eclipse_4_Architecture.png)

E4RCP Context
![Context](https://www.vogella.com/tutorials/EclipseRCP/img/contexthierarchy_withosgi12.png)

The  model elements implement the MContext interface:
- MApplication
- MWindow
- MPerspective
- MPart
- MPopupMenu
```
 @Inject MPart part;   // IoC Inject to access the context element
 
 final IEclipseContext context = EclipseContextFactory.create();
 
 EclipseContextOSGi osgiContext = EclipseContextFactory.getServiceContext(BundleContext);
```
