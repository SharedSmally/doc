# SQL

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
