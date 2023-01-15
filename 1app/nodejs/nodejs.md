# NodeJS
- [NodeJS](https://nodejs.org/en/docs/)
- [NodeJS API](https://nodejs.org/api/)

## VisualCode for nodejs

## [npm](https://docs.npmjs.com/about-npm)
- [npm CLI](https://docs.npmjs.com/cli/v9/commands)
- [Tutorial](https://docs.npmjs.com/getting-started)
- npm init
- npm install/install-test/install-ci-test/clean-install/clean-install-test [-g] <module>  [--save/--save-dev]
- npm ls/uninstall/update/test/star/stars/rebuild  # list installed package  
- npm login/logout/publish/unpublish/ping/whoami
- npm start/stop/rn/test

  The global packages are installed in **/usr/lib/node_modules**.

The Node.js project needs to have a **package.json** file, it describes the project manifest that includes the packages and applications it depends on, information about its unique source control, and specific metadata like the project's name, description, and author.

### Dependencies
- dependencies 
- devDepenendcies
```
  "devDependencies": {
    "mocha": "~3.1",
    "native-hello-world": "^1.0.0",
    "sinon": "~1.9"
  },
  "dependencies": {
    "fill-keys": "^1.0.2",
    "resolve": "~1.1.7"
  }  
```  
node app.js
