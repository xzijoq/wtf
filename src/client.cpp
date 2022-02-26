#include "defs.h"

void onConnect( error_code ec, Session* s1 )
{
    if ( ec.value() != 0 ) { checkec( ec, where ); }

    print( orStyle, "\nOnConneect\n" );

 //   s1->start();

    while ( true )
    {
        getline( cin, s1->wStr );
        s1->fwstr();
        cout<<"pmg;";
    //    s1->frstr();
    }
}

int main( int argc, char* argv[] )
{
    print( orStyle, "\nCLIENT STARTS HERE\n" );

    error_code ec;
    io_context ioc;

    //! Client local
    string ClientIPstring = "127.1.12.11";
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

    //! buffers

    //! socket

    tcp::socket soc( ioc );
    soc.open( protocol );

    soc.set_option( socket_base::reuse_address( true ), ec );

    Session s1{ move( soc ) };

    s1.wStr = "clie";

    s1.sock.async_connect( ServerEndPoint, bind( onConnect, _1, &s1 ) );

    checkec( ec, where );

    ioc.run();

    //   tsoc.bind(ServerEndPoint);
    print( orStyle, "\nCLIENT ENDS HERE\n" );
    return 0;
}
