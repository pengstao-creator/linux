#ifndef APIHANDLER_H_
#define APIHANDLER_H_

#include "BaseHandler.hpp"
#include <string>

class ApiHandler : public BaseHandler
{
public:
    std::string handle(const HttpRequest& req) override;

private:
    std::string handleStatus();
    std::string handleUsers();
    std::string handleTime();
};

#endif // APIHANDLER_H_
