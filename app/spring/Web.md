# Spring Web 
- Web Service
- REST Web Service
- WebSocket

## Web Application Layout
- com.cainet.xxx.web
     - WebApp.java: @ComponentScan will scan @Component, including @Repository,@Service,@Controller,@RestController for the given packages, and create @Bean for each class, default is for local and sub-packages
     - com.cainet.xxx.web.config
         - XxxConfig.java: @Configuration with @Bean
     - com.cainet.xxx.web.model
         - XxxPOJO.java (@Entity)
     - com.cainet.xxx.web.repository
         - XxxRepository.java: For Data access for model(one) 
     - com.cainet.xxx.web.service
         - XxxService.java: use Repository to access data 
     - com.cainet.xxx.web.controller
         - XxxController.java: use @AutoWired services 
         - @Controller: return xxx.html template file
  
  ## Component Annotations
  - @Configuration
  - @Bean
  - @Component
  - @Repository
  - @Service
  - @Controller
  - @RestController
  - @AutoWired
  - @ComponentScan
  - @EnableAutoConfig
  - @SpringBootApplication
  

  ## Web Controller Annotations
  - @Controller
  - @RestController
  - @
  -
  ## Web Security
  
