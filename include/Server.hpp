#pragma once
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/SocketStream.h>
#include <thread>

namespace Protocol {
    class Server {
    public:
        void start(int port);
    };
}
