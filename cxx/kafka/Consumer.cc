#include <Consumer.h>

#include <iostream>
#include <sstream>
#include <unistd.h>


template< class T >
static void setKafkaParam(RdKafka::Conf *conf, const char *name,
                    const T &param) throw (KafkaException)
{
    std::string errstr;
    if(conf->set(name, param, errstr) != RdKafka::Conf::CONF_OK)
    {
        std::ostringstream oss;
        oss << "failed to set kafka parameter " << name << " to " << param << " with error " << errstr;
        throw KafkaException(oss.str());
    }
}

Consumer::Consumer(const std::string &prefix)
: RdKafka::EventCb(), RdKafka::ConsumeCb(), RdKafka::RebalanceCb()
, offsetValue_(0)
, offsetAssigned_(false)
, commitInterval_(0)
, type_()
, id_()
, kconsumer_(nullptr)
, running_(false)
, listener_(nullptr)
, thread_(nullptr)
, wakeUp_(false)
{
}

Consumer::~Consumer()
{
    stop();
    delete thread_;
}

void Consumer::start(const std::string &type, const std::string &id, KafkaListener *listener) throw (KafkaException)
{
    listener_ = listener;
    std::string errstr;

    type_ = type;
    id_ = id;

    /*
    if(offset_ == "beginning")
    {
        offsetValue_ = RdKafka::Topic::OFFSET_BEGINNING;
    }
    else if(offset_ == "end")
    {
        offsetValue_ = RdKafka::Topic::OFFSET_END;
    }
    else if(offset_ == "stored")
    {
        offsetValue_ = RdKafka::Topic::OFFSET_STORED;
    }
    else
    {
        try
        {
            offsetValue_ = std::stoll(offset_.get());
        }
        catch(...)
        {
            std::string text("invalid value encountered for ");
            text += offset_.getName();

            throw data::KafkaException(text);
        }
    }
   */
    offsetValue_ = RdKafka::Topic::OFFSET_BEGINNING;

    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

    //setKafkaParam(conf, "debug", "debug");

    setKafkaParam(conf, "metadata.broker.list", "localhost:9092");
    setKafkaParam(conf, "group.id", "wchen_LDR_group");

    setKafkaParam(conf, "rebalance_cb", (RdKafka::RebalanceCb *)this);
    setKafkaParam(conf, "event_cb", (EventCb *)this);


    if(!id_.empty())
    {
        setKafkaParam(conf, "client.id", id_);
    }

    if(commitInterval_ == 0)
    {
        setKafkaParam(conf, "enable.auto.commit", "false");
    }
    else
    {
        setKafkaParam(conf, "enable.auto.commit", "true");
        setKafkaParam(conf, "auto.commit.interval.ms", std::to_string(commitInterval_));
    }

    setKafkaParam(conf, "enable.auto.commit", "false");

    // Create cosumer using accumulated global configuration.
    kconsumer_ = RdKafka::KafkaConsumer::create(conf, errstr);
    delete conf;

    if (!kconsumer_)
    {
        std::string text("failed to create kafka consumer with error ");
        text += errstr;
        throw KafkaException(text);
    }

    std::vector<std::string> topics_;
    topics_.push_back("wchen_LDR");
    RdKafka::ErrorCode err = kconsumer_->subscribe(topics_);

    if (err)
    {
        std::ostringstream oss;
        oss << "failed to subscribe to " << topics_.size() << " kafka topics with error : " << RdKafka::err2str(err);
        throw KafkaException(oss.str());
    }

    std::cout << type_ << " Kafka - created consumer " << kconsumer_->name() << std::endl;

    running_ = true;
    thread_ = thread_ = new std::thread([&]{ doTask(); });

}

void Consumer::stop()
{
    if(running_)
    {
        running_ = false;

        thread_->join();

        kconsumer_->close(); // Stop consumer
        delete kconsumer_;
    }
}

void Consumer::commit()
{
    if(running_)
    {
        kconsumer_->commitAsync(); //may use others
    }
}

void Consumer::doTask()
{
    while(running_)
    {
        //kconsumer_->poll(0); // non-blocking

        RdKafka::Message *msg = kconsumer_->consume(1000); // block to 1 sec

        try
        {
            ++receiveCnt_;
            consume_cb(*msg, NULL);
        }
        catch(const KafkaException & be)
        {
        	std::cout << "caught KafkaException:" << be.what() << std::endl;
        }
        catch(std::exception &se)
        {
            std::cout << "caught exception:" << se.what() << std::endl;
        }
        catch(...)
        {
            std::cout << "caught an unknown exception" << std::endl;
        }

        delete msg;

        if(wakeUp_)
        {
            listener_->onWakenUp();
            wakeUp_ = false;
        }
    }
}

void Consumer::consume_cb (RdKafka::Message &msg, void *opaque)
{
    switch (msg.err())
    {
    case RdKafka::ERR__TIMED_OUT:
    case RdKafka::ERR__TIMED_OUT_QUEUE:
        listener_->onTimeout();
        break;

    case RdKafka::ERR_NO_ERROR:
        listener_->onMessage((uint8_t *)msg.payload(), msg.len());
        break;

    case RdKafka::ERR__PARTITION_EOF: // Last message
        listener_->onLastMessage();
        break;

    case RdKafka::ERR__UNKNOWN_TOPIC:
    case RdKafka::ERR__UNKNOWN_PARTITION:
    default:
        std::cout << type_ << " Kafka - Consume failed: " << msg.errstr() << std::endl;
        listener_->onError(msg.errstr());
        break;
    }
}

void Consumer::event_cb (RdKafka::Event &event)
{
    switch (event.type())
    {
    case RdKafka::Event::EVENT_ERROR:
        std::cout << type_ << " Kafka - ERROR (" << RdKafka::err2str(event.err())
                  << "): " << event.str() << std::endl;
        break;

    case RdKafka::Event::EVENT_STATS:
        std::cout << type_ << " Kafka - \"STATS\": " << event.str() << std::endl;
        break;

    case RdKafka::Event::EVENT_LOG:
        std::cout << type_ << " Kafka - LOG-" << event.severity() << "-"
                  << event.fac() << ": " << event.str() << std::endl;
        break;

    default:
        std::cout << type_ << " Kafka - EVENT " << event.type() << " ("
                  << RdKafka::err2str(event.err()) << "): "
                  << event.str() << std::endl;
        break;
    }
}

void Consumer::rebalance_cb(RdKafka::KafkaConsumer *consumer, RdKafka::ErrorCode err,
           std::vector<RdKafka::TopicPartition*> &partitions)
{
    if (err == RdKafka::ERR__ASSIGN_PARTITIONS)
    {
        if((offsetValue_ == RdKafka::Topic::OFFSET_STORED) || !offsetAssigned_)
        {
            offsetAssigned_ = true; // set offset once

            for (uint32_t i = 0 ; i < partitions.size(); i++)
            {
                partitions[i]->set_offset(offsetValue_);
            }
        }
    }


    {
        std::cout << " Kafka - rebalance: " << RdKafka::err2str(err) << ":" << std::endl;
        for (uint32_t i = 0 ; i < partitions.size(); i++)
        {
            std::cout << partitions[i]->topic() << "[" << partitions[i]->partition()
                                       << ":" << partitions[i]->offset() << "], " << std::endl;
        }
    }

    if (err == RdKafka::ERR__ASSIGN_PARTITIONS)
    {
        consumer->assign(partitions);
    }
    else
    {
        consumer->unassign();
    }
}
