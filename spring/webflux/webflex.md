# Spring WebFlux

## [Use Reactive DAO Respository](https://howtodoinjava.com/spring-webflux/spring-webflux-tutorial/)
- Application
```
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
 
@SpringBootApplication
public class WebfluxFunctionalApp {
 
    public static void main(String[] args) {
        SpringApplication.run(WebfluxFunctionalApp.class, args);
    }
}
```
- REST Controller
```
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;
 
import com.howtodoinjava.demo.model.Employee;
import com.howtodoinjava.demo.service.EmployeeService;
 
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;
 
@RestController
public class EmployeeController {
    @Autowired
    private EmployeeService employeeService;
 
    @RequestMapping(value = { "/create", "/" }, method = RequestMethod.POST)
    @ResponseStatus(HttpStatus.CREATED)
    public void create(@RequestBody Employee e) {
        employeeService.create(e);
    }
 
    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public ResponseEntity<Mono<Employee>> findById(@PathVariable("id") Integer id) {
        Mono<Employee> e = employeeService.findById(id);
        HttpStatus status = e != null ? HttpStatus.OK : HttpStatus.NOT_FOUND;
        return new ResponseEntity<Mono<Employee>>(e, status);
    }
 
    @RequestMapping(value = "/name/{name}", method = RequestMethod.GET)
    public Flux<Employee> findByName(@PathVariable("name") String name) {
        return employeeService.findByName(name);
    }
 
    @RequestMapping(method = RequestMethod.GET, produces = MediaType.TEXT_EVENT_STREAM_VALUE)
    public Flux<Employee> findAll() {
        Flux<Employee> emps = employeeService.findAll();
        return emps;
    }
 
    @RequestMapping(value = "/update", method = RequestMethod.PUT)
    @ResponseStatus(HttpStatus.OK)
    public Mono<Employee> update(@RequestBody Employee e) {
        return employeeService.update(e);
    }
 
    @RequestMapping(value = "/delete/{id}", method = RequestMethod.DELETE)
    @ResponseStatus(HttpStatus.OK)
    public void delete(@PathVariable("id") Integer id) {
        employeeService.delete(id).subscribe();
    }
}
```

- Service
```
import com.howtodoinjava.demo.model.Employee;
 
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;
 
public interface IEmployeeService 
{
    void create(Employee e);     
    Mono<Employee> findById(Integer id);
    Flux<Employee> findByName(String name);
    Flux<Employee> findAll();
    Mono<Employee> update(Employee e); 
    Mono<Void> delete(Integer id);
}

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
 
import com.howtodoinjava.demo.dao.EmployeeRepository;
import com.howtodoinjava.demo.model.Employee;
 
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;
 
@Service
public class EmployeeService implements IEmployeeService {     
    @Autowired
    EmployeeRepository employeeRepo;
 
    public void create(Employee e) {
        employeeRepo.save(e).subscribe();
    }
 
    public Mono<Employee> findById(Integer id) {
        return employeeRepo.findById(id);
    }
 
    public Flux<Employee> findByName(String name) {
        return employeeRepo.findByName(name);
    }
 
    public Flux<Employee> findAll() {
        return employeeRepo.findAll();
    }
 
    public Mono<Employee> update(Employee e) {
        return employeeRepo.save(e);
    }
 
    public Mono<Void> delete(Integer id) {
        return employeeRepo.deleteById(id);
    } 
}
```

- DAO repository
```
import org.springframework.data.mongodb.repository.Query;
import org.springframework.data.mongodb.repository.ReactiveMongoRepository;
 
import com.howtodoinjava.demo.model.Employee;
 
import reactor.core.publisher.Flux;
 
public interface EmployeeRepository extends ReactiveMongoRepository<Employee, Integer> {
    @Query("{ 'name': ?0 }")
    Flux<Employee> findByName(final String name);
}
```
- Model
```
import org.springframework.context.annotation.Scope;
import org.springframework.context.annotation.ScopedProxyMode;
import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;
 
@Scope(scopeName = "request", proxyMode = ScopedProxyMode.TARGET_CLASS)
@Document
public class Employee {
    @Id
    int id;
    String name;
    long salary;
 
    //Getters and setters
    @Override
    public String toString() {
        return "Employee [id=" + id + ", name=" + name + ", salary=" + salary + "]";
    }
}
```
