#include "Security.hpp"
#include <iostream>
#include <string>
int main() {
std::cout << "--- Starting Crypto Self-Test ---" << std::endl;
try {
// Test Data
std::string original_message = "{\"id\":\"test-001\",\"temperature\":99.9}";
std::cout << "Original Message: " << original_message << std::endl;

// Test Encrypt/Decrypt Cycle
    std::cout << "\n--- Testing Encrypt/Decrypt ---" << std::endl;
    std::string encrypted = Security::encrypt(original_message, "public.pem");
    std::cout << "Encryption successful." << std::endl;
    std::string decrypted = Security::decrypt(encrypted, "private.pem");
    std::cout << "Decryption successful." << std::endl;
    std::cout << "Decrypted Message: " << decrypted << std::endl;

    if (original_message == decrypted) {
        std::cout << "SUCCESS: Decrypted message matches original." << std::endl;
    } else {
        std::cout << "FAILURE: Decrypted message does NOT match original." << std::endl;
    }

    // Test Sign/Verify Cycle
    std::cout << "\n--- Testing Sign/Verify ---" << std::endl;
    std::string signature = Security::sign(original_message, "private.pem");
    std::cout << "Signing successful." << std::endl;
    bool is_valid = Security::verify(original_message, signature, "public.pem");
    std::cout << "Verification successful." << std::endl;
    std::cout << "Signature valid: " << (is_valid ? "Yes" : "No") << std::endl;

    if (is_valid) {
        std::cout << "SUCCESS: Signature is valid." << std::endl;
    } else {
        std::cout << "FAILURE: Signature is NOT valid." << std::endl;
    }

} catch (const std::exception& e) {
    std::cerr << "An exception occurred: " << e.what() << std::endl;
    return 1;
}

return 0;

}