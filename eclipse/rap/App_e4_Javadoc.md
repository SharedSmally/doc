
# RAP - Eclipse Remote Platform
- [RAP Project](https://www.eclipse.org/rap/) 
- [RAP github](https://github.com/eclipse-rap/org.eclipse.rap)
RAP includes:
- Runtime
- Tools

## [Bundles](https://github.com/eclipse-rap/org.eclipse.rap/tree/main/bundles)
- org.eclipse.e4.core.commands
- org.eclipse.e4.ui.bindings
- org.eclipse.e4.ui.workbench.addons.swt
- org.eclipse.e4.ui.workbench.renderers.swt
- org.eclipse.e4.ui.workbench.swt
- org.eclipse.e4.ui.workbench
- org.eclipse.rap.e4
- org.eclipse.rap.filedialog
- org.eclipse.rap.fileupload
- org.eclipse.rap.jface.databinding
- org.eclipse.rap.jface
- org.eclipse.rap.nebula.jface.gridviewer
- org.eclipse.rap.nebula.widgets.grid
- org.eclipse.rap.nebula.widgets.richtext
- org.eclipse.rap.rwt.osgi
- org.eclipse.rap.rwt
- org.eclipse.rap.ui.cheatsheets
- org.eclipse.rap.ui.forms
- org.eclipse.rap.ui.views
- org.eclipse.rap.ui.workbench
- org.eclipse.rap.ui

## Features
- org.eclipse.rap.e4.equinox.target.feature
- org.eclipse.rap.e4.examples.feature
- org.eclipse.rap.e4.feature
- org.eclipse.rap.e4.sdk.feature
- org.eclipse.rap.equinox.target.feature
- org.eclipse.rap.examples.feature
- org.eclipse.rap.feature
- org.eclipse.rap.sdk.feature

# Activator
Inherit from org.osgi.framework.BundleActivator to start/stop the Bundle, using org.eclipse.rap.ui.launch.RAPLauncher to launch RAP application.
```
import org.eclipse.rap.examples.IExampleContribution;
import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;
import org.osgi.framework.ServiceRegistration;

public class Activator implements BundleActivator {
  private static final String EXAMPLE_CONTRIB = IExampleContribution.class.getName();
  private ServiceRegistration<?> registration;

  @Override
  public void start( BundleContext context ) throws Exception {
    NebulaRichTextExampleContribution contribution = new NebulaRichTextExampleContribution();
    registration = context.registerService( EXAMPLE_CONTRIB, contribution, null );
  }

  @Override
  public void stop( BundleContext context ) throws Exception {
    registration.unregister();
  }
}
```

## Javadoc
-[e4 ui](https://git.eclipse.org/r/plugins/gitiles/platform/eclipse.platform.ui/+/2de72ce08f2ab9eabdcf22b39cd4c7d5149d898f/bundles/org.eclipse.e4.ui.workbench/src/org/eclipse/e4/ui?autodive=0/)
    - [WorkBench](https://git.eclipse.org/r/plugins/gitiles/platform/eclipse.platform.ui/+/2de72ce08f2ab9eabdcf22b39cd4c7d5149d898f/bundles/org.eclipse.e4.ui.workbench/src/org/eclipse/e4/ui/internal/workbench?autodive=0%2F%2F)
    - E4WorkBench/IWorkBench
    - E4XMIResourceFactory/E4XMIResource
