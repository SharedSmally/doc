# Deployment

## Depolyment
- Compile to dist/
```
ng build
```
Copy the contents of the dist/project folder to the web server.
- Run a web server (lite-server)
```
ng serve --port 4201  # run locally
lite-server --baseDir="dist/project-name"  #
```
- Nodejs server using express
```
const express = require("express");
const app = express();
const PORT = process.env.PORT || 3030;
// the code
app.listen(PORT, () => {
  console.log(`server started on port ${PORT}`);
});
```

## [Heroku](https://devcenter.heroku.com/)
### [Heroku CLI](https://devcenter.heroku.com/articles/heroku-cli)
- Install Heroku CLI
```
$ npm install -g heroku
$ heroku --version
```
- [Start with NodeJS](https://devcenter.heroku.com/articles/getting-started-with-nodejs#set-up)

