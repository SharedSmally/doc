#ifndef ADDRESS_H
#define ADDRESS_H

#include <netinet/in.h>

class Address {
public:
	virtual ~Address() {}
	virtual struct sockaddr * addr() = 0;
	virtual const struct sockaddr * addr() const = 0;
	virtual socklen_t length() const = 0;
	virtual socklen_t maxLength() const = 0;
};

#endif
