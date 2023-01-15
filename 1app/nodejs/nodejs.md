# NodeJS
- [NodeJS](https://nodejs.org/en/docs/)
- [NodeJS API](https://nodejs.org/api/)
- [nodejs](https://www.tutorialspoint.com/nodejs/index.htm)

## VisualCode for nodejs

## [npm](https://docs.npmjs.com/about-npm)
- [npm CLI](https://docs.npmjs.com/cli/v9/commands)
- [Tutorial](https://docs.npmjs.com/getting-started)
- npm init
- npm install/install-test/install-ci-test/clean-install/clean-install-test [-g] <module>  [--save/--save-dev]
- npm ls/uninstall/update/search  # list installed package  
- npm login/logout/publish/unpublish/ping/whoami/adduser
- npm start/stop/test/star/stars/rebuild
- npm run <script-name>   # script name in package.json
  
  The global packages are installed in **/usr/lib/node_modules**.

The Node.js project needs to have a **package.json** file, it describes the project manifest that includes the packages and applications it depends on, information about its unique source control, and specific metadata like the project's name, description, and author.

### Dependencies
- dependencies 
- devDepenendcies
```
  "scripts": {
    //"default": "node index.js",
    "dev": "node index.js",
    "test": "echo \"Error: no test specified\" && exit 1"
  },
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
app.js
```
  console.log("Hello World!");
```
node app.js  

  
## Creating a Node.js Application
```
var http = require("http");

http.createServer(function (request, response) {
   response.writeHead(200, {'Content-Type': 'text/plain'});  
   response.end('Hello World\n');
}).listen(8081);

// Console will print the message
console.log('Server running at http://127.0.0.1:8081/');
```  
  
