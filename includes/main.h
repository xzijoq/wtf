#pragma once


#if __clang__ || __GNUC__
    #define where __FILE__, __PRETTY_FUNCTION__, __LINE__
#else
    #define where __FILE__ , __function__ , __LINE__
#endif

//#include










