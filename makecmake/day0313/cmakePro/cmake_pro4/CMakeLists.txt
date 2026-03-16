# 根目录下的CMake配置文件，只是用来加载子目录的，不写任何任务逻辑
cmake_minimum_required(VERSION 3.10.0)
project(allpro VERSION 0.1.0 LANGUAGES C)

# 加载子目录
add_subdirectory(pro1)
add_subdirectory(pro2)