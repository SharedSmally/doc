# NodeJS
- [NodeJS](https://nodejs.org/en/): JavaScript runtime engine
    - [Docs](https://nodejs.org/en/docs/)
    - [v15.x docs](https://nodejs.org/dist/latest-v15.x/docs/api/)
- [npm](): Node Package Manager, with NodeJS
    - 
## Framework
- [express](https://expressjs.com/): 
    - [frameworks](https://expressjs.com/en/resources/frameworks.html) based on express
    - [4.x API](https://expressjs.com/en/4x/api.html)
    - [Application](https://expressjs.com/en/4x/api.html#app)
    - [Request](https://expressjs.com/en/4x/api.html#req)
    - [Response](https://expressjs.com/en/4x/api.html#res)
    - [Router](https://expressjs.com/en/4x/api.html#router)
```
var express = require('express')
var app = express()

express.json([options])
express.raw([options])
express.static([options])
express.text([options])
express.urlencoded([options])
express.Router([options])

app.get('/', function (req, res) {
  res.send('hello world')
})

app.listen(3000)
```



