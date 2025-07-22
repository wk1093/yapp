#include "file_writer.yapp.h"

#define pub
#define priv

// Emitted by yappc
// Emitting 10 declarations


#line 15 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) void emitWithNamespaces ( stream :: writer & out , const vec < DeclInfo > & decls ) { 
#line 16 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
out << "// Emitted by yappc\n" ; 
#line 17 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
out << "// Emitting " << decls . size ( ) << " declarations\n\n" ; 
#line 18 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
vec < str > currentNS ; 
#line 19 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
bool inExternC = false ; 
#line 20 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
for ( size_t idx = 0 ; idx < decls . size ( ) ; ++ idx ) { 
#line 21 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
const auto & d = decls [ idx ] ; 
#line 22 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
size_t common = 0 ; 
#line 23 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
while ( common < currentNS . size ( ) && common < d . namespaces . size ( ) && 
#line 24 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
currentNS [ common ] == d . namespaces [ common ] ) { 
#line 25 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
++ common ; 
#line 26 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 28 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( inExternC && ( currentNS . size ( ) != common || d . namespaces . size ( ) != common ) ) { 
#line 29 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
out << "#ifdef __cplusplus\n}\n#endif\n" ; 
#line 30 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
inExternC = false ; 
#line 31 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 33 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
for ( size_t i = currentNS . size ( ) ; i -- > common ; ) { 
#line 34 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
out << "}\n" ; 
#line 35 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 37 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
for ( size_t i = common ; i < d . namespaces . size ( ) ; ++ i ) { 
#line 38 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
out << "namespace " << d . namespaces [ i ] << " {\n" ; 
#line 39 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 40 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
currentNS = d . namespaces ; 
#line 42 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . isExternC && ! inExternC ) { 
#line 43 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
out << "#ifdef __cplusplus\nextern \"C\" {\n#endif\n" ; 
#line 44 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
inExternC = true ; 
#line 45 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 47 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
out << d . code << ";\n\n" ; 
#line 49 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
bool nextNeedsExtern = false ; 
#line 50 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
size_t nextCommon = common ; 
#line 51 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( idx + 1 < decls . size ( ) ) { 
#line 52 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
const auto & next = decls [ idx + 1 ] ; 
#line 53 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
nextCommon = 0 ; 
#line 54 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
while ( nextCommon < currentNS . size ( ) && nextCommon < next . namespaces . size ( ) && 
#line 55 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
currentNS [ nextCommon ] == next . namespaces [ nextCommon ] ) { 
#line 56 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
++ nextCommon ; 
#line 57 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 58 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
nextNeedsExtern = next . isExternC ; 
#line 59 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 60 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( inExternC && ( idx + 1 == decls . size ( ) || currentNS . size ( ) != nextCommon || ! nextNeedsExtern ) ) { 
#line 61 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
out << "#ifdef __cplusplus\n}\n#endif\n" ; 
#line 62 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
inExternC = false ; 
#line 63 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 64 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 66 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
for ( size_t i = currentNS . size ( ) ; i -- > 0 ; ) { 
#line 67 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
out << "}\n" ; 
#line 68 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 69 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} ;


#line 72 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) vec < DeclInfo > collectUniqueDecls ( ) { 
#line 73 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
vec < DeclInfo > seen ; 
#line 74 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
std :: unordered_map < str , size_t > usrToIndex ; 
#line 75 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
for ( auto & d : decls ) { 
#line 76 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . annotation . empty ( ) ) { 
#line 77 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
io :: println ( "Warning: Declaration without annotation for " , d . name ) ; 
#line 78 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
d . annotation = "priv" ; 
#line 79 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 80 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
auto it = usrToIndex . find ( d . usr ) ; 
#line 81 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( it == usrToIndex . end ( ) ) { 
#line 82 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
usrToIndex [ d . usr ] = seen . size ( ) ; 
#line 83 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
seen . push_back ( d ) ; 
#line 84 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} else { 
#line 85 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
auto & existing = seen [ it -> second ] ; 
#line 86 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( existing . annotation == "priv" && d . annotation == "pub" ) { 
#line 87 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
existing = d ; 
#line 88 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} else if ( ! existing . isDefinition && d . isDefinition ) { 
#line 90 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 91 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 92 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 93 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
std :: sort ( seen . begin ( ) , seen . end ( ) , [ ] ( const DeclInfo & a , const DeclInfo & b ) { 
#line 94 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return a . sourceOrderIndex < b . sourceOrderIndex ; 
#line 95 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} ) ; 
#line 96 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return seen ; 
#line 97 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} ;


#line 100 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) bool isGlobalVariable ( const DeclInfo & d ) { 
#line 102 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return ! d . isStatic && ! isAnonymousStruct ( d ) && 
#line 103 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
d . kind == CXCursor_VarDecl && 
#line 104 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
d . namespaces . empty ( ) ; 
#line 105 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} ;


#line 109 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"

#line 108 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
template < typename T > 
#line 109 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) bool isAnonymousTypeCursor ( T cursor ) { 
#line 110 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( ! clang_Cursor_isNull ( cursor ) ) { 
#line 111 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
CXString spelling = clang_getCursorSpelling ( cursor ) ; 
#line 112 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
bool anon = ! clang_getCString ( spelling ) || ! * clang_getCString ( spelling ) ; 
#line 113 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
clang_disposeString ( spelling ) ; 
#line 114 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
CXCursorKind kind = clang_getCursorKind ( cursor ) ; 
#line 115 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( anon && ( kind == CXCursor_StructDecl || kind == CXCursor_UnionDecl || kind == CXCursor_EnumDecl ) ) { 
#line 116 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return true ; 
#line 117 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 118 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 119 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return false ; 
#line 120 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} ;


#line 122 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) bool isAnonymousType ( const DeclInfo & d ) { 
#line 124 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . typeUsr . empty ( ) ) { 
#line 126 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return false ; 
#line 127 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 129 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( anonymousTypes . contains ( d . typeUsr ) ) { 
#line 130 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return true ; 
#line 131 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 132 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return false ; 
#line 133 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} ;


#line 135 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) extern vec < str > preprocStored ;


#line 136 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) extern vec < str > usingStored ;


#line 139 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) vec < DeclInfo > collectHeaderDecls ( const vec < DeclInfo > & seen ) { 
#line 140 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
vec < DeclInfo > pubDecls ; 
#line 141 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
for ( const auto & d : seen ) { 
#line 143 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . annotation == "pub" && d . name . find ( "__pub_preproc__" ) == 0 ) { 
#line 147 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
size_t index = str :: toul ( d . name . substr ( strlen ( "__pub_preproc__" ) ) ) ; 
#line 148 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( index >= preprocStored . size ( ) ) { 
#line 149 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
io :: println ( io :: err , "Warning: __pub_preproc__ index out of bounds: " , index ) ; 
#line 150 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
continue ; 
#line 151 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 152 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
DeclInfo copy = d ; 
#line 153 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
copy . code = "#" + preprocStored [ index ] + "\n" ; 
#line 154 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
pubDecls . push_back ( copy ) ; 
#line 155 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
continue ; 
#line 156 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 157 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . annotation == "pub" && d . name . find ( "__pub_using_alias__" ) == 0 ) { 
#line 160 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
size_t index = str :: toul ( d . name . substr ( strlen ( "__pub_using_alias__" ) ) ) ; 
#line 161 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( index >= usingStored . size ( ) ) { 
#line 162 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
io :: println ( io :: err , "Warning: __pub_using_alias__ index out of bounds: " , index ) ; 
#line 163 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
continue ; 
#line 164 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 165 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
DeclInfo copy = d ; 
#line 166 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
copy . code = usingStored [ index ] + "\n" ; 
#line 167 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
pubDecls . push_back ( copy ) ; 
#line 168 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
continue ; 
#line 169 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 170 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . isStatic && ! d . isUsingDec ) continue ; 
#line 171 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . annotation == "pub" ) { 
#line 172 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( isAnonymousStruct ( d ) ) { 
#line 173 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
continue ; 
#line 174 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 175 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( ( ( d . kind == CXCursor_StructDecl || 
#line 176 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
d . kind == CXCursor_UnionDecl || 
#line 177 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
d . kind == CXCursor_EnumDecl ) && 
#line 178 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
typedefBackedTags . count ( d . usr ) ) && ! d . isUsingDec ) 
#line 179 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
{ 
#line 180 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
continue ; 
#line 181 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 182 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
DeclInfo copy = d ; 
#line 184 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( ! d . isTemplate && ! d . isConstexpr && d . isDefinition && ! d . isInline && 
#line 185 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
( d . kind == CXCursor_FunctionDecl || d . kind == CXCursor_CXXMethod ) ) { 
#line 186 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
copy . code = makeDeclaration ( d . code ) ; 
#line 187 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 189 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( isGlobalVariable ( d ) && ! d . isUsingDec ) { 
#line 190 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( isAnonymousType ( d ) ) { 
#line 192 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
continue ; 
#line 193 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 195 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( ! d . isConstexpr && ! d . isExtern ) { 
#line 197 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
str code = d . code ; 
#line 198 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
size_t eq = code . find ( '=' ) ; 
#line 199 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( eq != str :: npos ) code = code . substr ( 0 , eq ) ; 
#line 201 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
code . erase ( 0 , code . find_first_not_of ( " \t\n\r" ) ) ; 
#line 202 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
code . erase ( code . find_last_not_of ( " \t\n\r" ) + 1 ) ; 
#line 203 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( ! code . empty ( ) && code . back ( ) == ';' ) code . pop_back ( ) ; 
#line 204 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
copy . code = "extern \n" + code ; 
#line 205 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 206 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 207 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
pubDecls . push_back ( copy ) ; 
#line 208 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 209 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 210 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
std :: sort ( pubDecls . begin ( ) , pubDecls . end ( ) , [ ] ( const DeclInfo & a , const DeclInfo & b ) { 
#line 211 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return a . sourceOrderIndex < b . sourceOrderIndex ; 
#line 212 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} ) ; 
#line 213 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return pubDecls ; 
#line 214 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} ;


#line 217 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) vec < DeclInfo > collectSourceDecls ( const vec < DeclInfo > & seen ) { 
#line 218 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
std :: unordered_map < str , bool > pubHasDefinition ; 
#line 219 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
for ( const auto & d : seen ) { 
#line 220 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . annotation == "pub" && d . isDefinition ) { 
#line 221 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
pubHasDefinition [ d . name ] = true ; 
#line 222 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 223 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 224 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
vec < DeclInfo > sourceDecls ; 
#line 225 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
for ( const auto & d : decls ) { 
#line 226 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . annotation . empty ( ) ) { 
#line 227 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
const_cast < DeclInfo & > ( d ) . annotation = "priv" ; 
#line 228 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 229 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . kind == CXCursor_TypedefDecl || d . kind == CXCursor_TypeAliasDecl || 
#line 230 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
d . kind == CXCursor_StructDecl || d . kind == CXCursor_EnumDecl || 
#line 231 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
d . kind == CXCursor_UnionDecl || d . kind == CXCursor_ClassDecl ) { 
#line 232 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
continue ; 
#line 233 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 236 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( isAnonymousStruct ( d ) ) continue ; 
#line 238 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( isGlobalVariable ( d ) && d . annotation == "priv" ) { 
#line 239 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
sourceDecls . push_back ( d ) ; 
#line 240 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
continue ; 
#line 241 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 242 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . annotation == "pub" ) { 
#line 243 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . isTemplate ) continue ; 
#line 244 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . isConstexpr ) continue ; 
#line 246 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( ! d . isDefinition && pubHasDefinition [ d . name ] ) continue ; 
#line 247 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . isInline ) continue ; 
#line 248 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( ! d . isDefinition ) continue ; 
#line 249 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . kind == CXCursor_FunctionDecl || d . kind == CXCursor_CXXMethod ) { 
#line 252 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
size_t start = d . code . find ( '(' , d . code . find ( d . name ) ) ; 
#line 253 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
int parenCount = 1 ; 
#line 254 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
size_t end = start + 1 ; 
#line 255 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
while ( end < d . code . size ( ) && parenCount > 0 ) { 
#line 256 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( d . code [ end ] == '(' ) { 
#line 257 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
++ parenCount ; 
#line 258 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} else if ( d . code [ end ] == ')' ) { 
#line 259 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
-- parenCount ; 
#line 260 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 261 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
++ end ; 
#line 262 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 263 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
str params = d . code . substr ( start + 1 , end - start - 2 ) ; 
#line 264 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( parenCount == 0 && ! params . empty ( ) && params . find ( '=' ) != str :: npos ) { 
#line 268 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
size_t pos = params . find ( '=' ) ; 
#line 269 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
while ( pos != str :: npos ) { 
#line 270 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
size_t nextComma = params . find ( ',' , pos ) ; 
#line 271 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
if ( nextComma == str :: npos ) { 
#line 272 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
params . erase ( pos ) ; 
#line 273 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
break ; 
#line 274 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} else { 
#line 275 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
params . erase ( pos , nextComma - pos + 1 ) ; 
#line 276 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 277 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
pos = params . find ( '=' , pos ) ; 
#line 278 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 280 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
str newCode = d . code . substr ( 0 , start + 1 ) + params + d . code . substr ( end - 1 ) ; 
#line 281 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
const_cast < DeclInfo & > ( d ) . code = newCode ; 
#line 282 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 283 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 284 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 286 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
sourceDecls . push_back ( d ) ; 
#line 287 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} 
#line 288 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
std :: sort ( sourceDecls . begin ( ) , sourceDecls . end ( ) , [ ] ( const DeclInfo & a , const DeclInfo & b ) { 
#line 289 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return a . sourceOrderIndex < b . sourceOrderIndex ; 
#line 290 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} ) ; 
#line 291 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
return sourceDecls ; 
#line 292 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} ;


#line 294 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void writeFiles ( const str & base , const str & dir ) { 
#line 295 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
file :: writer hfile ( std :: filesystem :: path ( dir . stdstr ( ) ) / ( base + ".yapp.h" ) ) ; 
#line 296 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
file :: writer cppfile ( std :: filesystem :: path ( dir . stdstr ( ) ) / ( base + ".yapp.cpp" ) ) ; 
#line 297 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
hfile << "#pragma once\n" ; 
#line 298 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
hfile << "#define pub\n#define priv\n\n" ; 
#line 299 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
cppfile << "#include \"" << base << ".yapp.h\"\n\n" ; 
#line 300 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
cppfile << "#define pub\n#define priv\n\n" ; 
#line 301 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
auto seen = collectUniqueDecls ( ) ; 
#line 302 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
auto pubDecls = collectHeaderDecls ( seen ) ; 
#line 303 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
emitWithNamespaces ( hfile , pubDecls ) ; 
#line 304 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
hfile << "#undef pub\n#undef priv\n" ; 
#line 305 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
auto sourceDecls = collectSourceDecls ( seen ) ; 
#line 306 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
emitWithNamespaces ( cppfile , sourceDecls ) ; 
#line 307 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
cppfile << "#undef pub\n#undef priv\n" ; 
#line 308 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
} ;

#undef pub
#undef priv
