# 指定CMake最低版本要求
cmake_minimum_required(VERSION 3.10.0)

# 子项目信息
project(project2 VERSION 0.1.0 LANGUAGES C)

# 设置构建类型为Debug
set(CMAKE_BUILD_TYPE Debug)

# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 搜索源文件
file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.c
)

# 生成可执行文件
add_executable(project2 ${SOURCE_FILES})
