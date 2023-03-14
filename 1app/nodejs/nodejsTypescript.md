# NodeJS with Typescript
- [NodeJS with Typescript](https://nodejs.dev/en/learn/nodejs-with-typescript/)
- [Typescript with NodeJS](https://www.section.io/engineering-education/how-to-use-typescript-with-nodejs/)
- [NodeJS+Typescript](https://betterstack.com/community/guides/scaling-nodejs/nodejs-typescript/)
```
$ npm install -g typescript
$ tsc --init
$ npm install -D @types/express
```
using **npm install -D @types/node**  to install types of the package written in javascript.
```
import express, {Request,Response,Application} from 'express';
const app:Application = express();
const PORT = process.env.PORT || 8000;
app.get("/", (req:Request, res:Response):void => {
  res.send("Hello Typescript with Node.js!")
});
app.listen(PORT, ():void => {
  console.log(`Server Running here -> https://localhost:${PORT}`);
});
```
- ts-node-dev: watches .ts files, and restart the server if the file is updated (in package.json):
```
  "scripts": {
    "dev": "ts-node-dev --respawn ./src/index.ts"
  }
```
- npm install -D nodemon: similar to ts-node-dev, automatically restart the server
```
 "scripts": {
   "dev": "nodemon ./src/index.ts"
 }
```
- npm run dev / npm run build
