# 指定CMake最低版本要求
cmake_minimum_required(VERSION 3.10.0)

# 项目信息
project(cmake_demo VERSION 0.1.0 LANGUAGES C)

# 启用测试
include(CTest)
enable_testing()

# 添加子目录
add_subdirectory(pro1)
add_subdirectory(pro2)

# CPack配置
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
