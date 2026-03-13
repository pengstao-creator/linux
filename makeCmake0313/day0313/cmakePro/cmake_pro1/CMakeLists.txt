# 声明 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称（可自定义）
project(hello)

# 添加可执行文件（第一个参数是目标文件名，后面是源文件）
# 第一个参数就是e生成的可执行文件的名称，建议第一个参数最好和项目名称保持一致
add_executable(hello main.c)