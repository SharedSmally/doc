# OAUTH 2

## Roles
- Client: Application

   Wants to access the user’s account. Before it may do so, it must be authorized by the user, and the authorization must be validated by the API.
   
- Resource Owner: User

  Authorizes an application to access their account. The application’s access to the user’s account is limited to the “scope” of the authorization granted (e.g. read or write access).

- Resource Server: API
 
   Hosts the protected user accounts

- Authorization Server: API

    Verifies the identity of the user then issues access tokens to the application.

## Flow 
![flow](https://assets.digitalocean.com/articles/oauth/abstract_flow.png)
- The application requests authorization to access service resources from the user
- If the user authorized the request, the application receives an authorization grant
- The application requests an access token from the authorization server (API) by presenting authentication of its own identity, and the authorization grant
- If the application identity is authenticated and the authorization grant is valid, the authorization server (API) issues an access token to the application. Authorization is complete.
- The application requests the resource from the resource server (API) and presents the access token for authentication
- If the access token is valid, the resource server (API) serves the resource to the application
The actual flow of this process will differ depending on the authorization grant type in use,


## Tutorial
- [Documents](https://oauth.net/2/)
- [Introduction](https://www.digitalocean.com/community/tutorials/an-introduction-to-oauth-2#:~:text=OAuth%202%20is%20an%20authorization,Facebook%2C%20GitHub%2C%20and%20DigitalOcean.&text=OAuth%202%20provides%20authorization%20flows,desktop%20applications%2C%20and%20mobile%20devices.)
