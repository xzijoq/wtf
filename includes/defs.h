#pragma once

#if __clang__ || __GNUC__
    #define where __FILE__, __PRETTY_FUNCTION__, __LINE__
#else
    #define where __function__, __LINE__
#endif

#include <asio.hpp>
#include <asio/ip/tcp.hpp>
#include <iostream>

using std::error_code;
using std::string;

using asio::ip::tcp;

void checkec( error_code ec1, string file = "", string func = "", int line = -1,
              string msg = "" );
