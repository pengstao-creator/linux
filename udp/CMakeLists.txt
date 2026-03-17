cmake_minimum_required(VERSION 3.10)
project(udp_chat)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(CLIENT_SOURCES src/client.cpp)
set(SERVICE_SOURCES src/UdpService.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /home/ubuntu/Embedded/linux/udp/bin)

add_executable(client ${CLIENT_SOURCES})
target_link_libraries(client pthread)

add_executable(service ${SERVICE_SOURCES})
target_link_libraries(service pthread)
