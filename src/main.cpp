
#include "main.h"

mutex              m1;
condition_variable cv1;
int                i{ 0 };

int a;

int longer()
{
    print( okStyle, "\nThats it im done" );
    cout << endl;
    this_thread::sleep_for( 2s );
    return 128;
}
int main( int argc, char* argv[] )
{
    print( orStyle, "\nMAIN STARTS HERE\n" );

    future<int> wtf = async( longer );

    // auto pp = wtf.get();
    int pp{};
    jthread jh2(
        [&]()
        {
            while ( true ) {
                
                 auto res=wtf.wait_for( 200ms ); 
                 if(res==std::future_status::ready){
                     break;
                 }
            
            }
            pp=wtf.get();
        } );
    jh2.join();
    print(okStyle,"\nThis IS what i get? {},",pp);

    print( orStyle, "\nMAIN ENDS HERE\n" );
    return 0;
}
