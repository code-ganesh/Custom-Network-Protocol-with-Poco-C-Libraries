#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <string>

namespace Protocol {

struct Message {
    std::string deviceId;
    double temperature;
    double humidity;
    double ph;
};

// Serialize Message struct to JSON string
std::string serialize(const Message& msg);

// (Day 2) Deserialize JSON string to Message struct
Message deserialize(const std::string& jsonStr);

} // namespace Protocol

#endif // PROTOCOL_HPP
