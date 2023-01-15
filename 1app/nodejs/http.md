# HTTP
- [http api](https://nodejs.org/api/http.html)

## http.Agent
An Agent is responsible for managing connection persistence and reuse for HTTP clients. 


## Server
```
const http = require('node:http');

const server = http.createServer((req, res) => {
  res.end();
});
server.on('clientError', (err, socket) => {
  socket.end('HTTP/1.1 400 Bad Request\r\n\r\n');
});
server.listen(8000);
```

## Client
```

```
