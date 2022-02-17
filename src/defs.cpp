
#include <defs.h>
#include <style.h>

using std::cout;
using std::endl;

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