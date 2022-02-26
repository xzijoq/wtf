#define ASIO_NO_DEPRECATED

#include <assert.h>

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
#include <system_error>
#include <thread>

#include "defs.h"
#include "style.h"

#pragma region using
using namespace asio;
using namespace std::chrono;
using namespace std::placeholders;
using asio::ip::tcp;
using fmt::print;
using std::cout;
using std::endl;
using std::string;
#pragma endregion

int main( int argc, char* argv[] )
{
    print( orStyle, "\nCLIENT STARTS HERE\n" );

    error_code ec;
    io_context ioc;

    //! Client local
    string ClientIPstring = "127.1.12.11";
    if ( argc > 1 ) { ClientIPstring = "127.1.12." + string( argv[1] ); }
    constexpr uint16_t ClientPort = 1336;
    tcp::endpoint      ClientEndpoint{ ip::make_address( ClientIPstring, ec ),
                                  ClientPort };
    checkec( ec, where );

    //! Server Remote
    const string       ServerIPstring = "127.1.0.0";
    constexpr uint16_t ServerPort     = 1338;
    tcp::endpoint      ServerEndPoint{ ip::make_address( ServerIPstring, ec ),
                                  ServerPort };
    checkec( ec, where );

    auto protocol = tcp::v4();

    //! buffers
    string rStr = "    ";
    string wStr = "fuck";
    //! socket

    tcp::socket soc( ioc );
    soc.open( protocol );

    soc.set_option( socket_base::reuse_address( true ), ec );
    checkec( ec, where );

    soc.async_connect(
        ServerEndPoint,
        [&ioc, &soc, &rStr, &wStr]( error_code ec )
        {
            if ( ec.value() != 0 ) { checkec( ec, where, "async_connect" ); }

            asio::async_write( soc, buffer( wStr ),
                               []( error_code ec, int len )
                               {
                                   if ( ec.value() != 0 )
                                   {
                                       checkec( ec, where, "async_connect" );
                                   }
                               } );
            asio::async_read( soc, buffer( rStr ),
                              []( error_code ec, int len )
                              {
                                  if ( ec.value() != 0 )
                                  {
                                      checkec( ec, where, "async_connect" );
                                  }
                              } );
        }

    );
    ioc.run();
    print( okStyle, "\nRad: {}", rStr );
    //   tsoc.bind(ServerEndPoint);
    print( orStyle, "\nCLIENT ENDS HERE\n" );
    return 0;
}
