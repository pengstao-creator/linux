cmake_minimum_required(VERSION 3.10)
project(sub_div_library)

set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_library(sub_div_static STATIC src/sub.c src/divide.c)

set_target_properties(sub_div_static PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    OUTPUT_NAME "subdivstatic"
)