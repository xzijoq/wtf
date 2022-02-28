#include <fmt/color.h>

#include <asio/basic_socket.hpp>
#include <asio/io_context.hpp>
#include <asio/read_until.hpp>
#include <asio/socket_base.hpp>
#include <asio/streambuf.hpp>
#include <cstdio>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>

#include "defs.h"
using namespace std::chrono;

class Session
{
   public:
    tcp::socket                    mSock;
    tcp::endpoint                  mServerEndpoint;
    asio::streambuf                mSbuf;
    asio::posix::stream_descriptor ins;
    asio::streambuf                mCRdStr;
    string                         rBuf;


    Session( tcp::socket soc, tcp::endpoint sep )
        : mSock( move( soc ) ),
          mServerEndpoint( sep ),
          ins( mSock.get_executor(), STDIN_FILENO )
    {
    }
    void AsyncConnectGo()
    {
        mSock.async_connect( mServerEndpoint,
                             [this]( error_code ec )
                             {
                                 if ( ec.value() != 0 )
                                 {
                                     checkec( ec, where );
                                     return;
                                 }

                                 ShowSock( mSock );
                                 AsyncRead();
                                 AsyncWrite();
                             } );
    }
    void AsyncRead()
    {
        async_read_until( mSock, mSbuf, '\n',
                          [this]( error_code ec, int len )
                          {
                              if ( ec.value() != 0 )
                              {
                                  checkec( ec, where );
                                  mSock.close();
                                  return;
                              }

                              string s;
                              std::getline( std::istream( &mSbuf ), s );
                              cout.flush();

                              print( bvStyle, "{}", s );
                              cout << endl;
                              AsyncRead();
                          } );
    }

    void AsyncWrite()
    {
        error_code ec;
        async_read_until( ins, mCRdStr, '\n',
                          [this]( error_code ec, int len )
                          {
                              if ( ec.value() != 0 )
                              {
                                  checkec( ec, where );
                                  return;
                              }

                              std::getline( std::istream( &mCRdStr ), rBuf );

                              // print( orStyle, "{} :", rBuf );
                              // cout << "\n" << endl;
                              //! IMP AS SERVEWR READS UNTIL THIS
                              rBuf.append( "\n" );
                              async_write( mSock, buffer( rBuf ),
                                           [this]( error_code ec, int wr )
                                           {
                                               if ( ec.value() != 0 )
                                               {
                                                   checkec( ec, where );
                                                   mSock.close();
                                                   return;
                                               }
                                               rBuf = "";
                                               AsyncWrite();
                                           } );
                          } );
    }
};

int main( int argc, char *argv[] )
{
    print( orStyle, "\nCLIENT STARTS HERE\n" );

    error_code ec;
    io_context ioc;

    string s;

    asio::streambuf d;

    tcp::socket s4( ioc );

    //! Client local
    string ClientIPstring = "127.1.12.11";
    if ( argc > 1 ) { ClientIPstring = "127.1.12." + string( argv[1] ); }
    constexpr uint16_t ClientPort = 1336;
    tcp::endpoint ClientEndpoint{ asio::ip::make_address( ClientIPstring, ec ),
                                  ClientPort };
    checkec( ec, where );

    //! Server Remote
    const string       ServerIPstring = "127.0.0.1";
    constexpr uint16_t ServerPort     = 1331;
    tcp::endpoint ServerEndPoint{ asio::ip::make_address( ServerIPstring, ec ),
                                  ServerPort };
    checkec( ec, where );

    auto protocol = tcp::v4();

    //! socket
    tcp::socket soc{ ioc };
    soc.open( protocol );
    soc.set_option( asio::socket_base::reuse_address( true ) );

    soc.bind( ClientEndpoint );

    Session S1( move( soc ), ServerEndPoint );

    S1.AsyncConnectGo();

    std::thread t( [&ioc]() { ioc.run(); } );
    t.join();
    print( orStyle, "\nCLIENT ENDS HERE\n" );
    return 0;
}
