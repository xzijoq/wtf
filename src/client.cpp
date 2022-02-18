#define ASIO_NO_DEPRECATED

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
#include "main.h"
#include "style.h"

#pragma region using
using fmt::print;
using std::cout;
using std::endl;
using std::string;
using namespace std::chrono;
using ull = unsigned long long;
using namespace asio;
using asio::ip::tcp;
using namespace std::placeholders;
#pragma endregion

void writeToTcpSocket( tcp::socket& soc );
int  main( int argc, char* argv[] )
{
    print( orStyle, "\nCLIENT STARTS HERE\n" );
    cout << nanoseconds( 2s ).count();
    error_code ec;
    io_context ioc;

    //! Client local
    string ClientIPstring = "127.1.12.1";
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

    //! Buffers
    string       inputbuf = "                          ";
    string const outbuf   = "FuckYou";
    auto         inb      = buffer( inputbuf, sizeof( inputbuf ) );
    auto         oub      = buffer( outbuf, sizeof( outbuf ) );

    // &b=c;

    //! Socket Stuff
    tcp::socket soc( ioc );

    soc.open( protocol, ec );
    checkec( ec, where );

    soc.set_option( socket_base::reuse_address( true ), ec );
    checkec( ec, where );

    soc.bind( ClientEndpoint, ec );
    checkec( ec, where );

    soc.connect( ServerEndPoint, ec );
    checkec( ec, where, "connection to server" );

    asio::write( soc, oub, ec );
    checkec( ec, where );

    // auto rb = soc.read_some( inb, ec );

    //  asio::read( soc, inb, ec );
    // if ( ec.value() != 0 && ec.value() != 2 ) { checkec( ec, where ); }

    asio::streambuf insb;
    asio::read_until( soc, insb, '\n', ec );
    if ( ec.value() != 0 && ec.value() != 2 ) { checkec( ec, where ); }


    std::istream ins( &insb );
    std::getline( ins, inputbuf );

    print( liStyle, "\nServerSays: {}", inputbuf );

    print( orStyle, "\nCLIENT ENDS HERE\n" );
    return 0;
}

// !todo how to bind client to a specific port without specifying the protocol,
// which can be determined by asio::connect
