#include "visitor.yapp.h"

#define pub
#define priv

// Emitted by yappc
// Emitting 10 declarations


#line 8 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) vec < DeclInfo > decls ;


#line 9 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) int orderCounter = 0 ;


#line 10 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: unordered_set < str > typedefBackedTags ;


#line 11 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) vec < str > anonymousTypes ;


#line 13 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) bool isTemplateType ( CXCursorKind kind ) { 
#line 14 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
return ( kind == CXCursor_ClassTemplate || 
#line 15 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
kind == CXCursor_ClassTemplatePartialSpecialization || 
#line 16 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
kind == CXCursor_TypeAliasTemplateDecl || 
#line 17 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
kind == CXCursor_FunctionTemplate ) ; 
#line 18 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} ;


#line 20 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) bool hasConstexprKeyword ( CXCursor cursor ) { 
#line 21 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXSourceRange range = clang_getCursorExtent ( cursor ) ; 
#line 22 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXTranslationUnit tu = clang_Cursor_getTranslationUnit ( cursor ) ; 
#line 23 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXToken * tokens = nullptr ; 
#line 24 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
unsigned numTokens = 0 ; 
#line 25 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_tokenize ( tu , range , & tokens , & numTokens ) ; 
#line 26 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
bool found = false ; 
#line 27 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
for ( unsigned i = 0 ; i < numTokens ; ++ i ) { 
#line 28 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXString spelling = clang_getTokenSpelling ( tu , tokens [ i ] ) ; 
#line 29 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
str tokenStr = clang_getCString ( spelling ) ; 
#line 30 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_disposeString ( spelling ) ; 
#line 32 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( tokenStr == "constexpr" ) { 
#line 33 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
found = true ; 
#line 34 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
break ; 
#line 35 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 36 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( tokenStr == "{" ) { 
#line 37 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
break ; 
#line 38 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 39 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( tokenStr == toStdString ( clang_getCursorSpelling ( cursor ) ) ) { 
#line 40 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
break ; 
#line 41 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 42 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 43 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_disposeTokens ( tu , tokens , numTokens ) ; 
#line 44 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
return found ; 
#line 45 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} ;


#line 47 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) bool hasTemplateKeyword ( CXCursor cursor ) { 
#line 48 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXSourceRange range = clang_getCursorExtent ( cursor ) ; 
#line 49 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXTranslationUnit tu = clang_Cursor_getTranslationUnit ( cursor ) ; 
#line 51 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXToken * tokens = nullptr ; 
#line 52 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
unsigned numTokens = 0 ; 
#line 53 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_tokenize ( tu , range , & tokens , & numTokens ) ; 
#line 55 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
bool found = false ; 
#line 56 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
for ( unsigned i = 0 ; i < numTokens ; ++ i ) { 
#line 57 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXString spelling = clang_getTokenSpelling ( tu , tokens [ i ] ) ; 
#line 58 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
str tokenStr = clang_getCString ( spelling ) ; 
#line 59 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_disposeString ( spelling ) ; 
#line 61 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( tokenStr == "template" ) { 
#line 62 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
found = true ; 
#line 63 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
break ; 
#line 64 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 65 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( tokenStr == "{" ) { 
#line 66 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
break ; 
#line 67 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 68 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( tokenStr == toStdString ( clang_getCursorSpelling ( cursor ) ) ) { 
#line 69 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
break ; 
#line 70 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 71 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 73 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_disposeTokens ( tu , tokens , numTokens ) ; 
#line 74 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
return found ; 
#line 75 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} ;


#line 77 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) bool hasConstKeyword ( CXCursor cursor ) { 
#line 78 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXSourceRange range = clang_getCursorExtent ( cursor ) ; 
#line 79 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXTranslationUnit tu = clang_Cursor_getTranslationUnit ( cursor ) ; 
#line 81 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXToken * tokens = nullptr ; 
#line 82 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
unsigned numTokens = 0 ; 
#line 83 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_tokenize ( tu , range , & tokens , & numTokens ) ; 
#line 85 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
bool found = false ; 
#line 86 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
for ( unsigned i = 0 ; i < numTokens ; ++ i ) { 
#line 87 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXString spelling = clang_getTokenSpelling ( tu , tokens [ i ] ) ; 
#line 88 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
str tokenStr = clang_getCString ( spelling ) ; 
#line 89 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_disposeString ( spelling ) ; 
#line 91 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( tokenStr == "const" ) { 
#line 92 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
found = true ; 
#line 93 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
break ; 
#line 94 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 95 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( tokenStr == "{" ) { 
#line 96 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
break ; 
#line 97 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 98 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( tokenStr == toStdString ( clang_getCursorSpelling ( cursor ) ) ) { 
#line 99 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
break ; 
#line 100 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 101 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 103 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_disposeTokens ( tu , tokens , numTokens ) ; 
#line 104 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
return found ; 
#line 105 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} ;


#line 107 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) bool isUsingDec ( CXCursor cursor ) { 
#line 108 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXCursorKind kind = clang_getCursorKind ( cursor ) ; 
#line 109 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
return ( kind == CXCursor_UsingDeclaration || kind == CXCursor_UsingDirective || kind == CXCursor_TypeAliasDecl ) ; 
#line 110 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} ;


#line 112 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) CXChildVisitResult visitor ( CXCursor cursor , CXCursor parent , CXClientData client_data ) { 
#line 113 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXCursorKind kind = clang_getCursorKind ( cursor ) ; 
#line 114 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
DeclInfo info ; 
#line 115 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . name = toStdString ( clang_getCursorSpelling ( cursor ) ) ; 
#line 116 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . usr = toStdString ( clang_getCursorUSR ( cursor ) ) ; 
#line 117 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( ! isUsingDec ( cursor ) ) { 
#line 118 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( ! clang_isDeclaration ( kind ) ) return CXChildVisit_Recurse ; 
#line 119 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( kind == CXCursor_LinkageSpec || kind == CXCursor_Namespace ) { 
#line 120 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
return CXChildVisit_Recurse ; 
#line 121 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 122 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 123 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
str annotation = getAnnotate ( cursor ) ; 
#line 124 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( isUsingDec ( cursor ) && annotation . empty ( ) ) { 
#line 125 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
annotation = "pub" ; 
#line 126 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 127 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( annotation . empty ( ) ) { 
#line 128 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( kind == CXCursor_TypedefDecl || kind == CXCursor_TypeAliasDecl || kind == CXCursor_StructDecl || CXCursor_UnionDecl || kind == CXCursor_ClassDecl ) { 
#line 129 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
annotation = "pub" ; 
#line 130 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 131 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
else if ( clang_isCursorDefinition ( cursor ) ) { 
#line 132 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
annotation = "priv" ; 
#line 133 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} else { 
#line 134 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
annotation = "pub" ; 
#line 135 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 136 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 137 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . annotation = annotation ; 
#line 138 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . isDefinition = clang_isCursorDefinition ( cursor ) ; 
#line 139 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . isInline = clang_Cursor_isFunctionInlined ( cursor ) ; 
#line 140 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . isExternC = isExternC ( cursor ) ; 
#line 141 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . isExtern = ( clang_getCursorLinkage ( cursor ) == CXLinkage_External ) && clang_Cursor_hasVarDeclExternalStorage ( cursor ) ; 
#line 142 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . kind = kind ; 
#line 143 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . namespaces = getNamespaceChain ( cursor ) ; 
#line 145 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . isStatic = ( clang_Cursor_getStorageClass ( cursor ) == CX_SC_Static ) ; 
#line 146 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . isConst = hasConstKeyword ( cursor ) ; 
#line 148 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . isTemplate = false ; 
#line 149 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . typeUsr = "" ; 
#line 150 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . isUsingDec = isUsingDec ( cursor ) ; 
#line 151 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
auto ct = clang_getCursorType ( cursor ) ; 
#line 152 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
auto typeDecl = clang_getTypeDeclaration ( ct ) ; 
#line 153 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( ! clang_Cursor_isNull ( typeDecl ) ) { 
#line 154 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . typeUsr = toStdString ( clang_getCursorUSR ( typeDecl ) ) ; 
#line 155 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 158 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( isTemplateType ( kind ) ) { 
#line 159 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . isTemplate = true ; 
#line 160 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 162 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( ! info . isTemplate ) { 
#line 163 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXCursor parent = clang_getCursorSemanticParent ( cursor ) ; 
#line 164 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXCursorKind pkind = clang_getCursorKind ( parent ) ; 
#line 165 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( isTemplateType ( pkind ) ) { 
#line 166 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . isTemplate = true ; 
#line 167 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 168 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 169 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( hasConstexprKeyword ( cursor ) ) { 
#line 170 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . isConstexpr = true ; 
#line 171 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 173 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( kind == CXCursor_StructDecl || kind == CXCursor_UnionDecl || kind == CXCursor_EnumDecl ) { 
#line 174 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
auto range = clang_Cursor_getSpellingNameRange ( cursor , 0 , 0 ) ; 
#line 175 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXTranslationUnit tu = * ( CXTranslationUnit * ) client_data ; 
#line 176 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXToken * tokens = nullptr ; 
#line 177 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
unsigned numTokens = 0 ; 
#line 178 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_tokenize ( tu , range , & tokens , & numTokens ) ; 
#line 179 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
for ( unsigned i = 0 ; i < numTokens ; ++ i ) { 
#line 180 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXString spelling = clang_getTokenSpelling ( tu , tokens [ i ] ) ; 
#line 181 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( clang_getTokenKind ( tokens [ i ] ) == CXToken_Keyword && 
#line 182 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
( strcmp ( clang_getCString ( spelling ) , "struct" ) == 0 ) ) { 
#line 183 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . name = "" ; 
#line 184 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
anonymousTypes . push_back ( info . usr ) ; 
#line 185 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 186 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( clang_getTokenKind ( tokens [ i ] ) == CXToken_Keyword && 
#line 187 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
( strcmp ( clang_getCString ( spelling ) , "union" ) == 0 ) ) { 
#line 188 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . name = "" ; 
#line 189 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
anonymousTypes . push_back ( info . usr ) ; 
#line 190 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 191 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( clang_getTokenKind ( tokens [ i ] ) == CXToken_Keyword && 
#line 192 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
( strcmp ( clang_getCString ( spelling ) , "enum" ) == 0 ) ) { 
#line 193 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . name = "" ; 
#line 194 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
anonymousTypes . push_back ( info . usr ) ; 
#line 195 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 196 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_disposeString ( spelling ) ; 
#line 197 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 198 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_disposeTokens ( tu , tokens , numTokens ) ; 
#line 199 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 200 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
CXTranslationUnit tu = * ( CXTranslationUnit * ) client_data ; 
#line 201 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . code = getSourceText ( cursor , tu ) ; 
#line 202 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . sourceOrderIndex = orderCounter ++ ; 
#line 203 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( clang_getCursorKind ( cursor ) == CXCursor_TypedefDecl ) { 
#line 204 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
clang_visitChildren ( cursor , [ ] ( CXCursor c , CXCursor , CXClientData client_data ) { 
#line 205 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
auto kind = clang_getCursorKind ( c ) ; 
#line 206 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( kind == CXCursor_StructDecl || kind == CXCursor_UnionDecl || kind == CXCursor_EnumDecl ) { 
#line 207 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
str structName = toStdString ( clang_getCursorUSR ( c ) ) ; 
#line 208 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( ! structName . empty ( ) ) { 
#line 209 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
static_cast < std :: unordered_set < str > * > ( client_data ) -> insert ( structName ) ; 
#line 210 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 211 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 212 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
return CXChildVisit_Continue ; 
#line 213 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} , & typedefBackedTags ) ; 
#line 214 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 215 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
if ( info . isTemplate && info . annotation == "" ) { 
#line 216 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
info . annotation = "pub" ; 
#line 217 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} 
#line 218 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
decls . push_back ( info ) ; 
#line 220 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
return CXChildVisit_Continue ; 
#line 221 "/home/wyatt/dev/cpp/pubprivattr/src/visitor.yapp"
} ;

#undef pub
#undef priv
