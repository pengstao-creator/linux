cmake_minimum_required(VERSION 3.10)

project(mainprocess)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rd-lib/include
)

find_package(PkgConfig REQUIRED)
set(ENV{PKG_CONFIG_PATH} "/usr/local/lib/x86_64-linux-gnu/pkgconfig:/usr/local/lib/pkgconfig:/usr/local/share/pkgconfig:$ENV{PKG_CONFIG_PATH}")
pkg_check_modules(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
include_directories(/usr/local/lib/x86_64-linux-gnu/glib-2.0/include)
link_directories(${GLIB_LIBRARY_DIRS})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

set(SOURCES
    src/main.c
    src/sendconfig.c
    src/requestMethod.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/src/log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/src/tool.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/src/msgQueue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rd-lib/src/elog.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rd-lib/src/elog_async.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rd-lib/src/elog_buf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rd-lib/src/elog_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rd-lib/port/elog_port.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_executable(mainprocess ${SOURCES})

target_link_libraries(mainprocess
    ${GLIB_LIBRARIES}
    ${CURL_LIBRARIES}
    pthread
)
