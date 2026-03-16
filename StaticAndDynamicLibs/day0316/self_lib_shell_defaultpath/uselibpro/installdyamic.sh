#!/bin/bash
# -l 后面是要跟链接库名字，但是要注意默认是去/usr/local/lib下去找
gcc ./src/maindynamic.c -lsubdynamic -o ./bin/maindynamic

# ~/.bashrc 这个文件刚刚配置过，但是它的路径i是/mnt下的
# 当动态链接库在默认路径下时，不需要再配置 动态库搜索路径了