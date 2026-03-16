# 声明伪目标
.PHONY: clean all

# 构建配置变量
TARGET = ./bin/game_app
CC = gcc
SRC_FILES = $(wildcard ./src/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)
INCLUDE_DIR = -I./inc

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJ_FILES)
	@echo "Linking objects..."
	$(CC) $(OBJ_FILES) $(INCLUDE_DIR) -o $(TARGET)
	@echo "Build completed successfully!"

# 编译源文件生成目标文件
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(INCLUDE_DIR) -c $< -o $@

# 清理生成的文件
clean:
	@echo "Cleaning build files..."
	rm -f $(OBJ_FILES) $(TARGET)
	@echo "Clean completed!"

# 运行程序
run:
	@echo "Running the application..."
	$(TARGET)
