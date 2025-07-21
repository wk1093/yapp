#include "decl_utils.yapp.h"

#define pub
#define priv

__attribute__ ( ( annotate ( "pub" ) ) ) bool isExternC ( CXCursor cursor ) { if ( clang_getCursorKind ( cursor ) != CXCursor_FunctionDecl ) return false ; if ( clang_getCursorLinkage ( cursor ) != CXLinkage_External ) return false ; CXCursor parent = clang_getCursorSemanticParent ( cursor ) ; if ( clang_getCursorKind ( parent ) == CXCursor_LinkageSpec ) { CXSourceRange range = clang_getCursorExtent ( parent ) ; CXTranslationUnit tu = clang_Cursor_getTranslationUnit ( parent ) ; CXToken * tokens = nullptr ; unsigned numTokens = 0 ; clang_tokenize ( tu , range , & tokens , & numTokens ) ; for ( unsigned i = 0 ; i < numTokens ; ++ i ) { CXString spelling = clang_getTokenSpelling ( tu , tokens [ i ] ) ; const char * token = clang_getCString ( spelling ) ; if ( strcmp ( token , "\"C\"" ) == 0 ) { clang_disposeString ( spelling ) ; clang_disposeTokens ( tu , tokens , numTokens ) ; return true ; } clang_disposeString ( spelling ) ; } clang_disposeTokens ( tu , tokens , numTokens ) ; } return false ; } ;

__attribute__ ( ( annotate ( "pub" ) ) ) bool isAnonymousStruct ( const DeclInfo & d ) { return ( d . kind == CXCursor_StructDecl ) && d . name . empty ( ) ; } ;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string toStdString ( CXString cxStr ) { std :: string str = clang_getCString ( cxStr ) ; clang_disposeString ( cxStr ) ; return str ; } ;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string createLineDirective ( CXSourceLocation loc ) { CXFile file ; unsigned line , column , offset ; clang_getFileLocation ( loc , & file , & line , & column , & offset ) ; CXString fileName = clang_getFileName ( file ) ; std :: string filePath = toStdString ( fileName ) ; clang_disposeString ( fileName ) ; if ( filePath == GLOBAL_INPUT_FILE ) { filePath = GLOBAL_SOURCE_FILE ; } std :: string lineDirective = "\n#line " + std :: to_string ( line ) + " \"" + filePath + "\"\n" ; return lineDirective ; } ;

__attribute__ ( ( annotate ( "pub" ) ) ) bool isDifferentDirective ( CXSourceLocation loc1 , CXSourceLocation loc2 ) { CXFile file1 , file2 ; unsigned line1 , line2 , column1 , column2 , offset1 , offset2 ; clang_getFileLocation ( loc1 , & file1 , & line1 , & column1 , & offset1 ) ; clang_getFileLocation ( loc2 , & file2 , & line2 , & column2 , & offset2 ) ; return ( file1 != file2 || line1 != line2 ) ; } ;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string getSourceText ( CXCursor cursor , CXTranslationUnit tu ) { CXSourceRange range = clang_getCursorExtent ( cursor ) ; CXToken * tokens = nullptr ; unsigned numTokens = 0 ; CXSourceLocation loc = clang_getCursorLocation ( cursor ) ; clang_tokenize ( tu , range , & tokens , & numTokens ) ; std :: string result = createLineDirective ( loc ) ; for ( unsigned i = 0 ; i < numTokens ; ++ i ) { CXSourceLocation tokenLoc = clang_getTokenLocation ( tu , tokens [ i ] ) ; if ( isDifferentDirective ( loc , tokenLoc ) ) { result += createLineDirective ( tokenLoc ) ; } loc = tokenLoc ; result += toStdString ( clang_getTokenSpelling ( tu , tokens [ i ] ) ) ; result += " " ; } clang_disposeTokens ( tu , tokens , numTokens ) ; return result ; } ;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string getAnnotate ( CXCursor cursor ) { std :: string annotation = "" ; clang_visitChildren ( cursor , [ ] ( CXCursor c , CXCursor , CXClientData data ) { if ( clang_getCursorKind ( c ) == CXCursor_AnnotateAttr ) { auto str = toStdString ( clang_getCursorSpelling ( c ) ) ; * static_cast < std :: string * > ( data ) = str ; return CXChildVisit_Break ; } return CXChildVisit_Continue ; } , & annotation ) ; return annotation ; } ;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: vector < std :: string > getNamespaceChain ( CXCursor cursor ) { std :: vector < std :: string > chain ; CXCursor parent = clang_getCursorSemanticParent ( cursor ) ; while ( ! clang_Cursor_isNull ( parent ) && clang_getCursorKind ( parent ) != CXCursor_TranslationUnit ) { if ( clang_getCursorKind ( parent ) == CXCursor_Namespace ) { std :: string ns = toStdString ( clang_getCursorSpelling ( parent ) ) ; chain . push_back ( ns ) ; } parent = clang_getCursorSemanticParent ( parent ) ; } std :: reverse ( chain . begin ( ) , chain . end ( ) ) ; return chain ; } ;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string makeDeclaration ( const std :: string & code ) { std :: string trimmed = code ; trimmed . erase ( trimmed . find_last_not_of ( " \t\n\r" ) + 1 ) ; size_t brace = trimmed . find ( '{' ) ; if ( brace != std :: string :: npos ) { trimmed = trimmed . substr ( 0 , brace ) ; } if ( trimmed . back ( ) != ';' ) { trimmed += ";" ; } return trimmed ; } ;

#undef pub
#undef priv
