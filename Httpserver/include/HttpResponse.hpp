#ifndef HTTPRESPONSE_HPP_
#define HTTPRESPONSE_HPP_

#include <string>
#include <sstream>

class HttpResponse
{
public:
    static std::string ok(const std::string& content, const std::string& content_type = "text/plain")
    {
        std::ostringstream response;
        response << "HTTP/1.1 200 OK\r\n"
                 << "Content-Type: " << content_type << "\r\n"
                 << "Content-Length: " << content.length() << "\r\n"
                 << "Connection: close\r\n"
                 << "\r\n"
                 << content;
        return response.str();
    }
    
    static std::string not_found()
    {
        std::string content = "<html><body><h1>404 Not Found</h1></body></html>";
        std::ostringstream response;
        response << "HTTP/1.1 404 Not Found\r\n"
                 << "Content-Type: text/html\r\n"
                 << "Content-Length: " << content.length() << "\r\n"
                 << "Connection: close\r\n"
                 << "\r\n"
                 << content;
        return response.str();
    }
    
    static std::string bad_request()
    {
        std::string content = "<html><body><h1>400 Bad Request</h1></body></html>";
        std::ostringstream response;
        response << "HTTP/1.1 400 Bad Request\r\n"
                 << "Content-Type: text/html\r\n"
                 << "Content-Length: " << content.length() << "\r\n"
                 << "Connection: close\r\n"
                 << "\r\n"
                 << content;
        return response.str();
    }
};

#endif // HTTPRESPONSE_HPP_
