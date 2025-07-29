#include "Protocol.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
   

    if (argc < 2) {
        std::cerr << "Usage:\n";
        std::cerr << "  " << argv[0] << " server\n";
        std::cerr << "  " << argv[0] << " client <host> <port>\n";
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "server") {
        Protocol::Server s;
        s.start(9090);
    }
    else if (mode == "client") {
        if (argc < 4) {
            std::cerr << "Client mode requires host and port.\n";
            return 1;
        }

        std::string host = argv[2];
        int port = std::stoi(argv[3]);

        Protocol::Client c;
        c.send(host, port);
    }
    else {
        std::cerr << "Unknown mode: " << mode << "\n";
        return 1;
    }

    return 0;
}
