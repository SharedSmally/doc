# NodeJS Session
Session-based authentication: When the client makes a login request to the server, the server will create a session and store it on the server-side. 
When the server responds to the client, it sends a cookie. This cookie will contain the session’s unique id stored on the server, 
which will now be stored on the client. This cookie will be sent on every request to the server.

A cookie is a key-value pair that is stored in the browser. The browser attaches cookies to every HTTP request that is sent to the server.

Components: 
- Express - a web framework for Node.js used to create HTTP web servers. 
- [Express-session](https://expressjs.com/en/resources/middleware/session.html) - an HTTP server-side framework used to create and manage a session middleware. 
      - Compatible Session Stores: in [Express-session](https://expressjs.com/en/resources/middleware/session.html)
- Cookie-parser - used to parse cookie header to store data on the browser whenever a session is established on the server-side.
```
npm install express express-session cookie-parser
```

## [Setup Session](https://www.section.io/engineering-education/session-management-in-nodejs-using-expressjs-and-express-session/)
```
const express = require('express');
const cookieParser = require("cookie-parser");
const sessions = require('express-session');

const app = express();
const PORT = 4000;

const oneDay = 1000 * 60 * 60 * 24;
app.use(sessions({
    secret: "thisismysecrctekeyfhrgfgrfrty84fwir767",
    saveUninitialized:true,
    cookie: { maxAge: oneDay },
    resave: false 
}));

// parsing the incoming data
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

//serving public file
app.use(express.static(__dirname));

// cookie parser middleware
app.use(cookieParser());

app.get('/',(req,res) => {
    session=req.session;
    if(session.userid){
        res.send("Welcome User <a href=\'/logout'>click to logout</a>");
    }else
    res.sendFile('views/index.html',{root:__dirname})
});

//username and password
const myusername = 'user1'
const mypassword = 'mypassword'

// a variable to save a session
var session;

app.post('/user',(req,res) => {
    if(req.body.username == myusername && req.body.password == mypassword){
        session=req.session;
        session.userid=req.body.username;
        console.log(req.session)
        res.send(`Hey there, welcome <a href=\'/logout'>click to logout</a>`);
    }
    else{
        res.send('Invalid username or password');
    }
})

app.get('/logout',(req,res) => {
    req.session.destroy();
    res.redirect('/');
});

app.listen(PORT, () => console.log(`Server Running at port ${PORT}`));
```

## Load Balance
- Server-Side LB: HAProxy,...
- Client-Side LB:
