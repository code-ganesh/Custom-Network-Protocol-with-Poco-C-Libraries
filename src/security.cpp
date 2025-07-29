#include "Security.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// This is a simple placeholder for real cryptography.

namespace DummyCrypto {
    const std::string XOR_KEY = "YourSecureRandomLongKeyForTesting12345!@#$"; // Make this long enough for your data

    std::string process(const std::string& input) {
        std::string output = input;
        for (size_t i = 0; i < input.size(); ++i) {
            output[i] = input[i] ^ XOR_KEY[i % XOR_KEY.size()];
        }
        return output;
    }
}



std::string Security::encrypt(const std::string& plaintext, const std::string& pubKeyFile) {
    // The pubKeyFile is not used with the dummy cipher, but kept for signature matching.
    std::cout << "[DEBUG]  Encrypting data." << std::endl;
    return DummyCrypto::process(plaintext);
}

std::string Security::decrypt(const std::string& ciphertext, const std::string& privKeyFile) {
    // The privKeyFile is not used with the dummy cipher, but kept for signature matching.
    std::cout << "[DEBUG]  Decrypting data." << std::endl;
    // XORing a second time decrypts the message.
    return DummyCrypto::process(ciphertext);
}

std::string Security::sign(const std::string& message, const std::string& privKeyFile) {
    // The privKeyFile is not used with the dummy cipher, but kept for signature matching.
    std::cout << "[DEBUG]  Signing data." << std::endl;
    // For this test, the "signature" is just an XOR of the message.
    return DummyCrypto::process(message);
}

bool Security::verify(const std::string& message, const std::string& signature, const std::string& pubKeyFile) {
    // The pubKeyFile is not used with the dummy cipher, but kept for signature matching.
    std::cout << "[DEBUG]  Verifying data." << std::endl;
    // We "verify" by XORing the signature back and checking if it matches the original message.
    std::string recovered_message = DummyCrypto::process(signature);
    return message == recovered_message;
}