#include <defs.h>

void checkec( error_code ec, string file, string func, int line, string msg )
{
    string errr = std::to_string( ec.value() ) + " : " + ec.message();
    if ( ec.value() != 0 )
    {
        print( eStyle, "\nError   :{:^52} ", errr );
        print( eStyle, "\nFunction:{:^52} ", func );
        print( eStyle, "\nOn Line :{:^52} ", line );
        print( eStyle, "\nIn File :{:^52} ", file );
        if ( msg != "" ) { print( eStyle, "\nMsg    :{:^52} ", msg ); }
        std::cout << std::endl;
        // abort();
    }
    else
    {
        if ( msg != "" )
        {
            print( okStyle, "\nCode -> {:<} ", errr );
            print( okStyle, "|| Msg -> {:<} ", msg );
            std::cout << std::endl;
        }
    }
}

void ShowSock( tcp::socket const& sock )
{
    error_code ec;

    auto lep = sock.local_endpoint( ec );
    checkec( ec, where );
    auto rep = sock.remote_endpoint( ec );
    checkec( ec, where );
    print( yeStyle, "RemoteEp {}:{}  |  ", rep.address().to_string(),
           rep.port() );
    print( yeStyle, "LocalEp {}:{}", lep.address().to_string(), lep.port() );
    cout .flush();
}
