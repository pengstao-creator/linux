#!/bin/bash
# -l 后面是要跟链接库名字，但是要注意默认是去/usr/local/lib下去找
# 如果链接库不在默认路径，那么就要加-L链接库文件所在目录
gcc ./src/mainstatic.c -I./inc -L/mnt/hgfs/code/linuxc/day0316/self_lib_shell/libpro/lib -laddstatic -o ./bin/mainstatic

