# Modules

## HTTP
- express

## REST

## JSON

## XML
[xml parser](https://openbase.com/categories/js/best-nodejs-xml-parser-libraries)
- **fast-xml-parser**
- xml2js / xmldoc: depends on sax.js 
- libxmljs/xml-stream: require node-gyp.
- remixml

## SQL
[SQL ORMs](https://www.prisma.io/dataguide/database-tools/top-nodejs-orms-query-builders-and-database-libraries); work for TypeScript
- Prisma
- Sequelize
- **TypeORM**
- Mongoose
- Bookshelf.js
- Objection.js
- Waterline
- Knex.js (Query Builder)
- MassiveJS
- Mikro-ORM
- Slonik

Database Drivers at low level:
- PostgreSQL: node-postgres, pg-promise
- MySQL: mysql, node-mysql2, mysql-connector-nodejs
- SQLite: node-sqlite3
- MSSQL: node-sqlserver-v8, node-mssql, tedious
- MongoDB: node-mongodb-native
- Redis: node-redis, ioredis
    

## MongoDB

## Redis
- node-redis: https://www.npmjs.com/package/redis
- node-redis: https://github.com/redis/node-redis
- Redis-om: https://redis.io/docs/stack/get-started/tutorials/stack-node/
```
npm install redis --save

var redis = require("redis");
var client = redis.createClient(
  url: 'redis://alice:foobared@awesome.redis.server:6380'
);
  
client.on("connect", function() {
  console.log("Connection Successful!!");
});
  
client.set("Intern", "gfg", (err, stu) => {
    if (err) console.log(err);
    else console.log(stu);
});
  
client.get('Intern', (err, stu) => {
    if (err) console.log(err);
    else console.log(stu); 
});
```
## Kafka
- **kafka-node**: https://www.npmjs.com/package/kafka-node
- KafkaJS: https://kafka.js.org/

##
