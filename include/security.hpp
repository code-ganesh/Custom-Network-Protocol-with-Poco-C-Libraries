#ifndef SECURITY_HPP
#define SECURITY_HPP
#include <string>
class Security {
public:
static std::string encrypt(const std::string& plaintext, const std::string& pubKeyFile);
static std::string decrypt(const std::string& ciphertext, const std::string& privKeyPath);

// Sign a message to create a signature
static std::string sign(const std::string& message, const std::string& privKeyPath);

// Verify a message using its signature. Returns true if valid.
static bool verify(const std::string& message, const std::string& signature, const std::string& pubKeyPath);

};
#endif 