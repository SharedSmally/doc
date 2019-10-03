#ifndef KafkaException_H
#define KafkaException_H

#include <string>
#include <stdexcept>

class KafkaException : public std::runtime_error
{
public:
    explicit KafkaException(const std::string& message)
        : std::runtime_error(message)
    {}

    explicit KafkaException(const char *message)
        : std::runtime_error(message)
    {}
};

#endif
