#!/bin/bash

#输出"pst"需要使用转义
echo "\"pst\""

#使字符串中的\n生效
echo -e "p\ns\nt"

#使用printf输出,和C语言的格式控制方式一致
printf "%-5d年%-5d月%-5d日\n" 2026 3 11

#获取键盘输入rade,-n表示不换行
# echo -n myname=
# read name 
# echo 我的名字是:$name

#数学计算，+ - \* /
sum1=` expr 1 + 2 `
((sum2=1+2))
echo $sum1 $sum2

#逻辑判断 
#test可以对字符串和数字进行判断
s=1314
test $s = 1314
echo $? 
test $s != 1314
echo $? 

test -t $s #测试字符串⻓度是否为0
echo $?

test -n $s #s的长度是否不为0
echo $?


# -d : 测试是否是⼀个⽬录⽂件 directory
# -f : 测试是否是⼀个普通⽂件 file
# -w : 测试是否可写
# -r : 测试是否可读
# -x : 测试是否可执⾏

filename=/home/ubuntu/Embedded/linux/test/func_04.sh

[ -d $filename ]
echo 测试是否是⼀个⽬录⽂件:$?

[ -f $filename ]
echo 测试是否是⼀个普通⽂件:$?
[ -r $filename ]
echo 测试是否可写:$?
[ -w $filename ]
echo 测试是否可读:$?
[ -x $filename ]
echo 测试是否可执⾏:$?
