#include "Protocol.hpp"
#include <Poco/JSON/Object.h>
#include <sstream> // Required for stringify

namespace Protocol {

    // The Message struct definition should be here if it's not in the .hpp
    // struct Message { ... };

    std::string serialize(const Message& msg) {
        // Create a new JSON Object
        Poco::JSON::Object::Ptr jsonObj = new Poco::JSON::Object;

        // Set the properties on the JSON object
        jsonObj->set("id", msg.deviceId);
        jsonObj->set("temperature", msg.temperature);
        jsonObj->set("humidity", msg.humidity);
        jsonObj->set("ph", msg.ph);

        // THE FIX: Use a stringstream and the stringify method to correctly
        // convert the JSON object to a string.
        std::stringstream ss;
        jsonObj->stringify(ss);
        
        return ss.str();
    }
}