
#include <deque>
#include <istream>
#include <memory>
#include <mutex>

#include "defs.h"
#include "style.h"


#define ASIO_NO_DEPRECATED
//#define ASIO_ENABLE_HANDLER_TRACKING

using std::shared_ptr;
using namespace std::chrono;
using std::thread;
using std::vector;
void ShowSock( tcp::socket const& sock );

class Server;

//$ -CLASS SESSION STARTS HERE ---
class SessionServer : public std::enable_shared_from_this<SessionServer>
{
   public:
    //? required stuff
    tcp::socket     mSock;
    asio::streambuf mSbuf;
    //! multiple thngs could simultaneously push into it
    //#CRASHES THE SERVER
    std::deque<string> mWdq;
    std::mutex         mMtx_Wdq;

    //?fancy stuff
    string mName;
    int    mId{ 23 };

    void ( *uu )( string );
    Server* Ser;

    std::function<void( int, string )> onError;

    SessionServer( tcp::socket sock ) : mSock( move( sock ) ) {}

    void ShowSock() {}
    void AsyncWrite();
    void QWrite( string const );

    void Start();
};

//$-CLASS SERVER STARTS HERE ---
class Server
{
   public:
    // std::unordered_set<shared_ptr<SessionServer>> mClients;
    io_context&                      mIoc;
    tcp::acceptor                    mAcp;
    std::uint32_t                    mPort;
    std::vector<shared_ptr<SessionServer>> mClients;
    uint32_t                         mBackLog{ 12 };

    //! ALEAST MAKE LAST ELEMENT ATOMIC
    std::vector<int> mFreeList;
    std::mutex       mM_Flist;

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
        //$ WORKS FOR NOW DOSE NOT CRASH OR MESSUP THE SERVER
        //$ via shared and weak pointers
        //$ SEVERAL CLIENTS CAN CLOSE AT ONCE
        //$ A CLIENT CAN FREE TWICE!!!
        //! DOUBLE FREE IS A KNWN BUG
        // Todo NEED TO FIX IT
        //? how? Prolly with weak pointers, it temp solution
        //$currently usiong weak pointer as a solution
        //? possible periodic garbage check on mCient
        //? Timers ??
        //?use a different container --prolly stilll abug
        //?most likely handled at SessionServer lvl
        //? STICKEY CANCEL
        //?UNIQUE ID ..may not be destroyed as shared poitner was sent into

        std::weak_ptr<SessionServer> alive = mClients[id];
        if ( alive.use_count() != 0 )
        {
            auto share=alive.lock();
            if ( mClients[id]->mSock.is_open() )
            {
                print( eStyle, "\nPossible Double close, SOcket still Open\n ",
                       id );
                cout.flush();
                return;
            }
        }
        print( orStyle, "\nClient Closed Id: {} ", id );
        cout << endl;

        mClients[id].reset();
        for ( auto j : mFreeList )
        {
            if ( j == id ) { return; }
        }
        //! Atleast the last one should be atomic
        //@LOCKING mM_Flist
        mM_Flist.lock();
        mFreeList.push_back( id );
        mM_Flist.unlock();
        //@UNLOCKING mM_Flist
    }
    void BroadCast( string const );
    // void what() { mClients.size(); }

    void DisplayState( int full = 0 )
    {
        print( orStyle, "\n--- SERVER STATE DISPLAY BEGIN ---\n" );
        print( liStyle, "\nmClient Total Size: {} Data:", mClients.size() );
        cout.flush();

        for ( auto i : mClients )
        {
            if ( i.use_count() != 0 )
            {
                print( liStyle, "\nName: {} Id: {} -- ", i->mName, i->mId );
                if ( full != 0 ) { ShowSock( i->mSock ); }
                cout.flush();
            }
            else
            {
                print( grStyle, "\n---EMPTY SHARED POINTER---" );
                cout.flush();
            }
        }
        cout.flush();
        print( liStyle, "\n\nFreeListSize: {} : |", mFreeList.size() );

        cout.flush();
        for ( auto i : mFreeList )
        {
            if ( mFreeList.size() != 0 )
            {
                print( okStyle, " - {}", i );
                cout.flush();
            }
        }
        print( orStyle, "\n\n--- SERVER STATE DISPLAY END ---\n" );
        cout << endl;
    }
};

void SessionServer::Start()
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
            else if ( s.starts_with( "show" ) )
            {
                Ser->DisplayState( 1 );
            }
            else
            {
                s = mName + ": " + s + '\n';
                Ser->BroadCast( s );
            }
            //$Test Io Load Multi Or Debug
           /* std::thread t1(
                [this]() {
                    asio::post( Ser->mIoc,
                                []() { std::this_thread::sleep_for( 5s ); } );
                } );t1.detach();*/

            Start();
        } );
}

void Server::BroadCast( string const msg )
{
    for ( auto i : mClients )
    {
        if ( i.use_count() != 0 ) { i->QWrite( msg ); }
    }
}

void SessionServer::QWrite( string const message )
{
    //#MUTEX IS REQUIRED
    bool idle = mWdq.empty();
    // if ( mWdq.size() < 63 )
    // {
    //@LOCKING m
    mMtx_Wdq.lock();
    mWdq.push_back( message );
    mMtx_Wdq.unlock();
    //@Unlock m
    //  }
    if ( idle ) { AsyncWrite(); }
    else
    {
        print( wStyle, "\nWrite is actually bussy" );
        cout.flush();
    }
}
void SessionServer::AsyncWrite()
{
    if ( !mWdq.empty() )
    {
        //@Possible garbage read to mWdq.front()
        async_write( mSock, asio::buffer( mWdq.front() ),
                     [this,plusOne=shared_from_this()]( error_code ec, int len )
                     {
                         if ( ec.value() != 0 )
                         {
                             mSock.close();
                             Ser->clientClosed( mId );
                             checkec( ec, where );
                             return;
                         }
                         ////@LOCKING MostLikelyNotRequired
                         mWdq.pop_front();

                         AsyncWrite();
                     } );
    }
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
            print( orStyle, "\nAccepted " );
            ShowSock( soc );
            cout << endl;

            auto client     = std::make_shared<SessionServer>( move( soc ) );
            client->onError = std::bind( &Server::clientClosed, this, _1, _2 );

            client->Ser = this;
            if ( !mFreeList.empty() )
            {
                for ( auto i : mFreeList )
                {  //@Possible Garbage Read
                    print( orStyle, "{} , ", i );
                    cout.flush();
                }

                //@LOCKING mM_Flist
                mM_Flist.lock();
                client->mId = mFreeList.back();
                mFreeList.pop_back();
                mM_Flist.unlock();
                //@UNLOCKING mM_Flist

                mClients[client->mId] = client;
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
            auto smid     = std::to_string( client->mId );
            client->mName = "Cli:-" + smid;

            // client->uu     = std::bind( &Server::clientClosed, this, _1
            // );

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

    auto count = thread::hardware_concurrency();
    count      = 2;
    cout << "\nNumber Of Hardware threads is :" << count << endl;

    vector<thread> iot;
    thread         t1;

    for ( auto i = 0; i < count; i++ )
    {
        iot.emplace_back( [&]() { ioc.run(); } );
    }
    for ( auto& i : iot ) { i.join(); }

    print( liStyle, "\nSERVER ENDS HERE\n" );
    return 0;
}
