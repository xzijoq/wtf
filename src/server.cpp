#define ASIO_NO_DEPRECATED

#pragma region includes

#include <asio.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/registered_buffer.hpp>
#include <chrono>
#include <system_error>

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

    uint16_t    sport    = 1330;
    ip::address ip4any   = ip::address_v4::any();
    auto        protocol = ip::tcp::v4();

    tcp::endpoint sep{ ip4any, sport };

    io_context ioc;
    error_code ec;

    tcp::acceptor acp( ioc );
    acp.open( protocol, ec );
    checkec( ec, "acp.open", where );

    print( liStyle, "\nSERVER ENDS HERE\n" );
    return 0;
}
