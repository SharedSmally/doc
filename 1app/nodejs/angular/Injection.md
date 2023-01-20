# Dependency Injection
Inject a new instance of a service into the the consumer of the services, such as component, pipe, directive, services, etc.
Consumers( decorated by @Injectable()) declare the dependencies that they need in their constructor. Injector reads the 
dependencies from the constructor of the Consumer. No need for  @Component, @pipe or @directive etc. for they are the subtype of Injectible.
