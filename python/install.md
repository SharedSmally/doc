# Install python 3
```
$ python --version
Python 2.7.18
$ sudo apt-get install python3.8 python3.8-dev python3.8-distutils python3.8-venv
$ python3.8 -m venv dev3.8/
$ source dev3.8/bin/activate
$ which python
$HOME/dev3.8/bin/python
$ python --version
Python 3.8.5
$ pip3 install numpy
$ pip3 install wxpython
$ pip3 install matplot
$ pip3 install pgopengl
```
Install eclipse with pydev


## Editors
- Grid Editor
    - wx.grid.GridCellAutoWrapStringEditor  (multi-line text control)
    - wx.grid.GridCellBooleanEditor:  An editor for Boolean cell data
    - wx.grid.GridCellChoiceEditor: An editor for a specific list of options. 
    - wx.grid.GridCellEnumEditor: Derives from wx.grid.GridCellChoiceEditor and manages equating the numeric data value to the string presented to the user.
    - wx.grid.GridCellFloatEditor: for floating point numbers with a specific precision. 
    - wx.grid.GridCellNumberEditor: for entering integer numbers. 
    - wx.grid.GridCellTextEditor:  The default editor for entering string data.
- Rich Text Editor:[RichTextCtrl](https://wxpython.org/Phoenix/docs/html/wx.richtext.RichTextCtrl.html)
- STC Styled Editor:[wxStyledTextCtrl](https://wxpython.org/Phoenix/docs/html/wx.stc.StyledTextCtrl.html#phoenix-title-wx-stc-styledtextctrl) and [API](https://wxpython.org/Phoenix/docs/html/wx.stc.StyledTextCtrl.html)
- [Customized Editor](https://www.pythonstudio.us/wxpython/creating-a-custom-editor.html)
