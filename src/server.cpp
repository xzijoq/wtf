
#define ASIO_NO_DEPRECATED

#include "defs.h"

#define ASIO_ENABLE_HANDLER_TRACKING

struct omg
{
    int a, b;
} omg1;

void onAccept( error_code ec, tcp::socket sock, Session* s1 )
{
    if ( ec.value() != 0 ) { checkec( ec, where ); }

    s1->sock = move( sock );
    s1->fwstr();
    s1->frstr();
   // std::thread t1(&Session::frstr,&s1)  ;
}

void wtd( int a, int b, string c ) {}

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
    //! new ioc
    io_context  cioc;
    tcp::socket c1( cioc );
    tcp::socket asoc( cioc );
    Session     s1{ move( c1 ) };

    //! buffers

    //! Go

    acp.listen( BackLog, ec );
    checkec( ec, where );

    auto f1 = bind( onAccept, _1, _2, &s1 );

    acp.async_accept( cioc, f1 );
    ioc.run();
    cioc.run();

    print( liStyle, "\nSERVER ENDS HERE\n" );
    return 0;
}
