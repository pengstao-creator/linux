include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(sticky_delimiter sticky_delimiter.cpp)
target_link_libraries(sticky_delimiter ${Boost_LIBRARIES})

add_executable(sticky_fixed_length sticky_fixed_length.cpp)
target_link_libraries(sticky_fixed_length ${Boost_LIBRARIES})
