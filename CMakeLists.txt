cmake_minimum_required(VERSION 3.15)
project(CustomProtocol)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This line is CRITICAL. It ensures the Crypto headers are found.
find_package(Poco REQUIRED COMPONENTS Foundation Util JSON Net Crypto)

add_executable(CustomProtocol
    src/main.cpp
    src/Protocol.cpp
    src/Server.cpp
    src/Client.cpp
    src/security.cpp
)

target_include_directories(CustomProtocol PRIVATE include)

# This line is CRITICAL. It ensures your program links to the Crypto library.
target_link_libraries(CustomProtocol PRIVATE
    Poco::Foundation
    Poco::Util
    Poco::JSON
    Poco::Net
    Poco::Crypto
)


add_executable(CryptoTest
    src/main_test.cpp
    src/security.cpp
)

target_include_directories(CryptoTest PRIVATE include)

target_link_libraries(CryptoTest PRIVATE Poco::Crypto)