#pragma once
#if __clang__ || __GNUC__
    #define where __FILE__, __PRETTY_FUNCTION__, __LINE__
#else
    #define where __function__, __LINE__
#endif
//#define ASIO_ENABLE_HANDLER_TRACKING

#include <asio.hpp>
#include <asio/error.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>
#include <asio/ip/basic_endpoint.hpp>
#include <asio/read.hpp>
#include <asio/read_until.hpp>
#include <asio/socket_base.hpp>
#include <asio/steady_timer.hpp>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <istream>
#include <memory>
#include <streambuf>
#include <system_error>
#include <thread>
#include <vector>

#include "style.h"

#define BACKWARD_HAS_DWARF     1
#define BACKWARD_HAS_LIBUNWIND 1
#include <backward.hpp>

#pragma region using

using namespace std::placeholders;

using asio::ip::tcp;
using fmt::print;

using std::cout;
using std::enable_shared_from_this;
using std::endl;
using std::error_code;
using std::move;
using std::string;

using asio::async_read;
using asio::async_read_until;
using asio::async_write;
using asio::buffer;
using asio::io_context;
using asio::ip::tcp;

#pragma endregion
#define ASIO_NO_DEPRECATED
void checkec( error_code ec1, string file = "", string func = "", int line = -1,
              string msg = "" );

void ShowSock( tcp::socket const& sock );
