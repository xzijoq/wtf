
#define ASIO_NO_DEPRECATED

#include <asio.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/registered_buffer.hpp>
#include <chrono>
#include <cstdint>
#include <source_location>
#include <system_error>
#include <thread>

#include "defs.h"
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

#define ASIO_ENABLE_HANDLER_TRACKING

int main()
{
    print( liStyle, "\nSERVER STARTS HERE\n" );

    std::error_code ec;
    io_context      ioc;

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

    //! temp accept into socket
    tcp::socket asoc( ioc );

    //! buffers
    string writeStr = "fuck";
    string readStr  = "    ";

    tcp::socket tsoc( ioc );

    acp.listen( BackLog, ec );
    checkec( ec, where );

    acp.async_accept( asoc,
                      [&writeStr, &readStr, &asoc]( error_code ec )
                      {
                          if ( ec.value() != 0 ) { checkec( ec, where ); }

                          auto rep = asoc.remote_endpoint( ec );
                          checkec( ec, where );

                          print( okStyle, "\nRep.addr:{} , Rep.Port:{}",
                                 rep.address().to_string(), rep.port() );

                          async_write( asoc, buffer( writeStr ),
                                       []( error_code ec, int byr )
                                       {
                                           if ( ec.value() != 0 )
                                           {
                                               checkec( ec, where );
                                           }
                                       } );

                          async_read( asoc, buffer( readStr ),
                                      [&readStr]( error_code ec, int byr )
                                      {
                                          if ( ec.value() != 0 )
                                          {
                                              checkec( ec, where );
                                          }
                                          print( orStyle, "\n{}", readStr );
                                      } );
                      } );

    ioc.run();

    print( liStyle, "\nSERVER ENDS HERE\n" );
    return 0;
}
