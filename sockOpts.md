# SOCK Opts
## [Socket manual](http://man7.org/linux/man-pages/man7/socket.7.html)

## [tcp keep alive](https://stackoverflow.com/questions/1480236/does-a-tcp-socket-connection-have-a-keep-alive)
There are three configurable properties that determine how Keep-Alives work. On Linux they are1:
- tcp_keepalive_time:  default 7200 seconds
- tcp_keepalive_probes: default 9
- tcp_keepalive_intvl:  default 75 seconds

This process is enabled by default on most operating systems, and thus dead TCP connections are regularly pruned once the other
end has been unresponsive for 2 hours 11 minutes (7200 seconds + 75 * 9 seconds).
