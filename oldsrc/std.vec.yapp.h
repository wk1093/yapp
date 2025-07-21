#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 6 declarations

#include "std.str.yapp.h"
;

#include "std.result.yapp.h"
;

#include <vector>
;

#include <functional>
;

#include <algorithm>
;


#line 8 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"

#line 7 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
template < typename T > 
#line 8 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
struct vec : public std :: vector < T > { 
#line 9 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
using std :: vector < T > :: vector ; 
#line 11 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
vec ( const std :: vector < T > & other ) : std :: vector < T > ( other ) { } 
#line 12 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
vec ( std :: vector < T > && other ) noexcept : std :: vector < T > ( std :: move ( other ) ) { } 
#line 13 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
vec & operator = ( const std :: vector < T > & other ) { 
#line 14 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
std :: vector < T > :: operator = ( other ) ; 
#line 15 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return * this ; 
#line 16 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 17 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
vec & operator = ( std :: vector < T > && other ) noexcept { 
#line 18 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
std :: vector < T > :: operator = ( std :: move ( other ) ) ; 
#line 19 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return * this ; 
#line 20 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 22 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
operator std :: vector < T > & ( ) { 
#line 23 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return * static_cast < std :: vector < T > * > ( this ) ; 
#line 24 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 26 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
str join ( const str & delimiter ) const { 
#line 27 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( this -> empty ( ) ) return str ( ) ; 
#line 28 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
str :: writer writer ; 
#line 29 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( size_t i = 0 ; i < this -> size ( ) ; ++ i ) { 
#line 30 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
writer << ( * this ) [ i ] ; 
#line 31 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( i < this -> size ( ) - 1 ) { 
#line 32 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
writer << delimiter ; 
#line 33 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 34 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 35 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return writer . str ( ) ; 
#line 36 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 38 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
str join ( ) const { 
#line 39 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return join ( ", " ) ; 
#line 40 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 42 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
str toString ( ) const { 
#line 43 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return str :: join ( * this , ", " ) ; 
#line 44 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 45 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
str toString ( const str & delimiter ) const { 
#line 46 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return str :: join ( * this , delimiter ) ; 
#line 47 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 49 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
template < typename U > 
#line 50 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
vec < U > map ( std :: function < U ( const T & ) > func ) const { 
#line 51 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
vec < U > result ; 
#line 52 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( const auto & item : * this ) { 
#line 53 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
result . push_back ( func ( item ) ) ; 
#line 54 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 55 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return result ; 
#line 56 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 58 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
template < typename U > 
#line 59 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
U reduce ( std :: function < U ( const U & , const T & ) > func , U initial ) const { 
#line 60 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
U result = initial ; 
#line 61 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( const auto & item : * this ) { 
#line 62 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
result = func ( result , item ) ; 
#line 63 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 64 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return result ; 
#line 65 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 67 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
vec < T > filter ( std :: function < bool ( const T & ) > predicate ) const { 
#line 68 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
vec < T > result ; 
#line 69 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( const auto & item : * this ) { 
#line 70 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( predicate ( item ) ) { 
#line 71 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
result . push_back ( item ) ; 
#line 72 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 73 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 74 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return result ; 
#line 75 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 77 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
bool contains ( const T & value ) const { 
#line 78 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return std :: find ( this -> begin ( ) , this -> end ( ) , value ) != this -> end ( ) ; 
#line 79 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 81 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
result < T > find ( std :: function < bool ( const T & ) > predicate , size_t start = 0 ) const { 
#line 82 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( start >= this -> size ( ) ) { 
#line 83 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Start index out of bounds" ) ; 
#line 84 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 85 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( size_t i = start ; i < this -> size ( ) ; ++ i ) { 
#line 86 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( predicate ( ( * this ) [ i ] ) ) { 
#line 87 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: ok ( ( * this ) [ i ] ) ; 
#line 88 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 89 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 90 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Item not found" ) ; 
#line 91 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 93 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
result < T > find ( const T & value , size_t start = 0 ) const { 
#line 94 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( start >= this -> size ( ) ) { 
#line 95 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Start index out of bounds" ) ; 
#line 96 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 97 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( size_t i = start ; i < this -> size ( ) ; ++ i ) { 
#line 98 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( ( * this ) [ i ] == value ) { 
#line 99 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: ok ( ( * this ) [ i ] ) ; 
#line 100 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 101 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 102 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Item not found" ) ; 
#line 103 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 105 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
result < T > find ( std :: function < bool ( const T & ) > predicate , size_t start , size_t end ) const { 
#line 106 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( start >= this -> size ( ) || end > this -> size ( ) || start >= end ) { 
#line 107 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Invalid range" ) ; 
#line 108 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 109 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( size_t i = start ; i < end ; ++ i ) { 
#line 110 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( predicate ( ( * this ) [ i ] ) ) { 
#line 111 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: ok ( ( * this ) [ i ] ) ; 
#line 112 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 113 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 114 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Item not found in range" ) ; 
#line 115 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 117 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
result < T > find ( const T & value , size_t start , size_t end ) const { 
#line 118 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( start >= this -> size ( ) || end > this -> size ( ) || start >= end ) { 
#line 119 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Invalid range" ) ; 
#line 120 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 121 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( size_t i = start ; i < end ; ++ i ) { 
#line 122 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( ( * this ) [ i ] == value ) { 
#line 123 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: ok ( ( * this ) [ i ] ) ; 
#line 124 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 125 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 126 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Item not found in range" ) ; 
#line 127 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 129 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
result < T > rfind ( std :: function < bool ( const T & ) > predicate ) const { 
#line 130 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( auto it = this -> rbegin ( ) ; it != this -> rend ( ) ; ++ it ) { 
#line 131 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( predicate ( * it ) ) { 
#line 132 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: ok ( * it ) ; 
#line 133 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 134 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 135 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Item not found" ) ; 
#line 136 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 138 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
result < T > rfind ( const T & value ) const { 
#line 139 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( auto it = this -> rbegin ( ) ; it != this -> rend ( ) ; ++ it ) { 
#line 140 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( * it == value ) { 
#line 141 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: ok ( * it ) ; 
#line 142 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 143 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 144 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Item not found" ) ; 
#line 145 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 147 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
result < T > rfind ( std :: function < bool ( const T & ) > predicate , size_t start , size_t end ) const { 
#line 148 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( start >= this -> size ( ) || end > this -> size ( ) || start >= end ) { 
#line 149 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Invalid range" ) ; 
#line 150 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 151 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( size_t i = end ; i -- > start ; ) { 
#line 152 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( predicate ( ( * this ) [ i ] ) ) { 
#line 153 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: ok ( ( * this ) [ i ] ) ; 
#line 154 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 155 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 156 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Item not found in range" ) ; 
#line 157 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 159 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
result < T > rfind ( const T & value , size_t start , size_t end ) const { 
#line 160 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( start >= this -> size ( ) || end > this -> size ( ) || start >= end ) { 
#line 161 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Invalid range" ) ; 
#line 162 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 163 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
for ( size_t i = end ; i -- > start ; ) { 
#line 164 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
if ( ( * this ) [ i ] == value ) { 
#line 165 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: ok ( ( * this ) [ i ] ) ; 
#line 166 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 167 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 168 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
return res :: err ( "Item not found in range" ) ; 
#line 169 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 171 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
void sort ( std :: function < bool ( const T & , const T & ) > comp ) { 
#line 172 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
std :: sort ( this -> begin ( ) , this -> end ( ) , comp ) ; 
#line 173 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} 
#line 174 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.vec.yapp"
} ;

#undef pub
#undef priv
