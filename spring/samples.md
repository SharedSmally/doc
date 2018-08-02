## Spring JPA
- Entity: the database table, the model 
- Validator: validate the data to provision the database
- Repository: provide functions to handle entities (querying), such as findOne, findAll,...
- Service: provide service interface, which may use repository 
- Viewer: provide UI to use the service/database, the frond-end of the web application
- Controller: the back-end of the web application, may use service for the work to provide model for the viewer that will be shown.
- Web Application:

## [J2EE Entity](https://docs.oracle.com/javaee/6/tutorial/doc/bnbpz.html)

## [Entity Inheritance](https://docs.oracle.com/javaee/6/tutorial/doc/bnbqn.html)
Entities support class inheritance, polymorphic associations, and polymorphic queries. Entity classes can extend non-entity classes, and non-entity classes can extend entity classes. Entity classes can be both abstract and concrete.
### Abstract Entities
- An abstract class may be declared an entity by decorating the class with @Entity. Abstract entities are like concrete entities but cannot be instantiated. 
- Abstract entities can be queried just like concrete entities. If an abstract entity is the target of a query, the query operates on all the concrete subclasses of the abstract entity:
```
@Entity
public abstract class Employee {
    @Id
    protected Integer employeeId;
    ...
}
@Entity
public class FullTimeEmployee extends Employee {
    protected Integer salary;
    ...
}
@Entity
public class PartTimeEmployee extends Employee {
    protected Float hourlyWage;
}
```
### Mapped Superclasses [javax.persistence.MappedSuperclass]
- Entities may inherit from superclasses that contain persistent state and mapping information but are not entities: the superclass is not decorated with the @Entity annotation and is not mapped as an entity by the Java Persistence provider. 
- These superclasses are most often used when have state and mapping information common to multiple entity classes.
- Mapped superclasses cannot be queried and can’t be used in EntityManager or Query operations. 
- Mapped superclasses can’t be targets of entity relationships. Mapped superclasses can be abstract or concrete.
- Mapped superclasses do not have any corresponding tables in the underlying datastore.
```
@MappedSuperclass
public class Employee {
    @Id
    protected Integer employeeId;
    ...
}
@Entity
public class FullTimeEmployee extends Employee {
    protected Integer salary;
    ...
}
@Entity
public class PartTimeEmployee extends Employee {
    protected Float hourlyWage;
    ...
}
```
### Non-Entity Superclasses
- Entities may have non-entity superclasses, and these superclasses can be either abstract or concrete.
- The state of non-entity superclasses is nonpersistent, and any state inherited from the non-entity superclass by an entity class is nonpersistent. 
- Non-entity superclasses may not be used in EntityManager or Query operations. 
- Any mapping or relationship annotations in non-entity superclasses are ignored.

### Entity Inheritance Mapping Strategies
Decorating the root class of the hierarchy with javax.persistence.Inheritance.

The Entity inheritance mapping strategies:
- A single table per class hierarchy. Needs @DiscriminatorColumn containing a value to identify the subclass
- A table per concrete entity class
- A “join” strategy, whereby fields or properties that are specific to a subclass are mapped to a different table than the fields or properties that are common to the parent class
```
public enum InheritanceType {
    SINGLE_TABLE,   # default
    JOINED,
    TABLE_PER_CLASS
};
```

## [spring-security-sample](https://hellokoding.com/registration-and-login-example-with-spring-security-spring-boot-spring-data-jpa-hsql-jsp/)
