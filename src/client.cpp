#define ASIO_NO_DEPRECATED
// the above is a mega error as it propogates to main.h

#pragma region includes
#include <asio.hpp>
#include <asio/error.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
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

int main( int argc, char* argv[] )
{
    // printallstyle();

    print( orStyle, "\nCLIENT STARTS HERE\n" );
    const char         cip[] = "127.168.0.0";
    constexpr uint16_t cport = 1330;
    const char         sip[] = "127.168.0.1";
    constexpr uint16_t sport = 1331;
    error_code         ec;
    io_context         ioc;
    auto               protocol = ip::tcp::v4();
    ip::address        seraddr  = ip::make_address_v4( sip, ec );
    checkec( ec, "ip.makeaddress", where );

    tcp::socket soc( ioc );
    soc.open( protocol, ec );
    checkec( ec, "soc.open", where );

    tcp::endpoint tep{ seraddr, sport };

    // dns resolution
    tcp::resolver res( ioc );
    auto          results = res.resolve(
                 "google.com", "80",
                 tcp::resolver::numeric_service | tcp::resolver::canonical_name, ec );
    

    checkec( ec, "resolver", where );
    for ( tcp::endpoint ep : results )
    {
        // print(okStyle,"\n{}",ep);
        cout << endl << ep;
    }
    for ( auto i = results.begin(); i != results.end(); i++ )
    {
        cout << endl << i->endpoint().address().to_string();
    }
    print( orStyle, "\nCLIENT ENDS HERE\n" );
    return 0;
}



// reading the code of the library is beyond me, it seems thats required to understand it
// i dont know how they get the return tpe of the fucking resulttype from reference