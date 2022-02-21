#define ASIO_NO_DEPRECATED

#include <asio.hpp>
#include <asio/error.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>
#include <asio/ip/basic_endpoint.hpp>

#include <assert.h>
#include <chrono>
#include <cstdint>
#include <system_error>
#include <thread>

#include "defs.h"
#include "main.h"
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

    string ts  = "127.1.12.1w";
    auto   wep = ip::make_address( ts, ec );
    checkec( ec, where );

    //! Server Remote
    const string       ServerIPstring = "127.1.0.0";
    constexpr uint16_t ServerPort     = 1338;
    tcp::endpoint      ServerEndPoint{ ip::make_address( ServerIPstring, ec ),
                                  ServerPort };
    checkec( ec, where );

    auto protocol = tcp::v4();

    //! socket

    print( orStyle, "\nCLIENT ENDS HERE\n" );
    return 0;
}
