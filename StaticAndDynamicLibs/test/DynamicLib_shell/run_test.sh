#!/bin/bash

# 编译动态库
./DynamicLibrary.sh

# 编译测试程序
gcc test_add.c -o test_add -I./include -L./lib -ladddynamic

# 运行测试程序
export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
./test_add