# docker Applications

In Windows, run Kitematic

## [postgres docker](https://hub.docker.com/_/postgres)
- list running container for postgresql
```
> docker container ls
CONTAINER_ID ... NAME
xxx              postgresql
```
- login postgresql server (wchen/wchendb)
```
> docker exec -it postgres /bin/bash
# su - postgres
> psql 
#
    CREATE USER docker PASSWORD 'docker';
    CREATE DATABASE dockerdb;
    GRANT ALL PRIVILEGES ON DATABASE dockerdb TO docker;
# exit
```
- access postgres
```
 docker exec -it postgres psql -h localhost -d dockerdb -U docker -W
```
- exec sql file
```
> echo 'CREATE TABLE IF NOT EXISTS myschema.mytable (i integer);' > table.sql
> vi table.sql
CREATE TABLE IF NOT EXISTS mytable (i integer);
INSERT INTO mytable ( i ) VALUES ( 10 );
SELECT * from mytable;
> docker cp table.sql postgres:/tmp/table.sql
> docker exec -it postgres psql -h localhost -d dockerdb -U docker -W -f /tmp/table.sql
```
- psql command
```
Usage: psql [OPTIONS]... [DBNAME [USERNAME]]
General options:
  -d DBNAME specify database name to connect to (default: "root")
  -c COMMAND run only single command (SQL or internal) and exit
  -f FILENAME execute commands from file, then exit
  -l list available databases, then exit
  -v NAME=VALUE set psql variable NAME to VALUE
  -X do not read startup file (~/.psqlrc)
  --help show this help, then exit
  --version output version information, then exit
Input and output options:
  -a echo all input from script
  -e echo commands sent to server
  -E display queries that internal commands generate
  -q run quietly (no messages, only query output)
  -o FILENAME send query results to file (or |pipe)
  -n disable enhanced command line editing (readline)
  -s single-step mode (confirm each query)
  -S single-line mode (end of line terminates SQL command)
Output format options:
  -A unaligned table output mode (-P format=unaligned)
  -H HTML table output mode (-P format=html)
  -t print rows only (-P tuples_only)
  -T TEXT set HTML table tag attributes (width, border) (-P tableattr=)
  -x turn on expanded table output (-P expanded)
  -P VAR[=ARG] set printing option VAR to ARG (see \pset command)
  -F STRING set field separator (default: "|") (-P fieldsep=)
  -R STRING set record separator (default: newline) (-P recordsep=)
Connection options:
  -h HOSTNAME database server host or socket directory (default: "local socket")
  -p PORT database server port (default: "5432")
  -U NAME database user name (default: "root")
  -W prompt for password (should happen automatically)
```
