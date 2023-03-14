# NodeJS ODBC: An asynchronous interface to unixODBC and its supported drivers
- https://www.npmjs.com/package/odbc
```
sudo apt-get install unixodbc unixodbc-dev
npm install odbc
```

## API:
- Connection
```
        constructor: odbc.connect()
        .query()
        .callProcedure()
        .createStatement()
        .tables()
        .columns()
        .setIsolationLevel()
        .beginTransaction()
        .commit()
        .rollback()
        .close()
```        
 - Pool
 ```` 
        constructor: odbc.pool()
        .connect()
        .query()
        .close()
```        
- Statement
```
        .prepare()
        .bind()
        .execute()
        .close()
```        
- Cursor
```
        .fetch()
        .noData
        .close()
```
