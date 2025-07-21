#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 18 declarations

#include "std.main.yapp.h"
#include "std.str.yapp.h"
#include "std.vec.yapp.h"
#include "std.result.yapp.h"
#include "std.stream.yapp.h"

;

#include <clang-c/Index.h>
;

#include <string>
;

#include <vector>
;

#include <cstring>
;

#include <algorithm>
;


#line 7 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
struct __attribute__ ( ( annotate ( "pub" ) ) ) DeclInfo { 
#line 8 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str name ; 
#line 9 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str usr ; 
#line 10 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str code ; 
#line 11 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str annotation ; 
#line 12 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
bool isDefinition = false ; 
#line 13 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
bool isInline = false ; 
#line 14 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
bool isExternC = false ; 
#line 15 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
bool isTemplate = false ; 
#line 16 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
bool isStatic = false ; 
#line 17 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
bool isExtern = false ; 
#line 18 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
bool isConstexpr = false ; 
#line 19 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
bool isConst = false ; 
#line 20 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
bool isUsingDec = false ; 
#line 21 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXCursorKind kind ; 
#line 22 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
int sourceOrderIndex = 0 ; 
#line 23 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
vec < str > namespaces ; 
#line 24 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str typeUsr ; 
#line 25 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} ;


#line 27 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) bool isExternC ( CXCursor cursor ) ;;


#line 54 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) bool isAnonymousStruct ( const DeclInfo & d ) ;;


#line 58 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str toStdString ( CXString cxStr ) ;;


#line 64 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
extern str GLOBAL_INPUT_FILE ;


#line 65 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
extern str GLOBAL_SOURCE_FILE ;


#line 67 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str createLineDirective ( CXSourceLocation loc ) ;;


#line 84 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) bool isDifferentDirective ( CXSourceLocation loc1 , CXSourceLocation loc2 ) ;;


#line 92 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str getSourceText ( CXCursor cursor , CXTranslationUnit tu ) ;;


#line 114 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str getAnnotate ( CXCursor cursor ) ;;


#line 127 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) vec < str > getNamespaceChain ( CXCursor cursor ) ;;


#line 141 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str makeDeclaration ( const str & code ) ;;

#undef pub
#undef priv
