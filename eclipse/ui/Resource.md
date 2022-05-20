
# Resources

## RCP resource:
In an Eclipse plugin (including RCP code) you should use the FileLocator class to find resources within the plugin.
You open a resource as a stream:
```
Bundle bundle = ... plugin bundle
IPath path = new Path("path relative to plugin root");
InputStream is = FileLocator.openStream(bundle, path, true);
```

You can also use FileLocator.find:
```
URL url = FileLocator.find(bundle, path, null);
URL fileUrl = FileLocator.toFileURL(url);
```
Don't forget to include your resources directory in the build.properties.
If your image is not in the plugin you can't really use relative paths.

In an e4 plugin you can inject the Bundle using @OSGiBundle:
```
@Inject
@OSGiBundle
Bundle bundle;
```
(@OSGiBundle requires a dependency on the org.eclipse.e4.core.di.extensions plugin).

