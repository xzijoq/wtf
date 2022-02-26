#pragma once

#if __clang__ || __GNUC__
    #define where __FILE__, __PRETTY_FUNCTION__, __LINE__
#else
    #define where __function__, __LINE__
#endif

#define ASIO_NO_DEPRECATED

#include <assert.h>

#include <array>
#include <asio.hpp>
#include <asio/error.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>
#include <asio/ip/basic_endpoint.hpp>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <system_error>
#include <thread>

#include "style.h"

#pragma region using
using namespace asio;
using namespace std;
using namespace std::chrono;
using namespace std::placeholders;

using asio::ip::tcp;
using fmt::print;
using std::cout;
using std::endl;
using std::error_code;

#pragma endregion

void checkec( error_code ec1, string file = "", string func = "", int line = -1,
              string msg = "" );

class Session
{
   public:
    tcp::socket sock;

    string rStr = "1111";
    string wStr = "omeg";

    Session( tcp::socket soc ) : sock( move( soc ) ) {}

    void fwstr();

    void frstr();
    void start();

};
