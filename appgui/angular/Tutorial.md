# Angular Tutorial
## Books
- Angular development with typescript: https://livebook.manning.com/book/angular-development-with-typescript-second-edition/about-this-book/
- Angular in Action

## Communication: use HttpClient for http
https://medium.com/@ZombieCodeKill/angular-fundamentals-communicating-with-the-server-using-http-observables-and-rx-2a1b939cc66b

- Use callback:
```
Server.request(requestData, function(responseData) {
 // asynchronously handle data
});

//this will be called before the callback
doSomethingElse();
```
- Use Promise: represent a single value which will be returned in the future.
```
var promise = http.get(url, data);
promise.then(function(responseData) {
   // handle response
});

//this will be execute before the then function
doSomethingElse();
return promise;
```

- Use RxJx Observeable: represent 0 or more values, returned either immediately or in the future. They can either be synchronous or asynchronous, and can be closed independently of returning a value. The have improved error handling over promises.
```
var obs= http.get(url, data);
obs.subscribe(function(responseData) {
   // handle response
});

doSomethingElse();
return obs;
```

## Service
- Title Service: https://blog.bitsrc.io/dynamic-page-titles-in-angular-98ce20b5c334
