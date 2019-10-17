#include <Channel.h>

const int Channel::IN_EVENT(0x01);      // bit0
const int Channel::IN_PRIO_EVENT(0x02); // bit1
const int Channel::OUT_EVENT(0x04);     // bit2
const int Channel::HUP_EVENT(0x10);     // bit3
const int Channel::ERROR_EVENT(0x20);   // bit4

const int Channel::ALL_EVENTS(0xFFFF);

std::atomic<Channel::id_type> Channel::idCnt_(0);
