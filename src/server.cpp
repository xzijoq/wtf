
#include <fmt/core.h>

#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/address_v4.hpp>
#include <asio/read_until.hpp>
#include <asio/socket_base.hpp>
#include <asio/streambuf.hpp>
#include <cstdint>
#include <cstdio>
#include <istream>
#include <memory>
#include <string>
#include <system_error>
#include <thread>
#include <unordered_set>
#include <vector>

#include "defs.h"
#include "style.h"

#define ASIO_NO_DEPRECATED
#define ASIO_ENABLE_HANDLER_TRACKING

using std::shared_ptr;

void ShowSock( tcp::socket const& sock );
class Server;
class Session : public std::enable_shared_from_this<Session>
{
   public:
    tcp::socket     mSock;
    asio::streambuf mSbuf;
    string          mName;
    int             mId{ 23 };

    void ( *uu )( string );
    Server* Ser;

    std::function<void( int, string )> onError;

    Session( tcp::socket sock ) : mSock( move( sock ) ) {}

    void ShowSock() {}
    void AsyncWrite();

    void Start();
};

class Server
{
   public:
    // std::unordered_set<shared_ptr<Session>> mClients;
    io_context&                      mIoc;
    tcp::acceptor                    mAcp;
    std::uint32_t                    mPort;
    std::vector<shared_ptr<Session>> mClients;
    uint32_t                         mBackLog{ 12 };

    //! ALEAST MAKE LAST ELEMENT ATOMIC
    std::vector<int> mFreeList;

    Server( io_context& ioc, uint32_t port = 1331 )
        : mIoc( ioc ), mAcp( mIoc ), mPort( port )
    {
        error_code ec;
        mAcp.open( tcp::v4(), ec );
        checkec( ec, where );
        mAcp.set_option( asio::socket_base::reuse_address( true ), ec );
        checkec( ec, where );
        mAcp.bind( tcp::endpoint( asio::ip::address_v4::any(), mPort ), ec );
        checkec( ec, where );
        mClients.reserve( 12 );
        mFreeList.reserve( 23 );
    }
    void fAacp();

    void clientClosed( int id, string what = "And It;s Gone" )
    {
        print( orStyle, "\nClient Closed Id: {} ", id );
        cout << endl;

        mClients[id].reset();

        mFreeList.push_back( id );
    }

    void DisplayState( int full = 0 )
    {
        print( orStyle, "\n--- SERVER STATE DISPLAY BEGIN ---\n" );
        print( liStyle, "mClientsz: {}", mClients.size() );
        cout.flush();
        cout << endl;
        for ( auto i : mClients )
        {
            if ( i.use_count() != 0 )
            {
                print( liStyle, "name: {} id: {} ---", i->mName, i->mId );
                if ( full != 0 ) { ShowSock( i->mSock ); }
                cout.flush();
            }
            else
            {
                print( grStyle, "---EMPTY SHARED POINTER---\n" );
                cout.flush();
            }
        }
        cout.flush();
        print( liStyle, "\nFreeListSize: {}\n|", mFreeList.size() );

        cout.flush();
        for ( auto i : mFreeList )
        {
            if ( i != 0 )
            {
                print( okStyle, " - {}", i );
                cout.flush();
            }
        }
        print( orStyle, "\n--- SERVER STATE DISPLAY END ---\n" );
        cout << endl;
    }
};

void Session::Start()
{
    async_read_until(
        mSock, mSbuf, '\n',
        [plusOne = shared_from_this(), this]( error_code ec, int bread )
        {
            if ( ec.value() != 0 )
            {
                checkec( ec, where );
                mSock.close();
                Ser->clientClosed( mId );
                return;
            }
            string s;
            std::getline( std::istream( &mSbuf ), s );

            print( bvStyle, "{} :", mName );
            print( fwStyle, " {}", s );
            cout << endl;

            if ( s.starts_with( "quit" ) )
            {
                mSock.close();
                Ser->clientClosed( mId );
                return;
            }
            if ( s.starts_with( "show" ) ) { Ser->DisplayState( 1 ); }

            //! Bug string s will go out of scope before whis is done
            for ( auto i : Ser->mClients )
            {
                if ( i.use_count() != 0 )
                {
                    if ( i->mId != mId )
                    {
                        async_write( i->mSock,
                                     asio::buffer( mName + ": " + s + "\n" ),
                                     [this]( error_code ec, int len )
                                     {
                                         if ( ec.value() != 0 )
                                         {
                                             mSock.close();
                                             Ser->clientClosed( mId );
                                             checkec( ec, where );
                                             return;
                                         }
                                     } );
                    }
                }
            }

            Start();
        } );
}
void Server::fAacp()
{
    mAcp.listen( mBackLog );
    mAcp.async_accept(
        [this]( error_code ec, tcp::socket soc )
        {
            if ( ec.value() != 0 )
            {
                checkec( ec, where );
                return;
            }

            ShowSock( soc );

            auto client     = std::make_shared<Session>( move( soc ) );
            client->onError = std::bind( &Server::clientClosed, this, _1, _2 );

            client->Ser = this;
            if ( !mFreeList.empty() )
            {
                for ( auto i : mFreeList )
                {
                    print( orStyle, "{} , ", i );
                    cout.flush();
                }

                client->mId           = mFreeList.back();
                mClients[client->mId] = client;
                mFreeList.pop_back();
                print( orStyle, "Allocated From Pool, Id: {} \n", client->mId );
                cout.flush();
            }
            else
            {
                mClients.push_back( client );
                client->mId = mClients.size() - 1;
                print( orStyle, "Allocated Id: {} Sz: {} \n", client->mId,
                       mClients.size() );
                cout.flush();
            }
            auto smid = std::to_string( client->mId );
            client->mName="Cli ";
            for ( int i = 0; i < client->mId; i++ )
            {
                client->mName +=   smid ;
            }

            // client->uu     = std::bind( &Server::clientClosed, this, _1 );

            client->Start();

            fAacp();
        } );
}

int main()
{
    print( liStyle, "\nSERVER STARTS HERE\n" );

    io_context ioc;
    Server     s1{ ioc };

    s1.fAacp();

    ioc.run();

    print( liStyle, "\nSERVER ENDS HERE\n" );
    return 0;
}
