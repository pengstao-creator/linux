#!/bin/bash

# 创建并进入build目录
mkdir -p build && cd build

# 运行CMake和make
cmake ..
make

# 回到主目录
cd ..

# 编译测试程序
gcc test_sub_div.c -o test_sub_div -I./include -L./lib -lsubdivstatic

# 运行测试程序
./test_sub_div