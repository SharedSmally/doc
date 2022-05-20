# JFace
- ListViewers
    - TableViewer
    - TreeViewer
- Dialogs
- Text editor framework

JFace list viewers, such as TableViewer and TreeViewer, can use the business objects directly. The trick is to provide adapters 
for things such as retrieving an item's name/label OR for retrieving an Tree parent's children (tree widget)

## List Viewers
- Label Providers: 
maps an element of the viewer's model to an optional image and optional text string used to display the element in the viewer's control.
    - ILabelProvider:  getImage and getText
    - ITableLabelProvider:  getColumnImage and getColumnText.

- Content Providers
The adapter type used used to feed the actual content to the viewer.
    - IStructuredContentProvider 
    - ITreeContentProvider

- Viewer Sorters
The adapter called by viewer before the elements/contents are displayed to the user. 

- Viewer Filters Providers
The adaptoer used to filter out some of the elements from original list of elements provided by the content provider. 

## JFace Dialogs
![Jface dialogs](https://www.wideskills.com/sites/default/files/subjects/Eclipse%20Plugin/Images/06/Jface_Dialogs.jpg)

| Subclass | Description| 
|----------|------------|
| IconAndMessageDialog| superclass of dialogs with an icon and a message.| 
| SelectionDialog| 	superclass for displaying a selection| 
| StatusDialog| superclass for dialogs with status bar| 
| TitleAreaDialog| dialog having a title area.| 
| ErrorDialog| A dialog to display errors| 
| MessageDialog| dialog class for showing messages to the user.| 
| ListDialog| A dialog which prompts for one element out of a list.| 
| ProgressMonitorDialog| A modal dialog to display progress of a operation.| 
| WizardDialog| A dialog to show a wizard to the end user.| 
| InputDialog| A simple input dialog for getting an input from the user.| 

## FieldEditorPreferencePage
FieldEditorPreferencePage is a special abstract preference page to host field editors.
A field editor can be thought of as an item which is used to show the user with the value of a preference. FieldEditor is mostly used together with a FieldEditorPreferencePage,
![FieldEditor](https://www.wideskills.com/sites/default/files/subjects/Eclipse%20Plugin/Images/09/Eclipse_Ready_to_use_Field_Editors.jpg)
