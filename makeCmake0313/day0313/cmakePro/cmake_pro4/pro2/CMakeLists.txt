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

#3 引入头文件路径
include_directories(
     ${PROJECT_SOURCE_DIR}/inc
)

#4 动态搜索c文件
#`file(GLOB)`：CMake 内置命令，用于匹配指定模式的文件并将路径存入变量。
file(GLOB_RECURSE SRCFILES
  ${CMAKE_SOURCE_DIR}/pro2/src/*.c  # 匹配src目录下所有.c文件
)


#5 生成一个可执行文件
#add_executable(cmaketest ./src/main.c ./src/hello.c)
add_executable(project2 ${SRCFILES})



#6其他配置
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

