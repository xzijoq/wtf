

#include <sys/socket.h>

#include <asio/connect.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/address_v4.hpp>
#include <asio/ssl.hpp>
#include <asio/ssl/context.hpp>
#include <asio/ssl/host_name_verification.hpp>
#include <asio/ssl/stream.hpp>
#include <asio/ssl/verify_mode.hpp>
#include <asio/streambuf.hpp>
#include <istream>
#include <memory>
#include <string>
#include <system_error>

#include "defs.h"
#include "style.h"

using namespace std::chrono;
using std::thread;
using std::vector;

int ip{ 0 };

#define ASIO_NO_DEPRECATED
#define HANDLER_LOCATION                                                       \
    ASIO_HANDLER_LOCATION( ( __FILE__, __LINE__, __func__ ) )
class SessionClient : public enable_shared_from_this<SessionClient>
{
   public:
    io_context&                    mIoc;
    tcp::socket                    mSock;
    tcp::endpoint                  mServerEndpoint;
    asio::streambuf                mSbuf;
    asio::posix::stream_descriptor ins;
    asio::streambuf                mCRdStr;
    string                         rBuf;

    SessionClient( io_context& ioc, string ServerName, string ServerPort,
                   string ClientName = "127.1.12.11", int ClientPort = 1336 )
        : mIoc( ioc ), mSock( mIoc ), ins( mIoc, STDIN_FILENO )

    {
        error_code ec;
        // auto          protocol = tcp::v4();
        tcp::resolver rer( ioc );
        auto          res = rer.resolve( ServerName, ServerPort, ec );
        checkec( ec, where );
        // mIoc.run();
        // mIoc.reset();
        for ( auto i : res )
        {
            if ( ClientPort != 1336 )
            {
                if ( i.endpoint().protocol() == tcp::v4() )
                {
                    mServerEndpoint = i.endpoint();
                    break;
                }
            }
            else
            {
                //! WOuld Likely be ipv6
                mServerEndpoint = i.endpoint();
                break;
            }
        }

        if ( ClientPort != 1336 )
        {
            mSock.open( tcp::v4() );
            mSock.set_option( asio::socket_base::reuse_address( true ), ec );
            checkec( ec, where );
            auto ClientEndpoint = tcp::endpoint(
                asio::ip::make_address( ClientName, ec ), ClientPort );
            checkec( ec, where );
            mSock.bind( ClientEndpoint, ec );
            checkec( ec, where );
        }
    }
    /*
        SessionClient( tcp::socket soc, tcp::endpoint sep )
            : mSock( move( soc ) ),
              mServerEndpoint( sep ),
              ins( mSock.get_executor(), STDIN_FILENO )
        {
            rBuf = "iam: " + std::to_string( ip ) + '\n';
        }
        SessionClient( tcp::socket soc )
            : mSock( move( soc ) ), ins( mSock.get_executor(), STDIN_FILENO )
        {
        }*/
    void AsyncConnectGo()
    {
        mSock.async_connect(
            mServerEndpoint,
            [this, PlusOne = shared_from_this()]( error_code ec )
            {
                if ( ec.value() != 0 )
                {
                    checkec( ec, where );
                    mSock.close();
                    return;
                }

                ShowSock( mSock );
                AsyncRead();
                AsyncWrite();
            } );
    }
    void AsyncRead()
    {
        async_read_until(
            mSock, mSbuf, '\n',
            [this, PlusOne = shared_from_this()]( error_code ec, int len )
            {
                if ( ec.value() != 0 )
                {
                    checkec( ec, where );
                    mSock.close();
                    return;
                }

                string s;
                std::getline( std::istream( &mSbuf ), s );
                cout.flush();

                print( bvStyle, "{}", s );
                cout << endl;
                AsyncRead();
            } );
    }

