#ifndef HANDLERFACTORY_H_
#define HANDLERFACTORY_H_

#include "BaseHandler.hpp"
#include "HtmlHandler.h"
#include "ApiHandler.h"
#include <memory>
#include <string>

class HandlerFactory
{
public:
    // 根据处理器类型创建对应的Handler
    static std::unique_ptr<BaseHandler> create(HandlerType type, const std::string& web_root)
    {
        switch (type)
        {
            case HandlerType::HTML:
                return std::unique_ptr<BaseHandler>(new HtmlHandler(web_root));
            case HandlerType::API:
                return std::unique_ptr<BaseHandler>(new ApiHandler());
            default:
                return nullptr;
        }
    }
};

#endif // HANDLERFACTORY_H_
