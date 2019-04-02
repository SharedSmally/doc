# [zookeeper]()
## Server Ports
- 2888: Peer Port: among peers to talk each other
- 3888: Leader Port: among peers to select leader
- 2191: Client Port: to accept client connections
- 9092: kafka to accept client connections

## Concepts
### Znode
The znode will be ephemeral, persistent, or sequential. By default, all znodes are persistent.
- Ephemeral znodes (flag: -e):  automatically be deleted when a session expires or when the client disconnects.
- Sequential znodes(flag: -s) : guaranty that the znode path will be unique.
- If no flags are specified, then the znode is considered as persistent.
- ZooKeeper ensemble will add sequence number along with 10 digit padding to the znode path. For example, the znode path /myapp will be converted to /myapp0000000001 and the next sequence number will be /myapp0000000002. 

## Zookeeper web-UI
- [zk-web](https://github.com/qiuxiafei/zk-web):
- [zkui](https://github.com/DeemOpen/zkui):
- [EasyUI](http://www.jeasyui.com/): based on jQuery/Angular/React
- [etcd-UI](https://github.com/evildecay/etcdkeeper)

## [ZooKeeper CLI](): zkCli.sh or zookeeper-shell.sh
- Create znodes
Create a znode with the given path. 
```
create [-s|-e] /path /data
create /FirstZnode “Myfirstzookeeper-app”
```
- Get data
```
get /path 
get /FirstZnode
```
- Set data
```
set /path /data
set /SecondZnode Data-updated
```
- Create Children / Sub-znode

Creating children is similar to creating new znodes. The only difference is that the path of the child znode will have the parent path as well.
```
create /parent/path/subnode/path /data
create /FirstZnode/Child1 firstchildren
```
- List children of a zn

List and display the children of a znode.
```
ls /path
ls /MyFirstZnode
```
- Remove / Delete a znode

Removes a specified znode and recursively all its children. This would happen only if such a znode is available.
```
rmr /path
rmr /FirstZnode
```
Delete (delete /path) command is similar to remove command, except the fact that it works only on znodes with no children.

- Check Status

Describes the metadata of a specified znode. It contains details such as Timestamp, Version number, ACL, Data length, and Children znode.
```
stat /path
stat /FirstZnode
```
- Watch znode for changes

Watches show a notification when the specified znode or znode’s children data changes. You can set a watch only in get command.
```
get /path [watch] 1
get /FirstZnode 1
```
