cmake_minimum_required(VERSION 3.10)
project(mul_library)

set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_library(mul_dynamic SHARED src/mul.c)

set_target_properties(mul_dynamic PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    OUTPUT_NAME "muldynamic"
)

# 安装配置
install(TARGETS mul_dynamic
    LIBRARY DESTINATION /usr/local/lib
)

install(FILES include/mul.h
    DESTINATION /usr/local/include
)
