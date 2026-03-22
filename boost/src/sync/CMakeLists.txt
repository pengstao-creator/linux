include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(sync_client client.cpp)
target_link_libraries(sync_client ${Boost_LIBRARIES})

add_executable(sync_client_mt client_mt.cpp)
target_link_libraries(sync_client_mt ${Boost_LIBRARIES} pthread)

add_executable(sync_server_single server_single.cpp)
target_link_libraries(sync_server_single ${Boost_LIBRARIES})

add_executable(sync_server_mt server_mt.cpp)
target_link_libraries(sync_server_mt ${Boost_LIBRARIES} pthread)
