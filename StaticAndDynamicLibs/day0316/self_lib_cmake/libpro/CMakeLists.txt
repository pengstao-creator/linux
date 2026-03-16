#指定cmake得最低版本
cmake_minimum_required(VERSION 3.10.0)
#项目相关的信息
project(libpro VERSION 0.1.0 LANGUAGES C)

#1测试相关配置 直接拷贝
SET(CMAKE_BUILD_TYPE Debug) #debug模式  动态调试
include(CTest)
enable_testing()

#编译链接库
#1 设置链接库编译输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


#2 设置头文件路径
include_directories(
    ${PROJECT_SOURCE_DIR}/inc #自己目录的头文件
)


#3编译链接库
# 根据add.c文件来生成静态库文件  第一个参数：静态库文件的名字
add_library(mymath_static src/add.c)

# n根据sub.c生成动态库文件  第一个参数：动态库文件名字
add_library(mymath_shared SHARED src/sub.c)


#6其他配置
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

