# [Eclipse RCP](https://wiki.eclipse.org/Rich_Client_Platform) (Rich Client Platform)

## java GUI
- Windows Builder: designer for GUI
- SWT (Standard Widget Toolkits): JNI wrapping the OS widgets, need native dll library, and dispose the resource directly (heavyweight components). When freed a parent resource, its child resources will automatically be disposed of.
- JFace: based on SWT to provide MVC model (Viewer wrapping DataModel and Control)
- AWT/Swing/JavaFX: from scratch, not use OS widgets (lightweight components)
- [Book: SWT-JFace in Action](https://www.manning.com/books/swt-jface-in-action)

## SWT
- [SWT Widgets](https://www.eclipse.org/swt/widgets/)
- [Layout]()
```
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

public class SWTHelloWorld {
 public static void main (String [] args) {
	Display display = new Display ();  // manage GUI resources and communicate with native OS
	Shell shell = new Shell(display);  // primary Window
	
	Text helloWorldTest = new Text(shell, SWT.NONE);
	helloWorldTest.setText("Hello World SWT");
	helloWorldTest.pack(); //size and postion Text component
	
	shell.pack();
	shell.open ();
	while (!shell.isDisposed ()) {
		if (!display.readAndDispatch ()) display.sleep ();
	}
	display.dispose ();
 }
}
```
## JFace
- [Snippets](https://wiki.eclipse.org/JFaceSnippets)
