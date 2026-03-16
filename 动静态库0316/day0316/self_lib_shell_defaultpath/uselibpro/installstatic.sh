#!/bin/bash
# -l 后面是要跟链接库名字，但是要注意默认是去/usr/local/lib下去找
gcc ./src/mainstatic.c -laddstatic -o ./bin/mainstatic

