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
 - Tag Libraries  
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
       - [range](http://docs.grails.org/latest/ref/Constraints/range.html):_http://docs.grails.org/latest/ref/Constraints/range.html_
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
 - Database Mapping
 - Tags
 - Servlet API
 
## [API]()
## [Plugins]()


