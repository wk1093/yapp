#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 12 declarations

#include "std.main.yapp.h"
#include "std.str.yapp.h"
#include "std.vec.yapp.h"
#include "std.result.yapp.h"
#include "std.stream.yapp.h"

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
__attribute__ ( ( annotate ( "pub" ) ) ) vec < DeclInfo > decls;

extern 
#line 9 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) int orderCounter;

extern 
#line 10 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: unordered_set < str > typedefBackedTags;

extern 
#line 11 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) vec < str > anonymousTypes;


#line 112 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) CXChildVisitResult visitor ( CXCursor cursor , CXCursor parent , CXClientData client_data ) ;;

#undef pub
#undef priv
