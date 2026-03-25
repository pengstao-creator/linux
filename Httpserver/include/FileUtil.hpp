#ifndef FILEUTIL_HPP_
#define FILEUTIL_HPP_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class FileUtil
{
public:
    // 读取文件内容
    static std::string read(const std::string& path)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file)
        {
            return "";
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    
    // 检查文件是否存在
    static bool exists(const std::string& path)
    {
        std::ifstream file(path);
        return file.good();
    }
    
    // 根据扩展名返回MIME类型
    static std::string mime(const std::string& path)
    {
        size_t dot_pos = path.find_last_of('.');
        if (dot_pos == std::string::npos)
        {
            return "application/octet-stream";
        }
        
        std::string ext = path.substr(dot_pos + 1);
        
        if (ext == "html" || ext == "htm") return "text/html";
        if (ext == "css") return "text/css";
        if (ext == "js") return "application/javascript";
        if (ext == "json") return "application/json";
        if (ext == "png") return "image/png";
        if (ext == "jpg" || ext == "jpeg") return "image/jpeg";
        if (ext == "gif") return "image/gif";
        if (ext == "svg") return "image/svg+xml";
        if (ext == "ico") return "image/x-icon";
        if (ext == "txt") return "text/plain";
        if (ext == "xml") return "application/xml";
        if (ext == "pdf") return "application/pdf";
        
        return "application/octet-stream";
    }
    
    // 安全检查：防止目录遍历攻击
    static bool isSafePath(const std::string& path)
    {
        // 检查是否包含 ".."
        if (path.find("..") != std::string::npos)
        {
            return false;
        }
        return true;
    }
};

#endif // FILEUTIL_HPP_
