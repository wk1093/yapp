#pragma once
#define pub
#define priv

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

extern __attribute__ ( ( annotate ( "pub" ) ) ) std :: vector < DeclInfo > decls;

extern __attribute__ ( ( annotate ( "pub" ) ) ) int orderCounter;

extern __attribute__ ( ( annotate ( "pub" ) ) ) std :: unordered_set < std :: string > typedefBackedTags;

extern __attribute__ ( ( annotate ( "pub" ) ) ) std :: vector < std :: string > anonymousTypes;

__attribute__ ( ( annotate ( "pub" ) ) ) CXChildVisitResult visitor ( CXCursor cursor , CXCursor parent , CXClientData client_data ) ;;

#undef pub
#undef priv
