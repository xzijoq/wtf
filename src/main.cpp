

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
using fmt::print;
using std::cout;
using std::endl;
using std::string;
#pragma endregion

int main( int argc, char* argv[] )
{
    print( orStyle, "\nMAIN STARTS HERE\n" );

 
    print( orStyle, "\nMAIN ENDS HERE\n" );
    return 0;
}
