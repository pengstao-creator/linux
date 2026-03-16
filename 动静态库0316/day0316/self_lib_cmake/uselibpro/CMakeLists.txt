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


# 定义链接属性
# 自定义一个属性，属性名叫MY_LIBRARY_PATH g属性值：本地链接库文件 目录
set(MY_LIBRARY_PATH "/mnt/hgfs/code/linuxc/day0316/self_lib_cmake/libpro/lib/")

# 动态库：指定 .so 文件路径
set_target_properties(mymath_shared PROPERTIES 
    IMPORTED_LOCATION "${MY_LIBRARY_PATH}/libmymath_shared.so"
)

# 静态库：指定 .a 文件路径
set_target_properties(mymath_static PROPERTIES 
    IMPORTED_LOCATION "${MY_LIBRARY_PATH}/libmymath_static.a"
)



#4 生成一个可执行文件
add_executable(cmaketest ./src/main.c)
# 链接静态库和动态库
target_link_libraries(cmaketest PRIVATE mymath_shared mymath_static)


#6其他配置
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

