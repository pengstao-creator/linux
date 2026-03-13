#.PHONY 的作用就是显式声明这些目标是 “伪目标”，让 make 忽略同名文件的存在，始终执行目标对应的命令
.PHONY:clean

# 在Makefile中，可以把下面的命令中的东西通过变量进行定义，如果这些发生改变，那么就可以只a修改变量就可以了
OUTPUT=./bin/hello
GCC=gcc
SRC=$(wildcard ./src/*.c)	# 匹配src/所有以.c结尾的文件
OBJ=$(SRC:%.c=%.o)	# ./src/game.o ./src/main.o
override CONFIG=-I./inc

# 编译的时候，就要依赖 src/所有的.o文件
compile:$(OBJ)	# ./src/game.o ./src/main.o
	$(GCC) $(^) $(CONFIG)  -o $(OUTPUT)
# gcc ./src/main.o ./src/game.o -I./inc -o ./bin/hello

# x执行compile这个目标时，需要依赖.o结尾的n文件，但是这个时候.o结尾的文件 还没有，所以那么他就会去执行
#下面的模式规则， 通过.c文件u去生成.o文件

# 所有的.o都要依赖于.c  
# %.o:%.c叫做模式规则，将所有.c文件编译成.o文件
# 在底层，会通过下面的目标和依赖，去找到src下所有的.c文件，然后会有一个依赖列表
# game.o:game.c   main.o:mian.c
%.o:%.c
	$(GCC) $(<) $(CONFIG)  -o $(@) -c

clean:
	$(RM) $(OUTPUT)