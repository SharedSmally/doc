/*
 * Utils.h
 *
 *  Created on: Oct 17, 2019
 *      Author: wchen
 */
#ifndef CPW_NET1_UTILS_H_
#define CPW_NET1_UTILS_H_

#include <Address.h>
#include <Channel.h>
#include <Client.h>
#include <Server.h>

template <typename ADDR>
std::shared_ptr<ChannelObj<ServerSocket<ADDR> > > serverChannel(const ADDR & addr,
		int backlog=Socket::DEFAULT_BACKLOG, bool sctp=false)
{
	std::shared_ptr<ChannelObj<ServerSocket<ADDR> > > channel
	   = std::make_shared<ChannelObj<ServerSocket<ADDR> > >(addr, sctp);
	channel->server(true); //events(Channel::IN_EVENT);
	channel->sock().listen(backlog);
	return channel;
}

template <typename ADDR>
std::shared_ptr<ChannelObj<ClientSocket<ADDR> > > clientChannel(const ADDR & addr,
		const ADDR & svraddr, bool bind = false, bool sctp=false)
{
	std::shared_ptr<ChannelObj<ClientSocket<ADDR> > > channel
	   = std::make_shared<ChannelObj<ClientSocket<ADDR> > >(addr, svraddr, sctp);

	channel->events(Channel::IN_EVENT|Channel::OUT_EVENT);
	channel->sock().connect(bind);
	return channel;
}

template <typename ADDR>
std::shared_ptr<ChannelObj<Connection<ADDR> > > connectChannel( std::shared_ptr<ChannelObj<ServerSocket<ADDR> > >  & svc )
{
	ADDR addr;
	int fd = svc->sock().accept(addr);
	return std::make_shared<ChannelObj<Connection<ADDR> > >(svc->sock().serverAddr(), addr, fd);
}

typedef std::shared_ptr<ChannelObj<Connection<IPv4Address> > > Connection4Ptr;

#endif /* CPW_NET1_UTILS_H_ */
