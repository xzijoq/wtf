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
using std::error_code;

using namespace asio;
using asio::ip::tcp;
using namespace std::placeholders;
#pragma endregion

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
