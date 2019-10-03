#include <iostream>
#include <sstream>

#include <Producer.h>

template< class PARAM >
static void setKafkaParam(RdKafka::Conf *conf, const char *name, const PARAM &param) throw (KafkaException)
{
    std::string errstr;
    if(conf->set(name, param, errstr) != RdKafka::Conf::CONF_OK)
    {
        std::ostringstream oss;
        oss << "failed to set kafka parameter " << name << " to " << param << " with error " << errstr << std::endl;
        throw KafkaException(oss.str().c_str());
    }
}

Producer::Producer(const std::string &prefix)
    : thread_(nullptr)
{
}

Producer::~Producer()
{
    stop();

    delete thread_;
}

void Producer::start(const std::string &type, const std::string &id) throw (KafkaException)
{
    type_ = type;
    id_ = id;

    std::string errstr;

    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    // See https://github.com/edenhill/librdkafka/blob/master/CONFIGURATION.md for the Kafka configs
    //setKafkaParam(conf, "debug", "trace"); //[none|overview|trace|detail|debug]

    setKafkaParam(conf, "client.id", id_);
    setKafkaParam(conf, "metadata.broker.list","localhost:9092"); //Comma delimited list of initial brokers
    setKafkaParam(conf, "compression.codec", "none"); //Compression Codec (none, gzip, snappy)
    setKafkaParam(conf, "event_cb", (EventCb *)this);
    /* Set delivery report callback */
    setKafkaParam(conf, "dr_cb", (DeliveryReportCb *)this);
    setKafkaParam(conf, "queue.buffering.max.messages", "100000"); //Local max queue size

    setKafkaParam(tconf, "message.timeout.ms", "300000"); //Local timeout in ms for message delivery to MQ

    setKafkaParam(conf, "retries", "2"); //Number of Retries

    //The number of acknowledgments the producer requires the leader to have received before
    //considering a request complete: valid values [-1,1000]
    //setKafkaParam(conf,"acks", "1");

    //setKafkaParam(conf,"linger.ms", "0"); //The linger time in ms

    /*
     * Create producer using accumulated global configuration.
     */
    kproducer_ = RdKafka::Producer::create(conf, errstr);
    delete conf;
    if (!kproducer_)
    {
        std::string text("failed to create kafka producer with error ");
        text += errstr;

        throw KafkaException(text);
    }

    // Create topic handle.
    std::string topic_("wchen_LDR");
    ktopic_ = RdKafka::Topic::create(kproducer_, topic_, tconf, errstr);
    delete tconf;
    if (!ktopic_)
    {
        delete kproducer_;  kproducer_ = nullptr;
        std::string text("failed to create kafka topic with error ");
        text += errstr;
        throw KafkaException(text);
    }

    running_ = true;
    thread_ = new std::thread([&]{ doTask(); });
}

void Producer::stop()
{
    if(running_)
    {
        running_ = false;
        thread_->join();

        if(kproducer_)
        {
            // wait until all messages have been written.
            // this will unwind when all messages have been written or expired (see Timeout configuration).
            while(kproducer_->outq_len() > 0) // could also use flush()
            {
                kproducer_->poll(1000);
            }

            if(ktopic_)
            {
                delete ktopic_; // deleted before kproducer_;
            }

            delete kproducer_;
        }
        else if(ktopic_)
        {
            delete ktopic_;
        }
    }
}

void Producer::send(const uint8_t *buffer, const uint32_t len, const uint8_t *key,
    const uint32_t keyLength) throw (KafkaException)
{
    int32_t partition = RdKafka::Topic::PARTITION_UA;

    if(running_)
    {
        ++sendCnt_;
        RdKafka::ErrorCode resp = kproducer_->produce(ktopic_, partition,
                              RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
                              (void*)buffer, len, key, keyLength, NULL);
        if (resp != RdKafka::ERR_NO_ERROR)
        {
            ++errorCnt_;
            std::string text("Kafka failed to send with error ");
            text += RdKafka::err2str(resp);

            throw KafkaException(text);
        }
        else
        {
            std::cout << type_ << " Kafka - produced message (" << len << " octets)" << std::endl;
        }

        return;
    }
    else
    {
        throw KafkaException("producer not running");
    }
}

void Producer::send(const std::string & key, const std::string & value) throw (KafkaException)
{
	send( (const uint8_t*) value.c_str(), value.length(), (const uint8_t*)key.c_str(), key.length());
}

void Producer::doTask()
{
    while(running_)
    {
        kproducer_->poll(1000);
    }
}

void Producer::event_cb (RdKafka::Event &event)
{
    switch (event.type())
    {
    case RdKafka::Event::EVENT_ERROR:
        std::cout << type_ << " Kafka - ERROR (" << RdKafka::err2str(event.err()) << "): " << event.str() << std::endl;
/*
        if (event.err() == RdKafka::ERR__ALL_BROKERS_DOWN)
            run = false;
*/
        break;

    case RdKafka::Event::EVENT_STATS:
        std::cout << type_ << " Kafka - \"STATS\": " << event.str() << std::endl;
        break;

    case RdKafka::Event::EVENT_LOG:
        std::cout << type_ << " Kafka - LOG-" << event.severity() << "-" << event.fac() << ": " << event.str() << std::endl;
        break;

    default:
        std::cout << type_ << " Kafka - EVENT " << event.type() << " (" << RdKafka::err2str(event.err()) << "): " << event.str() << std::endl;
        break;
    }
}

void Producer::dr_cb (RdKafka::Message &message)
{
    if(message.err() == RdKafka::ERR_NO_ERROR)
    {
        ++successCnt_;
        std::cout << type_ << " Kafka - Message delivery for (" << message.len() << " bytes): " << message.errstr() << std::endl;
    }
    else
    {
        ++errorCnt_;
        std::cout << type_ << " Kafka - Error event: " << message.errstr() << std::endl;
    }
}
