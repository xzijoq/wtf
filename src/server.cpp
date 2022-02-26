

//#define ASIO_NO_DEPRECATED

#include "defs.h"
#include <thread>

#define ASIO_ENABLE_HANDLER_TRACKING

void hd(error_code ec, size_t len){}
int main()
{
    print( liStyle, "\nSERVER STARTS HERE\n" );

    std::error_code ec;
    io_context      ioc;

    //! LocalConfig
    auto          IPany      = asio::ip::address_v4::any();
    uint16_t      ServerPort = 1338;
    tcp::endpoint ServerEndpoint{ IPany, ServerPort };

    auto Protocol = tcp::v4();

    //! Buffers
    constexpr int BackLog = 12;

    //! Accepter Socket
    tcp::acceptor acp( ioc );

    acp.open( Protocol, ec );

    checkec( ec, where );

    acp.set_option( asio::socket_base::reuse_address( true ), ec );
    checkec( ec, where );

    acp.bind( ServerEndpoint, ec );
    checkec( ec, where );

    //! temp accept into socket

    //! new ioc

   Server Sv{ioc,1331};

    Sv.fAacp();

    std::thread t1(
        [&ioc](){

            ioc.run();

        }

    );

   // ioc.run();
    t1.join();

    print( liStyle, "\nSERVER ENDS HERE\n" );
    return 0;
}
