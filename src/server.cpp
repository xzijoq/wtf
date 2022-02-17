#include <cstdint>
#define ASIO_NO_DEPRECATED

#pragma region includes

#include <asio.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/registered_buffer.hpp>
#include <chrono>
#include <system_error>
#include <thread>

#include "defs.h"
#include "main.h"
#include "style.h"

#pragma endregion

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

int main()
{
    print( liStyle, "\nSERVER STARTS HERE\n" );

    uint16_t           sport    = 1330;
    ip::address        ip4any   = ip::address_v4::any();
    auto               protocol = ip::tcp::v4();
    constexpr uint16_t qSize{ 12 };
    tcp::endpoint      sep{ ip4any, sport };

    io_context ioc;
    error_code ec;
    int        counter{ 0 };

    tcp::acceptor acp( ioc );
    acp.open( protocol, ec );
    checkec( ec, where );
    acp.set_option( asio::ip::tcp::acceptor::reuse_address( true ) );
    acp.bind( sep, ec );
    checkec( ec, where );
    while ( true )
    {
        acp.listen( qSize, ec );
        checkec( ec, where );

        tcp::socket soc( ioc );
        acp.accept( soc, ec );
        checkec( ec, where );
        auto a = soc.local_endpoint();
        print( okStyle, "\nlocalip: {},localport: {}", a.address().to_string(),
               a.port() );
        auto b = soc.remote_endpoint();
        print( okStyle, "\nremotelip: {},remoteport: {} counter: {}",
               b.address().to_string(), b.port(), ++counter );

        string rbuf = "                             ";
        auto   rb   = buffer( rbuf, sizeof( rbuf ) );
        int    lol  = soc.read_some( rb, ec );
        checkec( ec, where );

        auto wb = buffer( "FuckYouToo" + std::to_string( counter ), 12 );
        soc.send( wb, 12, ec );
        checkec( ec, where );
        // std::this_thread::sleep_for( 1s );

        print( orStyle, "\n{}", rbuf );
    }
    print( "s" );
    print( liStyle, "\nSERVER ENDS HERE\n" );
    return 0;
}
