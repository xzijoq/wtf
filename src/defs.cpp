
#include <defs.h>
#include <style.h>

#include <asio.hpp>
#include <asio/error.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>
#include <asio/ip/basic_endpoint.hpp>

#pragma region using
using fmt::print;
using std::cout;
using std::endl;
using std::string;
using namespace std::chrono;

using namespace asio;
using asio::ip::tcp;
using namespace std::placeholders;
#pragma endregion

void checkec( std::error_code ec1, std::string fname, int lno, std::string sw )
{
    if ( ec1.value() != 0 )
    {
        print( eStyle,
               "\nFucked up: {:^52} \nErrorcode: {:^52} \nMessage  : {:^52}",
               sw, ec1.value(), ec1.message() );
        print( eStyle, "\nFunction : {:^52} \nLine Num : {:^52}", fname,
               lno - 1 );
        std::cout << std::endl;
        // abort();
    }
    else
    {
        if ( sw != "" )
        {
            print( okStyle,
                   "\nlineNo: {} :- {:<20}:  Errorcode: {} Message: {}", lno,
                   sw, ec1.value(), ec1.message() );
        }
    }
}

void WriteString( std::shared_ptr<tcp::socket> sock, string const& WriteString )
{
    auto datab = std::make_shared<SessionWrite>();

    datab->setOutString( WriteString );
    datab->mSoc              = sock;
    datab->TotalBytesWritten = 0;

    // datab->mSoc->async_write_some( buffer( datab->OutString ), f2 );
    auto f2 = std::bind( WriteCallBack, _1, _2, datab );

    asio::async_write( *( datab->mSoc ), buffer( datab->OutString ), f2 );
}

void WriteCallBack( error_code ec, int fTotalBytesWritten,
                    std::shared_ptr<SessionWrite> sp )
{
    if ( ec.value() != 0 )
    {
        checkec( ec, where, "callback writesome" );
        return;
    }
}

void ReadString( std::shared_ptr<tcp::socket> soc )
{
    auto re = std::make_shared<SessionRead>();
    re->InputString.clear();
    re->InputString.resize( SessionRead::HEADERSIZE );
    re->mSoc       = soc;
    re->ReadHeader = true;

    auto f1 = std::bind( ReadCallBack, _1, _2, re );

    asio::async_read( *( re->mSoc ),
                      buffer( static_cast<char*>( re->InputString.data() ),
                              re->InputString.length() ),
                      f1 );
}
void ReadCallBack( error_code ec, int byRead, std::shared_ptr<SessionRead> rs )
{
    // print(wStyle,"\nwaaa");
    if ( ec.value() != 0 )
    {
        checkec( ec, where, "callbackread" );
        return;
    }

    if ( rs->ReadHeader == true )
    {
        int totals      = stoi( rs->InputString );
        rs->InputHeader = rs->InputString.substr( 0, SessionRead::HEADERSIZE );
        rs->InputString.clear();

        rs->InputString.resize( totals - SessionRead::HEADERSIZE );
        rs->ReadHeader = false;
    }
    else
    {
        tcp::endpoint rep = rs->mSoc->remote_endpoint( ec );
        checkec( ec, where );
        print( grStyle,
               "\nSomeOne From: {}:{} says:", rep.address().to_string(),
               rep.port() );
        print( yeStyle, "\n{}", rs->InputString );
        print( yeStyle, "\nThe Header Was: {}", rs->InputHeader );
        cout << endl;
        return;
    }
    auto f1 = std::bind( ReadCallBack, _1, _2, rs );

    asio::async_read( *( rs->mSoc ),
                      buffer( static_cast<char*>( rs->InputString.data() ),
                              rs->InputString.length() ),
                      f1 );
}
