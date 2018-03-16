## SCTP

### Multi-Homing
- [Tutorial 1](http://lteuniversity.com/get_trained/expert_opinion1/b/gcote/archive/2012/12/18/sctp-multi-homing.aspx)
- [Tutorial 2](http://petanode.com/blog/posts/multi-homing-in-sctp.html)
SCTP’s multi-homing feature assigns multiple IP addresses to a single association. During association initialisation each endpoint may announce list of additional IP address that can be used for communication. *Remember that the port number is the same for all addresses in this list. One association can't use more than one port number.* One of the paths, between the endpoints, is considered PRIMARY. The others are used either when the primary goes down or when the upper layer implicitly requires the message to be sent to another IP address.
