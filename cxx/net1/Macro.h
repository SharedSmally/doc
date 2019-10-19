#ifndef CPW_NET_MACRO_H
#define CPW_NET_MACRO_H

#include <iostream>

#ifndef INFO
#define INFO(msg) std::cout << __FILE__ << "@" << __LINE__ << ": " << msg << std::endl;
#endif

#ifndef ERROR
#define ERROR(msg) std::cout << __FILE__ << "@" << __LINE__ << ": errno=" << errno << ": "<< msg << std::endl;
#endif

#endif

