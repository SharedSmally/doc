#[Spring Boot](https://spring.io/projects/spring-boot)
Auto Config for the basic services

## Spring Boot CLI
- Install sdkman
```
$ curl -s "https://get.sdkman.io" | bash
$ source "$HOME/.sdkman/bin/sdkman-init.sh"
$ sdk version
$ sdk help
$ sdk list
```
- Install Spring Boot CLI
```
$ sdk install springboot
$ spring version
$ sdk ls springboot
$ spring help
```
- Simple Spring Boot App
app.groovy
```
@RestController
class ThisWillActuallyRun {    
    @RequestMapping("/")    
    String home() {       
        "Hello World!"    
    }
}
```
Run application
```
$spring run app.groovy
```

