## NodeJS: https://nodejs.org/en/

Node.js is a JavaScript runtime built on Chrome's V8 JavaScript engine. It uses an event-driven, non-blocking I/O model that 
makes it lightweight and efficient, andnpm for package management.

- Download Site:  https://nodejs.org/en/download/
- Document Site:  https://nodejs.org/en/docs/
    - NodeJS API:  https://nodejs.org/api/
- Install:   sudo apt-get install nodejs
```
For centos:
curl -sL https://rpm.nodesource.com/setup_8.x | sudo bash -
sudo yum remove -y nodejs npm
sudo yum install -y nodejs
npm i npm@latest -g
```
- Usage:
```
node [options] [v8 options] [script.js | -e "script" | - ] [arguments]
```
- Sample js script (test.js):
```
const http = require('http');
const hostname = '127.0.0.1';
const port = 3000;

const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  res.end('Hello World\n');
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});
```
or
```
http = require('http');
http.createServer(function (req, res) {
   res.writeHead(200, {'Content-Type': 'text/plain'});
   res.end('It is working!\n');
}).listen(3000);
console.log('Server running at port 3000');
```

- Run the script:
```
node test.js
```
- Open a browser: http://192.168.109.11:3000/
- npm: nodejs package manager(under /usr/lib/node_modules/npm)

###
- http/https/https: create Http server/clent
- [net](https://gist.github.com/tedmiston/5935757): net.createServer for TCP server and net.Socket/createConnection for TCP client
```
const net = require('net');
var server = net.createServer(function(socket) {
	socket.write('Echo server\r\n');
	socket.pipe(socket);
});
server.on('eventName', function(){
    ........
});
server.listen(1337, '127.0.0.1');

var client = new net.Socket(); //or createConnection
client.connect(1337, '127.0.0.1', function() {// Connected
	client.write('Hello, server! Love, Client.');
});
client.on('data', function(data) { // Received data;
	client.destroy(); // kill client after server's response
});
client.on('close', function() { // Connection closed
});
```
- [udp]

### ORM:
- [TypeORM](https://github.com/typeorm/typeorm)
- [Waterline](http://waterlinejs.org/)
- [Sequelize](http://docs.sequelizejs.com/)

### UI:  PrimeNG + Angular is the best.
- [jQuery](https://jquery.com/)
    - [jQuery API](https://api.jquery.com/)
    - [jQueryUI](https://jqueryui.com/): Based on jQuery
    - [jQuery Theme Roller](https://jqueryui.com/themeroller/)
- [Bootstrap](https://getbootstrap.com/): UI based on jQuery
- [Angular](https://angular.io/): component uses service to access data, based on css and html template[could be bootstrap] to generate UI, and ts file to take action on UI [Module=>Component;Service;].
- [Angular CLI](https://cli.angular.io/): [wiki](https://github.com/angular/angular-cli/wiki); npm install -g @angular/cli
- [Karma](http://karma-runner.github.io/): Angular testing; npm install karma --save-dev
- [PrimeNG](https://www.primefaces.org/primeng/#/): based on Angular; more UI components: 
       - npm install primeng --save; 
       - npm install primeicons --save
- [NVD3](http://nvd3.org/index.html)
- [Font awesone](https://fontawesome.com)
   - Solid	  Free	fas	```<i class="fas fa-stroopwafel"></i>```	
   - Regular  Pro 	far	```<i class="far fa-stroopwafel"></i>```	
   - Light	  Pro 	fal	```<i class="fal fa-stroopwafel"></i>```	
   - Brands	  Free	fab	```<i class="fab fa-font-awesome"></i>```
```
<i class="fas fa-stroopwafel"></i> <!-- this icon's 1) style prefix == fas and 2) icon name == stroopwafel -->
<i class="fas fa-stroopwafel"></i> <!-- using an <i> element to reference the icon -->
<span class="fas fa-stroopwafel"></span> <!-- using a <span> element to reference the icon -->

<span style="font-size: 3em; color: Tomato;">
  <i class="fas fa-stroopwafel"></i>
</span>

<span style="font-size: 48px; color: Dodgerblue;">
  <i class="fas fa-stroopwafel"></i>
</span>

<span style="font-size: 3rem;">
  <span style="color: Mediumslateblue;">
  <i class="fas fa-stroopwafel"></i>
  </span>
</span>
```

### C++ Addons: https://nodejs.org/api/addons.html
Node.js Addons are dynamically-linked shared objects written in C++. They can be loaded into Node.js using the require() function, and used just as if they were an ordinary Node.js module. They are used primarily to provide an interface between JavaScript running in Node.js and C/C++ libraries.

-  create the file hello.cc:
```
// hello.cc
#include <node.h>

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(addon, init)

}  // namespace demo
```
Note that all Node.js Addons must export an initialization function following the pattern:
```
void Initialize(Local<Object> exports);
NODE_MODULE(module_name, Initialize)
``` 
     - There is no semi-colon after NODE_MODULE as it's not a function (see node.h).
     - The module_name must match the filename of the final binary (excluding the .node suffix).
     - In the hello.cc example, then, the initialization function is init and the Addon module name is addon

- Building:
The source code must be compiled into the binary addon.node file:
     - create a file called binding.gyp in the top-level of the project describing the build configuration of the module using a JSON-like format. This file is used by node-gyp -- a tool written specifically to compile Node.js Addons.
```
{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "hello.cc" ]
    }
  ]
}
```

     - Once the binding.gyp file has been created, use node-gyp configure to generate the appropriate project build files for the current platform. This will generate either a Makefile (on Unix platforms) or a vcxproj file (on Windows) in the build/ directory.

     - Next, invoke the node-gyp build command to generate the compiled addon.node file. This will be put into the build/Release/ directory.

     - When using npm install to install a Node.js Addon, npm uses its own bundled version of node-gyp to perform this same set of actions, generating a compiled version of the Addon for the user's platform on demand.
     
- Once built, the binary Addon can be used from within Node.js by pointing require() to the built addon.node module:
```
// hello.js
const addon = require('./build/Release/addon');

console.log(addon.hello());
// Prints: 'world'
```
