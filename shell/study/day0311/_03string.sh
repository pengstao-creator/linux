#!/bin/bash
#1 字符串可以用单引号，也可以用双引号，也可以不用引号
str1='aaaaa'
str2="bbbbbb"
str3=cccccc
echo $str1,$str2,$str3

#2 单引号里的任何字符都会原样输出，单引号字符串中的变量是无效的；
echo '$str1'
echo "$str1"

# 单引号字符串中不能出现单独一个的单引号（对单引号使用转义符后也不行），但可成对出现，作为字符串拼接使用。
echo 'str1='$str1';'    # str1=aaaaa;

# 使用双引号拼接,双引号里面的只要有变量的获取都会拼接，但是’’默认变量不会拼接，如果要拼接嵌套‘$变量’
echo "str1=$str1"str2="$str2"

# 3 字符串其他操作
str4=helloworld!!!!!!
# 获取字符串长度
echo "str4的长度是:"${#str4}
# 截取字符串，比如想截取str4中的world
# 第一个数字是下标，从0开始数  i第二个数字是说：往后取几个
echo "${str4:5:5}"

# 查找某种字符所在位置
# 比如：想查找str4h中第一个w出现的位置
# "we" 意思是，要查询str4中，w | e第一次出现的位置,谁先出现就直接返回
echo ` expr index  $str4 "we" `

# 获取str4中从w开始，后续所有字符  截取字符串，结果是"world!!!!!!
position=` expr index $str4 "w" `
len=${#str4}
echo ${str4:position-1:len-position+1}


# 上面这个有啥用，最常见的场景就是:
fileName=test.txt
# 获取上面文件的后缀
p1=` expr index $fileName "." `
l1=${#fileName}
echo "文件后缀:${fileName:p1-1:l1-p1+1}"