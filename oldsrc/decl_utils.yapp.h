#pragma once
#define pub
#define priv

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

struct __attribute__ ( ( annotate ( "pub" ) ) ) DeclInfo { std :: string name ; std :: string usr ; std :: string code ; std :: string annotation ; bool isDefinition = false ; bool isInline = false ; bool isExternC = false ; bool isTemplate = false ; bool isStatic = false ; bool isExtern = false ; bool isConstexpr = false ; bool isConst = false ; bool isUsingDec = false ; CXCursorKind kind ; int sourceOrderIndex = 0 ; std :: vector < std :: string > namespaces ; std :: string typeUsr ; } ;

__attribute__ ( ( annotate ( "pub" ) ) ) bool isExternC ( CXCursor cursor ) ;;

__attribute__ ( ( annotate ( "pub" ) ) ) bool isAnonymousStruct ( const DeclInfo & d ) ;;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string toStdString ( CXString cxStr ) ;;

extern std :: string GLOBAL_INPUT_FILE ;

extern std :: string GLOBAL_SOURCE_FILE ;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string createLineDirective ( CXSourceLocation loc ) ;;

__attribute__ ( ( annotate ( "pub" ) ) ) bool isDifferentDirective ( CXSourceLocation loc1 , CXSourceLocation loc2 ) ;;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string getSourceText ( CXCursor cursor , CXTranslationUnit tu ) ;;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string getAnnotate ( CXCursor cursor ) ;;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: vector < std :: string > getNamespaceChain ( CXCursor cursor ) ;;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string makeDeclaration ( const std :: string & code ) ;;

#undef pub
#undef priv
