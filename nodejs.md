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

