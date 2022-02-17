#define ASIO_NO_DEPRECATED

#include <asio/ip/address.hpp>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>
#include <asio/ip/basic_endpoint.hpp>
#include <asio/error.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>

#include <asio.hpp>

#include <cstdint>
#include <thread>
#include <chrono>
#include <system_error>

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

int main( int argc, char* argv[] )
{
    // printallstyle();

    print( orStyle, "\nCLIENT STARTS HERE\n" );

    error_code ec;
    io_context ioc;


    string     clientIpString = "127.168.12.1";
    if(argc>1){
        clientIpString="127.168.12."+(string)argv[1];

    }
    constexpr uint16_t clientPort       = 1331;
    ip::address        ClientIp = ip::make_address( clientIpString, ec );
    checkec( ec, where );
    tcp::endpoint ClientEp{ ClientIp, clientPort };

    constexpr char     ServerIpString[] = "127.168.1.0";
    constexpr uint16_t ServerPort       = 1330;
    ip::address_v4     ServerIp = ip::make_address_v4( ServerIpString, ec );
    checkec( ec, where );
    tcp::endpoint ServerEp{ ServerIp, ServerPort };
    // auto lol=ClientEp.protocol();
    
    tcp::socket soc{ ioc };

    soc.open( ClientEp.protocol(), ec );
    checkec( ec, where );
   soc.set_option(asio::ip::tcp::socket::reuse_address(true));
    soc.bind( ClientEp, ec );
    checkec( ec, where );

 

   // tcp::resolver re{ ioc };
  //  auto          res = re.resolve( "google.com", "180", ec );
   // checkec( ec, where );

    //   asio::connect(soc,res,ec);
    soc.connect( ServerEp, ec );
    checkec( ec, where, "connect" );

    const char bufao[]="Fuck You nigga\n";
    auto bafae=asio::buffer(bufao);

    soc.send(bafae);
  //  std::this_thread::sleep_for(3s);

    string gets="                   ";
    auto rb=buffer(gets,sizeof(gets));
    soc.read_some(rb,ec);

    print(liStyle,"\n{}",gets);

    soc.close(ec);
    checkec(ec,where);
    print( orStyle, "\nCLIENT ENDS HERE\n" );
    return 0;
}

// reading the code of the library is beyond me, it seems thats required to
// understand it i dont know how they get the return tpe of the fucking
// resulttype from reference

// !todo how to bind client to a specific port without specifying the protocol,
// which can be determined by asio::connect
