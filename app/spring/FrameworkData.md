# [Data Access](https://docs.spring.io/spring-framework/docs/current/reference/html/data-access.html)
- Transactions
- DAO support
- JDBC
- ORM
- Marshalling XML


## Transactions
- use @Transactional at class or method level
```
public class TransactionalService {
    @Transactional("order")
    public void setSomething(String name) { ... }

    @Transactional("account")
    public void doSomething() { ... }

    @Transactional("reactive-account")
    public Mono<Void> doSomethingReactive() { ... }
}
```
- Use TransactionTemplate
```
public class SimpleService implements Service {
    // single TransactionTemplate shared amongst all methods in this instance
    private final TransactionTemplate transactionTemplate;

    // use constructor-injection to supply the PlatformTransactionManager
    public SimpleService(PlatformTransactionManager transactionManager) {
        this.transactionTemplate = new TransactionTemplate(transactionManager);
    }

    public Object someServiceMethod() {
        return transactionTemplate.execute(new TransactionCallback() {
            // the code in this method runs in a transactional context
            public Object doInTransaction(TransactionStatus status) {
                updateOperation1();
                return resultOfUpdateOperation2();
            }
        });
    }
}
```
TransactionTemplate setup:
```
public class SimpleService implements Service {
    private final TransactionTemplate transactionTemplate;

    public SimpleService(PlatformTransactionManager transactionManager) {
        this.transactionTemplate = new TransactionTemplate(transactionManager);

        // the transaction settings can be set here explicitly if so desired
        this.transactionTemplate.setIsolationLevel(TransactionDefinition.ISOLATION_READ_UNCOMMITTED);
        this.transactionTemplate.setTimeout(30); // 30 seconds
        // and so forth...
    }
}
```
- Using the TransactionOperator for Reactive
```
public class SimpleService implements Service {
    // single TransactionOperator shared amongst all methods in this instance
    private final TransactionalOperator transactionalOperator;

    // use constructor-injection to supply the ReactiveTransactionManager
    public SimpleService(ReactiveTransactionManager transactionManager) {
        this.transactionOperator = TransactionalOperator.create(transactionManager);
    }

    public Mono<Object> someServiceMethod() {
        // the code in this method runs in a transactional context
        Mono<Object> update = updateOperation1();
        return update.then(resultOfUpdateOperation2).as(transactionalOperator::transactional);
    }
}
```
### DAO support

### JDBC

### ORM

### Marshalling XML


