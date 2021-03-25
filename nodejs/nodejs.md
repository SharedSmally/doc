# NodeJS
- [NodeJS](https://nodejs.org/en/): JavaScript runtime engine
    - [Docs](https://nodejs.org/en/docs/)
    - [v15.x docs](https://nodejs.org/dist/latest-v15.x/docs/api/)
- [npm](): Node Package Manager, with NodeJS
    
## Framework
- Express.js- Express for Everyone
- [Koa.js](https://github.com/koajs/koa)- Next Generation Node.js Framework
- Meteor.js- One Application, One Language
- Socket.io- Chat Apps Made Easy with Socket.io
- Nest.js- A Nestling of Code
- Sails.js- Modernized Data-Oriented MVC Framework 
- Total.js- A Complete Framework
- Hapi.js- Secure than Ever
- Feather.js- F for Flexible
- Loopback.js- Better Connectivity
- Adonis.js-The Dependable Framework
- Derby.js-The Racer

### [express](https://expressjs.com/): 
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

### ORM
- Low level: Database driver
    - mysql: MySQL 
    - pg: PostgreSQL 
    - sqlite3: SQLite 
- High level ORM
    - knex: Query Builder 
    - sequelize: 
    - bookshelf: Knex based 
    - waterline: 
    - objection: Knex based 
    


