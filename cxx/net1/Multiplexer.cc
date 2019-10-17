#include <unistd.h>
#include <sys/eventfd.h>

#include <Multiplexer.h>

const uint64_t Notifier::ONE(1);

Notifier::Notifier(uint32_t initval, bool semaphore, bool cloexec, bool nonblock)
{
	int flags = nonblock ? EFD_NONBLOCK : 0;
	if (cloexec) flags |= EFD_CLOEXEC;
	if (semaphore) flags |= EFD_SEMAPHORE;

	efd_ = eventfd(initval, flags);
}

Notifier::~Notifier()
{
	::close(efd_);
}

bool Notifier::notify()
{
	return ::write(efd_, &ONE, sizeof(ONE));
}

bool Notifier::onNotified(uint64_t & value)
{
	return ::read(efd_, &value, sizeof(value)) != sizeof(value);
}

const int Multiplexer::STEP_BIT_NUM(10); // 10bits = 1K

Multiplexer::Multiplexer(uint32_t initSize)
 : running_(false)
{
	channels_.reserve(initSize);
    for(int n = 0; n < initSize; ++n)
        channels_.push_back(nullptr);
}

bool Multiplexer::start()
{
	if (running_) return false;

	guard_type guard(mtx_);
	if (running_) return false;

	running_ = true;
	ioThread_ = std::make_shared<std::thread>([&] { _run(); } );

	return true;
}
void Multiplexer::stop()
{
	if (!running_) return ;

	guard_type guard(mtx_);
	if (!running_) return;

	running_ = false;
	notify();
}

bool Multiplexer::manage(ChannelPtr & channel)
{
	if (!channel) return false;

	int fd = channel->fd();
	int fd1 = fd+1;

	guard_type guard(mtx_);
	if (fd1 > channels_.size()) {
		fd1 >> STEP_BIT_NUM;
		++fd1;
		fd1 << STEP_BIT_NUM;
		channels_.resize(fd1);
	}

	bool modify(channels_[fd]);
	if (modify && channels_[fd]->id() != channel->id())
		channels_[fd] = channel;

	_join(channel, modify);

	notify();

	return true;
}

bool Multiplexer::unmanage(ChannelPtr & channel)
{
	if (!channel) return false;

	int fd = channel->fd();
	int fd1 = fd+1;

	guard_type guard(mtx_);
	if (fd1 > channels_.size())
		return false;

	if (channels_[fd]->id() != channel->id())
		return false;

	channels_[fd] = nullptr;
	_leave(channel);

	notify();

	return true;
}
