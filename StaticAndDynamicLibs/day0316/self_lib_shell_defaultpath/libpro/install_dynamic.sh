#!/bin/bash

# 编译前可以先做一下清理
rm -rf ./lib/*
rm -rf ./src/*.o

# 编译动态库
# 编译动态库第一步：需要先将源文件.c文件编译成.o文件
gcc ./src/sub.c -I./inc -o ./src/sub.o -c


# 第二步：编译动态库
gcc -shared -fPIC -o ./lib/libsubdynamic.so ./src/sub.o

# 将编译后的静态库文件拷贝到/usr/local/lib
echo 123456 | sudo -S cp -rf ./lib/libsubdynamic.so /usr/local/lib

# 将头文件拷贝到/usr/local/include/
echo 123456 | sudo -S  mkdir -p /usr/local/include/mathtest
echo 123456 | sudo -S  cp -rf ./inc/sub.h /usr/local/include/mathtest

# 编译后，可以将.o文件d删除掉
rm -rf ./src/*.o