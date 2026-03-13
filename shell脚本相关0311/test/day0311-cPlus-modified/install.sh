#!/bin/bash
# 编译
rm -rf ./bin/*
g++ ./sources/*.cpp -I./headers -o ./bin/person

chmod 777 ./bin/person

./bin/person