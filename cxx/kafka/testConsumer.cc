#include <iostream>
using namespace std;

#include <unistd.h>

#include <Consumer.h>

class MyKafkaListener : public KafkaListener
{
public:
    virtual void onMessage(uint8_t *buffer, uint32_t len)
    {
        std::cout << "receive data: length=" << len << std::endl;
        if (len < 100)
        {
        	std::string str((const char *)buffer, len);
        	std::cout << "receive data: data=" << str << std::endl;
        }
    }

    virtual void onError(const std::string error)
    {
    	std::cout << "receive error: " << error << std::endl;
    }

    virtual void onLastMessage()
    {
       	std::cout << " onLastMessage() " << std::endl;
    }

    virtual void onWakenUp()
    {
       	std::cout << " onWakenUp() " << std::endl;
    }
};

int main()
{
	MyKafkaListener listener;

	Consumer consumer("test");
	consumer.start("mytype","myid",&listener);

	sleep(40);
	consumer.stop();
}
