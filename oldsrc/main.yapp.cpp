#include "main.yapp.h"

#define pub
#define priv

// Emitted by yappc
// Emitting 9 declarations


#line 15 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) vec < str > preprocStored ;


#line 16 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) vec < str > usingStored ;


#line 18 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str prePreprocess ( const str & inputFile , const str & outputDir , bool stdlib ) { 
#line 19 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
file :: reader in ( inputFile ) ; 
#line 20 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! in ) { 
#line 21 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Failed to open input file for pre-preprocessing: " , inputFile ) ; 
#line 22 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
exit ( 1 ) ; 
#line 23 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 24 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str :: writer out ; 
#line 25 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str line ; 
#line 27 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( stdlib ) { 
#line 28 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocStored . push_back ( "include \"std.main.yapp.h\"\n#include \"std.str.yapp.h\"\n#include \"std.vec.yapp.h\"\n#include \"std.result.yapp.h\"\n#include \"std.stream.yapp.h\"\n" ) ; 
#line 29 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << "pub __attribute__((annotate(\"__pub_preproc__\"))) void __pub_preproc__0();" ; 
#line 30 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 33 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: regex pubPreproc ( R"(^\s*#pub\s+(.*?)$)" ) ; 
#line 34 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: regex importPreproc ( R"(^\s*#import\s+(.*?)$)" ) ; 
#line 35 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: regex usingDefRegex ( R"(^\s*#using\s+(.*?)$)" ) ; 
#line 36 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
while ( std :: getline ( in , line ) ) { 
#line 37 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: smatch m ; 
#line 38 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( std :: regex_search ( line , m , pubPreproc ) ) { 
#line 39 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocStored . push_back ( m [ 1 ] . str ( ) ) ; 
#line 40 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << "pub __attribute__((annotate(\"__pub_preproc__\"))) void __pub_preproc__" << preprocStored . size ( ) - 1 << "();\n" ; 
#line 41 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( std :: regex_search ( line , m , importPreproc ) ) { 
#line 42 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str importedFile = m [ 1 ] . str ( ) ; 
#line 45 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool angledQuotes = ( importedFile [ 0 ] == '<' && importedFile [ importedFile . size ( ) - 1 ] == '>' ) ; 
#line 46 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool doubleQuotes = ( importedFile [ 0 ] == '"' && importedFile [ importedFile . size ( ) - 1 ] == '"' ) ; 
#line 47 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( angledQuotes || doubleQuotes ) { 
#line 49 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
importedFile = importedFile . substr ( 1 , importedFile . size ( ) - 2 ) ; 
#line 50 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 51 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( importedFile . find ( ".yapp" ) != str :: npos ) { 
#line 52 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
importedFile = importedFile . substr ( 0 , importedFile . find_last_of ( '.' ) ) + ".yapp.h" ; 
#line 53 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 54 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( angledQuotes ) { 
#line 55 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
importedFile = "<" + importedFile + ">" ; 
#line 56 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( doubleQuotes ) { 
#line 57 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
importedFile = "\"" + importedFile + "\"" ; 
#line 58 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else { 
#line 59 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
importedFile = "\"" + importedFile + ".yapp.h\"" ; 
#line 60 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 62 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocStored . push_back ( "include " + importedFile ) ; 
#line 63 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << "pub __attribute__((annotate(\"__pub_preproc__\"))) void __pub_preproc__" << preprocStored . size ( ) - 1 << "();\n" ; 
#line 64 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( std :: regex_search ( line , m , usingDefRegex ) ) { 
#line 67 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << "pub __attribute__((annotate(\"__pub_using_alias__\"))) void __pub_using_alias__" << usingStored . size ( ) << "();\n" ; 
#line 69 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
usingStored . push_back ( m [ 1 ] . str ( ) ) ; 
#line 70 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else { 
#line 71 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << line << "\n" ; 
#line 72 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 73 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 74 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str outFile = std :: filesystem :: path ( outputDir . stdstr ( ) ) / ( inputFile . substr ( inputFile . find_last_of ( "/\\" ) + 1 ) + ".pp0" ) ; 
#line 75 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
file :: writer p0f ( outFile ) ; 
#line 76 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! p0f ) { 
#line 77 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Failed to write pre-preprocessed file: " , outFile ) ; 
#line 78 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
exit ( 1 ) ; 
#line 79 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 80 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
p0f << out . str ( ) ; 
#line 81 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
p0f . close ( ) ; 
#line 82 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return outFile ; 
#line 83 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} ;


#line 85 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str preprocessStep2 ( const str & p0File , const str & outputDir ) { 
#line 90 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: regex usingNamespaceFix ( R"((pub|priv)?\s*using\s+namespace\s+([a-zA-Z_][a-zA-Z0-9_:]*);)" ) ; 
#line 91 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: regex usingAliasFix ( R"((template\s*\<.*?\>\s*)?(pub|priv)?\s*using\s+([a-zA-Z_][a-zA-Z0-9_:<>, ]*)\s*(=\s*([a-zA-Z_][a-zA-Z0-9_:<>, ]*)\s*)?;)" ) ; 
#line 92 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str content = io :: fileReadText ( p0File ) . unwrap ( ) ; 
#line 94 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: smatch m ; 
#line 95 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string result ; 
#line 96 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string :: const_iterator searchStart = content . cbegin ( ) ; 
#line 98 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
while ( std :: regex_search ( searchStart , content . cend ( ) , m , usingNamespaceFix ) ) { 
#line 100 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
result . append ( searchStart , m [ 0 ] . first ) ; 
#line 102 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string attr = m [ 1 ] . str ( ) ; 
#line 103 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string namespaceName = m [ 2 ] . str ( ) ; 
#line 106 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( attr . empty ( ) ) { 
#line 107 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
result += "\nnamespace " + namespaceName + " {};using namespace " + namespaceName + ";\n" ; 
#line 108 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else { 
#line 109 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
result += "\nnamespace " + namespaceName + " {};" + attr + " using namespace " + namespaceName + ";\n" ; 
#line 110 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 113 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
searchStart = m [ 0 ] . second ; 
#line 114 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 117 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
result . append ( searchStart , content . cend ( ) ) ; 
#line 118 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
content = std :: move ( result ) ; 
#line 121 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
while ( std :: regex_search ( content , m , usingAliasFix ) ) { 
#line 125 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
usingStored . push_back ( m [ 0 ] . str ( ) ) ; 
#line 126 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
content = std :: regex_replace ( content , usingAliasFix , "\npub __attribute__((annotate(\"__pub_using_alias__\"))) void __pub_using_alias__" + std :: to_string ( usingStored . size ( ) - 1 ) + "();\n" , std :: regex_constants :: format_first_only ) ; 
#line 127 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 128 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str outFile = std :: filesystem :: path ( outputDir . stdstr ( ) ) / ( p0File . substr ( p0File . find_last_of ( "/\\" ) + 1 ) + ".pp1" ) ; 
#line 129 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
file :: writer p1f ( outFile ) ; 
#line 130 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! p1f ) { 
#line 131 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Failed to write second preprocessed file: " , outFile ) ; 
#line 132 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
exit ( 1 ) ; 
#line 133 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 134 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
p1f << content ; 
#line 135 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
p1f . close ( ) ; 
#line 136 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return outFile ; 
#line 137 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} ;


#line 139 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void postProcess ( const str & headerFile ) { 
#line 140 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
file :: reader in ( headerFile ) ; 
#line 141 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! in ) { 
#line 142 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Failed to open input header file for post-processing: " , headerFile ) ; 
#line 143 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
exit ( 1 ) ; 
#line 144 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 145 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str :: writer out ; 
#line 146 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str line ; 
#line 147 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: regex usingAliasRegex ( R"(__attribute__\s*\(\s*\(\s*annotate\s*\(\s*"pub"\s*\)\s*\)\s*\)\s*__attribute__\s*\(\s*\(\s*annotate\s*\(\s*"__pub_using_alias__"\s*\)\s*\)\s*\)\s*void\s+__pub_using_alias__(\d+)\s*\(\s*\)\s*;)" ) ; 
#line 148 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
while ( std :: getline ( in , line ) ) { 
#line 149 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: smatch m ; 
#line 150 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( std :: regex_search ( line , m , usingAliasRegex ) ) { 
#line 153 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
int index = str :: toInt ( m [ 1 ] . str ( ) ) ; 
#line 154 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( index < 0 || index >= usingStored . size ( ) ) { 
#line 155 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Error: Using alias index out of bounds: " , index ) ; 
#line 156 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
exit ( 1 ) ; 
#line 157 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 158 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << usingStored [ index ] << "\n" ; 
#line 159 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else { 
#line 160 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << line << "\n" ; 
#line 161 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 162 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 164 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
in . close ( ) ; 
#line 166 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
file :: writer outFileStream ( headerFile ) ; 
#line 167 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! outFileStream ) { 
#line 168 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Failed to write post-processed header file: " , headerFile ) ; 
#line 169 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
exit ( 1 ) ; 
#line 170 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 171 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
outFileStream << out . str ( ) ; 
#line 172 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
outFileStream . close ( ) ; 
#line 173 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} ;


#line 175 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "priv" ) ) ) const char * usageString = R"(
Usage: yappc <source.yapp> [OPTIONS] -- [Preprocessor Args] -- [Compiler Args]
Options:
    -s          Toggle whether the source file is left in the output. This is useful for debugging.
    -g          Show generated intermediate preprocessing files.
    -h          Show this help message
    -o <output> Specify output folder for generated files (default: same as input file)
    -r          Remove the header from the generated .yapp.cpp file (not very useful)
    -c          Compile the generated files.
    --          Separator for different argument sections
Preprocessor Args:
    These arguments are passed directly to the preprocessor (clang -E).
    You can use -D to define macros, e.g., -DDEBUG=1.
Compiler Args:
    These arguments are passed directly to the compiler (clang++).
    You can use -o to specify the output file.
)" ;


#line 192 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str GLOBAL_SOURCE_FILE ;


#line 193 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str GLOBAL_INPUT_FILE ;


#line 195 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) int main ( vec < str > argv ) { 
#line 196 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
int argc = argv . size ( ) ; 
#line 197 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( argc < 2 ) { 
#line 198 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Usage: ./yappc <source.yapp> [OPTIONS] -- [Preprocessor Args] -- [Compiler Args]" ) ; 
#line 199 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 200 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 202 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
vec < str > preprocArgs ; 
#line 203 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
vec < str > compileArgs ; 
#line 204 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
vec < str > myArgs ; 
#line 206 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
int argState = 0 ; 
#line 207 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
for ( int i = 2 ; i < argc ; ++ i ) { 
#line 208 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( argv [ i ] == "--" ) { 
#line 209 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
argState ++ ; 
#line 210 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
continue ; 
#line 211 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 212 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( argState == 0 ) { 
#line 213 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
myArgs . push_back ( argv [ i ] ) ; 
#line 214 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( argState == 1 ) { 
#line 215 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocArgs . push_back ( argv [ i ] ) ; 
#line 216 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( argState == 2 ) { 
#line 217 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
compileArgs . push_back ( argv [ i ] ) ; 
#line 218 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 219 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 221 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool debugMode = false ; 
#line 222 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool sourceToggle = false ; 
#line 223 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool removeHeader = false ; 
#line 224 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool compileGenerated = false ; 
#line 225 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool useStdlib = true ; 
#line 226 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str outputDir = "" ; 
#line 227 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
for ( int i = 0 ; i < myArgs . size ( ) ; i ++ ) { 
#line 228 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str arg = myArgs [ i ] ; 
#line 229 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-s" ) { 
#line 230 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
sourceToggle = true ; 
#line 231 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 232 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-g" ) { 
#line 233 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
debugMode = true ; 
#line 234 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 235 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-h" ) { 
#line 236 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: print ( usageString ) ; 
#line 237 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 0 ; 
#line 238 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 239 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-o" ) { 
#line 241 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( i + 1 >= myArgs . size ( ) ) { 
#line 243 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Error: -o option requires a directory argument." ) ; 
#line 244 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 245 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( myArgs [ i + 1 ] [ 0 ] == '-' ) { 
#line 247 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Error: -o option requires a directory argument." ) ; 
#line 248 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 249 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else { 
#line 250 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
outputDir = myArgs [ i + 1 ] ; 
#line 251 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
i ++ ; 
#line 252 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: filesystem :: path dirPath ( outputDir . stdstr ( ) ) ; 
#line 253 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! std :: filesystem :: exists ( dirPath ) ) { 
#line 254 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Warning: Specified output directory does not exist. Creating: " , outputDir ) ; 
#line 255 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: filesystem :: create_directories ( dirPath ) ; 
#line 256 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 257 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 258 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 259 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-r" ) { 
#line 261 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
removeHeader = true ; 
#line 262 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 263 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-c" ) { 
#line 265 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
compileGenerated = true ; 
#line 266 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 267 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "--no-std" || arg == "--no-stdlib" ) { 
#line 269 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
useStdlib = false ; 
#line 270 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 271 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 273 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str base = argv [ 1 ] ; 
#line 274 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
size_t slash = base . find_last_of ( "/\\" ) ; 
#line 275 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
size_t dot = base . find_last_of ( '.' ) ; 
#line 276 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str filename = base . substr ( slash == str :: npos ? 0 : slash + 1 , dot - ( slash == str :: npos ? 0 : slash + 1 ) ) ; 
#line 277 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str dir = ( slash == str :: npos ) ? "./" : base . substr ( 0 , slash + 1 ) ; 
#line 278 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( outputDir . empty ( ) ) { 
#line 279 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
outputDir = dir ; 
#line 280 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 284 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str step0File = prePreprocess ( argv [ 1 ] , outputDir , useStdlib ) ; 
#line 285 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str step1File = preprocessStep2 ( step0File , outputDir ) ; 
#line 287 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str preprocOutputFile = step1File ; 
#line 289 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocOutputFile = preprocOutputFile . substr ( 0 , preprocOutputFile . size ( ) - 2 ) + ".pp2" ; 
#line 290 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str preprocCommand = "clang -E " ; 
#line 291 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
for ( const auto & arg : preprocArgs ) { 
#line 292 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocCommand += "\"" + arg + "\" " ; 
#line 293 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 294 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocCommand += "\"-Dpub=__attribute__((annotate(\\\"pub\\\")))\" " ; 
#line 295 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocCommand += "\"-Dpriv=__attribute__((annotate(\\\"priv\\\")))\" " ; 
#line 296 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocCommand += "-D__yaplusplus " ; 
#line 297 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocCommand += "-x c++ \"" + step1File + "\" > \"" + preprocOutputFile + "\"" ; 
#line 298 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( system ( preprocCommand . c_str ( ) ) != 0 ) { 
#line 299 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Preprocessing failed. Check the preprocessor arguments and input file." ) ; 
#line 300 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 301 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 303 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
file :: reader preprocFile ( preprocOutputFile ) ; 
#line 304 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! preprocFile ) { 
#line 305 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Failed to open preprocessed file: " , preprocOutputFile ) ; 
#line 306 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 307 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 308 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str line ; 
#line 309 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str :: writer cleanedOutput ; 
#line 310 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
while ( std :: getline ( preprocFile , line ) ) { 
#line 311 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( line . empty ( ) || line [ 0 ] != '#' ) { 
#line 312 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
cleanedOutput << line << "\n" ; 
#line 313 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 314 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 315 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocFile . close ( ) ; 
#line 316 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
file :: writer cleanedFile ( preprocOutputFile ) ; 
#line 317 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! cleanedFile ) { 
#line 318 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Failed to write cleaned preprocessed file: " , preprocOutputFile ) ; 
#line 319 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 320 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 321 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
cleanedFile << cleanedOutput . str ( ) ; 
#line 322 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
cleanedFile . close ( ) ; 
#line 324 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
CXIndex index = clang_createIndex ( 0 , 0 ) ; 
#line 325 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
const char * args [ ] = { 
#line 326 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
"-x" , "c++-cpp-output" , 
#line 327 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
"-std=c++20" , 
#line 328 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
"-Dpub=__attribute__((annotate(\"pub\")))" , 
#line 329 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
"-Dpriv=__attribute__((annotate(\"priv\")))" , 
#line 330 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
"-P" 
#line 331 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} ; 
#line 333 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
GLOBAL_SOURCE_FILE = argv [ 1 ] ; 
#line 334 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
GLOBAL_INPUT_FILE = preprocOutputFile . c_str ( ) ; 
#line 336 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
CXTranslationUnit tu = clang_parseTranslationUnit ( 
#line 337 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
index , preprocOutputFile . c_str ( ) , args , sizeof ( args ) / sizeof ( args [ 0 ] ) , nullptr , 0 , CXTranslationUnit_Incomplete ) ; 
#line 338 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! tu ) { 
#line 339 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( unsigned numErrors = clang_getNumDiagnostics ( tu ) ) { 
#line 340 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
unsigned displayOptions = clang_defaultDiagnosticDisplayOptions ( ) ; 
#line 341 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
for ( unsigned i = 0 ; i < numErrors ; ++ i ) { 
#line 342 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
CXDiagnostic diag = clang_getDiagnostic ( tu , i ) ; 
#line 343 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
CXString str = clang_formatDiagnostic ( diag , displayOptions ) ; 
#line 344 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , clang_getCString ( str ) ) ; 
#line 345 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
clang_disposeString ( str ) ; 
#line 346 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
clang_disposeDiagnostic ( diag ) ; 
#line 347 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 348 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 2 ; 
#line 349 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 350 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Failed to parse input file: " , preprocOutputFile ) ; 
#line 351 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 352 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 354 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
CXCursor root = clang_getTranslationUnitCursor ( tu ) ; 
#line 355 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
clang_visitChildren ( root , visitor , & tu ) ; 
#line 357 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
writeFiles ( filename , outputDir ) ; 
#line 358 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
clang_disposeTranslationUnit ( tu ) ; 
#line 359 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
clang_disposeIndex ( index ) ; 
#line 362 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str headerFile = std :: filesystem :: path ( outputDir . stdstr ( ) ) / ( filename + ".yapp.h" ) ; 
#line 363 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
postProcess ( headerFile ) ; 
#line 365 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( compileGenerated ) { 
#line 366 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( "WARNING: Auto compiling generated files is not recommended. Use with caution." ) ; 
#line 367 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str outdirfilename = std :: filesystem :: path ( outputDir . stdstr ( ) ) / ( filename + ".yapp.cpp" ) ; 
#line 368 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str compileCommand = "clang++ \"" + outdirfilename + "\" " ; 
#line 369 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
for ( const auto & arg : compileArgs ) { 
#line 370 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
compileCommand += "\"" + arg + "\" " ; 
#line 371 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 372 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( system ( compileCommand . c_str ( ) ) != 0 ) { 
#line 373 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
io :: println ( io :: err , "Compilation failed." ) ; 
#line 374 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 375 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 376 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 378 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! debugMode ) { 
#line 380 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: remove ( preprocOutputFile . c_str ( ) ) ; 
#line 381 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: remove ( step1File . c_str ( ) ) ; 
#line 382 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: remove ( step0File . c_str ( ) ) ; 
#line 384 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ( ! compileGenerated && sourceToggle ) || ( compileGenerated && ! sourceToggle ) ) { 
#line 385 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: remove ( ( std :: filesystem :: path ( outputDir . stdstr ( ) ) / ( filename + ".yapp.cpp" ) ) . c_str ( ) ) ; 
#line 386 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 388 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( removeHeader ) { 
#line 389 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: remove ( ( std :: filesystem :: path ( outputDir . stdstr ( ) ) / ( filename + ".yapp.h" ) ) . c_str ( ) ) ; 
#line 390 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 391 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 393 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 0 ; 
#line 394 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} ;

#undef pub
#undef priv
