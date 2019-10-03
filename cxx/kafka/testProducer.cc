#include <iostream>
using namespace std;

#include <unistd.h>

#include <Producer.h>

int main()
{
        Producer producer("test");
        producer.start("mytype","myid");

        std::string key("test key");
        std::string msg("test message");

        producer.send(key, msg);

        sleep(3);
        producer.stop();
}
