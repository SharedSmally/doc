# Eclipse THEIA: https://theia-ide.org/
Eclipse THEIA is an Open, Flexible and Extensible Cloud & Desktop IDE Platform.

Theia is designed to work as a native desktop application as well as in the context of a browser and a remote server. To support both situations with a single source, Theia runs in two separate processes. Those processes are called frontend and backend respectively, and they communicate through JSON-RPC messages over WebSockets or REST APIs over HTTP. In the case of Electron, the backend, as well as the frontend, run locally, while in a remote context the backend would run on a remote host.

Both the frontend and backend processes have their dependency injection (DI) container (see below) to which extensions can contribute.

## Tutorial
- [Architecture](https://theia-ide.org/docs/architecture/)
- [Eclipse Theia Applications - Docker & Electron](https://github.com/theia-ide/theia-apps)

## Launch Theia:
- [How to launch](https://eclipsesource.com/de/blogs/2019/09/25/how-to-launch-eclipse-theia/)
    - Download and launch the Theia Blueprint: chmod u+x TheiaBlueprint.AppImage; ./TheiaBlueprint.AppImage
    - Launch it from a package.json (plain and simple)
    - Use the preconfigured docker image (‚cause container are great)
    - Clone, build and run from the sources (for contributors)
    - Use Eclipse Che (to host runtimes and workspaces)
    - Use Gitpod
    - Try online in an example tool based on Eclipse Theia
