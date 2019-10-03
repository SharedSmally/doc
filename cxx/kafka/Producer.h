#ifndef PRODUCER_H
#define PRODUCER_H

#include <atomic>
#include <thread>

#include <librdkafka/rdkafkacpp.h>

#include <KafkaException.h>

typedef std::atomic<unsigned int> Count;

struct KProducerConfig
{
    std::string brokers;
    std::string topic;
    uint32_t timeout;
    uint32_t maxLocalQueueSize;
    uint32_t numberRetries;
    int32_t  acks;
    uint32_t lingerMS;
    std::string compression;
    std::string debug;
};

class Producer : public RdKafka::EventCb, public RdKafka::DeliveryReportCb
{
public:
	Producer(const std::string &prefix);
    virtual ~Producer();

    virtual void start(const std::string &type, const std::string &id) throw (KafkaException);
    virtual void stop();

    virtual void send(const std::string & key, const std::string & value) throw (KafkaException);
    virtual void send(const uint8_t *buffer, const uint32_t length, const uint8_t *key = 0,
                    const uint32_t keyLength = 0) throw (KafkaException);

    virtual void event_cb(RdKafka::Event &event);
    virtual void dr_cb (RdKafka::Message &message);

private:
    void doTask();

    Count sendCnt_, successCnt_, errorCnt_;

    volatile bool running_;
    std::string type_;
    std::string id_;
    std::thread * thread_;

    RdKafka::Producer *kproducer_;
    RdKafka::Topic *ktopic_;
};


#endif
