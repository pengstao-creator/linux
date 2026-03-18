cmake_minimum_required(VERSION 3.10)
project(EpollServer)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# 设置编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

# 包含头文件目录
include_directories(include)

# 源文件
set(SOCKET_SOURCES src/socket.c)
set(SERVER_SOURCES src/EpollService.c)
set(CLIENT_SOURCES src/client.c)

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 创建可执行文件
add_executable(EpollService ${SOCKET_SOURCES} ${SERVER_SOURCES})
add_executable(client ${SOCKET_SOURCES} ${CLIENT_SOURCES})

# 确保bin目录存在
add_custom_target(bin_directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Creating bin directory"
)