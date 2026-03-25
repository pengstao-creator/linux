#ifndef HTTPREQUEST_HPP_
#define HTTPREQUEST_HPP_

#include <string>
#include <map>

struct HttpRequest
{
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;
};

#endif // HTTPREQUEST_HPP_
