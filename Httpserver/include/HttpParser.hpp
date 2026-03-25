#ifndef HTTPPARSER_HPP_
#define HTTPPARSER_HPP_

#include "HttpRequest.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <sstream>

class HttpParser
{
public:
    static bool parse(boost::asio::streambuf& buf, HttpRequest& req)
    {
        std::istream stream(&buf);
        std::string request_line;
        
        // 读取请求行
        if (!std::getline(stream, request_line))
        {
            return false;
        }
        
        // 解析请求行: METHOD PATH VERSION
        std::istringstream line_stream(request_line);
        line_stream >> req.method >> req.path >> req.version;
        
        // 移除版本字符串中的回车符
        if (!req.version.empty() && req.version.back() == '\r')
        {
            req.version.pop_back();
        }
        
        // 读取请求头
        std::string header_line;
        while (std::getline(stream, header_line) && header_line != "\r")
        {
            size_t colon_pos = header_line.find(':');
            if (colon_pos != std::string::npos)
            {
                std::string key = header_line.substr(0, colon_pos);
                std::string value = header_line.substr(colon_pos + 1);
                
                // 去除首尾空格
                size_t start = value.find_first_not_of(" \t");
                size_t end = value.find_last_not_of(" \t\r");
                if (start != std::string::npos && end != std::string::npos)
                {
                    value = value.substr(start, end - start + 1);
                }
                
                req.headers[key] = value;
            }
        }
        
        return true;
    }
};

#endif // HTTPPARSER_HPP_
