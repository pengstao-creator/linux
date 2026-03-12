#!/bin/bash

# 脚本功能：批量编译src目录下的C文件，编译完成后运行，每次运行前清空bin目录

echo "=== 开始编译和运行流程 ==="

# 1. 清空bin目录
echo "1. 清空bin目录..."
rm -rf ./bin/*
if [ $? -eq 0 ]; then
    echo "bin目录清空成功"
else
    echo "bin目录清空失败"
    exit 1
fi

# 2. 批量编译src目录下的所有.c文件
echo "\n2. 开始编译src目录下的C文件..."

# 切换到src目录
cd ./src || {
    echo "切换到src目录失败"
    exit 1
}

# 编译所有.c文件
for file in *.c; do
    # 提取文件名（不含扩展名）
    filename=$(basename "$file" .c)
    # 编译命令
    gcc "$file" -o "../bin/$filename"
    
    if [ $? -eq 0 ]; then
        echo "编译 $file 成功"
    else
        echo "编译 $file 失败"
        # 编译失败继续处理其他文件
    fi
done

# 切换回test目录
cd ..

# 3. 运行编译生成的所有可执行文件
echo "\n3. 开始运行编译生成的可执行文件..."

for executable in ./bin/*; do
    if [ -x "$executable" ]; then
        echo "\n运行 $(basename "$executable"):" 
        "./$executable"
        echo "-----------------------------------"
    fi
done

echo "4. 清空bin目录..."
rm -rf ./bin/*
if [ $? -eq 0 ]; then
    echo "bin目录清空成功"
else
    echo "bin目录清空失败"
    exit 1
fi

rm -rf *.txt
echo "\n=== 编译和运行流程完成 ==="
