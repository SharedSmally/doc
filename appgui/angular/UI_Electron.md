# Electron
Desktop Application on Angular, NodeJS, and Chrome.

## Tutorial
- Electron: https://www.electronjs.org/

## Setup
- Create electron project
```
mkdir my-electron-app && cd my-electron-app
npm init
npm install --save-dev electron
```
add a start command in the scripts field of package.json config, 
```
  "scripts": {
    "start": "electron ."
  }
```
- Start application
```
npm start
```

## Run the main process
The entry point of any Electron application is its main script. This script controls the main process, which runs in a full Node.js environment and is responsible for controlling your app's lifecycle, displaying native interfaces, performing privileged operations, and managing renderer processes 

