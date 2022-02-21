#pragma once
#include <iostream>

#if __clang__ || __GNUC__
    #define where __PRETTY_FUNCTION__, __LINE__
#else
    #define where __function__, __LINE__
#endif

using std::string;
void checkec( std::error_code ec1, std::string fname = "", int lno = -1,
              std::string sw = "" );

#include <asio.hpp>
#include <asio/ip/tcp.hpp>

using asio::ip::tcp;
using std::error_code;

struct SessionWrite
{
    static constexpr uint_fast32_t HEADERSIZE = 9;

    std::shared_ptr<tcp::socket> mSoc;

    string OutString{ "" };
    int    TotalBytesWritten{ 0 };
    void   setOutString( string instr )
    {
        string slen;
        slen.resize( SessionWrite::HEADERSIZE );

        int    ins  = instr.length() + slen.length();
        string sins = std::to_string( ins );

        slen.replace( 0, sins.length(), sins );

        OutString.reserve( instr.length() + slen.length() );
        OutString = instr;

        OutString = OutString.insert( 0, slen );
    }
};
struct SessionRead
{
    static constexpr uint_fast32_t HEADERSIZE = SessionWrite::HEADERSIZE;
    //! can be:  static constexpr uint_fast32_t HEADERSIZE=9;
    std::shared_ptr<tcp::socket> mSoc;
    string                       InputString;
    int                          TotalBytesRead{ 0 };
    string                       InputHeader;
};

void WriteString( std::shared_ptr<tcp::socket> sock,
                  string const&                WriteString );
void WriteCallBack( error_code ec, int fTotalBytesWritten,
                    std::shared_ptr<SessionWrite> sp );

void ReadString( std::shared_ptr<tcp::socket> soc );
void ReadCallBack( error_code ec, int byRead, std::shared_ptr<SessionRead> rs );