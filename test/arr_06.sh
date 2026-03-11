#!/bin/bash

#定义数组
s=()
s[0]=0
s[1]=1
s[2]=2
s[3]=3
s[4]=4

#获取数组中的所有元素
echo ${s[*]}

# 获取数组中的元素个数就是长度${#名字[@]}
echo "数组元素个数:"${#s[@]}

#获取所有元素键值,对于没有i键值的数组，获取的就是所有元素的下标
echo "所有元素的key:"${!s[@]}

# 获取数组指定元素的长度${#名字[index]}
echo ${#s[0]}
echo ${#s[2]}

for a in ${s[*]}
do
    echo $a
done

# shell中也可以存放像c++中的map一样的数组，可以存key-value
declare -A maps
# 给z键值数组赋值
maps[name]=pst
maps[age]=23
maps[sex]=男

# 获取map中所有的key,value
# ${!maps[@]} 获取maps中 所有的key  键值数组，如果想获取value,只能通过key获取value
for key in ${!maps[@]}
do
    echo $key  ${maps[$key]}
done