# NodeJS
Node.js = Javascript Runtime Environment + JavaScript Library to develop server-side Http server

## Tutorial
- NodeJS: https://nodejs.org/en/; include npm
- API document: https://nodejs.org/api/documentation.html
- Tutorial: https://www.tutorialspoint.com/nodejs/index.htm

## Setup
- Install NodeJS:  node -v
- Install NPM: npm -v
- Create NodeJS application:  
    - npm init: generate project with package.json, including the dependencies
    - npm install/uninstall/upgrade module //--save: save dep in package; -g: install in global site
    - vi app.js
    - node app.js

## Application: app.js
- AddImport Required Module
```
var http = require("http");
```
- Create Http Server: using different modules, such as http, express, ...
```
var server = http.createServer(function (request, response) {
   // Send the HTTP header 
   response.writeHead(200, {'Content-Type': 'text/plain'});
   
   // Send the response body as "Hello World"
   response.end('Hello World\n');
});

server.listen(8081);

console.log('Server running at http://127.0.0.1:8081/');
```
## Concept
- Callback:
Callback is an asynchronous equivalent for a function. A callback function is called at the completion of a given task.
- EventLoop: Single Thread for EventLoop

![EventLoop](https://www.tutorialspoint.com/nodejs/images/event_loop.jpg)
```
// Import events module
var events = require('events');

// Create an eventEmitter object
var eventEmitter = new events.EventEmitter();

// Create an event handler
var eventHandler = function connected() {
   console.log('connection succesful.');
  
   // Fire the data_received event 
   eventEmitter.emit('data_received');
}

// Bind event and event handler
eventEmitter.on('eventName', eventHandler);

// Fire an event 
eventEmitter.emit('eventName');
```

- EventEmiter
All objects which emit events are the instances of events.EventEmitter.

- Buffer
Object to store raw data similar to an array of integers

- Streams 
objects to read data from a source or write data to a destination in continuous fashion:
    - Readable − Stream which is used for read operation.
    - Writable − Stream which is used for write operation.
    - Duplex − Stream which can be used for both read and write operation.
    - Transform − A type of duplex stream where the output is computed based on input.
- FileSystem
- Global Objects
    - \_\_filename: the filename of the code being executed.
    - \_\_dirname: the name of the directory that the currently executing script resides in
    - setTimeout(cb, ms)/clearTimeout(t): run callback cb after at least ms milliseconds.
    - setInterval(cb, ms): run callback cb repeatedly after at least ms milliseconds.
    - console: Used to print information on stdout and stderr.
    - process: Used to get information on current process.

## express
- Allows to set up middlewares to respond to HTTP Requests. express.static to serve static files
- Defines a routing table which is used to perform different actions based on HTTP Method and URL.
- Allows to dynamically render HTML Pages based on passing arguments to templates.
```
$ npm install express --save
$ npm install body-parser --save
$ npm install cookie-parser --save
$ npm install multer --save

var express = require('express');
var app = express();

var fs = require("fs");

var bodyParser = require('body-parser');
var multer  = require('multer');

app.use(express.static('public'));
app.use(bodyParser.urlencoded({ extended: false }));
app.use(multer({ dest: '/tmp/'}));

app.get('/', function (req, res) {
   res.send('Hello World');
})
//.........
app.post('/', function (req, res) {
   console.log("Got a POST request for the homepage");
   res.send('Hello POST');
})

app.get('/listUsers', function (req, res) {
   fs.readFile( __dirname + "/" + "users.json", 'utf8', function (err, data) {
      console.log( data );
      res.end( data );
   });
})

app.post('/addUser', function (req, res) {   
   fs.readFile( __dirname + "/" + "users.json", 'utf8', function (err, data) {
      data = JSON.parse( data );
      data["user4"] = user["user4"];
      console.log( data );
      res.end( JSON.stringify(data));
   });
})
app.use(express.static('public')); // for static files

var server = app.listen(8081, function () {
   var host = server.address().address
   var port = server.address().port   
   console.log("Example app listening at http://%s:%s", host, port)
})
```

## Module


## c++ addson
