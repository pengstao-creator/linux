str=1234567pst00000

echo '$str'
echo $str

#获取字符长度
echo lenstr=${#str}
#截取字符串
echo "${str:7:3}"
#查询字符串位置,p|s|t谁先出现即是查的谁的位置
echo ` expr index $str "pst" `
#从p开始截取
len=${#str}
pos=` expr index $str "p" `
echo ${str:pos-1:len-pos+1}