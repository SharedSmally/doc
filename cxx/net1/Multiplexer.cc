#include <unistd.h>
#include <sys/eventfd.h>

#include <Macro.h>
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

Multiplexer::Multiplexer(ChannelListener & listener, uint32_t initSize)
 : listener_(listener), running_(false)
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

    ioThread_->join();
}

bool Multiplexer::manage(ChannelPtr & channel)
{
	INFO("Multiplexer::manage: channel=" << (bool)channel);
    if (!channel) return false;

    INFO("Multiplexer::manage: channel: fd=" << channel->fd() << "; id=" << channel->id() << "; channels size=" << channels_.size());
    int fd = channel->fd();
    int fd1 = fd+1;

    guard_type guard(mtx_);
    if (fd1 > channels_.size()) {
        fd1 >> STEP_BIT_NUM;
        ++fd1;
        fd1 << STEP_BIT_NUM;
        channels_.resize(fd1);
        INFO("Multiplexer::manage: channel resize: fd1=" << fd1 << "; size=" <<  channels_.size())
    }

    bool modify(channels_[fd]);
    if (modify && channels_[fd]->id() != channel->id())
    {
        INFO("Multiplexer::update channel: channels[fd].id=" << channels_[fd]->id() << "; channel.id="<<channel->id());
    }
    channels_[fd] = channel;

    INFO("Multiplexer::join channel: modify=" << modify);
    if (!_join(channel, modify) ) {
    	INFO("Multiplexer::join channel fails" );
    } else {
    	INFO("Multiplexer::join channel success" );
    }

    notify();

    return true;
}

bool Multiplexer::unmanage(ChannelPtr & channel)
{
	INFO("Multiplexer::unmanage: channel=" << (bool)channel);
    if (!channel) return false;

    int fd = channel->fd();
    int fd1 = fd+1;

    INFO("Multiplexer::unmanage: channel: fd=" << channel->fd() << "; id=" << channel->id() << "; channels size=" << channels_.size());

    guard_type guard(mtx_);
    if (fd1 > channels_.size())
        return false;

    if (channels_[fd]->id() != channel->id())
        return false;

    INFO("Multiplexer::leave channel: " );

    channels_[fd] = nullptr;
    _leave(channel);

    notify();

    return true;
}
