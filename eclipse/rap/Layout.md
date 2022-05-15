# Layout
A layout controls the position and size of children in a Composite. 
Layout classes are subclasses of the abstract class Layout. SWT provides several standard layout classes.
- FillLayout – lays out equal-sized widgets in a single row or column
- RowLayout – lays out widgets in a row or rows, with fill, wrap, and spacing options
- GridLayout – lays out widgets in a grid

![Layout](https://www.eclipse.org/articles/Article-Understanding-Layouts/files/image002.jpg)
```
import org.eclipse.swt.layout.*;

Shell shell = new Shell();
shell.setLayout(new RowLayout());    
```
A layout class may have a corresponding layout data class – a subclass of Object that contains 
layout data for a specific child. By convention, layout data classes are identified by 
substituting Data for Layout in the class name. For example, the standard layout class 
RowLayout has a layout data class called RowData, and the layout class GridLayout uses a 
layout data class called GridData. Layout data classes are set into a widget as follows:
``` 
    Button button = new Button(shell, SWT.PUSH);
    button.setLayoutData(new RowData(50, 40));
```

- [Tutorial](https://www.eclipse.org/articles/Article-Understanding-Layouts/Understanding-Layouts.htm)
- 

## FillLayout
FillLayout lays out widgets in a single row or column, forcing them to be the same size. 
Initially, the widgets will all be as tall as the tallest widget, and as wide as the widest. 
FillLayout does not wrap, and you cannot specify margins or spacing. 
You might use it to lay out buttons in a task bar or tool bar, or to stack checkboxes in a Group. 
FillLayout can also be used when a Composite only has one child. For example, if a Shell has 
a single Group child, FillLayout will cause the Group to completely fill the Shell.
![fillLayout.type = SWT.HORIZONTAL](https://www.eclipse.org/articles/Article-Understanding-Layouts/files/image008.jpg)
![fillLayout.type = SWT.VERTICAL](https://www.eclipse.org/articles/Article-Understanding-Layouts/files/image012.jpg)
```
   FillLayout fillLayout = new FillLayout();
   fillLayout.type = SWT.VERTICAL;
   shell.setLayout(fillLayout);
```
In a FillLayout, children are always the same size, and they fill all available space.

## RowLayout
RowLayout provides configurable margins and spacing for wrap. The height and width of each widget in a RowLayout can be 
specified by setting a RowData object into the widget using setLayoutData.

- Wrap: controls whether or not the RowLayout will wrap widgets into the next row if there isn’t enough space in the current row. RowLayouts wrap by default.
- Pack: If true, widgets in a RowLayout will take their natural size, and they will be aligned as far to the left as possible. 
        If false, widgets will fill the available space, similar to the widgets in a FillLayout. RowLayouts pack by default.
- Justify: If the justify field is true, widgets in a RowLayout are spread across the available space from left to right. 
        If the parent Composite grows wider, the extra space is distributed evenly among the widgets. 
        If both pack and justify are true, widgets take their natural size, and the extra space is placed between 
        the widgets in order to keep them fully justified. By default, RowLayouts do not justify.
- MarginLeft, MarginTop, MarginRight, MarginBottom and Spacing:
     These fields control the number of pixels between widgets (spacing) and the number of pixels between a widget 
     and the side of the parent Composite (margin). By default, RowLayouts leave 3 pixels for margin and spacing. 
     The margin and spacing fields are shown in the following diagram.
![RowLayout](https://www.eclipse.org/articles/Article-Understanding-Layouts/files/image016.jpg)
```
    RowLayout rowLayout = new RowLayout();
    rowLayout.wrap = false;
    rowLayout.pack = false;
    rowLayout.justify = true;
    rowLayout.marginLeft = 5;
    rowLayout.marginTop = 5;
    rowLayout.marginRight = 5;
    rowLayout.marginBottom = 5;
    rowLayout.spacing = 0;
    shell.setLayout(rowLayout);
```
Each widget controlled by a RowLayout can have its initial width and height specified by setting a RowData object into the widget. 
```
       Shell shell = new Shell(display);
       shell.setLayout(new RowLayout());
       Button button1 = new Button(shell, SWT.PUSH);
       button1.setText("Button 1");
       button1.setLayoutData(new RowData(50, 40));
       Button button2 = new Button(shell, SWT.PUSH);
       button2.setText("Button 2");
       button2.setLayoutData(new RowData(50, 30));
       Button button3 = new Button(shell, SWT.PUSH);
       button3.setText("Button 3");
       button3.setLayoutData(new RowData(50, 20));
       shell.pack();
       shell.open();
```

## GridLayout
With a GridLayout, the widget children of a Composite are laid out in a grid. GridLayout has a number of configuration fields, 
ande widgets it lays out can have an associated layout data object, called GridData. 
- NumColumns: Widgets are laid out in columns from left to right, and a new row is created when numColumns + 1 widgets are added to the Composite. The default is to have only 1 column. 
- MakeColumnsEqualWidth: forces the columns to be the same width. The default is false.
- MarginWidth, MarginHeight, HorizontalSpacing, and VerticalSpacing: margins and spaces
![Grid Layout](https://www.eclipse.org/articles/Article-Understanding-Layouts/files/image041.jpg)

### GridData 
GridData is the layout data object associated with GridLayout. To set a GridData object into a widget, you use the setLayoutData method.
```
       Button button1 = new Button(shell, SWT.PUSH);
       button1.setText("B1");
       GridData gridData = new GridData();
       gridData.horizontalAlignment = GridData.FILL;
       gridData.grabExcessHorizontalSpace = true;
       button1.setLayoutData(gridData);
```
- HorizontalAlignment and VerticalAlignment: specify where to place a widget horizontally and/or vertically within its grid cell.
    - BEGINNING
    - CENTER
    - END
    - FILL
- HorizontalIndent: allows you to move a widget to the right by a specified number of pixels. only useful when the horizontalAlignment is BEGINNING
- HorizontalSpan and VerticalSpan: The span fields let widgets occupy more than one grid cell.
- GrabExcessHorizontalSpace and GrabExcessVerticalSpace: typically used for larger widgets such as Texts or Lists to allow them to grow if their containing Composite grows. 
The widget that is grabbing excess space is also the first one to shrink when the Shell gets smaller in the context of resizing.
- WidthHint and HeightHint: indicate the number of pixels wide or tall that you would like a widget to be, if it does not conflict with other requirements in the GridLayout.

## Layouts Work
Layout is the abstract superclass of all layouts:
```
public abstract class Layout {
    protected abstract Point computeSize(Composite composite, int widthHint, int heightHint, boolean flushCache);
    protected abstract void layout(Composite composite, boolean flushCache);
}
```