    void AsyncWrite( bool chat = true )
    {
        error_code ec;
        if ( !chat )
        {
            //$testing
            async_write(
                mSock, buffer( rBuf ),
                [this, PlusOne = shared_from_this()]( error_code ec, int wr )
                {
                    if ( ec.value() != 0 )
                    {
                        checkec( ec, where );
                        mSock.close();
                        return;
                    }
                    // std::this_thread::sleep_for(milliseconds(ip*10));

                    AsyncWrite( false );
                } );
        }
        else
        {
            async_read_until(
                ins, mCRdStr, '\n',
                [this, PlusOne = shared_from_this()]( error_code ec, int len )
                {
                    if ( ec.value() != 0 )
                    {
                        checkec( ec, where );
                        mSock.close();
                        return;
                    }

                    std::getline( std::istream( &mCRdStr ), rBuf );

                    // print( orStyle, "{} :", rBuf );
                    // cout << "\n" << endl;
                    //! IMP AS SERVEWR READS UNTIL THIS
                    rBuf.append( "\n" );
                    async_write( mSock, buffer( rBuf ),
                                 [this, PlusOne = shared_from_this()](
                                     error_code ec, int wr )
                                 {
                                     if ( ec.value() != 0 )
                                     {
                                         checkec( ec, where );
                                         mSock.close();
                                         return;
                                     }
                                     rBuf = "";
                                     AsyncWrite();
                                 } );
                } );
        }
    }
};


bool verify_certificate(bool preverified,
      asio::ssl::verify_context& ctx)
  {
    // The verify callback can be used to check whether the certificate that is
    // being presented is valid for the peer. For example, RFC 2818 describes
    // the steps involved in doing this for HTTPS. Consult the OpenSSL
    // documentation for more details. Note that the callback is called once
    // for each certificate in the certificate chain, starting from the root
    // certificate authority.

    // In this example we will simply print the certificate's subject name.
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    std::cout << "Verifying " << subject_name << "\n";

    std::cout<<preverified<<endl;

    return preverified;
  }


int main( int argc, char* argv[] )
{
    print( orStyle, "\nCLIENT STARTS HERE\n" );

    error_code ec1;
    error_code ec;
    io_context ioc;

    // auto S1 = make_shared<SessionClient>( ioc, "localhost", "1331" );
    // S1->AsyncConnectGo();
    tcp::resolver res( ioc );
    auto          resu = res.resolve( "nc.xzijoq.gq", "https" );

    asio::ssl::context tctx( asio::ssl::context::tlsv13 );
  // tctx.set_verify_depth(0);
   tctx.set_default_verify_paths(ec);
   // tctx.load_verify_file("/etc/ssl/certs/Amazon_Root_CA_4.pem",ec);
  //   tctx.load_verify_file("/etc/ssl/certs/Amazon_Root_CA_3.pem",ec);
   //     tctx.load_verify_file("/etc/ssl/certs/ca-certificates.crt");
   tctx.load_verify_file("/home/babayaga/Downloads/test.crt",ec);
    checkec(ec,where);

    asio::ssl::stream<tcp::socket> tsoc( ioc, tctx );

    asio::connect( tsoc.lowest_layer(), resu, ec );
    checkec( ec, where );
    tsoc.lowest_layer().set_option(tcp::no_delay(true));


    tsoc.set_verify_mode( asio::ssl::verify_peer );
   // tsoc.set_verify_callback(verify_certificate,ec);
    checkec(ec,where);
    //tsoc.set_verify_callback(asio::ssl::host_name_verification("www.google.com"));
    tsoc.handshake( asio::ssl::stream<tcp::socket>::client, ec );

    checkec( ec, where );

    char getRq[] =
        "GET / HTTP/1.1\n"
        "Host: www.amazonss.com\n"
        "Connection: close\n\n";

    asio::write( tsoc, buffer( getRq ), ec );
    checkec( ec, where );

    asio::streambuf buf;
    asio::read( tsoc, buf, ec );
    checkec( ec, where );

    cout << endl
         << "and so it begins:" << endl
         << std::istream( &buf ).rdbuf() << endl;

    /*
        int count = thread::hardware_concurrency();
        count     = 3;

        vector<thread> tv;

        for ( int i = 0; i < count; i++ )
        {
            tv.emplace_back( [&]() { ioc.run(); } );
        }
        for ( auto& i : tv ) { i.join(); }*/
    print( orStyle, "\nCLIENT ENDS HERE\n" );
    cout.flush();
    return 0;
}

void PassSoc() {}

/* //! Client local
    string ClientIPstring = "127.1.12.11";
    if ( argc > 1 )
    {
        string ipl     = string( argv[1] );
        ClientIPstring = "127.1.12." + string( argv[1] );
        ip             = std::stoi( ipl );
    }
*/
