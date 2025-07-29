#include "Server.hpp"
#include "Protocol.hpp"
#include "Security.hpp"
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/Base64Encoder.h>
#include <Poco/Base64Decoder.h>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <iterator> // Required for istreambuf_iterator

namespace fs = std::filesystem;
using namespace Poco::Net;
using namespace Protocol;
using namespace std;
using namespace Poco;

void Server::start(int port) {
    cout << "Custom Protocol using Poco C++ - Final Version\n";
    ServerSocket server(port);
    cout << "Server listening on port " << port << endl;

    fs::path base = fs::current_path();
    string privKeyPath = (base / "../keys/private.pem").lexically_normal().string();
    string pubKeyPath  = (base / "../keys/public.pem").lexically_normal().string();

    while (true) {
        // Inside Server::start's while(true) loop
try {
    StreamSocket client = server.acceptConnection();
    SocketStream stream(client);
    
    // Receive the Base64-encoded message from the client.
    string received_base64;
    getline(stream, received_base64);
    if (received_base64.empty()) continue;
    cout << "[DEBUG] Received Encrypted Data: " << received_base64 << endl;

    // Explicitly Base64-decode it to get the raw binary.
    stringstream ss_to_decode(received_base64);
    Base64Decoder decoder(ss_to_decode);
    string received_encrypted_binary;
    copy(istreambuf_iterator<char>(decoder), istreambuf_iterator<char>(), back_inserter(received_encrypted_binary));

    // Pass the clean, raw binary to our robust decrypt function.
    string decrypted = Security::decrypt(received_encrypted_binary, privKeyPath);
    cout << "Received from client (decrypted): " << decrypted << endl;

    // The server response logic is correct and does not need to change.
    string plaintext_response = "SUCCESS: Data received!";
    string signature = Security::sign(plaintext_response, privKeyPath);

    stringstream ss_plain, ss_sig;
    Base64Encoder plain_encoder(ss_plain);
    Base64Encoder sig_encoder(ss_sig);
    plain_encoder.write(plaintext_response.data(), plaintext_response.size());
    plain_encoder.close();
    sig_encoder.write(signature.data(), signature.size());
    sig_encoder.close();
    
    stream << ss_plain.str() << endl;
    stream << ss_sig.str() << endl;
    stream.flush();

}   catch (const Poco::Exception& e) {
            cerr << "Server runtime error: " << e.displayText() << endl;
        } catch (const std::exception& e) {
            cerr << "Standard error: " << e.what() << endl;
        }
    }
}