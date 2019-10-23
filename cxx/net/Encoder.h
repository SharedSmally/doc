#ifndef CPW_NET_ENCODER_H
#define CPW_NET_ENCODER_H

class App
{

};

class Service
{
public:
	Service(const std::string & name, App &app)
	: name_(name), app_(app)
	{};
	virtual ~Service() {}
	virtual bool start() = 0;
	virtual bool config() = 0;
	virtual void stop() = 0;

	App & app() { return app_; }
	const std::string & name()const { return name_; }

protected:
	App & app_;
	std::string name_;
};

class ConnectionSocketCfg
{

};
// Channel <->Buffer<->Object
// read binary data from channel
typedef std::string Buffer;
class ChannelReader  {
public:
	virtual ~ChannelReader();
	virtual Buffer read(ChannelPtr & channel);
};

// first n bytes indicates the length;
class ChannelLengthReader : public ChannelReader {
public:
	static const LEN_MAX_SIZE = 4; //4 bytes
	ChannelLengthReader(int nlength, int offset);
	virtual ~ChannelLengthReader() { };
	virtual Buffer read(ChannelPtr & channel);

protected:
	int nlength_, offset_;
};

template <typename MAXLEN>
class ChannelMaxLengthReader : public ChannelReader {
public:
	ChannelMaxLengthReader(int nlength, int offset);
	virtual ~ChannelMaxLengthReader() { };
	virtual Buffer read(ChannelPtr & channel);

protected:
	int nlength_, offset_;
};

// convert object and binary
template <typename T>
class Encoder {
public:
	virtual ~Encoder(){};
	virtual Buffer encode(const T & obj);
};
template <typename T>
class Decoder {
public:
	virtual ~Decoder(){};
	virtual T decode(const Buffer & Buffer);
};
template <typename T>
class Coder {
public:
	virtual ~Coder(){};
	virtual Buffer encode(const T & obj);
	virtual T decode(const Buffer & Buffer);
};

class CoderFactory {
public:
	virtual ~CoderFactory(){};
	template <typename T >
	virtual Buffer encode(const T & obj);
	template <typename T >
	virtual T decode(const Buffer & Buffer);
};

//Encoder/Decoder/Coder
//Encryptor/Decryptor/Cryptor
//Jsoner/Xmler/Stringer

class ServerService : public Service
{
public:
	typedef IPv4Address addr_type;
	typedef ServerSocket<addr_type> server_sock_type;
	typedef Connection<addr_type> conn_sock_type;

	typedef std::shared_ptr< ChannelObj<server_sock_type> > server_channel_ptr;
	typedef std::shared_ptr< ChannelObj<conn_sock_type> > conn_chnnel_ptr;

	ServerService(const std::string & name, App &app)
	: Service(name, app)
	{};

	virtual bool start() { return true; }
	virtual bool config()
	{ return true; }
	virtual void stop()
	{
		;
	}

	// from App Context to get the components: Multiplexer; Executor; Scheduler; SocketHandler
	Multiplexer & get() {
		;
	}

protected:
	addr_type addr_;
	server_channel_ptr server_;
	container_type conns_;
	ConnectionSocketCfg svrCfg_;
	ConnectionSocketCfg connCfg_;
};


#endif
