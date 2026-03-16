#指定cmake得最低版本
cmake_minimum_required(VERSION 3.10.0)

#项目相关的信息
project(cmakePro3 VERSION 0.1.0 LANGUAGES C)


# 添加编译开关（默认开启 Debug 模式）
option(ENABLE_DEBUG "Enable debug mode" ON)
# 如果ENABLE_DEBUGi开启了，那么编译模式就要i使用debug，否则就使用Release
if(ENABLE_DEBUG)
    add_definitions(-DDEBUG_MODE)
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
else()
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
endif()


#2定义可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#3 引入头文件路径
include_directories(
     ${PROJECT_SOURCE_DIR}/inc
)

#4 动态搜索c文件
#`file(GLOB)`：CMake 内置命令，用于匹配指定模式的文件并将路径存入变量。
file(GLOB_RECURSE SRCFILES
  ${CMAKE_SOURCE_DIR}/src/*.c  # 匹配src目录下所有.c文件
)


#5 生成一个可执行文件
# add_executable(cmaketest ./src/main.c ./src/game.c)
add_executable(cmakePro3 ${SRCFILES})

# 安装可执行文件到/usr/local/bin目录下
install(TARGETS cmakePro3 DESTINATION bin)

file(GLOB_RECURSE SRCHS
  ${CMAKE_SOURCE_DIR}/inc/*.h  # 匹配src目录下所有.h文件
)

# 安装头文件/usr/local/include
install(FILES ${SRCHS} DESTINATION include)

#6其他配置
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

