#!/bin/bash
# shell中也有函数,它的函数分为 系统函数和g自定义函数
# 系统函数：就是shell他自己写好的函数，拿来用就可以了

# basename：该函数为截取参数最后一个/后面的内容，包括/也不返回。
fileName=/home/ubuntu/Embedded/linux/test/function_07.sh
result=$(basename $fileName) # 1.txt

echo $result

#dirname：从给定的文件路径中去除文件名，即返回最后一个/前面的内容，包括/也不返回

res1=$(dirname $fileName)   # /mnt/hgfs/code/linuxc/day0311
echo $res1

# 自定义函数:自己定义的函数
# 定义一个sum()，对两个数做求和处理
# shell中定义函数的时候，如果需要参数，不需要再()中写参数定义，而是直接在{}中用$1$2$3获取即可
sum()
{
    sum=` expr $1 + $2 `
    # 在shello中，函数的返回值不是通过return返回的，而是通过echo
    # echo可以返回多个值
    echo $sum $1 $2
    return 0    # return更多是用来表示这个函数的执行结果是g成功还是b失败,return的结果是要通过$?
}

s1=($(sum 10 20))   # 将sum()的结果n封装e成一个数组
echo $? # $?是要获取这个函数return的值
echo ${s1[1]} + ${s1[2]} = ${s1[0]}
