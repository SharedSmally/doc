# Executor (ThreadGroup) - Scheduler

## Task
- Runnable: void run()
- Task: 
    - state: init,waiting,running,cancelled,complete
    - cancel()
- Timer:  single; timeout
    - Repeater: initial; interval; maxCount;
        - CronJob
- Job

## BlockQueue

## ThreadPool
- exec(Runnable)

## Executor
- exec(Task)

## Scheduler
- schedule(Timer)
- schedule(Task, TimePoint)
- schedule(Task, Duration)


