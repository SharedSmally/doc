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

## Application Registration
Application must be registered with the service before using OAuth2. This is done through a registration form in the “developer” or “API” portion of the service’s website providing the following information (with application details):
- Application Name
- Application Website
- Redirect URI or Callback URL

The redirect URI is where the service will redirect the user after they authorize (or deny) the application, and the of the application that will handle authorization codes or access tokens.

## Client ID and Client Secret
Once the application is registered, the service will issue “client credentials” in the form of a client identifier and a client secret. The Client ID is a publicly exposed string that is used by the service API to identify the application, and is also used to build authorization URLs that are presented to users. The Client Secret is used to authenticate the identity of the application to the service API when the application requests to access a user’s account, and must be kept private between the application and the API.

## Authorization Grant
The first four steps cover obtaining an authorization grant and access token. The authorization grant type depends on the method used by the application to request authorization, and the grant types supported by the API. OAuth 2 defines four grant types, each of which is useful in different cases:
- Authorization Code: used with server-side Applications
- Implicit: used with Mobile Apps or Web Applications (applications that run on the user’s device)
- Resource Owner Password Credentials: used with trusted Applications, such as those owned by the service itself
- Client Credentials: used with Applications API access

### Grant Type: Authorization Code:  most commonly used
Optimized for server-side applications, where source code is not publicly exposed, and Client Secret confidentiality can be maintained. This is a redirection-based flow, which means that the application must be capable of interacting with the user-agent (i.e. the user’s web browser) and receiving API authorization codes that are routed through the user-agent.

![Flow](https://assets.digitalocean.com/articles/oauth/auth_code_flow.png)
- Authorization Code Link:
The user is given an authorization code link. 
```
https://cloud.digitalocean.com/v1/oauth/authorize?response_type=code&client_id=CLIENT_ID&redirect_uri=CALLBACK_URL&scope=read
```
When the user clicks the link, they must first log in to the service, to authenticate their identity (unless they are already logged in). Then they will be prompted by the service to authorize or deny the application access to their account. 

- Application Receives Authorization Code
If the user clicks “Authorize Application”, the service redirects the user-agent to the application redirect URI, which was specified during the client registration, along with an authorization code:
```
https://dropletbook.com/callback?code=AUTHORIZATION_CODE
```

- Application Requests Access Token
The application requests an access token from the API, by passing the authorization code along with authentication details, including the client secret, to the API token endpoint:
```
https://cloud.digitalocean.com/v1/oauth/token?client_id=CLIENT_ID&client_secret=CLIENT_SECRET&grant_
```

- Application Receives Access Token (response)
If the authorization is valid, the API will send a response containing the access token (and optionally, a refresh token) to the application:
```
{"access_token":"ACCESS_TOKEN","token_type":"bearer","expires_in":2592000,"refresh_token":"REFRESH_TOKEN","scope":"read","uid":100101,"info":{"name":"Mark E. Mark","email":"mark@thefunkybunch.com"}}
```
Now the application is authorized! It may use the token to access the user’s account via the service API, limited to the scope of access, until the token expires or is revoked. If a refresh token was issued, it may be used to request new access tokens if the original token has expired.

### Grant Type: Implicit
Used for mobile apps and web applications, where the client secret confidentiality is not guaranteed. It is also a redirection-based flow but the access token is given to the user-agent to forward to the application, so it may be exposed to the user and other applications on the user’s device. Also, this flow does not authenticate the identity of the application, and relies on the redirect URI (that was registered with the service) to serve this purpose.

The basic flow: the user is asked to authorize the application, then the authorization server passes the access token back to the user-agent, which passes it to the application.

![Flow](https://assets.digitalocean.com/articles/oauth/implicit_flow.png)
- Implicit Authorization Link
With the implicit grant type, the user is presented with an authorization link, that requests a token from the API. 
```
https://cloud.digitalocean.com/v1/oauth/authorize?response_type=token&client_id=CLIENT_ID&redirect_uri=CALLBACK_URL&scope=read
```
When the user clicks the link, they must first log in to the service, to authenticate their identity (unless they are already logged in). Then they will be prompted by the service to authorize or deny the application access to their account. 

- User-agent Receives Access Token with Redirect URI
If the user clicks “Authorize Application”, the service redirects the user-agent to the application redirect URI, and includes a URI fragment containing the access token:
```
https://dropletbook.com/callback#token=ACCESS_TOKEN
```
- User-agent Follows the Redirect URI
The user-agent follows the redirect URI but retains the access token.

- Application Sends Access Token Extraction Script
The application returns a webpage that contains a script that can extract the access token from the full redirect URI that the user-agent has retained.

- Access Token Passed to Application
The user-agent executes the provided script and passes the extracted access token to the application.

Once the application is authorized, it may use the token to access the user’s account via the service API, limited to the scope of access, until the token expires or is revoked.
 
### Grant Type: Resource Owner Password Credentials
The user provides their service credentials (username and password) directly to the application, which uses the credentials to obtain an access token from the service. This grant type should only be enabled on the authorization server if other flows are not viable. Also, it should only be used if the application is trusted by the user (e.g. it is owned by the service, or the user’s desktop OS).

After the user gives their credentials to the application, the application will then request an access token from the authorization server. The POST request might be::
```
https://oauth.example.com/token?grant_type=password&username=USERNAME&password=PASSWORD&client_id=CLIENT_ID
```
If the user credentials check out, the authorization server returns an access token to the application. Now the application is authorized!

### Grant Type: Client Credentials
Provides an application a way to access its own service account. For example to update its registered description or redirect URI, or access other data stored in its service account via the API.

The application requests an access token by sending its credentials, its client ID and client secret, to the authorization server.
```
https://oauth.example.com/token?grant_type=client_credentials&client_id=CLIENT_ID&client_secret=CLIENT_SECRET
```
If the application credentials check out, the authorization server returns an access token to the application. Now the application is authorized to use its own account.

## Access Token
Once the application has an access token, it may use the token to access the user’s account via the API, limited to the scope of access, until the token expires or is revoked.
```
curl -X POST -H "Authorization: Bearer ACCESS_TOKEN""https://api.digitalocean.com/v2/$OBJECT" 
```

## Refresh Token Flow
After an access token expires, using it to make a request from the API will result in an “Invalid Token Error”. At this point, if a refresh token was included when the original access token was issued, it can be used to request a fresh access token from the authorization server.
```
https://cloud.digitalocean.com/v1/oauth/token?grant_type=refresh_token&client_id=CLIENT_ID&client_secret=CLIENT_SECRET&refresh_token=REFRESH_TOKEN
```
## Tutorial
- [Documents](https://oauth.net/2/)
- [Introduction](https://www.digitalocean.com/community/tutorials/an-introduction-to-oauth-2)
