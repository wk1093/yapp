#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 24 declarations

#include <iostream>
;

#include <fstream>
;

#include "std.str.yapp.h"
;

#include "std.result.yapp.h"
;

namespace file {
    using reader = std::ifstream;
;

    using writer = std::ofstream;
;

    using stream = std::fstream;
;

}

#line 10 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
; ;

namespace io {

#line 13 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
enum io_output_stream_type { 
#line 14 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
out , 
#line 15 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
err 
#line 16 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 19 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"

#line 18 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
template < typename ... Args > 
#line 19 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void print ( Args ... args ) { 
#line 20 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
( void ) std :: initializer_list < int > { ( std :: cout << args , 0 ) ... } ; 
#line 21 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 24 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"

#line 23 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
template < typename ... Args > 
#line 24 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void print ( io_output_stream_type type , Args ... args ) { 
#line 25 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
if ( type == out ) { 
#line 26 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
( void ) std :: initializer_list < int > { ( std :: cout << args , 0 ) ... } ; 
#line 27 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} else { 
#line 28 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
( void ) std :: initializer_list < int > { ( std :: cerr << args , 0 ) ... } ; 
#line 29 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} 
#line 30 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 33 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"

#line 32 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
template < typename ... Args > 
#line 33 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void print ( std :: ostream & stream , Args ... args ) { 
#line 34 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
( void ) std :: initializer_list < int > { ( stream << args , 0 ) ... } ; 
#line 35 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 38 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"

#line 37 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
template < typename ... Args > 
#line 38 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void println ( Args ... args ) { 
#line 39 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
( void ) std :: initializer_list < int > { ( std :: cout << args , 0 ) ... } ; 
#line 40 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
std :: cout << std :: endl ; 
#line 41 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 44 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"

#line 43 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
template < typename ... Args > 
#line 44 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void println ( io_output_stream_type type , Args ... args ) { 
#line 45 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
if ( type == out ) { 
#line 46 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
( void ) std :: initializer_list < int > { ( std :: cout << args , 0 ) ... } ; 
#line 47 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
std :: cout << std :: endl ; 
#line 48 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} else { 
#line 49 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
( void ) std :: initializer_list < int > { ( std :: cerr << args , 0 ) ... } ; 
#line 50 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
std :: cerr << std :: endl ; 
#line 51 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} 
#line 52 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 55 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"

#line 54 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
template < typename ... Args > 
#line 55 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void println ( std :: ostream & stream , Args ... args ) { 
#line 56 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
( void ) std :: initializer_list < int > { ( stream << args , 0 ) ... } ; 
#line 57 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
stream << std :: endl ; 
#line 58 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 61 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"

#line 60 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
template < typename ... Args > 
#line 61 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void printError ( Args ... args ) { 
#line 62 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
( void ) std :: initializer_list < int > { ( std :: cerr << args , 0 ) ... } ; 
#line 63 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 66 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"

#line 65 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
template < typename ... Args > 
#line 66 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void printlnError ( Args ... args ) { 
#line 67 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
( void ) std :: initializer_list < int > { ( std :: cerr << args , 0 ) ... } ; 
#line 68 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
std :: cerr << std :: endl ; 
#line 69 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 72 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"

#line 71 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
template < typename T > 
#line 72 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) T read ( ) { 
#line 73 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
T value ; 
#line 74 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
std :: cin >> value ; 
#line 75 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
return value ; 
#line 76 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 79 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"

#line 78 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
template < typename T > 
#line 79 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) T readLine ( ) { 
#line 80 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
T value ; 
#line 81 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
std :: getline ( std :: cin , value ) ; 
#line 82 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
return value ; 
#line 83 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 85 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void flush ( ) ;;


#line 89 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < str > fileReadText ( const str & filename ) ;;


#line 103 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < bytestr > fileReadBin ( const str & filename ) ;;


#line 118 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < void > fileWrite ( const str & filename , const str & content ) ;;


#line 128 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < void > fileAppend ( const str & filename , const str & content ) ;;

}
#undef pub
#undef priv
