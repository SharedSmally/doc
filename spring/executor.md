# Executor

Spring provides the TaskExecutor as an abstraction for dealing with executors.

## Define TaskExecutor bean
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

## Define Task
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

## Use TaskExecutor
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

