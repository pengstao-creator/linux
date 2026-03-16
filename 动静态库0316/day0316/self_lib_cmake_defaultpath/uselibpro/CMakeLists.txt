#指定cmake得最低版本
cmake_minimum_required(VERSION 3.10.0)
#项目相关的信息
project(project2 VERSION 0.1.0 LANGUAGES C)

#1测试相关配置 直接拷贝
SET(CMAKE_BUILD_TYPE Debug) #debug模式  动态调试
include(CTest)
enable_testing()

#2定义可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#3 引入头文件路径,这个地方的头文件是指当前这个项目它自己的u头文件
include_directories(
     ${PROJECT_SOURCE_DIR}/inc
)


#4 生成一个可执行文件
add_executable(cmaketest ./src/main.c)
# 链接静态库和动态库,s只是说e这个a地方它就会去默认路径i下去找e链接库
target_link_libraries(cmaketest PRIVATE mymath_shared mymath_static)


#6其他配置
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

