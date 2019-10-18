#include <Utils.h>
#include <EpollMux.h>

#include <iostream>
using namespace std;

#include <unistd.h>

int main()
{
	IPv4Address addr("10.32.119.152", 9999);
	auto channel = serverChannel(addr);

	EpollMux epoll;
	epoll.start();
	epoll.manage(channel);
	sleep(10);
	epoll.stop();

}
