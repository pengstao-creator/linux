#ifndef BASEHANDLER_HPP_
#define BASEHANDLER_HPP_

#include "HttpRequest.hpp"
#include <string>

// 处理器类型枚举
enum class HandlerType
{
    HTML,  // 静态文件处理器
    API    // API处理器
};

// 抽象基类
class BaseHandler
{
public:
    virtual ~BaseHandler() = default;
    virtual std::string handle(const HttpRequest& req) = 0;
};

#endif // BASEHANDLER_HPP_
