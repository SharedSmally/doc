# Eclipse UI

## PlatformUI

| Method | 	Description| 
|--------|-------------|
| static int 	createAndRunWorkbench(Display display, WorkbenchAdvisor advisor) 	| Creates the workbench and associates it with the given display and workbench advisor, and runs the workbench UI.| 
| static Display 	createDisplay() 	| Creates the Display to be used by the workbench.| 
| static IPreferenceStore 	createPreferenceStore(Class<?> clazz) 	| Creates a IPreferenceStore store for the bundle that loaded that class| 
| static IDialogSettingsProvider 	getDialogSettingsProvider(Bundle bundle) 	| Returns the dialog settings provider for the passed bundle.| 
| static IPreferenceStore 	getPreferenceStore() 	| Returns the preference store used for publicly settable workbench preferences.| 
| static TestableObject 	getTestableObject() 	| Returns the testable object facade, for use by the test harness.| 
| static IWorkbench 	getWorkbench() 	| Returns the workbench.| 
| static boolean 	isWorkbenchRunning() 	| Returns whether createAndRunWorkbench has been called to create the workbench, and the workbench has yet to terminate.| 


## IWorkbench

PlatformUI.getWorkbench(): https://javadoc.scijava.org/Eclipse/org/eclipse/ui/IWorkbench.html

A workbench is the root object for the Eclipse Platform user interface.

A workbench has one or more main windows which present to the end user information based on some underlying model, typically on resources in an underlying workspace. A workbench usually starts with a single open window, and automatically closes when its last window closes.

Each workbench window has a collection of pages; the active page is the one that is being presented to the end user; at most one page is active in a window at a time.

Each workbench page has a collection of workbench parts, of which there are two kinds: views and editors. A page's parts are arranged (tiled or stacked) for presentation on the screen. The arrangement is not fixed; the user can arrange the parts as they see fit. A perspective is a template for a page, capturing a collection of parts and their arrangement. 
