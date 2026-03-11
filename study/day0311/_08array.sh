#!/bin/bash
# 定义数组n方式一：
stus=()

# 给数组添加元素
stus[0]=zhangsan
stus[1]=xiaoming
stus[2]=xiaohua

# 定义数组的方式二：定义数组的同时添加元素,注意i赋值的时候，不要加","
names=(zs ls ww)

#三 使用
#1 获取元素的值
echo ${stus[0]}
echo ${stus[1]}

# 获取数组中 的所有元素${名字[*]}
echo ${names[*]}

# 获取数组中的元素个数就是长度${#名字[@]}
echo "数组元素个数:"${#names[@]}

#获取所有元素键值,对于没有i键值的数组，获取的就是所有元素的下标
echo "所有元素的key:"${!names[@]}

# 获取数组指定元素的长度${#名字[index]}
echo ${#stus[0]}
echo ${#stus[2]}

# 遍历数组打印元素,注意：如果ia想遍历拿到数组中的每一个u元素，那么是要对数组中的元素 做遍历
for val in ${stus[*]}
do
    echo $val
done

# shell中也可以存放像c++中的map一样的数组，可以存key-value
declare -A maps
# 给z键值数组赋值
maps[name]=zhangsan
maps[age]=30
maps[sex]=男

# 获取map中所有的key,value
# ${!maps[@]} 获取maps中 所有的key  键值数组，如果想获取value,只能通过key获取value
for key in ${!maps[@]}
do
    echo $key  ${maps[$key]}
done