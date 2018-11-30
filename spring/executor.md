# Executor/Scheduling

## 1. Task Executor

Spring provides the [TaskExecutor](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/core/task/TaskExecutor.html) as an abstraction in [core.task](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/core/task/package-summary.html) for dealing with executors.

### Define TaskExecutor bean
```
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.core.task.TaskExecutor;
import org.springframework.scheduling.concurrent.ThreadPoolTaskExecutor;
import java.util.concurrent.Executor;

@Configuration
public class ThreadConfig {
    @Bean
    public TaskExecutor threadPoolTaskExecutor() {
        ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();
        executor.setCorePoolSize(4);
        executor.setMaxPoolSize(4);
        executor.setThreadNamePrefix("default_task_executor_thread");
        executor.initialize();
        return executor;
    }
}
```
### Define Task
```
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

@Component
@Scope("prototype")
public class MyTask implements Runnable {
    private static final Logger LOGGER = LoggerFactory.getLogger(MyTask.class);
    
    @Override
    public void run() {
        LOGGER.info("Called for MyTask");
    }
}
```

### Use TaskExecutor
```
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.ApplicationContext;
import org.springframework.core.task.TaskExecutor;
import org.springframework.stereotype.Service;
import java.util.List;

@Service
public class AppService {
    @Autowired
    private TaskExecutor taskExecutor;

    @Autowired
    private ApplicationContext applicationContext;
       
    public void execute () {
        taskExecutor.execute(new Runnable() {
            @Override
            public void run() {
                //TODO add long running task
            }
        });
        Runnable task = applicationContext.getBean(MyTask.class);
        taskExecutor.execute(
    }
}
```


## 2. Async
Execute function in another thread, just to annotate the functions with the @Async annotation:

#### Mode 1: fire and forget mode: a method returns a void type
```
@Async
@Transactional
public void printEmployees() {
   .......
}
```

### Mode 2: A results retrieval mode: a method which returns a future type.
```
@Async
@Transactional
public CompletableFuture<List<Employee>> fetchEmployess() {
    List<Employee> employees = entityManager.createQuery("SELECT e FROM Employee e").getResultList();
    return CompletableFuture.completedFuture(employees);
}
```

### Enable async capability for the Executor
Need to enable Spring’s asynchronous method execution capability by using the @EnableAsync annotation in the configuration classes.
```
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.core.task.TaskExecutor;
import org.springframework.scheduling.concurrent.ThreadPoolTaskExecutor;
 
import java.util.concurrent.Executor;

@Configuration
@EnableAsync
public class ThreadConfig {
    @Bean
    public TaskExecutor threadPoolTaskExecutor() {
        ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();
        executor.setCorePoolSize(4);
        executor.setMaxPoolSize(4);
        executor.setThreadNamePrefix("sgfgd");
        executor.initialize();
        return executor;
    }
}
```

### For specific Async Executor
```
@Configuration
@EnableAsync
public class ThreadConfig {
    @Bean(name = "specificTaskExecutor")
    public TaskExecutor specificTaskExecutor() {
        ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();
        executor.initialize();
        return executor;
    }
}
```
```
@Async("specificTaskExecutor")
public void runFromAnotherThreadPool() {
    System.out.println("You function code here");
}
```

## 3. [Transactions](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/transaction/annotation/Transactional.html)
Transaction information in spring is stored in ThreadLocal variables. These variables are specific for an ongoing transaction on a single thread. The transactions cannot be passed from thread to thread. In case of a @Transactional  annotated service spawns a thread, the transaction will not be propagated from the @Transactional service to the newly created thread. The result will be an error indicating that the transaction is missing. Therefore by annotating a method with the @Transactional, a new transaction will be created and will be propagated to the other services called from our thread. Make sure that your @Async and @Transactional functions are public and go though the proxy that will make the necessary actions before being invoked.


## 4. [Scheduling](https://spring.io/guides/gs/scheduling-tasks/)
- Use [TaskScheduler](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/scheduling/TaskScheduler.html) with a variety of methods for scheduling tasks to run at some point in the future. 
- Use Spring’s [@Scheduled](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/scheduling/annotation/Scheduled.html) annotation.
### Create Schduled Task
```
import java.text.SimpleDateFormat;
import java.util.Date;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

@Component
public class ScheduledTasks {
    private static final Logger log = LoggerFactory.getLogger(ScheduledTasks.class);
    private static final SimpleDateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");

    @Scheduled(fixedRate = 5000)
    public void reportCurrentTime() {
        log.info("The time is now {}", dateFormat.format(new Date()));
    }
}
```

### Enable Schduling
```
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.scheduling.annotation.EnableScheduling;

@SpringBootApplication
@EnableScheduling
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class);
    }
}
```
