# Timers

## Tutorial
- Timers: https://nodejs.org/api/timers.html
- https://www.knowledgehut.com/blog/web-development/how-to-use-timers-in-nodejs
- Promise with timeout: https://spin.atomicobject.com/2020/01/16/timeout-promises-nodejs/

## Timeout:
```
console.log("One");
setTimeout(function(){
   console.log("Two");
}, 1000);
console.log("Three");
```

setInterval() and setTimeout(): delay code execution and allow one or more operations to be performed repeatedly.
- setTimeout(): allows users to postpone the execution of code. The setTimeout() method accepts two parameters, one of which is a user-defined function, and the other is a time parameter to delay execution. The time parameter, which is optional to pass, stores the time in milliseconds (1 second = 1000 milliseconds).
- clearTimeout():: deactivates a timer that was previously set with the setTimeout() method.
```
function welcome () {   
    console.log("Welcome to Knowledgehut!");   
  }   
var id1 = setTimeout(welcome,1000);   
var id2 = setInterval(welcome,1000);   
clearTimeout(id1);
```

- setInterval(): It repeats the specified function after a time interval, executed repeatedly after a certain amount of time specified by the user in this function.
- clearInterval():
```
var si = setInterval(function A() { 
    return console.log("Hello World!"); 
}, 1000); 

setTimeout(function() { 
    clearInterval(si); 
}, 4000);
```
