#!/bin/bash
# 编译
gcc ./src/main.c ./src/hello.c -I./inc -o ./bin/helloC

# 最好是给编译后的名字设置一下x权限
chmod 777 ./bin/helloC

# 运行
./bin/helloC