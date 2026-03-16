#!/bin/bash

# 循环 while  for
# while循环 - 从1加到100
i=1
sum=0
while [ $i -le 100 ]    # i<=100
do
    # 写加法逻辑
    sum=` expr $i + $sum `
    # i还要自增1
    i=` expr $i + 1 `
done
echo "循环结果是:$sum"

# for循环
list=`ls /`
# 对list做遍历，打印返回来的所有的文件名

for var in $list   
do
    echo $var
done

