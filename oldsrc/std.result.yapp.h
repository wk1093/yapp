#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 11 declarations

#include <memory>
;

#include "std.str.yapp.h"
;


#line 4 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
struct __attribute__ ( ( annotate ( "pub" ) ) ) base_result { 
#line 5 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
virtual ~ base_result ( ) = default ; 
#line 6 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
virtual bool isOk ( ) const = 0 ; 
#line 7 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
virtual bool isErr ( ) const = 0 ; 
#line 8 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} ;


#line 11 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"

#line 10 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
template < typename T = void > 
#line 11 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
struct __attribute__ ( ( annotate ( "pub" ) ) ) ok_result : public base_result { 
#line 12 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
T value ; 
#line 13 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
ok_result ( const T & v ) : value ( v ) { } 
#line 14 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
bool isOk ( ) const override { return true ; } 
#line 15 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
bool isErr ( ) const override { return false ; } 
#line 16 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} ;


#line 19 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"

#line 18 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
template < > 
#line 19 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
struct __attribute__ ( ( annotate ( "pub" ) ) ) ok_result < void > : base_result { 
#line 20 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
ok_result ( ) { } 
#line 21 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
bool isOk ( ) const override { return true ; } 
#line 22 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
bool isErr ( ) const override { return false ; } 
#line 23 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} ;


#line 25 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
struct __attribute__ ( ( annotate ( "pub" ) ) ) err_result : public base_result { 
#line 26 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
str error ; 
#line 27 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
err_result ( const str & err ) : error ( err ) { } 
#line 28 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
bool isOk ( ) const override { return false ; } 
#line 29 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
bool isErr ( ) const override { return true ; } 
#line 30 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} ;


#line 33 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"

#line 32 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
template < typename T = void > 
#line 33 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
struct __attribute__ ( ( annotate ( "pub" ) ) ) result { 
#line 34 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
std :: unique_ptr < ok_result < T >> ok_ptr = nullptr ; 
#line 35 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
std :: unique_ptr < err_result > err_ptr = nullptr ; 
#line 37 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
result ( ) = default ; 
#line 39 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
bool isOk ( ) const { return ok_ptr != nullptr ; } 
#line 40 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
bool isErr ( ) const { return err_ptr != nullptr ; } 
#line 42 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
T unwrap ( ) const { 
#line 43 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
if ( ! isOk ( ) ) throw std :: runtime_error ( "Tried to unwrap error result: " + err_ptr -> error ) ; 
#line 44 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
return ok_ptr -> value ; 
#line 45 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} 
#line 47 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
str unwrapErr ( ) const { 
#line 48 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
if ( ! isErr ( ) ) throw std :: runtime_error ( "Tried to unwrap error from Ok" ) ; 
#line 49 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
return err_ptr -> error ; 
#line 50 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} 
#line 53 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
operator T ( ) const { 
#line 54 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
return unwrap ( ) ; 
#line 55 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} 
#line 58 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
operator bool ( ) const { 
#line 59 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
return isOk ( ) ; 
#line 60 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} 
#line 61 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} ;


#line 64 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"

#line 63 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
template < > 
#line 64 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
struct __attribute__ ( ( annotate ( "pub" ) ) ) result < void > { 
#line 65 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
std :: unique_ptr < ok_result < void >> ok_ptr = nullptr ; 
#line 66 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
std :: unique_ptr < err_result > err_ptr = nullptr ; 
#line 68 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
result ( ) = default ; 
#line 70 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
bool isOk ( ) const { return ok_ptr != nullptr ; } 
#line 71 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
bool isErr ( ) const { return err_ptr != nullptr ; } 
#line 73 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
void unwrap ( ) const { 
#line 74 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
if ( ! isOk ( ) ) throw std :: runtime_error ( "Tried to unwrap error result: " + err_ptr -> error ) ; 
#line 75 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} 
#line 77 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
str unwrapErr ( ) const { 
#line 78 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
if ( ! isErr ( ) ) throw std :: runtime_error ( "Tried to unwrap error from Ok" ) ; 
#line 79 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
return err_ptr -> error ; 
#line 80 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} 
#line 82 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
template < typename U > 
#line 83 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
operator result < U > ( ) const { 
#line 84 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
if ( ! isErr ( ) ) throw std :: runtime_error ( "Attempted to convert normal result to error result" ) ; 
#line 85 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
result < U > res ; 
#line 86 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
res . err_ptr = std :: make_unique < err_result > ( err_ptr -> error ) ; 
#line 87 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
return res ; 
#line 88 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} 
#line 90 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
operator bool ( ) const { 
#line 91 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
return isOk ( ) ; 
#line 92 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} 
#line 93 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} ;

namespace res {

#line 97 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"

#line 96 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
template < typename U > 
#line 97 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < U > ok ( const U & value ) { 
#line 98 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
result < U > res ; 
#line 99 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
res . ok_ptr = std :: make_unique < ok_result < U >> ( value ) ; 
#line 100 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
return res ; 
#line 101 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} ;


#line 103 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < void > ok ( ) ;;


#line 109 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < void > err ( const str & error ) ;;

}
#undef pub
#undef priv
