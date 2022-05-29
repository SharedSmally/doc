# Angular CLI

## Document
- [Angular CLI](https://angular.io/cli)

- Install  nodejs and npm
```
$ sudo apt update
$ sudo apt install nodejs npm
```
Update: https://linuxize.com/post/how-to-install-node-js-on-ubuntu-20-04/
```
$ curl -sL https://deb.nodesource.com/setup_14.x | sudo -E bash -
$ sudo apt install nodejs
$ sudo apt install build-essential
$ sudo npm install -g npm 
```
- Install CLI
```
$ sudo npm install -g @angular/cli
``
- Start project
```
$ ng new my-first-project
$ cd my-first-project
$ ng serve
```

## ng commands
- **new(n)**: Creates a new workspace and an initial Angular application.
- **generate(g)**: Generates and/or modifies files based on a schematic.
- **build(b)**: Compiles an Angular app into an output directory named dist/ at the given output path. Must be executed from within a workspace directory.
- **deploy**: Invokes the deploy builder for a specified project or for the default project in the workspace.
- **serve(s)**: Builds and serves your app, rebuilding on file changes.
Additional commands:
- add: Adds support for an external library to your project.
- analytics: Configures the gathering of Angular CLI usage metrics.
- config: Retrieves or sets Angular configuration values in the angular.json file for the workspace.
- doc (d): Opens the official Angular documentation (angular.io) in a browser, and searches for a given keyword.
- e2e (e): Builds and serves an Angular app, then runs end-to-end tests.
- extract-i18n: (i18n-extract, xi18n) Extracts i18n messages from source code.
- help: Lists available commands and their short descriptions.
- lint (l): Runs linting tools on Angular app code in a given project folder.
- run: Runs an Architect target with an optional custom builder configuration defined in your project.
- test (t): Runs unit tests in a project.
- **update **: Updates your application and its dependencies. 
- **version (v)**: Outputs Angular CLI version.

