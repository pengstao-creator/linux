#!/bin/bash

# 卸载动态库和头文件
echo "正在卸载动态库和头文件..."
sudo rm -f /usr/local/lib/libmuldynamic.so
sudo rm -f /usr/local/include/mul.h
sudo ldconfig  # 更新动态链接库缓存
echo "卸载完成！"
