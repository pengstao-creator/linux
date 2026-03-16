#!/bin/bash
fileName=/mnt/hgfs/code/linuxc/day0311

if [ -f $fileName ]
then
    echo "this is a file....."
else
    echo "this not is a file......"
fi

num1=10
if [ $num1 -lt 10 ]
then 
    echo "num1 < 10"
else if [ $num1 -eq 10 ]
then 
    echo "num1 = 10"
else if [ $num1 -gt 10 ]
then 
    echo "num1 > 10"
else 
    echo "g以上都不满足"
fi
fi
fi

# case 就类似于c中的switch case,只是语法不太一样
str1=A
case $str1 in 
    ABC)
        echo "str1=ABC"
    ;;
    123)
        echo "str1=123"
    ;;
    abc)
        echo "str1=abc"
    ;;
    "A" | "B" | "C")
        echo "A | B | C"
    ;;
    *)
        echo "other..............."
# case写完后，也要有结束
esac