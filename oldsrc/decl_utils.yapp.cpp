#include "decl_utils.yapp.h"

#define pub
#define priv

// Emitted by yappc
// Emitting 9 declarations


#line 27 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) bool isExternC ( CXCursor cursor ) { 
#line 28 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
if ( clang_getCursorKind ( cursor ) != CXCursor_FunctionDecl ) 
#line 29 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return false ; 
#line 30 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
if ( clang_getCursorLinkage ( cursor ) != CXLinkage_External ) 
#line 31 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return false ; 
#line 32 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXCursor parent = clang_getCursorSemanticParent ( cursor ) ; 
#line 33 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
if ( clang_getCursorKind ( parent ) == CXCursor_LinkageSpec ) { 
#line 34 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXSourceRange range = clang_getCursorExtent ( parent ) ; 
#line 35 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXTranslationUnit tu = clang_Cursor_getTranslationUnit ( parent ) ; 
#line 36 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXToken * tokens = nullptr ; 
#line 37 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
unsigned numTokens = 0 ; 
#line 38 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_tokenize ( tu , range , & tokens , & numTokens ) ; 
#line 39 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
for ( unsigned i = 0 ; i < numTokens ; ++ i ) { 
#line 40 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXString spelling = clang_getTokenSpelling ( tu , tokens [ i ] ) ; 
#line 41 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
const char * token = clang_getCString ( spelling ) ; 
#line 42 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
if ( strcmp ( token , "\"C\"" ) == 0 ) { 
#line 43 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_disposeString ( spelling ) ; 
#line 44 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_disposeTokens ( tu , tokens , numTokens ) ; 
#line 45 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return true ; 
#line 46 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} 
#line 47 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_disposeString ( spelling ) ; 
#line 48 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} 
#line 49 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_disposeTokens ( tu , tokens , numTokens ) ; 
#line 50 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} 
#line 51 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return false ; 
#line 52 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} ;


#line 54 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) bool isAnonymousStruct ( const DeclInfo & d ) { 
#line 55 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return ( d . kind == CXCursor_StructDecl ) && d . name . empty ( ) ; 
#line 56 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} ;


#line 58 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str toStdString ( CXString cxStr ) { 
#line 59 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str str = clang_getCString ( cxStr ) ; 
#line 60 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_disposeString ( cxStr ) ; 
#line 61 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return str ; 
#line 62 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} ;


#line 67 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str createLineDirective ( CXSourceLocation loc ) { 
#line 68 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXFile file ; 
#line 69 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
unsigned line , column , offset ; 
#line 70 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_getFileLocation ( loc , & file , & line , & column , & offset ) ; 
#line 71 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXString fileName = clang_getFileName ( file ) ; 
#line 72 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str filePath = toStdString ( fileName ) ; 
#line 73 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_disposeString ( fileName ) ; 
#line 75 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
if ( filePath == GLOBAL_INPUT_FILE ) { 
#line 76 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
filePath = GLOBAL_SOURCE_FILE ; 
#line 77 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} 
#line 79 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str lineDirective = "\n#line " + str :: from ( line ) + " \"" + filePath + "\"\n" ; 
#line 81 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return lineDirective ; 
#line 82 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} ;


#line 84 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) bool isDifferentDirective ( CXSourceLocation loc1 , CXSourceLocation loc2 ) { 
#line 85 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXFile file1 , file2 ; 
#line 86 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
unsigned line1 , line2 , column1 , column2 , offset1 , offset2 ; 
#line 87 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_getFileLocation ( loc1 , & file1 , & line1 , & column1 , & offset1 ) ; 
#line 88 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_getFileLocation ( loc2 , & file2 , & line2 , & column2 , & offset2 ) ; 
#line 89 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return ( file1 != file2 || line1 != line2 ) ; 
#line 90 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} ;


#line 92 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str getSourceText ( CXCursor cursor , CXTranslationUnit tu ) { 
#line 93 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXSourceRange range = clang_getCursorExtent ( cursor ) ; 
#line 94 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXToken * tokens = nullptr ; 
#line 95 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
unsigned numTokens = 0 ; 
#line 97 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXSourceLocation loc = clang_getCursorLocation ( cursor ) ; 
#line 99 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_tokenize ( tu , range , & tokens , & numTokens ) ; 
#line 100 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str result = createLineDirective ( loc ) ; 
#line 101 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
for ( unsigned i = 0 ; i < numTokens ; ++ i ) { 
#line 102 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXSourceLocation tokenLoc = clang_getTokenLocation ( tu , tokens [ i ] ) ; 
#line 103 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
if ( isDifferentDirective ( loc , tokenLoc ) ) { 
#line 104 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
result += createLineDirective ( tokenLoc ) ; 
#line 105 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} 
#line 106 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
loc = tokenLoc ; 
#line 107 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
result += toStdString ( clang_getTokenSpelling ( tu , tokens [ i ] ) ) ; 
#line 108 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
result += " " ; 
#line 109 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} 
#line 110 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_disposeTokens ( tu , tokens , numTokens ) ; 
#line 111 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return result ; 
#line 112 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} ;


#line 114 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str getAnnotate ( CXCursor cursor ) { 
#line 115 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str annotation = "" ; 
#line 116 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
clang_visitChildren ( cursor , [ ] ( CXCursor c , CXCursor , CXClientData data ) { 
#line 117 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
if ( clang_getCursorKind ( c ) == CXCursor_AnnotateAttr ) { 
#line 118 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
auto stri = toStdString ( clang_getCursorSpelling ( c ) ) ; 
#line 119 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
* static_cast < str * > ( data ) = stri ; 
#line 120 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return CXChildVisit_Break ; 
#line 121 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} 
#line 122 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return CXChildVisit_Continue ; 
#line 123 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} , & annotation ) ; 
#line 124 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return annotation ; 
#line 125 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} ;


#line 127 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) vec < str > getNamespaceChain ( CXCursor cursor ) { 
#line 128 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
vec < str > chain ; 
#line 129 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
CXCursor parent = clang_getCursorSemanticParent ( cursor ) ; 
#line 130 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
while ( ! clang_Cursor_isNull ( parent ) && clang_getCursorKind ( parent ) != CXCursor_TranslationUnit ) { 
#line 131 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
if ( clang_getCursorKind ( parent ) == CXCursor_Namespace ) { 
#line 132 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str ns = toStdString ( clang_getCursorSpelling ( parent ) ) ; 
#line 133 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
chain . push_back ( ns ) ; 
#line 134 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} 
#line 135 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
parent = clang_getCursorSemanticParent ( parent ) ; 
#line 136 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} 
#line 137 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
std :: reverse ( chain . begin ( ) , chain . end ( ) ) ; 
#line 138 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return chain ; 
#line 139 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} ;


#line 141 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str makeDeclaration ( const str & code ) { 
#line 142 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
str trimmed = code ; 
#line 143 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
trimmed . erase ( trimmed . find_last_not_of ( " \t\n\r" ) + 1 ) ; 
#line 144 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
size_t brace = trimmed . find ( '{' ) ; 
#line 145 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
if ( brace != str :: npos ) { 
#line 146 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
trimmed = trimmed . substr ( 0 , brace ) ; 
#line 147 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} 
#line 148 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
if ( trimmed . back ( ) != ';' ) { 
#line 149 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
trimmed += ";" ; 
#line 150 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} 
#line 151 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
return trimmed ; 
#line 152 "/home/wyatt/dev/cpp/pubprivattr/src/decl_utils.yapp"
} ;

#undef pub
#undef priv
