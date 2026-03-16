#!/bin/bash

# echo 	Shell 的 echo 指令与 c的 printf指令类似，都是用于字符串的输出。命令格式：
echo "helloworld!!"
echo 'helloworld'
echo helloshell

# 假如输出的结果中，想带上""  就可以使用n转义字符
echo "\"zhangsan\""

# 如果ng想让""中的\n生效，那么 就要加-e
echo -e "hello\nworld"

echo -e "hello\nworld" > 1.txt
echo -e "hello\nworld" >> 1.txt

# 使用printf输出
printf "%-10s %-4s %-8s\n"   姓名  年龄   体重
printf "%-10s %-4d %-4.2f\n" 张三   30   55.551
printf "%-10s %-4d %-4.2f\n" 李四   20   60.551

# read 输入，获取键盘所输入
# echo  后面如果加-n 表示这一行输出时不换行
# echo -n "请输入姓名，年龄:"
# read name age
# echo "姓名:$name   年龄:$age"

# 计算，数学运算
# 方式一  ` expr 数学公式e就可以了`
sum1=` expr 1 + 3 `
echo "1+3=$sum1"

# 方式二   ((变量名=数学公式))
((sum2=1+3))
echo "1+3=$sum2"

num1=10
num2=2
echo ` expr $num1 + $num2 `
echo ` expr $num1 - $num2 `
echo ` expr $num1 \* $num2 `
echo ` expr $num1 / $num2 `