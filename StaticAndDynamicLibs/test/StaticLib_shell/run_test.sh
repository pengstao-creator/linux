#!/bin/bash

# 编译静态库
./StaticLibrary.sh

# 编译测试程序
gcc test_sub.c -o test_sub -I./include -L./lib -lsubstatic

# 运行测试程序
./test_sub