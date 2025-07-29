#pragma once
#include <string>  

namespace Protocol {
    class Client {
    public:
        void send(const std::string& host, int port);  
    };
}
