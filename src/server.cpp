
#define ASIO_NO_DEPRECATED

#include <asio.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/registered_buffer.hpp>
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

using namespace asio;
using asio::ip::tcp;
using namespace std::placeholders;
#pragma endregion

int main()
{
    print( liStyle, "\nSERVER STARTS HERE\n" );

    error_code ec;
    io_context ioc;

    //! LocalConfig
    auto          IPany      = ip::address_v4::any();
    uint16_t      ServerPort = 1338;
    tcp::endpoint ServerEndpoint{ IPany, ServerPort };

    auto Protocol = tcp::v4();

    //! Buffers
    constexpr int BackLog = 12;

    //! Accepter Socket
    tcp::acceptor acp( ioc );

    acp.open( Protocol, ec );
    checkec( ec, where );

    acp.set_option( socket_base::reuse_address( true ), ec );
    checkec( ec, where );

    acp.bind( ServerEndpoint, ec );
    checkec( ec, where );

    while ( true )
    {
        print( liStyle, "\nListening: " );
        cout << endl;
        acp.listen( BackLog, ec );
        checkec( ec, where );


        auto soc = std::make_shared<tcp::socket>( ioc );
;

        acp.accept( *soc, ec );
        checkec( ec, where );
        print( okStyle, "\nClient Address: {} Port: {} ",
               soc->remote_endpoint().address().to_string(),
               soc->remote_endpoint().port() );

        // auto inb = soc.read_some( InBuf, ec );
        ReadString( soc );
        WriteString( soc, "yep i" );
        checkec( ec, where );

        ioc.run();
        ioc.restart();
    }

    print( liStyle, "\nSERVER ENDS HERE\n" );
    return 0;
}
