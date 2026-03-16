#指定cmake得最低版本
cmake_minimum_required(VERSION 3.10.0)
#项目相关的信息
project(allpro VERSION 0.1.0 LANGUAGES C)

# 添加子目录
add_subdirectory(libpro)
add_subdirectory(uselibpro)