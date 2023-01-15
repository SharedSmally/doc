# SQL
- [Tutorial](https://www.w3schools.com/sql/default.asp)

##
```
SELECT column1, column2, ... FROM table_name; 
SELECT * FROM table_name; 
SELECT DISTINCT column1, column2, ... FROM table_name; 
SELECT column1, column2, ... FROM table_name WHERE condition;   //The WHERE clause can be combined with AND, OR, and NOT operators.
SELECT column1, column2, ... FROM table_name WHERE condition1 AND condition2 AND condition3 ...; 
SELECT column1, column2, ... FROM table_name WHERE condition1 OR condition2 OR condition3 ...; 
SELECT column1, column2, ... FROM table_name WHERE NOT condition; 
SELECT * FROM Customers WHERE Country='Germany' AND (City='Berlin' OR City='München'); 
SELECT column1, column2, ... FROM table_name ORDER BY column1, column2, ... ASC|DESC; 
SELECT * FROM Customers ORDER BY Country ASC, CustomerName DESC; 
SELECT column_names FROM table_name WHERE column_name IS NULL; 
SELECT column_names FROM table_name WHERE column_name IS NOT NULL; 

INSERT INTO table_name (column1, column2, column3, ...) VALUES (value1, value2, value3, ...); 
INSERT INTO table_name VALUES (value1, value2, value3, ...); 

UPDATE table_name SET column1 = value1, column2 = value2, ... WHERE condition; 

DELETE FROM table_name WHERE condition;

SELECT TOP number|percent column_name(s) FROM table_name WHERE condition; 

SELECT OP(column_name) FROM table_name WHERE condition;  OP: MIN,MAX,COUNT,AVG,SUM

SELECT column1, column2, ... FROM table_name WHERE columnN LIKE pattern;  //
There are two wildcards often used in conjunction with the LIKE operator:
     The percent sign (%) represents zero, one, or multiple characters
     The underscore sign (_) represents one, single character

SELECT column_name(s) FROM table_name WHERE column_name IN (value1, value2, ...);
SELECT column_name(s) FROM table_name WHERE column_name IN (SELECT STATEMENT); 
SELECT column_name(s) FROM table_name WHERE column_name BETWEEN value1 AND value2; 
     The BETWEEN operator is inclusive: begin and end values are included. 

SELECT column_name AS alias_name FROM table_name;
SELECT column_name(s) FROM table_name AS alias_name;

SELECT column_name(s) FROM table1 UNION SELECT column_name(s) FROM table2; 
SELECT column_name(s) FROM table1 UNION ALL SELECT column_name(s) FROM table2;   can have WHERE
The UNION operator is used to combine the result-set of two or more SELECT statements.
    Every SELECT statement within UNION must have the same number of columns
    The columns must also have similar data types
    The columns in every SELECT statement must also be in the same order

SELECT column_name(s) FROM table_name WHERE condition GROUP BY column_name(s) ORDER BY column_name(s); //

```
## [Join](https://www.geeksforgeeks.org/sql-join-set-1-inner-left-right-and-full-joins/)
- Inner Join: the common parts from left and right tables: n = common(n1, n2), no null items 
- Left Join: all from left table, right table items are null if not found in right table
- Right Join: all from right table, left table items are null if not found in left table 
- Outer Join: all from left and right tables: item is null if not found in another table
```
SELECT table1.column1,table1.column2,table2.column1,....
FROM table1 INNER JOIN table2
ON table1.matching_column = table2.matching_column;

SELECT table1.column1,table1.column2,table2.column1,....
FROM table1 LEFT JOIN table2
ON table1.matching_column = table2.matching_column;

SELECT table1.column1,table1.column2,table2.column1,....
FROM table1 RIGHT JOIN table2
ON table1.matching_column = table2.matching_column;

SELECT table1.column1,table1.column2,table2.column1,....
FROM table1 FULL JOIN table2
ON table1.matching_column = table2.matching_column;
```

## Union
Combine two separate select statements and produce the result set as a union of both the select statements:
```
SELECT column_name(s) FROM table1 UNION SELECT column_name(s) FROM table2;     // Resultant set consists of distinct values.
SELECT column_name(s) FROM table1 UNION ALL SELECT column_name(s) FROM table2; // Resultant set consists of duplicate values too.
```
