# Liquibase: [https://www.liquibase.org/](https://www.liquibase.org/)
- Download liquidbase, and lib/ needs to have the following jars (for postgresql):
```
logback-classic-1.2.3.jar 
logback-core-1.2.3.jar
slf4j-api-1.7.25.jar  
snakeyaml-1.18.jar
postgresql-9.2-1004.jdbc4.jar  
```

- Edit the changelog.xml
```
<?xml version="1.0" encoding="UTF-8"?>
<databaseChangeLog
  xmlns="http://www.liquibase.org/xml/ns/dbchangelog"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://www.liquibase.org/xml/ns/dbchangelog
         http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.1.xsd">
    <changeSet id="1" author="bob">
        <createTable tableName="department">
            <column name="id" type="int">
                <constraints primaryKey="true" nullable="false"/>
            </column>
            <column name="name" type="varchar(50)">
                <constraints nullable="false"/>
            </column>
            <column name="active" type="boolean" defaultValueBoolean="true"/>
        </createTable>
    </changeSet>
</databaseChangeLog>
```

- Update the database table:
```
./liquibase --driver=org.postgresql.Driver 
    --classpath=./lib --changeLogFile=db.xml 
    --url="jdbc:postgresql://192.168.250.11/wchendb" 
    --username=wchen --password=wchen update
```
```
liquibase.sh --driver=oracle.jdbc.OracleDriver \
        --url=jdbc:oracle:thin:@testdb:1521:test \
        --username=bob \
        --password=bob \
        --changeLogFile=path/to/changelog.xml \
        dbDoc /docs/dbdoc
```
The available commands in [command line](https://www.liquibase.org/documentation/command_line.html) are:   
   - [Update](https://www.liquibase.org/documentation/update.html)
   - [Rollback](https://www.liquibase.org/documentation/rollback.html)
   - [Diff](https://www.liquibase.org/documentation/diff.html)
   - [SQL Output](https://www.liquibase.org/documentation/sql_output.html)
   - [DBDoc](https://www.liquibase.org/documentation/dbdoc.html)

