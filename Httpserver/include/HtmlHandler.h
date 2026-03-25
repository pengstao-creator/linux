#ifndef HTMLHANDLER_H_
#define HTMLHANDLER_H_

#include "BaseHandler.hpp"
#include <string>

class HtmlHandler : public BaseHandler
{
public:
    HtmlHandler(const std::string& web_root);
    std::string handle(const HttpRequest& req) override;

private:
    std::string _web_root;
};

#endif // HTMLHANDLER_H_
