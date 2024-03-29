# HTTP2

## Components:
- **express**: A Node.js framework for building web applications and backend APIs.
- **spdy**: Express compatible module that creates HTTP/2 enabled servers in Node.js.
```
npm install express spdy
```
- Generate an SSL certificate
```
openssl req -x509 -sha256 -nodes -days 365 -newkey rsa:2048 -keyout server.key -out server.crt
```
- Main nodejs file: index.js
```
const spdy = require("spdy")
const express = require("express")
const fs = require("fs")
const {promisify} = require("util")
const readFile = promisify(fs.readFile)
const app = express()

app.use(express.static("public"))

app.get("/push", async (req, res) => {
  try {
    if(res.push){
      [
        "/app.js",
        "/styles.css",
        "/images/image.png"
      ].forEach(async (file) => {
       res.push(file, {}).end(await readFile(`public${file}`))
      })
    }

    res.writeHead(200)
    res.end(await readFile("index.html"))
  }catch(error){
    res.status(500).send(error.toString())
  }
})

spdy.createServer(
  {
    key: fs.readFileSync("./server.key"),
    cert: fs.readFileSync("./server.crt")
  },
  app
).listen(8000, (err) => {
  if(err){
    throw new Error(err)
  }
  console.log("Listening on port 3001")
})
```
