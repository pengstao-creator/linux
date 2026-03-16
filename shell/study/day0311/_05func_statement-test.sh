#!/bin/bash
# test可以对字符串或者数字做判断
# test对字符串做判断
str1=aaaa
test $str1 = aaaa  # 判断str1是否=aaaa
echo "str1=aaaa的结果是:$?" # 真

test $str1 != "aaaa"
echo "str1!=aaaa的结果是:$?"    # 假

test -z $str1
echo $?  # 假 - 1

test -n $str1   # str1的长度是否是不为0
echo $? # 真 - 0

# test还可以对数字 做判断
num1=10
num2=20
num3=30
test $num1 -eq $num2
echo "num1=num2:$?" # 假
test $num1 -ne $num2   
echo "num1!=num2:$?"    #真
test $num1 -gt $num2
echo "num1>num2:$?" # 假
test $num1 -lt $num2
echo "num1<num2:$?" # 真

test $num2 -gt $num1 -a $num2 -lt $num3
echo $?  # 真

# -d : 测试是否是⼀个⽬录⽂件 directory
# -f : 测试是否是⼀个普通⽂件 file
# -w : 测试是否可写
# -r : 测试是否可读
# -x : 测试是否可执⾏
# 语法:   [ -d/-f  跟要判断的路径 ]
fileName=/mnt/hgfs/code/linuxc/day0311
[ -d $fileName ]
echo "判断是否是一个文件夹:"$?

[ -f $fileName ]
echo "判断是否是一个文件:"$?

[ -w $fileName ]
echo "判断是否可写:"$?

[ -r $fileName ]
echo "判断是否可读:"$?

[ -x $fileName ]
echo "判断是否可执行:"$?