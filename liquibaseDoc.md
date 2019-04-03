#[liquibase](https://www.liquibase.org/)
- [Documentation](https://www.liquibase.org/documentation/index.html)
- [cli](https://www.liquibase.org/documentation/command_line.html)
   ```
     liquibase [options] [command] [command parameters]
   ```
   Commands:
   - Database Update Commands: update/updateCount: updateSQL/updateCountSQL:
   - Database Rollback Commands: rollback/rollbackToxxx
   - Diff Commands: diff
   - Maintenance Commands: tag, status, validate,...
   
- [databaseChangeLog xsd](http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.1.xsd)
   - [preConditions](https://www.liquibase.org/documentation/preconditions.html): 	Pre-conditions required to execute the change log.
   - [propert](https://www.liquibase.org/documentation/changelog_parameters.html):	Value to set property to, if not set by another means. 
   - [changeSet](https://www.liquibase.org/documentation/changeset.html):	The change sets to execute. 
   - [include](https://www.liquibase.org/documentation/include.html)	Additional files containing change sets to execute. 
```
<?xml version="1.0" encoding="UTF-8"?>
<databaseChangeLog
        xmlns="http://www.liquibase.org/xml/ns/dbchangelog"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xmlns:ext="http://www.liquibase.org/xml/ns/dbchangelog-ext"
        xsi:schemaLocation="http://www.liquibase.org/xml/ns/dbchangelog http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.0.xsd
        http://www.liquibase.org/xml/ns/dbchangelog-ext http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-ext.xsd">

    <preConditions>
        <runningAs username="liquibase"/>
    </preConditions>

    <changeSet id="1" author="nvoxland">
        <createTable tableName="person">
            <column name="id" type="int" autoIncrement="true">
                <constraints primaryKey="true" nullable="false"/>
            </column>
            <column name="firstname" type="varchar(50)"/>
            <column name="lastname" type="varchar(50)">
                <constraints nullable="false"/>
            </column>
            <column name="state" type="char(2)"/>
        </createTable>
    </changeSet>

    <changeSet id="2" author="nvoxland">
        <addColumn tableName="person">
            <column name="username" type="varchar(8)"/>
        </addColumn>
    </changeSet>
    <changeSet id="3" author="nvoxland">
        <addLookupTable
            existingTableName="person" existingColumnName="state"
            newTableName="state" newColumnName="id" newColumnDataType="char(2)"/>
    </changeSet>

</databaseChangeLog>
```
