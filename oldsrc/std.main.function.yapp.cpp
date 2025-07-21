#include "std.main.function.yapp.h"

#define pub
#define priv

// Emitted by yappc
// Emitting 1 declarations


#line 8 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) int main ( int argc , char * * argv ) { 
#line 9 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
vec < str > args ; 
#line 10 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
for ( int i = 0 ; i < argc ; ++ i ) { 
#line 11 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
args . push_back ( str ( argv [ i ] ) ) ; 
#line 12 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
} 
#line 13 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
if ( __user_main ) { 
#line 14 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
return __user_main ( args ) ; 
#line 15 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
} else { 
#line 16 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
printf ( "No user main defined.\n" ) ; 
#line 17 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
return 1 ; 
#line 18 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
} 
#line 19 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.main.function.yapp"
} ;

#undef pub
#undef priv
