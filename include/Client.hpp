#pragma once
#include <string>  // ✅ Needed for std::string

namespace Protocol {
    class Client {
    public:
        void send(const std::string& host, int port);  // ✅ Use const std::string& properly
    };
}
