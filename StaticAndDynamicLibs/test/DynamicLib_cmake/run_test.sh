#!/bin/bash

# 创建并进入build目录
mkdir -p build && cd build

# 运行CMake和make
cmake ..
make

# 回到主目录
cd ..

# 编译测试程序
gcc test_mul.c -o test_mul -I./include -L./lib -lmuldynamic

# 运行测试程序
export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
./test_mul