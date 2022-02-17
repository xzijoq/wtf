#pragma once
#include <iostream>

#if __clang__ || __GNUC__
    #define where __PRETTY_FUNCTION__, __LINE__
#else
    #define where __function__, __LINE__
#endif

void checkec( std::error_code ec1, std::string sw = "", std::string fname = "",
              int lno = -1 );
