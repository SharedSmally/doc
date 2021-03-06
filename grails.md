[GRAILS](http://www.grails.org/)
=======
- [User Guide](http://docs.grails.org/latest/guide/single.html)
- [Grails API](http://docs.grails.org/latest/api/)

[GORM](http://gorm.grails.org/latest/): 
=======
- [GORM API](http://gorm.grails.org/latest/api/)
- [GORM User Guide](http://docs.grails.org/latest/guide/GORM.html)
- Hibernate:  [Documentation](http://gorm.grails.org/latest/hibernate/manual/index.html) / [API](http://gorm.grails.org/latest/hibernate/api/index.html)
- Neo4j: [Documentation](http://gorm.grails.org/latest/neo4j/manual/index.html) / [API](http://gorm.grails.org/latest/neo4j/api/index.html)
- Cassandra: [Documentation](http://gorm.grails.org/latest/cassandra/manual/index.html) / [API](http://gorm.grails.org/latest/cassandra/api/index.html)
- MongoDB: [Documentation](http://gorm.grails.org/latest/mongodb/manual/index.html) / [API](http://gorm.grails.org/latest/mongodb/api/index.html)
- RxGORM: [Documentation](http://gorm.grails.org/latest/rx/manual/index.html) / [API](http://gorm.grails.org/latest/rx/api/index.html)
       - [For REST](http://gorm.grails.org/latest/rx/rest-client/manual/index.html)
       - [For MongoDB](http://gorm.grails.org/latest/rx/manual/index.html)
- Redis: [Documentation](http://gorm.grails.org/latest/redis/manual/index.html) / [API](http://gorm.grails.org/latest/redis/api/index.html)
[Plugins](http://docs.grails.org/latest/guide/plugins.html)
======
- Repository
   - [Grails repositiory](http://grails.org/plugins.html)
   - [Bintray repository](https://bintray.com/grails/plugins)
- Plugins
   - [Spring Security Core](http://grails.org/plugins.html#plugin/spring-security-core):
      - Dependency: compile 'org.grails.plugins:spring-security-core:3.1.1'
      - [GitHub](https://github.com/grails-plugins/grails-spring-security-core)
      - [Document](https://github.com/grails-plugins/grails-spring-security-core)
      - [User Guide] (https://grails-plugins.github.io/grails-spring-security-core/v3/)
      - Script: 
```        
        grails s2-quickstart DOMAIN_CLASS_PACKAGE USER_CLASS_NAME ROLE_CLASS_NAME [REQUESTMAP_CLASS_NAME] [--groupClassName=GROUP_CLASS_NAME]
        
        grails s2-create-persistent-token <classname>
        
        grails s2-create-role-hierarchy-entry <classname>
```        
   - [Spring Security UI](http://grails.org/plugins.html#plugin/spring-security-ui)
      - Dependency: compile 'org.grails.plugins:spring-security-ui:3.0.0.M2'
      - [Document](http://grails-plugins.github.io/grails-spring-security-ui/)
      - [User Guide](http://grails-plugins.github.io/grails-spring-security-ui/v3/index.html)
      - Scripts
```
    grails s2ui-override <type> [controllerPackage]
```    
       type: 
            - aclclass; aclentry; aclobjectidentity; aclsid; 
            - auth; layout; persistentlogin; 
            - register; registrationcode; 
            - requestmap; role; user; securityinfo; 
  
   - [Spring REST Security](http://grails.org/plugins.html#plugin/spring-security-rest)
        - [GitHub](https://github.com/alvarosanchez/grails-spring-security-rest)
        - [User Guide](http://alvarosanchez.github.io/grails-spring-security-rest/latest/docs/index.html)
   - [Actuator UI](http://grails.org/plugins.html#plugin/actuator-ui)
        - Dependency:  compile 'org.grails.plugins:actuator-ui:1.1'
        - [GitHub]()
        - [User Guide]()
   - [Asset-pipeline]:  static resources
        - Dependency:  compile 'org.grails.plugins:asset-pipeline:3.2.1'
        
Quick Reference 
======
Include profile/plugin/app;  domain,service,controller,taglib; unit/integration/functional-test.
 - Command Line
     - [Usage](http://docs.grails.org/latest/ref/Command%20Line/Usage.html):  **grails** _[environment]_\* _command name_
     - Main Tasks
         - [clean](http://docs.grails.org/latest/ref/Command%20Line/clean.html): **grails** __clean__
         - [compile](http://docs.grails.org/latest/ref/Command%20Line/compile.html): **grails** __compile__
         - Packaging
              - [package](http://docs.grails.org/latest/ref/Command%20Line/package.html):**grails package**
              - [package-plugin](http://docs.grails.org/latest/ref/Command%20Line/package-plugin.html):**grails package-plugin**
              - [war](http://docs.grails.org/latest/ref/Command%20Line/war.html):**grails [environment]\* war** _arguments\*_
              - install
         - [docs](http://docs.grails.org/latest/ref/Command%20Line/docs.html):**apply plugin: "org.grails.grails-doc"; gradle docs**
         - [console](http://docs.grails.org/latest/ref/Command%20Line/console.html):**grails** _[environment]_\* __console__ 
         - [shell](http://docs.grails.org/latest/ref/Command%20Line/shell.html):**grails _environment]\*_ shell**
     - Help Tasks   
         - [help](http://docs.grails.org/latest/ref/Command%20Line/help.html):**grails help** _[command_name]_\*
         - [stats](http://docs.grails.org/latest/ref/Command%20Line/stats.html):**grails stats**
         - [bug-report](http://docs.grails.org/latest/ref/Command%20Line/bug-report.html): **grails bug-report**
         - [dependency-report](http://docs.grails.org/latest/ref/Command%20Line/dependency-report.html):**grails dependency-report** _configuration_      
     - Plugins:
         - [create-plugin](http://docs.grails.org/latest/ref/Command%20Line/create-plugin.html):**grails create-plugin** _simple name_
         - [list-plugins](http://docs.grails.org/latest/ref/Command%20Line/list-plugins.html):**grails list-plugins**
         - [plugin-info](http://docs.grails.org/latest/ref/Command%20Line/plugin-info.html):**grails plugin-info** _name_
     - Profile
         - [create-profile](http://docs.grails.org/latest/ref/Command%20Line/create-profile.html):**grails create-profile** _simple name_
         - [list-profiles](http://docs.grails.org/latest/ref/Command%20Line/list-profiles.html):**grails list-profiles** 
              $ grails list-profiles

               Available Profiles
               -  base \- The base profile extended by other profiles
               - profile \- A profile for creating new Grails profiles
               - plugin \- Profile for plugins designed to work across all profiles               
                     - rest\-api-plugin \- Profile for REST API plugins    
                     - web\-plugin \- Profile for Plugins designed for Web applications                              
               -  angular \- A profile for creating applications using AngularJS
               -  angular2 \- A profile for creating Grails applications with Angular 2
                     - less\-asset\-pipeline;asset\-pipeline
                     - hibernate4; hibernate5; mongodb; neo4j; rx\-mongodb;
                     - json\-views; markup]\-views; 
                     - security
               -  rest-api \- Profile for REST API applications:
                     - less\-asset\-pipeline;asset\-pipeline
                     - hibernate4; hibernate5; mongodb; neo4j; rx\-mongodb;
                     - json\-views; markup]\-views; 
                     - security
               -  web \- Profile for Web applications:
                     - less\-asset\-pipeline;asset\-pipeline
                     - hibernate4; hibernate5; mongodb; neo4j; rx\-mongodb;
                     - json\-views; markup]\-views; 
               -  react \- A profile for creating Grails applications with a React frontend               
               -  webpack \- A profile for creating applications with node-based frontends using webpack
         - [profile-info](http://docs.grails.org/latest/ref/Command%20Line/profile-info.html):**grails profile-info** _name_
     - Application
         - [create-app](http://docs.grails.org/latest/ref/Command%20Line/create-app.html): **grails create-app** _simplename_ **[--profile] _PROFILE NAME_ [--features] _FEATURE NAMES_**
         - [run-app](http://docs.grails.org/latest/ref/Command%20Line/run-app.html):**grails ** _[env]_ **run-app** _[args]_
         - [stop-app](http://docs.grails.org/latest/ref/Command%20Line/stop-app.html):**grails stop-app** _[--port=9090 --host=mywebsite]_
         - [install-templates](http://docs.grails.org/latest/ref/Command%20Line/install-templates.html):**grails install-templates**
     - Controller
         - [create-controller](http://docs.grails.org/latest/ref/Command%20Line/create-controller.html): **grails create-controller** _fullname_ 
         - [generate-controller](http://docs.grails.org/latest/ref/Command%20Line/generate-controller.html):**grails generate-controller** _domain class name_ _[-Dforce]_
         - [generate-all](http://docs.grails.org/latest/ref/Command%20Line/generate-all.html):**grails generate-all** _fullname_ _[-Dforce]_
         - [generate-views](http://docs.grails.org/latest/ref/Command%20Line/generate-views.html):**grails generate-views _domain class name_
         - [create-interceptor](http://docs.grails.org/latest/ref/Command%20Line/create-interceptor.html):**grails create-interceptor** _fullname_
         - [create-taglib](http://docs.grails.org/latest/ref/Command%20Line/create-taglib.html):**grails create-taglib** _fullname_
     - Domain
         - [create-domain-class](http://docs.grails.org/latest/ref/Command%20Line/create-domain-class.html):**grails create-domain-class** _fullname_
         - [create-hibernate-cfg-xml](http://docs.grails.org/latest/ref/Command%20Line/create-hibernate-cfg-xml.html): **grails create-hibernate-cfg-xml**
         - [schema-export](http://docs.grails.org/latest/ref/Command%20Line/schema-export.html):**grails** _[environment]\*_ **schema-export** _action ['stdout'] filename [--datasource]_       
     - Service
         - [create-service](http://docs.grails.org/latest/ref/Command%20Line/create-service.html):**grails create-service** _fullname_
     - Testing
         - [create-unit-test](http://docs.grails.org/latest/ref/Command%20Line/create-unit-test.html): **grails create-unit-test** _fullname_
         - [create-functional-test](http://docs.grails.org/latest/ref/Command%20Line/create-functional-test.html): **grails create-functional-test** _fullname_
         - [create-integration-test](http://docs.grails.org/latest/ref/Command%20Line/create-integration-test.html):**grails create-integration-test** _fullname_
         - [test-app](http://docs.grails.org/latest/ref/Command%20Line/test-app.html): **grails _environment_\* test-app** _names\*_
     - Script / Command
         - [create-script](http://docs.grails.org/latest/ref/Command%20Line/create-script.html):**grails create-script** _simplename_
         - [run-script](http://docs.grails.org/latest/ref/Command%20Line/run-script.html):**grails** _[env]\*_ **run-script** _scripts_
         - [create-command](http://docs.grails.org/latest/ref/Command%20Line/create-command.html):**grails create-command** _simplename_
         - [run-command](http://docs.grails.org/latest/ref/Command%20Line/run-command.html):**grails _[env]_\* run-command** _command_   
 - [Controllers](http://docs.grails.org/latest/ref/Plug-ins/controllers.html)
     - Attributes
         - [grailsApplication](http://docs.grails.org/latest/ref/Controllers/grailsApplication.html):An instance of the GrailsApplication class
         - [controllerName](http://docs.grails.org/latest/ref/Controllers/controllerName.html):Returns the name of the currently executing controller.
         - [actionName](http://docs.grails.org/latest/ref/Controllers/actionName.html):Returns the name of the currently executing action
         - [errors](http://docs.grails.org/latest/ref/Controllers/errors.html):An instance of the Spring Errors interface containing errors associated with this controller.
         - [hasErrors]():Check if a controller has errors associated with it.
     - Settable Properties 
         - [responseFormats](http://docs.grails.org/latest/ref/Controllers/responseFormats.html):_static responseFormats = ['xml', 'json']_         
         - [scope](http://docs.grails.org/latest/ref/Controllers/scope.html):_static scope = "session" [singleton|prototype|session]_
         - [namespace](http://docs.grails.org/latest/ref/Controllers/namespace.html):_static namespace = 'reports'_
         - [allowedMethods](http://docs.grails.org/latest/ref/Controllers/allowedMethods.html):_static allowedMethods = [action1:'POST', action3:['POST', 'DELETE']]_
         - [bindData](http://docs.grails.org/latest/ref/Controllers/bindData.html):_bindData(target, params, [include: ['firstName', 'lastName']], "author")_
            - target - The target object to bind to
            - params - A Map of source parameters, often the params object when used in a controller
            - includesExcludes - (Optional) A map with 'include' and/or 'exclude' lists containing the names of properties to either include or exclude.
            - prefix - (Optional) A string representing a prefix to use to filter parameters. The method will automatically append a '.' when matching the prefix to parameters, so you can use 'author' to filter for parameters such as 'author.name'.
         - [chain](http://docs.grails.org/latest/ref/Controllers/chain.html):_chain(controller*, action, id*, model, params*)_
            - uri - The full uri to redirect to (example /book/list, book/show/2)
            - controller (optional) - The controller to redirect to; defaults to the current controller if not specified
            - namespace (optional) - the namespace of the controller to chain to
            - action - The action to redirect to, either a string name or a reference to an action within the current controller
            - id (optional) - The id to use in redirection
            - model - The model to chain to the next action
            - params (optional) - Parameters to pass to the action chained to.
         - [defaultAction](http://docs.grails.org/latest/ref/Controllers/defaultAction.html): _static defaultAction = "list"_
     - Actions
         - [forward](http://docs.grails.org/latest/ref/Controllers/forward.html):_forward action: "show", id: 4, params: [author: "Stephen King"]_
             - controller - The controller to redirect to; defaults to the current controller if not specified
             - namespace (optional) - the namespace of the controller to forward to
             - action - The action to redirect to, either a string name or a reference to an action within the current controller
             - id - The id to use in redirection
             - params - Parameters to pass to the action redirected to.
         - [redirect](http://docs.grails.org/latest/ref/Controllers/redirect.html):_redirect(controller: "book", action: "show", fragment: "profile")_
             - action (optional) - the name of the action to use in the link, if not specified the default action will be linked
             - controller (optional) - the name of the controller to use in the link, if not specified the current controller will be linked
             - namespace (optional) - the namespace of the controller to redirect to
             - plugin (optional) - the name of the plugin which provides the controller
             - id (optional) - the id to use in the link
             - fragment (optional) - The link fragment (often called anchor tag) to use
             - mapping (optional) - The named URL mapping to use to rewrite the link
             - params (optional) - a map containing request parameters
             - url (optional) - a map containing the action, controller, id etc.
             - absolute (optional) - If true will prefix the link target address with the value of the grails.serverURL property from application.groovy, or http://localhost:port; if there is no value in application.groovy and not running in the production environment.
             - base (optional) - Sets the prefix to be added to the link target address, typically an absolute server URL. This overrides the behaviour of the absolute property if both are specified.
             - permanent (optional) - If true the redirect will be issued with a 301 HTTP status code (permanently moved), otherwise a 302 HTTP status code will be issued
         - [render](http://docs.grails.org/latest/ref/Controllers/render.html):_render(view: "viewName", model: [book: theShining])_
             - text (optional) - The text to render
             - builder (optional) - The builder to use when rendering markup
             - view (optional) - The view to delegate the rendering to
             - template (optional) - The template to render. A template is usually an HTML snippet and the file starts with an underscore ("_"). This is used mostly in AJAX requests.
             - layout (optional) - The layout to use for the response
             - var (optional) - The name of the variable to be passed into a template, defaults to the Groovy default argument 'it' if not specified
             - bean (optional) - The bean to use in rendering
             - model (optional) - The model to use in rendering
             - collection (optional) - For rendering a template against each item in a collection
             - contentType (optional) - The contentType of the response
             - encoding (optional) - The encoding of the response
             - converter (as single non-named first parameter) - A Converter that should be rendered as Response
             - plugin (optional) - The plugin to look for the template in
             - status (optional) - The HTTP status code to use
             - file (optional) - The byte[], java.io.File, or inputStream you wish to send with the response
             - fileName (optional) - For specifying an attachment file name while rendering a file.         
         - [withForm](http://docs.grails.org/latest/ref/Controllers/withForm.html)
         - [withFormat](http://docs.grails.org/latest/ref/Controllers/withFormat.html):            
     - Common Parameters     
         - [params](http://docs.grails.org/latest/ref/Controllers/params.html):
         - [request](http://docs.grails.org/latest/ref/Controllers/request.html):        
         - [flash](http://docs.grails.org/latest/ref/Controllers/flash.html):
         - [respond](http://docs.grails.org/latest/ref/Controllers/respond.html):
         - [response](http://docs.grails.org/latest/ref/Controllers/response.html):
         - [servletContext](http://docs.grails.org/latest/ref/Controllers/servletContext.html):
         - [session](http://docs.grails.org/latest/ref/Controllers/session.html):        
 - [Domain Classes](http://docs.grails.org/latest/ref/Domain%20Classes/Usage.html):_grails create-domain-class org.bookstore.Book_
     - Relationship
         - [belongsTo](http://docs.grails.org/latest/ref/Domain%20Classes/belongsTo.html):_static belongsTo = [author: Author]_
         - [constraints](http://docs.grails.org/latest/ref/Domain%20Classes/constraints.html):_static constraints = { }_
         - [hasMany](http://docs.grails.org/latest/ref/Domain%20Classes/hasMany.html):_static hasMany = [books: Book]_
         - [hasOne](http://docs.grails.org/latest/ref/Domain%20Classes/hasOne.html):_static hasOne = [nose: Nose]_
         - [mapWith](http://docs.grails.org/latest/ref/Domain%20Classes/mapWith.html):_static mapWith = "none"_
         - [mappedBy](http://docs.grails.org/latest/ref/Domain%20Classes/mappedBy.html):_static mappedBy = [outgoingFlights: 'departureAirport',incomingFlights: 'destinationAirport']_
         - [mapping](http://docs.grails.org/latest/ref/Domain%20Classes/mapping.html):_static mapping = { ...}_
         - [embedded](http://docs.grails.org/latest/ref/Domain%20Classes/embedded.html):_static embedded = ['bornInCountry', 'livesInCountry']_
         - [transients](http://docs.grails.org/latest/ref/Domain%20Classes/transients.html):_static transients = ['upperCaseName']_
         - [fetchMode](http://docs.grails.org/latest/ref/Domain%20Classes/fetchMode.html):_static fetchMode = [books: 'eager']_              - CRUD 
         - [get](http://docs.grails.org/latest/ref/Domain%20Classes/get.html):_def b = Book.get(1)_
         - [load](http://docs.grails.org/latest/ref/Domain%20Classes/load.html):_def b = Book.load(1)_     
         - [delete](http://docs.grails.org/latest/ref/Domain%20Classes/delete.html):_def book = Book.get(1); book.delete()_
         - [read](http://docs.grails.org/latest/ref/Domain%20Classes/read.html):_def b = Book.read(1)_
         - [save](http://docs.grails.org/latest/ref/Domain%20Classes/save.html):_def b = new Book(title: "The Shining");b.save()_
         - [isAttached](http://docs.grails.org/latest/ref/Domain%20Classes/isAttached.html):_if (!b.isAttached()) {b.attch(); }_         
         - [attach](http://docs.grails.org/latest/ref/Domain%20Classes/attach.html):_b.attach();_
         - [isDirty](http://docs.grails.org/latest/ref/Domain%20Classes/isDirty.html):_if (b.isDirty()) {  if (b.isDirty('title')) {}}_
         - [getDirtyPropertyNames](http://docs.grails.org/latest/ref/Domain%20Classes/getDirtyPropertyNames.html):_def names = b.dirtyPropertyNames_
         - [getPersistentValue](http://docs.grails.org/latest/ref/Domain%20Classes/getPersistentValue.html):_def originalName = b.getPersistentValue('name')_
         - [discard](http://docs.grails.org/latest/ref/Domain%20Classes/discard.html):_def b = Book.get(1); b.title = "Blah"; b.discard() _
         - [exists](http://docs.grails.org/latest/ref/Domain%20Classes/exists.html):_if (Account.exists(accountId)) {}_
         - [lock](http://docs.grails.org/latest/ref/Domain%20Classes/lock.html):_def book = Book.get(1);book.lock()_
         - [merge](http://docs.grails.org/latest/ref/Domain%20Classes/merge.html):_def b = new Book(title: "The Shining");b = b.merge()_
         - [refresh](http://docs.grails.org/latest/ref/Domain%20Classes/refresh.html):_def b = Book.get(1); ...; b.refresh()_
         - [addTo](http://docs.grails.org/latest/ref/Domain%20Classes/addTo.html):_def a = new Author(name: "Stephen King").addToFiction(fictBook).addToNonFiction(nonFictBook).save()_                    
     - Operations
         - [getAll](http://docs.grails.org/latest/ref/Domain%20Classes/getAll.html):_def bookList = Book.getAll([1, 2, 3])_
         - [count](http://docs.grails.org/latest/ref/Domain%20Classes/count.html):_int bookCount = Book.count()_
         - [countBy](http://docs.grails.org/latest/ref/Domain%20Classes/countBy.html):_def c = Book.countByTitle("The Shining")_
         - [first](http://docs.grails.org/latest/ref/Domain%20Classes/first.html):_p = Person.first(sort: 'lastName')_
         - [last](http://docs.grails.org/latest/ref/Domain%20Classes/last.html):_p = Person.last('lastName')_
         - [list](http://docs.grails.org/latest/ref/Domain%20Classes/list.html):_def results = Book.list(max: 10)_
             - max - The maximum number to list
             - offset - The offset from the first result to list from
             - order - How to order the list, either "desc" or "asc"
             - sort - The property name to sort by
             - ignoreCase - Whether to ignore the case when sorting. Default is true.
             - fetch - The fetch policy for the object’s associations as a Map
             - readOnly - true if returned objects should not be automatically dirty-checked (simlar to read())
             - fetchSize - number of rows fetched by the underlying JDBC driver per round trip
             - flushMode - Hibernate FlushMode override, defaults to FlushMode.AUTO
             - timeout - query timeout in seconds     
         - [listOrderBy](http://docs.grails.org/latest/ref/Domain%20Classes/listOrderBy.html):_def results=Book.listOrderByTitle(max: 10)_
             - max - The maximum number to list
             - offset - The offset from the first result to list from
             - order - The order to list by, either "desc" or "asc"    
         - [removeFrom](http://docs.grails.org/latest/ref/Domain%20Classes/removeFrom.html):_def author = Author.findByName("Stephen King"); def book = author.books.find { it.title == 'The Stand' }; author.removeFromBooks(book)_
     - Find
         - [find](http://docs.grails.org/latest/ref/Domain%20Classes/find.html):_Book.find("from Book as b where b.author='Dan Brown'")_
             - query - An HQL query
             - positionalParams - A List of parameters for a positional parametrized HQL query
             - namedParams - A Map of named parameters a HQL query
             - queryParams - A Map of query parameters. Currently, only cache is supported
             - example - An instance of the domain class for query by example     
         - [findAll](http://docs.grails.org/latest/ref/Domain%20Classes/findAll.html):_Book.findAll("from Book as b where b.author=?", ['Dan Brown'])_
         - [findAllBy](http://docs.grails.org/latest/ref/Domain%20Classes/findAllBy.html):_results = Book.findAllByReleaseDateBetween(firstDate, new Date())_
         - [findAllWhere](http://docs.grails.org/latest/ref/Domain%20Classes/findAllWhere.html):_def books = Book.findAllWhere(author: "Stephen King", title: "The Stand")_
         - [findBy](http://docs.grails.org/latest/ref/Domain%20Classes/findBy.html):_def b = Book.findByTitle("The Shining")_
         - [findOrCreateBy](http://docs.grails.org/latest/ref/Domain%20Classes/findOrCreateBy.html):_def b = Book.findOrCreateByTitle("The Shining")_
         - [findOrCreateWhere](http://docs.grails.org/latest/ref/Domain%20Classes/findOrCreateWhere.html):_def book = Book.findOrCreateWhere(author: "Stephen King", title: "The Stand")_
         - [findOrSaveBy](http://docs.grails.org/latest/ref/Domain%20Classes/findOrSaveBy.html):_def b = Book.findOrSaveByTitleAndAuthor("The Sum of All Fears", "Tom Clancy")_
         - [findOrSaveWhere](http://docs.grails.org/latest/ref/Domain%20Classes/findOrSaveWhere.html):_def book = Book.findOrSaveWhere(author: "Stephen King", title: "The Stand")_
         - [findWhere](http://docs.grails.org/latest/ref/Domain%20Classes/findWhere.html):_def book = Book.findWhere(author: "Stephen King", title: "The Stand")_
     - Query
         - [createCriteria](http://docs.grails.org/latest/ref/Domain%20Classes/createCriteria.html):_def c = Account.createCriteria(); cxxx_
         - [executeQuery](http://docs.grails.org/latest/ref/Domain%20Classes/executeQuery.html):_ccount.executeQuery("select distinct a.number from Account a")_
             - query - An HQL query
             - positionalParams - A List of parameters for a positional parameterized query
             - namedParams - A Map of named parameters for a named parameterized query
             - metaParams - A Map of pagination parameters max or/and offset, as well as Hibernate query parameters readOnly, fetchSize, timeout, and flushMode
         - [executeUpdate](http://docs.grails.org/latest/ref/Domain%20Classes/executeUpdate.html):_Account.executeUpdate("delete Book b where b.author=?",[Author.load(1)])_
             - query - An HQL query with DML-style operations
             - positionalParams - A List of parameters for a positional parameterized HQL query
             - namedParams - A Map of parameters for a named parameterized HQL query     
         - [where](http://docs.grails.org/latest/ref/Domain%20Classes/where.html):_def query = Person.where { firstName == "Bart"};Person bart = query.find()_
         - [whereAny](http://docs.grails.org/latest/ref/Domain%20Classes/whereAny.html):_def query = Person.whereAny { firstName == "Bart"; firstName == "Lisa"}; Person bart = query.find()_
         - [namedQueries](http://docs.grails.org/latest/ref/Domain%20Classes/namedQueries.html):__         
     - Validate
         - [validate](http://docs.grails.org/latest/ref/Domain%20Classes/validate.html):_if (!b.validate()) {}_
         - [clearErrors](http://docs.grails.org/latest/ref/Domain%20Classes/clearErrors.html):_b.clearErrors()_
         - [hasErrors](http://docs.grails.org/latest/ref/Domain%20Classes/hasErrors.html):_b.validate(); if (b.hasErrors()) { }_
         - [errors](http://docs.grails.org/latest/ref/Domain%20Classes/errors.html):__
     - Misc   
         - [ident](http://docs.grails.org/latest/ref/Domain%20Classes/ident.html):_b.save(); println b.ident()_
         - [instanceOf](http://docs.grails.org/latest/ref/Domain%20Classes/instanceOf.html):_ if (child.instanceOf(Other)) {_
         - [properties](http://docs.grails.org/latest/ref/Domain%20Classes/properties.html):_def b = new Book(title: "The Shining");b.properties = params; b.save()_
         - [withCriteria](http://docs.grails.org/latest/ref/Domain%20Classes/withCriteria.html):__
         - [withNewSession](http://docs.grails.org/latest/ref/Domain%20Classes/withNewSession.html):_Book.withNewSession { session ->// do work }_
         - [withSession](http://docs.grails.org/latest/ref/Domain%20Classes/withSession.html):_Book.withSession { session ->  session.clear() }_
         - [withTransaction](http://docs.grails.org/latest/ref/Domain%20Classes/withTransaction.html):_Account.withTransaction { status ->...}_
 - [Services](http://docs.grails.org/latest/ref/Services/Usage.html):_grails create-service org.bookstore.Book_
     - [scope](http://docs.grails.org/latest/ref/Services/scope.html): _class BookService {  static scope = "session";  ... }_
         - prototype - A new service is created every time it is injected into another class
         - request - A new service will be created per request
         - flash - A new service will be created for the current and next request only
         - flow - In web flows the service will exist for the scope of the flow
         - conversation - In web flows the service will exist for the scope of the conversation. ie a root flow and its sub flows
         - session - A service is created for the scope of a user session
         - singleton (default) - Only one instance of the service ever exists
     - [Transactional](http://docs.grails.org/latest/ref/Services/transactional.html):_static transactional = true_
 - Tags: ${_expression_}, **${it}** for iterator variable
    - Flow Control
         - [if](http://docs.grails.org/latest/ref/Tags/if.html):**\<g:if test="${name == 'fred'}">...\</g:if>**
         - [else](http://docs.grails.org/latest/ref/Tags/else.html):**\<g:else>...\</g:else>**
         - [elseif](http://docs.grails.org/latest/ref/Tags/elseif.html):**\<g:elseif test="${name == 'bob'}">\</g:elseif>**
         - [unless](http://docs.grails.org/latest/ref/Tags/unless.html):**\<g:unless test="${name == 'fred'}"> Hello ${name}!\</g:unless>
         - [while](http://docs.grails.org/latest/ref/Tags/while.html):**\<g:while test="${i < 5}">...\</g:while>**
         - [each](http://docs.grails.org/latest/ref/Tags/each.html):**\<g:each in="${books}">...\</g:each>**
         - [eachError](http://docs.grails.org/latest/ref/Tags/eachError.html):**\<g:eachError bean="${book}">\</g:eachError>**
         - [grep](http://docs.grails.org/latest/ref/Tags/grep.html):**\<g:grep in="${books.title}" filter="~/.*Groovy.*/">...\</g:grep>**
         - [hasErrors](http://docs.grails.org/latest/ref/Tags/hasErrors.html):**\<g:hasErrors bean="${book}">...\</g:hasErrors>**
         - [collect](http://docs.grails.org/latest/ref/Tags/collect.html):**\<g:collect in="${books}" expr="it.title">...\</g:collect>**
         - [set](http://docs.grails.org/latest/ref/Tags/set.html):**\<g:set var="tomorrow" value="${new Date() + 1}" />**
         - [pageProperty](http://docs.grails.org/latest/ref/Tags/pageProperty.html):**\<g:pageProperty name="page.title"/>**         
         - [isAvailable](http://docs.grails.org/latest/ref/Tags/isAvailable.html):**\<plugin:isAvailable name="spring-security-core">    \</plugin:isAvailable>**
         - [isNotAvailable](http://docs.grails.org/latest/ref/Tags/isNotAvailable.html):**\<plugin:isNotAvailable name="spring-security-core">\</plugin:isNotAvailable>**      
         - [findAll](http://docs.grails.org/latest/ref/Tags/findAll.html):**\<g:findAll in="${books}" expr="it.author == 'Stephen King'">  ...\</g:findAll>**         
    - UI Element
         - [form](http://docs.grails.org/latest/ref/Tags/form.html):**\<g:form name="myForm" action="myaction" id="1">...\</g:form>**   
         - [actionSubmit](http://docs.grails.org/latest/ref/Tags/actionSubmit.html):**\<g:actionSubmit value="DeleteAll"                onclick="return confirm('Are you sure???')" />**
         - [actionSubmitImage](http://docs.grails.org/latest/ref/Tags/actionSubmitImage.html):**\<g:actionSubmitImage value="Update" action="update" src="${resource(dir: 'images', file: 'update.gif')}" />**
         - [submitButton](http://docs.grails.org/latest/ref/Tags/submitButton.html):**\<g:submitButton name="update" value="Update" />**
         - [checkBox](http://docs.grails.org/latest/ref/Tags/checkBox.html):**\<g:checkBox name="myCheckbox" value="${true}" />**
         - [radio](http://docs.grails.org/latest/ref/Tags/radio.html):**\<g:radio name="myGroup" value="2" checked="true"/>**
         - [radioGroup](http://docs.grails.org/latest/ref/Tags/radioGroup.html):**\<g:radioGroup name="myGroup" values="[1,2,3]" value="1" >...\</g:radioGroup>**
         - [field](http://docs.grails.org/latest/ref/Tags/field.html):**\<g:field type="number" name="isbn" min="5" max="10" required="" value="${bookInstance?.isbn}"/>**
         - [hiddenField ](http://docs.grails.org/latest/ref/Tags/hiddenField.html):**\<g:hiddenField name="myField" value="myValue" />**
         - [passwordField](http://docs.grails.org/latest/ref/Tags/passwordField.html):**\<g:passwordField name="myPasswordField" value="${myPassword}" />**         
         - [textField]():**\<g:textArea name="myField" value="myValue" rows="5" cols="40"/>**
         - [textArea](http://docs.grails.org/latest/ref/Tags/textArea.html):**<\g:textArea name="myField" value="myValue" rows="5" cols="40"/>**
         - [select](http://docs.grails.org/latest/ref/Tags/select.html):**\<g:select name="user.company.id" from="${Company.list()}"  value="${user?.company.id}"   optionKey="id" />**         
         - [countrySelect](http://docs.grails.org/latest/ref/Tags/countrySelect.html):**\<g:countrySelect name="user.country" value="${country}" noSelection="['':'-Choose your country-']"/>**        
         - [timeZoneSelect](http://docs.grails.org/latest/ref/Tags/timeZoneSelect.html):**\<g:timeZoneSelect name="myTimeZone" value="${tz}" />**
         - [currencySelect](http://docs.grails.org/latest/ref/Tags/currencySelect.html):**\<g:currencySelect name="myCurrency" value="${currency}" />**
         - [datePicker](http://docs.grails.org/latest/ref/Tags/datePicker.html):**\<g:datePicker name="myDate" value="${new Date()}" noSelection="['':'-Choose-']"/>**        
         - [localeSelect](http://docs.grails.org/latest/ref/Tags/localeSelect.html):**\<g:localeSelect name="myLocale" value="${locale}" />**
         - [uploadForm](http://docs.grails.org/latest/ref/Tags/uploadForm.html):**\<g:uploadForm name="myUpload">\<input type="file" name="myFile" />\</g:uploadForm>**
         - [paginate](http://docs.grails.org/latest/ref/Tags/paginate.html):**\<g:paginate controller="book" action="list" total="${bookCount}" />**
         - [render](http://docs.grails.org/latest/ref/Tags/render.html):**\<g:render template="displaybook" bean="${book}" />**
         - [renderErrors](http://docs.grails.org/latest/ref/Tags/renderErrors.html):**\<g:renderErrors bean="${book}" as="list" />**               
    - HTML element
         - [include](http://docs.grails.org/latest/ref/Tags/include.html):**\<g:include action="show" id="${currentBook.id}" />**
         - [javascript](http://docs.grails.org/latest/ref/Tags/javascript.html):**\<g:javascript src="myscript.js" />**
         - [header](http://docs.grails.org/latest/ref/Tags/header.html):**\<g:header name="Content-Type" />**
         - [img](http://docs.grails.org/latest/ref/Tags/img.html):**\<g:img dir="images" file="logo.png" width="40" height="40"/>**
         - [link](http://docs.grails.org/latest/ref/Tags/link.html):**\<g:link action="show" id="${currentBook.id}">${currentBook.name}</g:link>**     
         - [resource](http://docs.grails.org/latest/ref/Tags/resource.html):**\<g:resource dir="css" file="main.css" absolute="true" />** 
         - [layoutBody](http://docs.grails.org/latest/ref/Tags/layoutBody.html):** \<g:layoutHead />**
         - [layoutHead](http://docs.grails.org/latest/ref/Tags/layoutHead.html):**\<body>\<g:layoutBody />\</body>**
         - [layoutTitle](http://docs.grails.org/latest/ref/Tags/layoutTitle.html):**\<title>\<g:layoutTitle default="Some Title" />\</title>**
         - [applyLayout](http://docs.grails.org/latest/ref/Tags/applyLayout.html):**\<g:applyLayout name="myLayout" template="displaybook" params="[books: books]" />**
         - [message](http://docs.grails.org/latest/ref/Tags/localeSelect.html):**\<g:message error="${it}" />**
         - [meta](http://docs.grails.org/latest/ref/Tags/meta.html):**\<g:meta name="info.app.version"/>**
         - [cookie](http://docs.grails.org/latest/ref/Tags/cookie.html):**\<g:cookie name="myCookie" />**
         - [country](http://docs.grails.org/latest/ref/Tags/country.html):**\<g:country code="${user.country}"/>**
         - [createLink](http://docs.grails.org/latest/ref/Tags/createLink.html):**\<g:createLink controller="book" />**
         - [createLinkTo](http://docs.grails.org/latest/ref/Tags/createLinkTo.html):**\<g:createLinkTo dir="css" file="main.css" />**
         - [external](http://docs.grails.org/latest/ref/Tags/external.html):**\<g:external dir="css" file="main.css" />**
         - [fieldError](http://docs.grails.org/latest/ref/Tags/fieldError.html):**\<g:fieldError bean="${book}" field="title" />**
         - [fieldValue](http://docs.grails.org/latest/ref/Tags/fieldValue.html):**\<g:fieldValue bean="${book}" field="title" />**
    - Misc
         - [formatBoolean](http://docs.grails.org/latest/ref/Tags/formatBoolean.html):**\<g:formatBoolean boolean="${myBoolean}" true="True!" false="False!" />**
         - [formatDate](http://docs.grails.org/latest/ref/Tags/formatDate.html):**\<g:formatDate date="${date}" type="datetime" style="LONG" timeStyle="SHORT"/>**
         - [formatNumber](http://docs.grails.org/latest/ref/Tags/formatNumber.html):**\<g:formatNumber number="${myCurrencyAmount}" type="currency" currencyCode="EUR" />**
         - [join](http://docs.grails.org/latest/ref/Tags/join.html):**\<g:join in="['Grails', 'Groovy', 'Gradle']" delimiter="_"/>**
         - [sortableColumn](http://docs.grails.org/latest/ref/Tags/set.html):**\<g:sortableColumn property="title" title="Title" style="width: 200px" />**
 - Tag Libraries: The objects used in Tag Libraries
     - [actionName](http://docs.grails.org/latest/ref/Tag%20Libraries/actionName.html):
     - [controllerName](http://docs.grails.org/latest/ref/Tag%20Libraries/controllerName.html):
     - [flash](http://docs.grails.org/latest/ref/Tag%20Libraries/flash.html):
     - [pageScope](http://docs.grails.org/latest/ref/Tag%20Libraries/pageScope.html):
     - [params](http://docs.grails.org/latest/ref/Tag%20Libraries/params.html):
     - [request](http://docs.grails.org/latest/ref/Tag%20Libraries/request.html):
     - [response](http://docs.grails.org/latest/ref/Tag%20Libraries/response.html):
     - [servletContext](http://docs.grails.org/latest/ref/Tag%20Libraries/servletContext.html):
     - [session](http://docs.grails.org/latest/ref/Tag%20Libraries/session.html):
 - [Constraints](http://docs.grails.org/latest/ref/Constraints/Usage.html):  **static constraints = { ... }**
    - Pattern
       - [creditCard](http://docs.grails.org/latest/ref/Constraints/creditCard.html):_cardNumber creditCard: true_
       - [email](http://docs.grails.org/latest/ref/Constraints/email.html):_homeEmail email: true_
       - [url](http://docs.grails.org/latest/ref/Constraints/url.html):_homePage url: true_
       - [matches](http://docs.grails.org/latest/ref/Constraints/matches.html):_login matches: "[a-zA-Z]+"_
    - Range
       - [max](http://docs.grails.org/latest/ref/Constraints/max.html):_age max: new Date();price max: 999F_    
       - [min](http://docs.grails.org/latest/ref/Constraints/min.html):_age min: new Date();price min: 0F_
       - [inList](http://docs.grails.org/latest/ref/Constraints/inList.html):_name inList: ["Joe", "Fred", "Bob"]_
       - [range](http://docs.grails.org/latest/ref/Constraints/range.html):_age range: 18..65_
       - [notEqual](http://docs.grails.org/latest/ref/Constraints/notEqual.html):_username notEqual: "Bob"_
    - Size
       - [maxSize](http://docs.grails.org/latest/ref/Constraints/maxSize.html):_children maxSize: 25_
       - [minSize](http://docs.grails.org/latest/ref/Constraints/minSize.html):_children minSize: 25_
       - [size](http://docs.grails.org/latest/ref/Constraints/size.html):_children size: 5..15_
    - Boolean Flags
       - [bindable](http://docs.grails.org/latest/ref/Constraints/bindable.html):_salary bindable: false_
       - [blank](http://docs.grails.org/latest/ref/Constraints/blank.html):_login blank: false_
       - [nullable](http://docs.grails.org/latest/ref/Constraints/nullable.html):_age nullable: true_
       - [unique](http://docs.grails.org/latest/ref/Constraints/unique.html):_username unique: true_
    - Misc 
       - [attributes](http://docs.grails.org/latest/ref/Constraints/attributes.html): _birthDate attributes: [years: 2000..2011]_
       - [validator](http://docs.grails.org/latest/ref/Constraints/validator.html):
       - [scale](http://docs.grails.org/latest/ref/Constraints/scale.html):_salary scale: 2_
       - [widget](http://docs.grails.org/latest/ref/Constraints/widget.html):_description widget: 'textarea'_       
 - [Database Mapping](http://docs.grails.org/latest/ref/Database%20Mapping/Usage.html): **static mapping = { .... }**
    - Data Structure
       - [table](http://docs.grails.org/latest/ref/Database%20Mapping/table.html):_table "book_catalog" [name; schema; catalog]_    
       - [joinTable](http://docs.grails.org/latest/ref/Database%20Mapping/joinTable.html):_chapterPageCounts indexColumn: [name: "chapter_number", type: Integer], joinTable: [column: "page_count"]_
       - [column](http://docs.grails.org/latest/ref/Database%20Mapping/column.html):_currency column: "currency", sqlType: "char", length: 3;  [map:column; sqlType; enumType[ordinal|string]; index(string); unique(true|false); length(integer); precision(integer); scale(integer);comment (string);defaultValue(value)]_
       - [indexColumn](http://docs.grails.org/latest/ref/Database%20Mapping/indexColumn.html):_matrix indexColumn: [name: "the_matrix", type: Integer]_
       - [id](http://docs.grails.org/latest/ref/Database%20Mapping/id.html):_id generator: 'hilo',
           params: [table: 'hi_value', column: 'next_value', max_lo: 100]_
       - [discriminator](http://docs.grails.org/latest/ref/Database%20Mapping/discriminator.html):_discriminator "audio" [column; value; formula; type ]_
       - [cascade](http://docs.grails.org/latest/ref/Database%20Mapping/cascade.html):_books cascade: 'all-delete-orphan'  [all, merge, save-update, delete, lock, refresh, evict, replicate or all-delete-orphan]_       
    - Boolean Flags      
       - [dynamicInsert](http://docs.grails.org/latest/ref/Database%20Mapping/dynamicInsert.html):_dynamicInsert true_
       - [dynamicUpdate](http://docs.grails.org/latest/ref/Database%20Mapping/dynamicUpdate.html):_dynamicUpdate true_
       - [updateable](http://docs.grails.org/latest/ref/Database%20Mapping/updateable.html):_ author insertable: false_
       - [insertable](http://docs.grails.org/latest/ref/Database%20Mapping/insertable.html):_author insertable: false_       
       - [autoTimestamp](http://docs.grails.org/latest/ref/Database%20Mapping/autoTimestamp.html):_autoTimestamp false_
       - [version](http://docs.grails.org/latest/ref/Database%20Mapping/version.html):_version false_
       - [autoImport](http://docs.grails.org/latest/ref/Database%20Mapping/autoImport.html):_autoImport false_
       - [cache](http://docs.grails.org/latest/ref/Database%20Mapping/cache.html):_cache true_
       - [lazy](http://docs.grails.org/latest/ref/Database%20Mapping/lazy.html):_author lazy: false_
       - [ignoreNotFound](http://docs.grails.org/latest/ref/Database%20Mapping/ignoreNotFound.html):_thumbnail ignoreNotFound: true_
    - Misc Options
       - [batchSize](http://docs.grails.org/latest/ref/Database%20Mapping/batchSize.html):_batchSize 10_
       - [comment](http://docs.grails.org/latest/ref/Database%20Mapping/comment.html):_comment "your comment here"_
       - [fetch](http://docs.grails.org/latest/ref/Database%20Mapping/fetch.html):_books fetch: 'join' [join or select.]_
       - [order](http://docs.grails.org/latest/ref/Database%20Mapping/order.html):_order "desc" ["desc" or "asc"]_
       - [sort](http://docs.grails.org/latest/ref/Database%20Mapping/sort.html):_sort "releaseDate"_
       - [type](http://docs.grails.org/latest/ref/Database%20Mapping/type.html):_title type: "text"_    
 - [Scaffolding](http://docs.grails.org/latest/guide/scaffolding.html): Generate basic CRUD interfaces for a domain class:
     - index
     - show
     - edit
     - delete
     - create
     - save
     - update

 build.gradle:
 ```
 dependencies {
        // ...
        compile "org.grails.plugins:scaffolding"
        // ...
    }
 ```
 For Controller:
 ```
 class BookController {
      static scaffold = true
    or
      static scaffold = Book
}
 ```
 To generate a controller type:
 ```
grails generate-controller Book
```
 To generate the views:
```
grails generate-views Book
```
 To generate everything:
```
grails generate-all Book
```
 - Servlet API
    - [request](http://docs.grails.org/latest/ref/Servlet%20API/request.html): The **_request_** object is an instance of the Grails enhanced HttpServletRequest instance by adding the following new properties and methods:
       - XML - An instance of `XmlSlurper’s GPathResult class that allows parsing of an incoming XML request (useful for REST)
       - JSON - An instance of Grails' JSONObject class that allows parsing of an incoming JSON request (useful for JSON based REST)
       - forwardURI - Useful for obtaining the current request URI since the request object’s requestURI property returns the original URI, not the matched one
       - isRedirected() - Returns true if a redirect has been issued for this request 
       - get - Returns true if the current request is an HTTP GET request
       - post - Returns true if the current request is an HTTP POST request
       - each - Implementation of Groovy’s each method for iterating over request attributes
       - find - Implementation of Groovy’s default find method for searching request attributes
       - findAll - Implementation of Groovy’s default findAll method for searching request attributes
       - format - The request format, used for Content Negotiation
       - withFormat(Closure) - The withFormat method, used for Content Negotiation
       - xhr - Returns true if the current request is an Ajax request    
    - [response](http://docs.grails.org/latest/ref/Servlet%20API/response.html):The **_response**_ object is an instance of the Servlet API’s HttpServletResponse class:
       - format - The request format, used for Content Negotiation.
       - withFormat(Closure) - The withFormat method, used for Content Negotiation.
       - Grails also overrides the left shift operator on the response object making it easier to write to the response writer:       
            response << "Hello World"            
    - [servletContext]():The **_ervletContext_** object is an instance of the Servlet API’s ServletContext class.
    - [session]():The **_session_** object is an instance of the Servlet API’s HttpSession class
    
 - [Plug-ins](http://docs.grails.org/latest/ref/Plug-ins/Usage.html): **grails create-plugin simple; grails package-plugin; grails install**
    - [core](http://docs.grails.org/latest/ref/Plug-ins/core.html):The core plugin adds methods and beans that other plugins rely upon
    - [URL mappings](http://docs.grails.org/latest/ref/Plug-ins/URL%20mappings.html):The URLMappings plugin configures Grails' URL Mapping infrastructure.
        - grailsUrlMappingsHolderBean - A UrlMappingsHolderFactoryBean factory bean that constructs a grails.web.mapping.UrlMappingsHolder instance that stores all of the URL mappings.
        - urlMappingsTargetSource - A Spring HotSwappableTargetSource used in auto-reloading to automatically update URL mappings when changed.
        - grailsUrlMappingsHolder - A Spring ProxyFactoryBean that proxies onto the actual UrlMappingsHolder instance using the HotSwappableTargetSource
    - [codecs](http://docs.grails.org/latest/ref/Plug-ins/codecs.html): Provides the facility to register encoders and decoders of textual data as methods on any object. The provided Codecs are:
        - HTMLCodec - encodes/decodes HTML mark-up
        - URLCodec - encodes/decodes URLs
        - JavascriptCodec - encodes (escapes) JavaScript
        - Base64Codec - encodes/decodes Base64 data
        - HexCodec - encodes a byte array or list of integers into a hex string, and decodes hex strings into byte array
        - MD5Codec - encodes a byte array or list of integers, or the characters of a string (using default system encoding) into an MD5 digest as a hex string
        - MD5BytesCodec - encodes a byte array or list of integers, or the characters of a string (using default system encoding) into an MD5 digest as a byte array
        - SHA1Codec - encodes a byte array or list of integers, or the characters of a string (using default system encoding) into an SHA1 digest as a hex string
        - SHA1BytesCodec - encodes a byte array or list of integers, or the characters of a string (using default system encoding) into an SHA1 digest as a byte array
        - SHA256Codec - encodes a byte array or list of integers, or the characters of a string (using default system encoding) into an SHA256 digest as a hex string
        - SHA256BytesCodec - encodes byte array or list of integers, or the characters of a string (using default system encoding) into an SHA256 digest as a byte array    
    - [dataSource](http://docs.grails.org/latest/ref/Plug-ins/dataSource.html):The dataSource plugin configures the Grails JDBC DataSource.
    - [hibernate]():The hibernate plugin configures the Hibernate implementation of GORM.
    - [i18n](http://docs.grails.org/latest/ref/Plug-ins/i18n.html):The i18n plugin configures Grails' support for Internationalization.
    - [logging](http://docs.grails.org/latest/ref/Plug-ins/logging.html):The logging plugin configures Grails' support for Logging with logback.
    - [scaffolding](http://docs.grails.org/latest/ref/Plug-ins/scaffolding.html):The scaffolding plugin configures Grails' support for CRUD via scaffolding.
    - [controllers](http://docs.grails.org/latest/ref/Plug-ins/controllers.html):A plugin that configures core Grails MVC architecture using the underlying Spring MVC component model
    - [domainClasses](http://docs.grails.org/latest/ref/Plug-ins/domainClasses.html):The domainClass plugin configures Grails domain classes as prototyped beans in the Spring ApplicationContext
    - [services](http://docs.grails.org/latest/ref/Plug-ins/services.html):The services plugin configures Grails' support for Services.
    - [servlets](http://docs.grails.org/latest/ref/Plug-ins/servlets.html):The servlets plugin enhances Servlet API classes with new methods
    


