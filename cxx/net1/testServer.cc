#include <EpollMux.h>
#include <Socket.h>

#include <iostream>
using namespace std;

int main()
{
	IPv4Address addr("10.32.119.152", 9999);
	ChannelPtr channel = std::make_shared< ChannelObj<CSocket> >(addr, true);

	EpollMux epoll;


}
