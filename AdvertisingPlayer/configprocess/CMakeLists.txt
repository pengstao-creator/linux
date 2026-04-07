cmake_minimum_required(VERSION 3.10)

# 项目名称
project(configprocess)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rd-lib/include
)

# 查找依赖库
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

# 源文件
set(SOURCES
    src/main.c
    src/configprocess.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rd-lib/src/mongoose.c
)

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# 可执行文件
add_executable(configprocess ${SOURCES})

# 链接库
target_link_libraries(configprocess
    ${GLIB_LIBRARIES}
    pthread
)


