# Eclipse Resource API
- [Using the Eclipse resource API - Tutorial](https://www.vogella.com/tutorials/EclipseResources/article.html)
- [Eclipse Plugin Track Resource Changes Tutorial](https://www.wideskills.com/eclipse-plugin-tutorial/eclipse-plugin-track-resource-changes-tutorial)

The Eclipse resource API allows to access, create, delete and update resources like files and folders. 
It also allows to register for resource changes.

## Resource API

The Eclipse resource model provides API to access and modify files (resources).
```
IWorkspace workspace = ResourcesPlugin.getWorkspace();
IWorkspaceRoot root = workspace.getRoot();
IProject project = root.getProject("performancetest");
try {
    project.create(new NullProgressMonitor());
    project.open(null);
    } catch (CoreException e) {
    // nothing to do
}
```
- PlatformUI
- Workspace
    - IWorkspaceRoot 
        - IProject 
            -  IFolder
                - IFile

## Resource change notification
You can register to resource changes via a resource change listener. Listeners are informed what resources are 
changed and how they changed. The object passed to a resource change listener is an instance of IResourceChangeEvent.

