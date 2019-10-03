#ifndef CONSUMER_H
#define CONSUMER_H

#include <atomic>
#include <thread>
#include <string>
#include <vector>

#include <librdkafka/rdkafkacpp.h>

#include <KafkaException.h>

typedef std::atomic<unsigned int> Count;

class KafkaListener
{
public:
    virtual void onMessage(uint8_t *buffer, uint32_t len) = 0;
    virtual void onError(const std::string error) = 0;
    virtual void onTimeout() {}
    virtual void onLastMessage() {}
    virtual void onWakenUp() {}
};

struct ConsumerConfig
{
    std::string  brokers;
    std::string  groupID;
    std::vector< std::string >  topics;
    uint32_t commitInterval;
    std::string debug;
    std::string offset;
};

class Consumer : public RdKafka::EventCb, public RdKafka::ConsumeCb, public RdKafka::RebalanceCb
{
public:
    Consumer(const std::string &prefix);
    virtual ~Consumer();

    virtual void start(const std::string &type, const std::string &id, KafkaListener *listener) throw (KafkaException);
    virtual void stop();
    virtual void commit();
    virtual void wakeUp() { wakeUp_ = true; }

    virtual void event_cb(RdKafka::Event &event);
    virtual void consume_cb (RdKafka::Message &msg, void *opaque);
    virtual void rebalance_cb (RdKafka::KafkaConsumer *consumer, RdKafka::ErrorCode err,
                      std::vector<RdKafka::TopicPartition*> &partitions);

private:
    void doTask();

    Count receiveCnt_;

    int64_t offsetValue_;
    uint32_t commitInterval_;
    bool offsetAssigned_;
    std::string type_;
    std::string id_;

    std::thread * thread_;
    KafkaListener *listener_;

    volatile bool running_;
    volatile bool wakeUp_;
    RdKafka::KafkaConsumer *kconsumer_;
};

#endif
