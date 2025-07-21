#include "std.result.yapp.h"

#define pub
#define priv

// Emitted by yappc
// Emitting 2 declarations

namespace res {

#line 103 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < void > ok ( ) { 
#line 104 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
result < void > res ; 
#line 105 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
res . ok_ptr = std :: make_unique < ok_result < void >> ( ) ; 
#line 106 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
return res ; 
#line 107 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} ;


#line 109 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) result < void > err ( const str & error ) { 
#line 110 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
result < void > res ; 
#line 111 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
res . err_ptr = std :: make_unique < err_result > ( error ) ; 
#line 112 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
return res ; 
#line 113 "/home/wyatt/dev/cpp/pubprivattr/stdlib/std.result.yapp"
} ;

}
#undef pub
#undef priv
