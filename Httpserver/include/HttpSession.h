#ifndef HTTPSESSION_H_
#define HTTPSESSION_H_

#include "common.h"
#include <memory>
#include <string>
#include <boost/asio.hpp>

class HttpSession : public std::enable_shared_from_this<HttpSession>
{
public:
    HttpSession(Ip::tcp::socket socket, const std::string& web_root);
    void start();

private:
    void doRead();
    void onRead(const Sys::error_code& ec, std::size_t bytes_transferred);
    void doWrite(const std::string& response);
    void onWrite(const Sys::error_code& ec, std::size_t bytes_transferred);

    Ip::tcp::socket _socket;
    std::string _web_root;
    boost::asio::streambuf _request_buf;
};

#endif // HTTPSESSION_H_
