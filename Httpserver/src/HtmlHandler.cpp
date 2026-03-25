#include "../include/HtmlHandler.h"
#include "../include/HttpResponse.hpp"
#include "../include/FileUtil.hpp"
#include <iostream>

HtmlHandler::HtmlHandler(const std::string& web_root)
    : _web_root(web_root)
{
}

std::string HtmlHandler::handle(const HttpRequest& req)
{
    // 安全检查
    if (!FileUtil::isSafePath(req.path))
    {
        return HttpResponse::not_found();
    }
    
    // 构建文件路径
    std::string file_path;
    if (req.path == "/")
    {
        file_path = _web_root + "/index.html";
    }
    else
    {
        file_path = _web_root + req.path;
    }
    
    // 检查文件是否存在
    if (!FileUtil::exists(file_path))
    {
        return HttpResponse::not_found();
    }
    
    // 读取文件内容
    std::string content = FileUtil::read(file_path);
    if (content.empty())
    {
        return HttpResponse::not_found();
    }
    
    // 获取MIME类型
    std::string mime_type = FileUtil::mime(file_path);
    
    return HttpResponse::ok(content, mime_type);
}
