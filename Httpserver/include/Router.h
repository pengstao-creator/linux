#ifndef ROUTER_H_
#define ROUTER_H_

#include "BaseHandler.hpp"
#include <string>

class Router
{
public:
    // 根据请求路径判断处理器类型
    static HandlerType route(const std::string& path)
    {
        if (path.find("/api/") == 0)
        {
            return HandlerType::API;
        }
        return HandlerType::HTML;
    }
};

#endif // ROUTER_H_
