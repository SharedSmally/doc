# Eclipse

## Workbench
The term Workbench refers to the desktop development environment. 
The Workbench aims to achieve seamless tool integration and controlled openness by providing a common 
paradigm for the creation, management, and navigation of workspace resources.

Each Workbench window contains one or more perspectives. Perspectives contain views and editors and control what 
appears in certain menus and tool bars. More than one Workbench window can exist on the desktop at any given time.

## Feature
An Eclipse based product is structured as a collection of plug-ins. Each plug-in contains the code that provides some of the product's functionality. 
The code and other files for a plug-in are installed on the local computer, and get activated automatically as required. A product's plug-ins are 
grouped together into features. A feature is a unit of separately downloadable and installable functionality.

## Resources
Resources is a collective term for the projects, folders, and files that exist in the Workbench. 
The navigation views provide a hierarchical view of resources and allows you to open them for editing. 
Other tools may display and handle these resources differently.

There are three basic types of resources that exist in the Workbench:
- Files: Comparable to files as you see them in the file system.
- Folders: Comparable to directories on a file system. In the Workbench, folders are contained in projects or other folders. Folders can contain files and other folders.
- Projects:  Contain folders and files. Projects are used for builds, version management, sharing, and resource organization. Like folders, projects map to directories in the file system. (When you create a project, you specify a location for it in the file system.)
A project is either open or closed. When a project is closed, it cannot be changed in the Workbench. The resources of a closed project will not appear in the Workbench, but the resources still reside on the local file system. Closed projects require less memory. Since they are not examined during builds, closing a project can improve build time.
When a project is open, the structure of the project can be changed and you will see the contents.

Folders and files can be linked to locations in the file system outside of the project's location. These special folders and files are called linked resources.

## Perspectives
Each Workbench window contains one or more perspectives. A perspective defines the initial set and layout of views in the Workbench window. 
Within the window, each perspective shares the same set of editors. Each perspective provides a set of functionality aimed at accomplishing 
a specific type of task or works with specific types of resources. 

Perspectives control what appears in certain menus and toolbars. They define visible action sets, which you can change to customize a perspective. 
You can save a perspective that you build in this manner, making your own custom perspective that you can open again later.

## Editors (Edit resource)
Most perspectives in the Workbench are comprised of an editor area and one or more views. You can associate different editors with different types of files. 

Any number of editors can be open at once, but only one can be active at a time. The main menu bar and toolbar for the Workbench window contain 
operations that are applicable to the active editor.

## Views (View resources only)
Views support editors and provide alternative presentations as well as ways to navigate the information in your Workbench. 

Views also have their own menus. To open the menu for a view, click the icon at the left end of the view's title bar. 
Some views also have their own toolbars. The actions represented by buttons on view toolbars only affect the items within that view.

A view might appear by itself, or stacked with other views in a tabbed notebook. You can change the layout of a perspective 
by opening and closing views and by docking them in different positions in the Workbench window.
