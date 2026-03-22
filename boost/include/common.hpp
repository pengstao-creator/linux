#ifndef COMMON_HPP
#define COMMON_HPP

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>

using namespace boost::asio;
using boost::asio::ip::tcp;
namespace asio = boost::asio;

const int BUFFER_SIZE = 1024;
const int PORT = 8888;

#endif // COMMON_HPP
