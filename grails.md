[grails](http://www.grails.org/)
=======

## [User Guide](http://docs.grails.org/latest/guide/single.html)
## [Quick Reference] ()
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
        
 - Plug-ins
 - Controllers
 - Domain Classes
 - Services
 - Tags
 
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

 - [Tag Libraries](http://docs.grails.org/latest/ref/Tag%20Libraries/Usage.html)  
    - [actionName]():
    - [controllerName]():
    - [flash]():
    - [pageScope]():
    - [params]():
    
    - Servlet API Info
       - [request]():
       - [response]():
       - [servletContext]():
       - [session]():
    
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
    

## [API]()
## [Plugins]()


