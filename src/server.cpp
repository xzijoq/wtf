#include <cstdint>
#define ASIO_NO_DEPRECATED

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


void ReadFromSoc( tcp::socket& soc );
int main()
{
    print( liStyle, "\nSERVER STARTS HERE\n" );

    error_code ec;
    io_context ioc;

    //! LocalConfig
    auto     IPany      = ip::address_v4::any();
    uint16_t ServerPort = 1338;

    tcp::endpoint ServerEndpoint{ IPany, ServerPort };
    auto          Protocol = tcp::v4();

    //! Buffers
    constexpr int BackLog   = 12;
    const string  OutString = "Fuck You Too !!";
    string        InString  = "                      ";
    auto          OutBuf    = buffer( OutString, sizeof( OutString ) );
    auto          InBuf     = buffer( InString, sizeof( InString ) );

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

        tcp::socket soc( ioc );
        acp.accept( soc, ec );
        checkec( ec, where );

        print( okStyle, "\nClient Address: {} Port: {} ",
               soc.remote_endpoint().address().to_string(),
               soc.remote_endpoint().port() );

       // auto inb = soc.read_some( InBuf, ec );
        //checkec( ec, where );
        ReadFromSoc( soc );

        auto oub = soc.write_some( OutBuf, ec );
        checkec( ec, where );

        print( yeStyle, "\nClient Says: {}", InString );
    }

    print( liStyle, "\nSERVER ENDS HERE\n" );
    return 0;
}

void ReadFromSoc( tcp::socket& soc )
{
    error_code ec;
    string     res;
    res.resize( 23164);

    print(eStyle,":\nsize: {}",res.size());
    cout<<endl;
    

    int dataRead{ 0 };
    while ( dataRead < 23162 )
    {
        int rt{ 0 };
        print(eStyle,":\nsssDr{}",dataRead);
        dataRead += soc.read_some(
            buffer( (static_cast<char*>( res.data() ) + dataRead),
                    res.size() - dataRead ),
            ec );
        checkec( ec, where );
        print(eStyle,":\nDr{}",dataRead);
    }
    print( yeStyle, "\nOMG: \n{}", res );
}
