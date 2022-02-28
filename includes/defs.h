#pragma once
#if __clang__ || __GNUC__
    #define where __FILE__, __PRETTY_FUNCTION__, __LINE__
#else
    #define where __function__, __LINE__
#endif



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
#include <asio/read.hpp>
#include <asio/read_until.hpp>
#include <asio/socket_base.hpp>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <istream>
#include <memory>
#include <streambuf>
#include <system_error>
#include <thread>

#include "style.h"

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
/*
class Session : public enable_shared_from_this<Session>
{
   public:
    tcp::socket     mSock;
    asio::streambuf mSbuf;


    Session( tcp::socket soc ) : mSock( move( soc ) ) ,mSbuf(30) {}

    void Start();
};
*/

/*
class Server : public enable_shared_from_this<Server>
{
   public:
    //! THIS ORDER MATTERS ---WTF
    io_context&   mIoc;
    tcp::acceptor mAcp;
    int           mPort;
    // Server(tcp::acceptor acp,int port=1331):mAcp(move(acp)),mPort(port)
    //{}
    

    Server( io_context& ioc, int port = 1331 )
        : mIoc( ioc ), mAcp( mIoc ), mPort( port )
    {
        error_code ec;
        mAcp.open( tcp::v4(), ec );
        checkec( ec, where );
        mAcp.set_option( asio::socket_base::reuse_address( true ), ec );
        checkec( ec, where );
        mAcp.bind( tcp::endpoint( asio::ip::address_v4::any(), mPort ), ec );
        checkec( ec, where );
    }
    void fAacp();
};*/

