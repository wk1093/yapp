#include "std.io.yapp.h"

#define pub
#define priv

// Emitted by yappc
// Emitting 5 declarations

namespace io {

#line 85 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void flush ( ) { 
#line 86 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
std :: cout . flush ( ) ; 
#line 87 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 89 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < str > fileReadText ( const str & filename ) { 
#line 90 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file :: reader file ( filename ) ; 
#line 91 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
if ( ! file . is_open ( ) ) { 
#line 92 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
return res :: err ( "Not Found: " + filename ) ; 
#line 93 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} 
#line 94 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
str content ; 
#line 95 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
str line ; 
#line 96 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
while ( std :: getline ( file , line ) ) { 
#line 97 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
content += line + "\n" ; 
#line 98 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} 
#line 99 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file . close ( ) ; 
#line 100 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
return res :: ok ( content ) ; 
#line 101 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 103 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < bytestr > fileReadBin ( const str & filename ) { 
#line 104 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file :: reader file ( filename , std :: ios :: binary ) ; 
#line 105 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
if ( ! file . is_open ( ) ) { 
#line 106 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
return res :: err ( "Not Found: " + filename ) ; 
#line 107 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} 
#line 108 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
bytestr content ; 
#line 109 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file . seekg ( 0 , std :: ios :: end ) ; 
#line 110 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
size_t size = file . tellg ( ) ; 
#line 111 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file . seekg ( 0 , std :: ios :: beg ) ; 
#line 112 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
content . resize ( size ) ; 
#line 113 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file . read ( & content [ 0 ] , size ) ; 
#line 114 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file . close ( ) ; 
#line 115 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
return res :: ok ( content ) ; 
#line 116 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 118 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < void > fileWrite ( const str & filename , const str & content ) { 
#line 119 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file :: writer file ( filename ) ; 
#line 120 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
if ( ! file . is_open ( ) ) { 
#line 121 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
return res :: err ( "Not Found: " + filename ) ; 
#line 122 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} 
#line 123 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file << content ; 
#line 124 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file . close ( ) ; 
#line 125 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
return res :: ok ( ) ; 
#line 126 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;


#line 128 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < void > fileAppend ( const str & filename , const str & content ) { 
#line 129 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file :: writer file ( filename , std :: ios :: app ) ; 
#line 130 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
if ( ! file . is_open ( ) ) { 
#line 131 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
return res :: err ( "Not Found: " + filename ) ; 
#line 132 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} 
#line 133 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file << content ; 
#line 134 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
file . close ( ) ; 
#line 135 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
return res :: ok ( ) ; 
#line 136 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.io.yapp"
} ;

}
#undef pub
#undef priv
