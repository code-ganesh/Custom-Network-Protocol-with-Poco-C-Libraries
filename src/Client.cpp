#include "Client.hpp"
#include "Protocol.hpp"
#include "Security.hpp"

#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/Base64Encoder.h>
#include <Poco/Base64Decoder.h>
#include <iostream>
#include <sstream>

using namespace Poco::Net;
using namespace Protocol;
using namespace std;
using namespace Poco;

void Client::send(const std::string& host, int port) {
    cout << "Custom Protocol using Poco C++ - Final Version\n";

    // Inside Client::send's try block
try {
    SocketAddress sa(host, port);
    StreamSocket socket(sa);
    SocketStream stream(socket);

    Message msg = {"sensor-001", 24.8, 65.2, 7.0};
    string json = serialize(msg);
    
     cout << "DEBUG: Serialized JSON before encryption: " << json << endl;
    
    // encrypt now returns raw binary, which we MUST Base64-encode for transport.
    string encrypted_raw = Security::encrypt(json, "public.pem");

    // Explicitly Base64-encode the raw binary data.
    stringstream ss_to_encode;
    Base64Encoder encoder(ss_to_encode);
    encoder.write(encrypted_raw.data(), encrypted_raw.size());
    encoder.close();
    
    cout << "[DEBUG] Encrypted (Base64): " << ss_to_encode.str() << endl;


    // Send the safe Base64 string.
    stream << ss_to_encode.str() << endl;
    stream.flush();
    
    // The server response logic is correct and does not need to change.
    string response_plain_b64, response_sig_b64;
    getline(stream, response_plain_b64);
    getline(stream, response_sig_b64);

    stringstream ss_plain_decode(response_plain_b64);
    Base64Decoder plain_decoder(ss_plain_decode);
    string plaintext_response;
    copy(istreambuf_iterator<char>(plain_decoder), istreambuf_iterator<char>(), back_inserter(plaintext_response));
    
    stringstream ss_sig_decode(response_sig_b64);
    Base64Decoder sig_decoder(ss_sig_decode);
    string signature;
    copy(istreambuf_iterator<char>(sig_decoder), istreambuf_iterator<char>(), back_inserter(signature));
    
    bool is_valid = Security::verify(plaintext_response, signature, "public.pem");

    cout << "Server Response: " << plaintext_response << endl;
    cout << "Signature valid: " << (is_valid ? "Yes" : "No") << endl;

}  catch (const Poco::Exception& e) {
        cerr << "Client error: " << e.displayText() << endl;
    }
}