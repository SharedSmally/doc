# Eclipe SWT
 
## SWT Application
```
import org.eclipse.swt.*;
import org.eclipse.swt.graphics.*;
import org.eclipse.swt.widgets.*;

public class FirstExample {
    public static void main(String[] args){
        Display firstDisplay = new Display();
        Shell firstShell = new Shell(firstDisplay);
        firstShell.setText("First Example");
        firstShell.setSize(200,100);
         firstShell.open ();
         while (!firstShell.isDisposed()) {
             if (!firstDisplay.readAndDispatch())
                 firstDisplay.sleep ();
         }
         firstDisplay.dispose ();
     }
}
```
Components:
- Widgets
- Layout
- Resources: Font, Image, Color
- Transfer: Drag and Drop
- Data Binding
- Dialogs

## SWT Dialogs
![dialogs](https://www.wideskills.com/sites/default/files/subjects/Eclipse%20Plugin/Images/06/SWT_Dialogs.jpg)

| Subclass| Description| 
|---------|------------| 
| ColorDialog| Dialog for selecting a color| 
| DirectoryDialog| Dialog for selecting a directory in host file system| 
| FileDialog| Dialog for selecting a file in host file system. Supported styles are SWT.OPEN and SWT.SAVE| 
| FontDialog| Dialog for selecting text font| 
| MessageBox| Dialog for displaying a message. |
|PrintDialog|Dialog for selecting printer and for printer settings|


## org.eclipse.swt.widgets 
- [Hierarchy For All Packages](https://download.eclipse.org/rt/rap/doc/2.2/guide/reference/api/overview-tree.html)
- [Hierarchy For Package org.eclipse.swt.widgets](https://download.eclipse.org/rt/rap/doc/2.2/guide/reference/api/org/eclipse/swt/widgets/package-tree.html)
- org.eclipse.rap.rwt.RWT
- org.eclipse.rap.rwt.RWT.NLS
- org.eclipse.swt.SWT

### Display
- Device
    - Display

### Dialog
- Dialog
    - ColorDialog
    - FontDialog
    - MessageBox
- org.eclipse.rap.rwt.widgets.DialogUtil

### Listener
- Listener
    - TypedListener
- Event
    
### Layout
- Layout
    - FillLayout
    - FormLayout
    - GridLayout
    - RowLayout
    - StackLayout

### Widget
- Widget
    - Control
    - Item
    - Menu
    - ScrollBar
    - TaskBar
    - ToolTip
    - Tray
    
### Control
- Widget
    - Control
        - Button
        - Label
        - Link
        - ProgressBar
        - Sash
        - Scale
        - Scrollable
            - Composite
                - Canvas
                    - Decorations
                       - Shell
                - Combo
                - CoolBar
                - DateTime
                - ExpandBar
                - Group
                - Spinner
                - TabFolder
                - Table
                - ToolBar
                - Tree
            - List
            - Text
        - Slider
    
### Item
- Widget
    - Item
        - CoolItem
        - ExpandItem
        - MenuItem
        - TabItem
        - TableColumn
        - TableItem
        - TaskItem
        - ToolItem
        - TrayItem
        - TreeColumn
        - TreeItem

### Resource 
- org.eclipse.swt.graphics.Resource
   - Color
   - Cursor
   - Font
   - GC
   - Image
   - Path

### Transfer
- org.eclipse.swt.dnd.Transfer
    - ByteArrayTransfer
        - FileTransfer
        - HTMLTransfer
        - ImageTransfer
        - RTFTransfer
        - TextTransfer
        - URLTransfer
- org.eclipse.swt.dnd.TransferData


### Client Service: org.eclipse.rap.rwt.client.service 
- BrowserNavigation: provides methods to access a web browser's history for navigating within the application.
- BrowserNavigationListener 	An event handler that is invoked whenever the user navigates within the application, i.e.
- ClientInfo: provides basic information about the client device.
- ClientService: 	The generic interface for RWT client services.
- ExitConfirmation: allows applications to show a confirmation dialog before the user leaves the application, e.g.
- JavaScriptExecutor: allows executing JavaScript code on the client.
- JavaScriptLoader: allows loading additional JavaScript files at runtime.
- UrlLauncher: allows loading an URL in an external window, application or save dialog.
