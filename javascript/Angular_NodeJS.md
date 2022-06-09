# Javascript: Chrome - NodeJS - Angular
- v8: Javascript engine
- NodeJS: based on v8, with npm, a run time environment to load JavaScript applications into the server-side. 
- Angular: a single-page application web framework developed to create an application for web, mobile, and desktop 
- Chrome: Web Browser based on NodeJS + v8
- Electron: Desktop Application on Chrome: Create Windows using Html5,CSS,Javascript

## Angular + NodeJS + Bootstrap
- Sample: https://medium.com/bb-tutorials-and-thoughts/how-to-develop-and-build-angular-app-with-nodejs-e24c40444421
- CRUD: https://developer.okta.com/blog/2018/10/30/basic-crud-angular-and-node

- [retool](https://retool.com/integrations/)

## REST CRUD
- Create:

To create a new object under an endpoint, a post-request is sent to the REST-Endpoint containing the new object to create in the post-body.

- Read:

To read all objects from an endpoint, e.g if you want to know about all cats, a get-request is sent to the "cats" endpoint. If you are interested in one specific cat, you append the id/name of the cat to the route "cats/cat1".

- Update:

To update an object, a put request is sent to the endpoint. The identifier is added to the route e.g. "cat/cat1". The information of the object is added to the put-body.

- Delete:

To delete an object, a delete request is sent to the endpoint with the identifier of the wanted object added to the route.

- RUD: may be with the request parameters to select the object
