# Boost 网络编程示例

本项目包含了使用 Boost.Asio 库进行网络编程的示例代码，包括异步和同步IO操作，以及协议处理示例。

## 目录结构

```
.
├── CMakeLists.txt          # 主CMake配置文件
├── include/                # 头文件目录
│   └── common.hpp          # 通用头文件
├── src/                    # 源代码目录
│   ├── CMakeLists.txt      # 源代码CMake配置文件
│   ├── async/              # 异步IO示例
│   │   ├── CMakeLists.txt  # 异步IO示例CMake配置文件
│   │   ├── client.cpp      # 异步客户端
│   │   ├── server.cpp      # 异步服务器
│   │   └── server_improved.cpp  # 改进版异步服务器
│   ├── sync/               # 同步IO示例
│   │   ├── CMakeLists.txt  # 同步IO示例CMake配置文件
│   │   ├── client.cpp      # 同步客户端
│   │   ├── client_mt.cpp   # 同步多线程客户端
│   │   ├── server_single.cpp  # 同步单线程服务器
│   │   └── server_mt.cpp   # 同步多线程服务器
│   └── protocols/          # 协议处理示例
│       ├── CMakeLists.txt  # 协议处理示例CMake配置文件
│       ├── sticky_delimiter.cpp  # 带分隔符的粘性数据处理
│       └── sticky_fixed_length.cpp  # 固定长度的粘性数据处理
└── README.md               # 项目说明文件
```

## 编译说明

### 前提条件

- CMake 3.10 或更高版本
- Boost 库 1.66 或更高版本
- C++11 兼容的编译器

### 编译步骤

1. 创建构建目录：
   ```bash
   mkdir build && cd build
   ```

2. 运行CMake：
   ```bash
   cmake ..
   ```

3. 编译项目：
   ```bash
   make
   ```

## 运行示例

### 异步服务器和客户端

1. 启动异步服务器：
   ```bash
   ./src/async/async_server
   ```
   或使用改进版服务器：
   ```bash
   ./src/async/async_server_improved
   ```

2. 启动异步客户端：
   ```bash
   ./src/async/async_client
   ```

### 同步服务器和客户端

1. 启动同步单线程服务器：
   ```bash
   ./src/sync/sync_server_single
   ```
   或启动同步多线程服务器：
   ```bash
   ./src/sync/sync_server_mt
   ```

2. 启动同步客户端：
   ```bash
   ./src/sync/sync_client
   ```
   或启动同步多线程客户端：
   ```bash
   ./src/sync/sync_client_mt
   ```

### 协议处理示例

1. 先启动一个服务器（如同步多线程服务器）
2. 运行带分隔符的粘性数据处理示例：
   ```bash
   ./src/protocols/sticky_delimiter
   ```
3. 运行固定长度的粘性数据处理示例：
   ```bash
   ./src/protocols/sticky_fixed_length
   ```

## 示例说明

### 异步IO示例
- `async_client.cpp`：异步客户端，使用回调函数处理IO操作
- `async_server.cpp`：异步服务器，使用回调函数处理连接和IO操作
- `async_server_improved.cpp`：改进版异步服务器，添加了信号处理、连接统计和更完善的错误处理

### 同步IO示例
- `sync_client.cpp`：同步客户端，使用阻塞IO操作
- `sync_client_mt.cpp`：同步多线程客户端，使用线程处理接收操作
- `sync_server_single.cpp`：同步单线程服务器，一次只能处理一个连接
- `sync_server_mt.cpp`：同步多线程服务器，为每个连接创建一个线程

### 协议处理示例
- `sticky_delimiter.cpp`：使用分隔符处理粘性数据
- `sticky_fixed_length.cpp`：使用固定长度处理粘性数据

## 学习要点

1. **异步IO vs 同步IO**：了解两种IO模型的区别和适用场景
2. **多线程处理**：学习如何使用多线程处理并发连接
3. **协议处理**：了解如何处理网络通信中的粘性数据问题
4. **错误处理**：学习如何处理网络编程中的各种错误情况
5. **CMake构建系统**：学习如何使用CMake管理项目构建

## 注意事项

- 所有示例默认使用端口8888
- 异步服务器示例使用了C++11的lambda表达式和智能指针
- 多线程示例需要链接pthread库
- 改进版异步服务器添加了信号处理，可以通过Ctrl+C停止服务器
