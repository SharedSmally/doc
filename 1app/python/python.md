# Python
- [Python](https://www.python.org/): Original impl is cpython.
- [Doc 3](https://docs.python.org/3/)
    - [Language Reference](https://docs.python.org/3/reference/index.html)
    - [Standard Library Reference](https://docs.python.org/3/library/index.html)
    - [Python/C API](https://docs.python.org/3/c-api/index.html)

## Modules

## Python 2/3 (not compatibility)
|Item |	Python 2 |	Python 3 |
|-----|----------|-----------|
|Year of Release | 2000-2020 |	2008- |
|Print Keyword |	considered to be a statement and not a function. | considered to be a function and not a statement |
|Storage of Strings	| stored as ASCII by default | stored as UNICODE by default.|
|Division of Integers	| get an interger on the division of two integers | get a floating-point value on the division of two integers|
|Exceptions	| exceptions are enclosed in notations.| exceptions are enclosed in parentheses.|
|Variable leakage |	The values of global variables do change if used inside a for-loop. | The value of variables never changes |
| Iteration |xrange() function has been defined for iterations| the new Range() function was introduced to perform iterations.|
|Ease of Syntax	| more complicated syntax | an easier syntax |
|Libraries |are not forward compatible | strictly used with Python 3. |
|Application |	DevOps Engineer | Software Engineering, Data Science, etc.|

```
def main():
  print ("Hi! This is Python 3")
  //print "Hi! This is Python 2"
  
if __name__== "__main__":
  main()
```


