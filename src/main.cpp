

#include <assert.h>
#include <chrono>
#include <cstdint>
#include <system_error>
#include <thread>
#include <iostream>

#include "main.h"
#include "style.h"

#pragma region using

using namespace std::chrono;
using namespace std;
using fmt::print;
#pragma endregion

void testf(int x){
    print(liStyle,"omfg");
    cout<<endl;
    
}

int main( int argc, char* argv[] )
{
    print( orStyle, "\nMAIN STARTS HERE\n" );


    jthread r1(
        [](){
            print(okStyle,"\nRunning from a jthread");
            cout<<endl;
        }

    );
    jthread j1(testf,2);

 
    print( orStyle, "\nMAIN ENDS HERE\n" );
    return 0;
}
