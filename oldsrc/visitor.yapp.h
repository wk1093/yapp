#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 12 declarations


;

#include <clang-c/Index.h>
;

#include <vector>
;

#include <string>
;

#include <unordered_set>
;

#include <cstring>
;

#include "decl_utils.yapp.h"
;

extern 
#line 8 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: vector < DeclInfo > decls;

extern 
#line 9 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) int orderCounter;

extern 
#line 10 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: unordered_set < std :: string > typedefBackedTags;

extern 
#line 11 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: vector < std :: string > anonymousTypes;


#line 112 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) CXChildVisitResult visitor ( CXCursor cursor , CXCursor parent , CXClientData client_data ) ;;

#undef pub
#undef priv
