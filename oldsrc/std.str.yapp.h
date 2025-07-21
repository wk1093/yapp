#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 8 declarations

#include <string>
;

#include <sstream>
;

#include <vector>
;

#include <cstdarg>
;

#include <filesystem>
;


#line 7 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
class __attribute__ ( ( annotate ( "pub" ) ) ) str : public std :: string { 
#line 8 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
public : 
#line 9 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
    using reader = std::istringstream;
#line 10 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
    using writer = std::ostringstream;
#line 11 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
    using stream = std::stringstream;
#line 13 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
static const size_t NotFound = std :: string :: npos ; 
#line 15 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
using std :: string :: string ; 
#line 16 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
str ( ) : std :: string ( ) { } 
#line 17 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
str ( const std :: string & s ) : std :: string ( s ) { } 
#line 18 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
str ( const char * s ) : std :: string ( s ) { } 
#line 19 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
str ( const char * s , size_t length ) : std :: string ( s , length ) { } 
#line 20 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
str ( const str & other ) : std :: string ( other ) { } 
#line 21 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
str ( str && other ) noexcept : std :: string ( std :: move ( other ) ) { } 
#line 22 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
str ( const std :: filesystem :: path & p ) : std :: string ( p . string ( ) ) { } 
#line 23 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str & operator = ( const str & other ) { 
#line 24 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
std :: string :: operator = ( other ) ; 
#line 25 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
return * this ; 
#line 26 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 28 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: string stdstr ( ) const { 
#line 29 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
return * this ; 
#line 30 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 32 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) bool endsWith ( const str & suffix ) const { 
#line 33 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
if ( suffix . length ( ) > this -> length ( ) ) return false ; 
#line 34 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
return this -> std :: string :: rfind ( suffix ) == this -> length ( ) - suffix . length ( ) ; 
#line 35 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 36 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str toUpper ( ) const { 
#line 37 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
str result = * this ; 
#line 38 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
for ( char & c : result ) { 
#line 39 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
c = std :: toupper ( c ) ; 
#line 40 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 41 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
return result ; 
#line 42 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 43 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str toLower ( ) const { 
#line 44 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
str result = * this ; 
#line 45 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
for ( char & c : result ) { 
#line 46 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
c = std :: tolower ( c ) ; 
#line 47 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 48 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
return result ; 
#line 49 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 50 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str trim ( ) const { 
#line 51 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
size_t start = this -> find_first_not_of ( " \t\n\r\f\v" ) ; 
#line 52 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
size_t end = this -> find_last_not_of ( " \t\n\r\f\v" ) ; 
#line 53 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
if ( start == std :: string :: npos || end == std :: string :: npos ) return str ( ) ; 
#line 54 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
return this -> substr ( start , end - start + 1 ) ; 
#line 55 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 57 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) static str format ( const char * fmt , ... ) { 
#line 58 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
va_list args ; 
#line 59 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
va_start ( args , fmt ) ; 
#line 60 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
va_list args_copy ; 
#line 61 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
va_copy ( args_copy , args ) ; 
#line 62 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
size_t size = vsnprintf ( nullptr , 0 , fmt , args_copy ) + 1 ; 
#line 63 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
va_end ( args_copy ) ; 
#line 65 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
std :: vector < char > buffer ( size ) ; 
#line 66 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
vsnprintf ( buffer . data ( ) , size , fmt , args ) ; 
#line 67 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
va_end ( args ) ; 
#line 68 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
return str ( buffer . data ( ) ) ; 
#line 69 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 71 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
template < typename T > 
#line 72 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) static str toString ( const T & value ) { 
#line 73 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
writer ss ; 
#line 74 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
ss << value ; 
#line 75 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
return str ( ss . str ( ) ) ; 
#line 76 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 78 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
template < typename T > 
#line 79 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) static str join ( const std :: vector < T > & items , const str & delimiter = ", " ) { 
#line 80 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
if ( items . empty ( ) ) return str ( ) ; 
#line 81 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
writer ss ; 
#line 82 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
for ( size_t i = 0 ; i < items . size ( ) ; ++ i ) { 
#line 83 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
ss << items [ i ] ; 
#line 84 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
if ( i < items . size ( ) - 1 ) { 
#line 85 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
ss << delimiter ; 
#line 86 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 87 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 88 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
return str ( ss . str ( ) ) ; 
#line 89 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} 
#line 92 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.str.yapp"
} ;

template<> pub struct std::hash<str> { size_t operator()(const str& s) const noexcept { return std::hash<std::string>()(s); }};
;

using bytestr = str;
;

#undef pub
#undef priv
