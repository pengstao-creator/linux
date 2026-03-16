#!/bin/bash

filename=/home/ubuntu/Embedded/linux/test/flowcontrol_05.sh

if [ -f $filename ]
then
    echo 是文件
else
    echo 不是文件
fi

# //比较运算符
# -eq 等于
# -ne 不等于
# -ge ⼤于等于
# -le ⼩于等于
# -gt ⼤于
# -lt ⼩于
# //逻辑运算
# -a 且的关系连接多个命令 and
# -o 或的关系连接多个命令 or

# read num1 num2 num3

num1=1
num2=2
num3=3
if [ $num1 -eq $num2 ]
then
    echo num1=num2
else if [ $num1 -ne $num3 ]
then 
    echo num1!=num2
else if [ $num1 -ge $num3 ]
then 
    echo "num1>=num2"
else if [ $num1 -le $num3 ]
then 
    echo "num1<=num2"
else if [ $num1 -gt $num3 ]
then 
    echo "num1>num2"
else if [ $num1 -lt $num3 ]
then 
    echo "num1<num2"
else if [ $num1 -a $num3 ]
then 
    echo "num1&&num2"
else if [ $num1 -o $num3 ]
then 
    echo "num1||num2"
fi
fi
fi
fi
fi
fi
fi
fi

i=1
sum=0
while [ $i -le 100 ]
do
    sum=` expr $i + $sum `
    ((i++))
done
echo $sum

list=` ls / `
for f in $list
do
    echo $f
done