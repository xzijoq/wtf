
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
    auto datab = std::make_shared<Session>();

    // print(okStyle,"\n {}",datab->OutString.append(
    // datab->OutString.length()));
    datab->setOutString( WriteString );
    datab->mSoc              = sock;
    datab->TotalBytesWritten = 0;

    auto f2 = std::bind( WriteCallBack, _1, _2, datab );
    datab->mSoc->async_write_some( buffer( datab->OutString ), f2 );
}

void WriteCallBack( error_code ec, int fTotalBytesWritten,
                    std::shared_ptr<Session> sp )
{
    if ( ec.value() != 0 )
    {
        checkec( ec, where, "callback writesome" );
        return;
    }

    sp->TotalBytesWritten += fTotalBytesWritten;

    if ( ( sp->TotalBytesWritten ) >= ( sp->OutString.length() ) ) { return; }

    auto f1 = std::bind( WriteCallBack, _1, _2, sp );

    sp->mSoc->async_write_some(
        buffer( sp->OutString.c_str() + sp->TotalBytesWritten,
                sp->OutString.length() - sp->TotalBytesWritten ),
        f1 );
}

void ReadString( std::shared_ptr<tcp::socket> soc )
{
    auto re = std::make_shared<Session>();
    re->InputString.clear();
    re->InputString.resize( Session::HEADERSIZE );
    re->mSoc = soc;

    auto f1 = std::bind( ReadCallBack, _1, _2, re );

    re->mSoc->async_read_some(
        buffer(
            static_cast<char*>( re->InputString.data() + re->TotalBytesRead ),
            re->InputString.length() - re->TotalBytesRead ),
        f1 );
}

void ReadCallBack( error_code ec, int byRead, std::shared_ptr<Session> rs )
{
    if ( ec.value() != 0 )
    {
        checkec( ec, where, "callbackread" );
        return;
    }
    rs->TotalBytesRead += byRead;

    if ( rs->TotalBytesRead == Session::HEADERSIZE )
    {
        int totals = stoi( rs->InputString );
        rs->InputString.resize( totals );
    }
    if ( rs->TotalBytesRead >= rs->InputString.size() )
    {
        rs->InputHeader = rs->InputString.substr( 0, Session::HEADERSIZE );
        rs->InputString.erase( 0, Session::HEADERSIZE );

        print( grStyle, "\nSomeOne From: {}:{} says:",
               rs->mSoc->remote_endpoint().address().to_string(),
               rs->mSoc->remote_endpoint().port() );
        print( yeStyle, "\n{}", rs->InputString );
        print( yeStyle, "\nThe Header Was: {}", rs->InputHeader );
        cout << endl;
        return;
    }
    auto f1 = std::bind( ReadCallBack, _1, _2, rs );

    rs->mSoc->async_read_some(
        buffer(
            static_cast<char*>( rs->InputString.data() + rs->TotalBytesRead ),
            rs->InputString.length() - rs->TotalBytesRead ),
        f1 );
}
