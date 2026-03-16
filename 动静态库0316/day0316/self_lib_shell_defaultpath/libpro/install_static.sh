#!/bin/bash

# 编译前可以先做一下清理
rm -rf ./lib/*
rm -rf ./src/*.o

# 编译静态库
# 编译静态库第一步：需要先将源文件.c文件编译成.o文件
gcc ./src/add.c -I./inc -o ./src/add.o -c


# 第二步：就是将.o文件编译成静态库
# 链接库中只有源文件，不包含头文件的
ar -rcs ./lib/libaddstatic.a ./src/add.o

# 将编译后的静态库文件拷贝到/usr/local/lib
echo 123456 | sudo -S cp -rf ./lib/libaddstatic.a /usr/local/lib

# 将头文件拷贝到/usr/local/include/
echo 123456 | sudo -S  mkdir -p /usr/local/include/mathtest
echo 123456 | sudo -S  cp -rf ./inc/add.h /usr/local/include/mathtest

# 编译后，可以将.o文件d删除掉
rm -rf ./src/*.o