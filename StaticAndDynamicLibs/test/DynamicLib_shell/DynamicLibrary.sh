#!/bin/bash

# 清理旧文件
rm -rf ./lib/*
rm -rf ./*.o

# 编译动态库
gcc -c ./src/add.c -o ./add.o -I./include
gcc -shared -fPIC -o ./lib/libadddynamic.so ./add.o -I./include
rm -rf ./*.o

echo "动态库编译完成！"

# 安装功能
install_lib() {
    echo "正在安装动态库和头文件..."
    sudo cp ./lib/libadddynamic.so /usr/local/lib/
    sudo cp ./include/add.h /usr/local/include/
    sudo ldconfig  # 更新动态链接库缓存
    echo "安装完成！"
}

# 卸载功能
uninstall_lib() {
    echo "正在卸载动态库和头文件..."
    sudo rm -f /usr/local/lib/libadddynamic.so
    sudo rm -f /usr/local/include/add.h
    sudo ldconfig  # 更新动态链接库缓存
    echo "卸载完成！"
}

# 处理命令行参数
if [ "$1" == "install" ]; then
    install_lib
elif [ "$1" == "uninstall" ]; then
    uninstall_lib
fi
