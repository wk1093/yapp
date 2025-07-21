#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 5 declarations

#include "std.str.yapp.h"
;

#include "std.vec.yapp.h"
;

#include <cstdio>
;


#line 6 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) int __user_main ( vec < str > ) __attribute__ ( ( weak ) ) ;


#line 8 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) int main ( int argc , char * * argv ) ;;

#undef pub
#undef priv
