#!/bin/bash
# 编译
rm -rf ./bin/*

gcc ./src/main.c ./src/hello.c -I./inc -o ./bin/helloC

# 最好是给编译后的名字设置一下x权限
chmod a+x ./bin/helloC

# 运行
./bin/helloC