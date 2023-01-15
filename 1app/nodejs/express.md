# [Express](https://expressjs.com/)
- [API doc](https://expressjs.com/en/4x/api.html)
- []
- Components
    - Application
    - Request
    - Response
    - Router
    - Middleware(Filter)

## Tool
Use the application generator tool, express-generator, to quickly create an application skeleton.
```
$ sudo apt install node-express-generator
$ sudo npm install -g express
$ sudo npm install -g express-generator

//$ npx express-generator

```
## Express Application
```
var express = require('express')
var app = express()

app.get('/', function (req, res) {
  res.send('hello world')
})
app.get('/user/:id', function (req, res) {
  res.send('user ' + req.params.id)
})

app.listen(3000)
```

## Express Builtin middleware (filter)
### express.json()
Builtin middleware parsing incoming requests with JSON payloads on body-parser.
```
express.json([options])
```

### express.text()
Builtin middleware parsing incoming request payloads into a string based on body-parser.
```
express.text([options])
```
### express.raw()
Builtin middleware parsing incoming request payloads into a Buffer based on body-parser.
```
express.raw([options])
```
### express.urlencoded()
Middleware parsing incoming requests with urlencoded payloads based on body-parser.
```
express.urlencoded([options])
```

## express.static()
Middleware to serves the static files based on serve-static.
```
express.static(root, [options])

var options = {
  dotfiles: 'ignore',
  etag: false,
  extensions: ['htm', 'html'],
  index: false,
  maxAge: '1d',
  redirect: false,
  setHeaders: function (res, path, stat) {
    res.set('x-timestamp', Date.now())
  }
}

app.use(express.static('public', options))
```

### express.Router()
Creates a new router object.
```
var router = express.Router([options])

// invoked for any requests passed to this router
router.use(function (req, res, next) {  
  // .. some logic here .. like any other middleware
  next()
})

// will handle any request that ends in /events depends on where the router is "use()'d"
router.get('/events', function (req, res, next) {
  // ..
})

// only requests to /calendar/* will be sent to our "router"
app.use('/calendar', router)

```
