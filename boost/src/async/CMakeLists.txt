include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(async_client client.cpp)
target_link_libraries(async_client ${Boost_LIBRARIES})

add_executable(async_server server.cpp)
target_link_libraries(async_server ${Boost_LIBRARIES})

add_executable(async_server_improved server_improved.cpp)
target_link_libraries(async_server_improved ${Boost_LIBRARIES} pthread)
