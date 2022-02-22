#pragma once

#if __clang__ || __GNUC__
    #define where __FILE__, __PRETTY_FUNCTION__, __LINE__
#else
    #define where __FILE__, __function__, __LINE__
#endif

#include <assert.h>

#include <chrono>
#include <cstdint>
#include <iostream>
#include <system_error>

#include <thread>
#include <condition_variable>
#include <future>

#include "main.h"
#include "style.h"

#pragma region using

using namespace std::chrono;
using namespace std;
using fmt::print;
#pragma endregion

void show( string file, string func, int line, string msg = "" )
{
    auto t1 = hash<thread::id>{}( this_thread::get_id() );
    auto th=u_int16_t(t1);
    
    if(msg=="thread"){
        print(eStyle,"\nHash: {} Line: {} Func: {}",th,line,func);
        cout<<endl;
        return;
    }


    print( eStyle, "\nFunction:{:^52} ", func );
    print( eStyle, "\nOn Line :{:^52} ", line );
    print( eStyle, "\nIn File :{:^52} ", file );
    print( eStyle, "\nThr Hash:{:^52} ", (uint8_t)th );

  //  cout << endl << std::this_thread::get_id();
    if ( msg != "" ) { print( eStyle, "\nMsg    :{:^52} ", msg ); }
    std::cout << std::endl;

    // abort();
}

//#include
