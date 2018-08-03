## NodeJS: https://nodejs.org/en/

Node.js is a JavaScript runtime built on Chrome's V8 JavaScript engine. It uses an event-driven, non-blocking I/O model that 
makes it lightweight and efficient, andnpm for package management.

- Download Site:  https://nodejs.org/en/download/
- Document Site:  https://nodejs.org/en/docs/
    - NodeJS API:  https://nodejs.org/api/
- Install:   sudo apt-get install nodejs
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

### ORM:
- [TypeORM](https://github.com/typeorm/typeorm)
- [Waterline](http://waterlinejs.org/)
- [Sequelize](http://docs.sequelizejs.com/)

### UI
- [Angular2]()
- [PrimeNG]()
```
            'bootstrap',
            'bootstrap/dist/css/bootstrap.css',
            'font-awesome/css/font-awesome.css',
            'primeng/resources/primeng.css',
            'primeng/resources/themes/bootstrap/theme.css',
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
