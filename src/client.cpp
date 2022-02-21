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

bool flag = true;

void wtf(std::shared_ptr<tcp::socket> soc, string const& WriteString )
{
    auto datab = std::make_shared<SessionWrite>();

    datab->setOutString( "WriteString" );
    datab->mSoc              = soc;
    datab->TotalBytesWritten = 0;
    auto f2                  = std::bind( WriteCallBack, _1, _2, datab );

    asio::async_write( *( datab->mSoc ), buffer( datab->OutString ), f2 );
}
int main( int argc, char* argv[] )
{
    print( orStyle, "\nCLIENT STARTS HERE\n" );

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

    //! socket
    for ( auto i = 0; i < 11; i++ )
    {
        auto soc = std::make_shared<tcp::socket>( ioc );

        soc->open( protocol, ec );
        checkec( ec, where );

        soc->set_option( socket_base::reuse_address( true ), ec );
        checkec( ec, where );

        //! remove the for loop or bind call to remove new ip assign each

        string             ClientIPstring = "127.1.12." + std::to_string( i );
        constexpr uint16_t ClientPort     = 1336;
        tcp::endpoint ClientEndpoint{ ip::make_address( ClientIPstring, ec ),
                                      ClientPort };
        //! end remove

        soc->bind( ClientEndpoint );
        checkec( ec, where );
        soc->async_connect(
            ServerEndPoint,

            [soc, i]( error_code ec )
            {
                auto re = std::make_shared<SessionRead>();
                re->InputString.clear();
                re->InputString.resize( SessionRead::HEADERSIZE );
                re->mSoc       = soc;
                re->ReadHeader = true;

                //  auto f1 = std::bind( ReadCallBack, _1, _2, re );
            //    ReadString( soc );
                asio::async_read(
                    *( re->mSoc ),
                    buffer( static_cast<char*>( re->InputString.data() ),
                            re->InputString.length() ),
                    [re]( error_code ec, int bytesread )
                    { print( yeStyle, "\n{}", re->InputString ); } );

                WriteString( soc, "12345678" + std::to_string( i ) );
              //  wtf(soc,);
                //auto datab = std::make_shared<SessionWrite>();
//
                //datab->setOutString( "WriteString" );
                //datab->mSoc              = soc;
                //datab->TotalBytesWritten = 0;
                //auto f2 = std::bind( WriteCallBack, _1, _2, datab );
//
                //asio::async_write( *( datab->mSoc ), buffer( datab->OutString ),
                //                   f2 );
                // asio::async_write( *( datab->mSoc ), buffer( datab->OutString
                // ),
                //                    [datab]( error_code ec, int byre )
                //                    { print( yeStyle, "\nWroteSOmething" ); }
                //                    );

                // auto f2 = std::bind( WriteCallBack, _1, _2, datab );
            }

        );

        // checkec( ec, where );
        // WriteString( soc, "12345678" + std::to_string( i ) );
        // ReadString( soc );
        //  soc->async_connect( ServerEndPoint, std::bind( wtf, _1, soc ) );
    }  // for end
    std::thread t1(
        [&ioc]()
        {
            while ( true )
            {
                ioc.run();
                ioc.restart();
                std::this_thread::sleep_for( 2ms );
            }
        }

    );
    t1.join();

    print( orStyle, "\nCLIENT ENDS HERE\n" );
    return 0;
}
