#include "../include/ApiHandler.h"
#include "../include/HttpResponse.hpp"
#include <sstream>
#include <chrono>
#include <iomanip>

std::string ApiHandler::handle(const HttpRequest& req)
{
    if (req.path == "/api/status")
    {
        return HttpResponse::ok(handleStatus(), "application/json");
    }
    else if (req.path == "/api/users")
    {
        return HttpResponse::ok(handleUsers(), "application/json");
    }
    else if (req.path == "/api/time")
    {
        return HttpResponse::ok(handleTime(), "application/json");
    }
    
    return HttpResponse::not_found();
}

std::string ApiHandler::handleStatus()
{
    return R"({"status": "ok", "message": "Server is running"})";
}

std::string ApiHandler::handleUsers()
{
    return R"({"users": [{"id": 1, "name": "Alice"}, {"id": 2, "name": "Bob"}]})";
}

std::string ApiHandler::handleTime()
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    
    std::string json = R"({"time": ")" + ss.str() + R"("})";
    return json;
}
