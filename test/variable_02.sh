#!/bin/bash

echo "获取脚本的名称$0"
echo "获取脚本参数的个数$#"
echo "获取上一个命令的执行结果$?"
echo "获取执行shell脚本的进程号$$"
echo "获取第一个参数位置$1"
echo "获取第二个参数位置$2"
echo "获取第三个参数位置$3"
echo "获取所有参数位置$*"
echo "获取所有位置的参数$@"

#命令行输入 ./variable_02.sh 1 3 4 6 

#定义变量

name1=pst
name2="pat"
name3='pst'

echo myname=$name1,$name2,$name3