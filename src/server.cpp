
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
using namespace std::chrono;
using namespace asio;
using namespace std::placeholders;
using asio::ip::tcp;
using fmt::print;
using std::cout;
using std::endl;
using std::string;
#pragma endregion

int main()
{
    print( liStyle, "\nSERVER STARTS HERE\n" );

    std::error_code ec;
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


    print( liStyle, "\nSERVER ENDS HERE\n" );
    return 0;
}
