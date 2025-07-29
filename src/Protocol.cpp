#include "Protocol.hpp"
#include <Poco/JSON/Object.h>
#include <sstream> // Required for stringify

namespace Protocol {

    

    std::string serialize(const Message& msg) {
        // Create a new JSON Object
        Poco::JSON::Object::Ptr jsonObj = new Poco::JSON::Object;

        // Set the properties on the JSON object
        jsonObj->set("id", msg.deviceId);
        jsonObj->set("temperature", msg.temperature);
        jsonObj->set("humidity", msg.humidity);
        jsonObj->set("ph", msg.ph);

        
        std::stringstream ss;
        jsonObj->stringify(ss);
        
        return ss.str();
    }
}