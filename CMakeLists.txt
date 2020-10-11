cmake_minimum_required(VERSION 3.16)
project(Deconstruct)
project(Reconstruct)

find_package(OpenSSL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall")

add_executable(Deconstruct src/deconstruct.cpp src/base64.cpp)
add_executable(Reconstruct src/reconstruct.cpp src/base64.cpp)

target_include_directories(Deconstruct PUBLIC ${OPENSSL_INCLUDE_DIR} inc/)
target_include_directories(Reconstruct PUBLIC ${OPENSSL_INCLUDE_DIR} inc/)

target_link_libraries(Deconstruct ${OPENSSL_LIBRARIES})
target_link_libraries(Reconstruct ${OPENSSL_LIBRARIES})
