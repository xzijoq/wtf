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
    print( yeStyle, "\n    RemoteEp {}:{}  --  ", rep.address().to_string(),
           rep.port() );
    print( yeStyle, "LocalEp {}:{}", lep.address().to_string(), lep.port() );
    cout << endl;
}

/*
void Session::Start()
{
    async_read_until( mSock, mSbuf, '\n',
                      [inc = shared_from_this(), this]( error_code ec, int len )
                      {
                          //! Only need to increment the shared pointer no need
to use it if ( ec.value() != 0 )
                          {
                              checkec( ec, where );
                              // self->mSock.close();
                              mSock.close();
                              return;
                          }
                          string s1;  //=
                          // cout<<std::istream( &self->mSbuf).rdbuf();

                          std::getline( std::istream( &mSbuf ), s1 );
                          auto rep = mSock.remote_endpoint();
                          // auto wow=self1.use_count();
                          cout << std::endl;
                          print( okStyle, " {}:{} :- {} ",
                                 rep.address().to_string(), rep.port(), s1 );
                          cout << std::endl;

                          if ( s1.starts_with( "quit" ) )
                          {
                              print( wStyle, "\nclosing {}:{}",
                                     rep.address().to_string(), rep.port() );
                              cout << std::endl;
                              mSock.close();
                              return;
                          }

                          Start();
                      } );
}*/

/*
void Server::fAacp()
{
    print( orStyle, "\nListening" );
    cout << endl;
    mAcp.listen( 12 );

    mAcp.async_accept(
        [this]( error_code ec, tcp::socket soc )
        {
            auto rep = soc.remote_endpoint();
            print( orStyle, "\nAccpeted:" );
            print( orStyle, "{}:{}  ", rep.address().to_string(), rep.port() );
            cout << endl;
            auto s1 = std::make_shared<Session>( move( soc ) );
            // cout << std::endl << "asdasd: " << s1.use_count();
            s1->Start();
            fAacp();
        } );
}
void Session::Start()
{
    cout << "\nReading Only" << endl;
    error_code ec;
    auto       rep = mSock.remote_endpoint( ec );
    checkec( ec, where );
    print( okStyle, "\n:> {}:{}", rep.address().to_string(), rep.port() );
    cout << endl;
    async_read_until( mSock, mSbuf, '\n',
                      [inc = shared_from_this(), this]( error_code ec, int len )
                      {
                          //! Only need to increment the shared pointer no need
                          //! to use it
                          if ( ec.value() != 0 )
                          {
                              checkec( ec, where );
                              // self->mSock.close();
                              mSock.close();
                              return;
                          }
                          string s1;  //=
                          // cout<<std::istream( &self->mSbuf).rdbuf();

                          std::getline( std::istream( &mSbuf ), s1 );
                          auto rep = mSock.remote_endpoint();
                          // auto wow=self1.use_count();
                          cout << std::endl;
                          print( okStyle, " {}:{} :- {} ",
                                 rep.address().to_string(), rep.port(), s1 );
                          cout << std::endl;

                          if ( s1.starts_with( "quit" ) )
                          {
                              print( wStyle, "\nclosing {}:{}",
                                     rep.address().to_string(), rep.port() );
                              cout << std::endl;
                              mSock.close();
                              return;
                          }

                          Start();
                      } );
}*/