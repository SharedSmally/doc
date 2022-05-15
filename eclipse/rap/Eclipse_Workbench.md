# Eclipse Platform
![e4 architecture](https://wiki.eclipse.org/images/thumb/8/80/Eclipse_4_Architecture.png/640px-Eclipse_4_Architecture.png)

## Workbench
The term Workbench refers to the desktop development environment. It aims to achieve seamless tool integration and controlled openness by providing a common paradigm for the creation, management, and navigation of workspace resources.

Each Workbench window contains one or more perspectives. Perspectives contain views and editors and control what appears in certain menus and tool bars. More than one Workbench window can exist on the desktop at any given time.

## Features

On disk, an Eclipse based product is structured as a collection of plug-ins. Each plug-in contains the code that provides some of the product's functionality. The code and other files for a plug-in are installed on the local computer, and get activated automatically as required. A product's plug-ins are grouped together into features. A feature is a unit of separately downloadable and installable functionality.

Large Eclipse based products can organize their features into trees starting from the root feature that represents the entire product. This root feature then includes smaller units of functionality all the way down to leaf features that list one or more plug-ins and fragments. The capability to group features hierarchically allows products to be stacked - a large product can build on top of a smaller one by including it and adding more features.

Some included features may be useful add-ons, but are not vital to the proper functioning of the overall product. Feature providers can elect to mark them as optional. Optional features will only be installed if all their required features and plug-ins are available. If not installed right away, optional features can be added at a later date.

## Perspectives

Each Workbench window contains one or more perspectives. A perspective defines the initial set and layout of views in the Workbench window. Within the window, each perspective shares the same set of editors. Each perspective provides a set of functionality aimed at accomplishing a specific type of task or works with specific types of resources. Can switch perspectives frequently in the Workbench.

Perspectives control what appears in certain menus and toolbars. They define visible action sets, which you can change to customize a perspective. You can save a perspective that you build in this manner, making your own custom perspective that you can open again later.

## Editors

Most perspectives in the Workbench are comprised of an editor area and one or more views.

You can associate different editors with different types of files. For example, when you open a file for editing by double-clicking it in one of the navigation views, the associated editor opens in the Workbench. If there is no associated editor for a resource, the Workbench attempts to launch an external editor outside the Workbench. 

Any number of editors can be open at once, but only one can be active at a time. The main menu bar and toolbar for the Workbench window contain operations that are applicable to the active editor.

Tabs in the editor area indicate the names of resources that are currently open for editing. An asterisk (*) indicates that an editor has unsaved changes.

By default, editors are stacked in the editor area, but you can choose to tile them in order to view source files simultaneously.

## Views

Views support editors and provide alternative presentations as well as ways to navigate the information in your Workbench. For example, the Project Explorer and other navigation views display projects and other resources that you are working with.

Views also have their own menus. To open the menu for a view, click the icon at the left end of the view's title bar. Some views also have their own toolbars. The actions represented by buttons on view toolbars only affect the items within that view.

A view might appear by itself, or stacked with other views in a tabbed notebook. You can change the layout of a perspective by opening and closing views and by docking them in different positions in the Workbench window.

## Resources: Project Explorer view
Resources is a collective term for the projects, folders, and files that exist in the Workbench. The navigation views provide a hierarchical view of resources and allows you to open them for editing. 

There are three basic types of resources that exist in the Workbench:
- Files:    Comparable to files as you see them in the file system.
- Folders:  Comparable to directories on a file system. In the Workbench, folders are contained in projects or other folders. Folders can contain files and other folders.
- Projects: Contain folders and files. Projects are used for builds, version management, sharing, and resource organization. Like folders, projects map to directories in the file system. (When you create a project, you specify a location for it in the file system.)
    
    A project is either open or closed. When a project is closed, it cannot be changed in the Workbench. The resources of a closed project will not appear in the Workbench, but the resources still reside on the local file system. Closed projects require less memory. Since they are not examined during builds, closing a project can improve build time.
    When a project is open, the structure of the project can be changed and you will see the contents.

Folders and files can be linked to locations in the file system outside of the project's location. These special folders and files are called linked resources.



