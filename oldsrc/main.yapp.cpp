#include "main.yapp.h"

#define pub
#define priv

// Emitted by yappc
// Emitting 8 declarations


#line 12 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: vector < std :: string > preprocStored ;


#line 13 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: vector < std :: string > usingStored ;


#line 15 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: string prePreprocess ( const std :: string & inputFile , const std :: string & outputDir , bool stdlib ) { 
#line 16 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: ifstream in ( inputFile ) ; 
#line 17 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! in ) { 
#line 18 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Failed to open input file for pre-preprocessing: " << inputFile << "\n" ; 
#line 19 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
exit ( 1 ) ; 
#line 20 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 21 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: ostringstream out ; 
#line 22 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string line ; 
#line 24 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( stdlib ) { 
#line 25 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocStored . push_back ( "include \"std.main.yapp.h\"\n#include \"std.str.yapp.h\"\n#include \"std.vec.yapp.h\"\n#include \"std.result.yapp.h\"\n" ) ; 
#line 26 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << "pub __attribute__((annotate(\"__pub_preproc__\"))) void __pub_preproc__0();" ; 
#line 27 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 30 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: regex pubPreproc ( R"(^\s*#pub\s+(.*?)$)" ) ; 
#line 31 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: regex importPreproc ( R"(^\s*#import\s+(.*?)$)" ) ; 
std::regex usingDefRegex(R"(^\s*#using\s+(.*?)$)");
#line 32 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
while ( std :: getline ( in , line ) ) { 
#line 33 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: smatch m ; 
#line 34 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( std :: regex_search ( line , m , pubPreproc ) ) { 
#line 35 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocStored . push_back ( m [ 1 ] . str ( ) ) ; 
#line 36 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << "pub __attribute__((annotate(\"__pub_preproc__\"))) void __pub_preproc__" << preprocStored . size ( ) - 1 << "();\n" ; 
#line 37 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( std :: regex_search ( line , m , importPreproc ) ) { 
#line 38 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string importedFile = m [ 1 ] . str ( ) ; 
#line 41 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool angledQuotes = ( importedFile [ 0 ] == '<' && importedFile [ importedFile . size ( ) - 1 ] == '>' ) ; 
#line 42 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool doubleQuotes = ( importedFile [ 0 ] == '"' && importedFile [ importedFile . size ( ) - 1 ] == '"' ) ; 
#line 43 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( angledQuotes || doubleQuotes ) { 
#line 45 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
importedFile = importedFile . substr ( 1 , importedFile . size ( ) - 2 ) ; 
#line 46 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 47 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( importedFile . find ( ".yapp" ) != std :: string :: npos ) { 
#line 48 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
importedFile = importedFile . substr ( 0 , importedFile . find_last_of ( '.' ) ) + ".yapp.h" ; 
#line 49 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 50 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( angledQuotes ) { 
#line 51 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
importedFile = "<" + importedFile + ">" ; 
#line 52 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( doubleQuotes ) { 
#line 53 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
importedFile = "\"" + importedFile + "\"" ; 
#line 54 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else { 
#line 55 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
importedFile = "\"" + importedFile + ".yapp.h\"" ; 
#line 56 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 58 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocStored . push_back ( "include " + importedFile ) ; 
#line 59 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << "pub __attribute__((annotate(\"__pub_preproc__\"))) void __pub_preproc__" << preprocStored . size ( ) - 1 << "();\n" ; 
#line 60 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
else if (std::regex_search(line, m, usingDefRegex)) {
            // We found a #using directive
            // We need to add it to the usingStored vector
            out << "pub __attribute__((annotate(\"__pub_using_alias__\"))) void __pub_using_alias__" << usingStored.size() << "();\n";

            usingStored.push_back(m[1].str());
        }
else { 
#line 61 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << line << "\n" ; 
#line 62 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 63 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 64 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string outFile = std :: filesystem :: path ( outputDir ) / ( inputFile . substr ( inputFile . find_last_of ( "/\\" ) + 1 ) + ".pp0" ) ; 
#line 65 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: ofstream p0f ( outFile ) ; 
#line 66 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! p0f ) { 
#line 67 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Failed to write pre-preprocessed file: " << outFile << "\n" ; 
#line 68 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
exit ( 1 ) ; 
#line 69 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 70 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
p0f << out . str ( ) ; 
#line 71 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
p0f . close ( ) ; 
#line 72 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return outFile ; 
#line 73 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} ;


#line 75 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: string preprocessStep2 ( const std :: string & p0File , const std :: string & outputDir ) { 
#line 76 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: ifstream in ( p0File ) ; 
#line 77 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! in ) { 
#line 78 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Failed to open pre-preprocessed file for second preprocessing: " << p0File << "\n" ; 
#line 79 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
exit ( 1 ) ; 
#line 80 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 81 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: ostringstream out ; 
#line 82 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string line ; 
#line 85 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: regex usingNamespaceFix ( R"((pub|priv)?\s*using\s+namespace\s+([a-zA-Z_][a-zA-Z0-9_:]*);)" ) ; 
#line 86 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: regex usingAliasFix ( R"((pub|priv)?\s*using\s+([a-zA-Z_][a-zA-Z0-9_:]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_:]*)\s*;)" ) ; 
#line 89 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
while ( std :: getline ( in , line ) ) { 
#line 90 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: smatch m ; 
#line 91 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( std :: regex_search ( line , m , usingNamespaceFix ) ) { 
#line 95 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string attr = m [ 1 ] . str ( ) ; 
#line 96 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string namespaceName = m [ 2 ] . str ( ) ; 
#line 99 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << "namespace " << namespaceName << " {};" ; 
#line 101 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( attr . empty ( ) ) { 
#line 102 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << "using namespace " << namespaceName << ";\n" ; 
#line 103 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else { 
#line 104 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << attr << " using namespace " << namespaceName << ";\n" ; 
#line 105 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 106 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( std :: regex_search ( line , m , usingAliasFix ) ) { 
#line 110 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << "pub __attribute__((annotate(\"__pub_using_alias__\"))) void __pub_using_alias__" << usingStored . size ( ) << "();\n" ; 
#line 112 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
usingStored . push_back ( m [ 0 ] . str ( ) ) ; 
#line 113 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else { 
#line 114 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
out << line << "\n" ; 
#line 115 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 116 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 117 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string outFile = std :: filesystem :: path ( outputDir ) / ( p0File . substr ( p0File . find_last_of ( "/\\" ) + 1 ) + ".pp1" ) ; 
#line 118 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: ofstream p1f ( outFile ) ; 
#line 119 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! p1f ) { 
#line 120 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Failed to write second preprocessed file: " << outFile << "\n" ; 
#line 121 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
exit ( 1 ) ; 
#line 122 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 123 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
p1f << out . str ( ) ; 
#line 124 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
p1f . close ( ) ; 
#line 125 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return outFile ; 
#line 126 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} ;
void postProcess(const std::string& headerFile) {
    // find something like this:
    // __attribute__ ( ( annotate ( "pub" ) ) ) __attribute__ ( ( annotate ( "__pub_using_alias__" ) ) ) void __pub_using_alias__0 ( ) ; 
    // and replace it with the string in usingStored at the given index
    std::ifstream in(headerFile);
    if (!in) {
        std::cerr << "Failed to open input header file for post-processing: " << headerFile << "\n";
        exit(1);
    }
    std::ostringstream out;
    std::string line;
    std::regex usingAliasRegex(R"(__attribute__\s*\(\s*\(\s*annotate\s*\(\s*"pub"\s*\)\s*\)\s*\)\s*__attribute__\s*\(\s*\(\s*annotate\s*\(\s*"__pub_using_alias__"\s*\)\s*\)\s*\)\s*void\s+__pub_using_alias__(\d+)\s*\(\s*\)\s*;)");
    while (std::getline(in, line)) {
        std::smatch m;
        if (std::regex_search(line, m, usingAliasRegex)) {
            // We found a using alias declaration
            // We need to replace it with the actual using alias from usingStored
            int index = std::stoi(m[1].str());
            if (index < 0 || index >= usingStored.size()) {
                std::cerr << "Error: Using alias index out of bounds: " << index << "\n";
                exit(1);
            }
            out << usingStored[index] << "\n"; // Replace with the actual using alias
        } else {
            out << line << "\n"; // Keep the line as is
        }
    }

    in.close();

    std::ofstream outFileStream(headerFile);
    if (!outFileStream) {
        std::cerr << "Failed to write post-processed header file: " << headerFile << "\n";
        exit(1);
    }
    outFileStream << out.str();
    outFileStream.close();
}

#line 128 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
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


#line 145 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string GLOBAL_SOURCE_FILE ;


#line 146 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string GLOBAL_INPUT_FILE ;


#line 148 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) int main ( int argc, char ** argv ) { 
#line 149 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"

#line 150 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( argc < 2 ) { 
#line 151 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Usage: ./yappc <source.yapp> [OPTIONS] -- [Preprocessor Args] -- [Compiler Args]\n" ; 
#line 152 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 153 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 155 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: vector < std :: string > preprocArgs ; 
#line 156 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: vector < std :: string > compileArgs ; 
#line 157 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: vector < std :: string > myArgs ; 
#line 158 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
int argState = 0 ; 
#line 159 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
for ( int i = 2 ; i < argc ; ++ i ) { 
#line 160 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( strcmp(argv [ i ], "--") == 0 ) { 
#line 161 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
argState ++ ; 
#line 162 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
continue ; 
#line 163 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 164 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( argState == 0 ) { 
#line 165 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
myArgs . push_back ( argv [ i ] ) ; 
#line 166 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( argState == 1 ) { 
#line 167 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocArgs . push_back ( argv [ i ] ) ; 
#line 168 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( argState == 2 ) { 
#line 169 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
compileArgs . push_back ( argv [ i ] ) ; 
#line 170 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 171 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 172 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"

#line 188 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool debugMode = false ; 
#line 189 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool sourceToggle = false ; 
#line 190 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool removeHeader = false ; 
#line 191 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool compileGenerated = false ; 
#line 192 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
bool useStdlib = true ; 
#line 193 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string outputDir = "" ; 
#line 194 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
for ( int i = 0 ; i < myArgs . size ( ) ; i ++ ) { 
#line 195 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string arg = myArgs [ i ] ; 
#line 196 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-s" ) { 
#line 197 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
sourceToggle = true ; 
#line 198 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 199 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-g" ) { 
#line 200 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
debugMode = true ; 
#line 201 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 202 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-h" ) { 
#line 203 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cout << usageString ; 
#line 204 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 0 ; 
#line 205 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 206 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-o" ) { 
#line 208 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( i + 1 >= myArgs . size ( ) ) { 
#line 210 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Error: -o option requires an argument.\n" ; 
#line 211 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 212 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else if ( myArgs [ i + 1 ] [ 0 ] == '-' ) { 
#line 214 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Error: -o option requires a directory argument.\n" ; 
#line 215 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 216 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} else { 
#line 217 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
outputDir = myArgs [ i + 1 ] ; 
#line 218 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
i ++ ; 
#line 219 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: filesystem :: path dirPath ( outputDir ) ; 
#line 220 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! std :: filesystem :: exists ( dirPath ) ) { 
#line 221 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Warning: Specified output directory does not exist. Creating: " << outputDir << "\n" ; 
#line 222 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: filesystem :: create_directories ( dirPath ) ; 
#line 223 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 224 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 225 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 226 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-r" ) { 
#line 228 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
removeHeader = true ; 
#line 229 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 230 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "-c" ) { 
#line 232 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
compileGenerated = true ; 
#line 233 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 234 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( arg == "--no-std" || arg == "--no-stdlib" ) { 
#line 236 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
useStdlib = false ; 
#line 237 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 238 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 240 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string base = argv [ 1 ] ; 
#line 241 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
size_t slash = base . find_last_of ( "/\\" ) ; 
#line 242 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
size_t dot = base . find_last_of ( '.' ) ; 
#line 243 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string filename = base . substr ( slash == std :: string :: npos ? 0 : slash + 1 , dot - ( slash == std :: string :: npos ? 0 : slash + 1 ) ) ; 
#line 244 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string dir = ( slash == std :: string :: npos ) ? "./" : base . substr ( 0 , slash + 1 ) ; 
#line 245 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( outputDir . empty ( ) ) { 
#line 246 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
outputDir = dir ; 
#line 247 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 251 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string step0File = prePreprocess ( argv [ 1 ] , outputDir , useStdlib ) ; 
#line 252 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string step1File = preprocessStep2 ( step0File , outputDir ) ; 
#line 254 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string preprocOutputFile = step1File ; 
#line 256 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocOutputFile = preprocOutputFile . substr ( 0 , preprocOutputFile . size ( ) - 2 ) + ".pp2" ; 
#line 257 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string preprocCommand = "clang -E " ; 
#line 258 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
for ( const auto & arg : preprocArgs ) { 
#line 259 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocCommand += "\"" + arg + "\" " ; 
#line 260 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 261 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocCommand += "\"-Dpub=__attribute__((annotate(\\\"pub\\\")))\" " ; 
#line 262 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocCommand += "\"-Dpriv=__attribute__((annotate(\\\"priv\\\")))\" " ; 
#line 263 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocCommand += "-D__yaplusplus " ; 
#line 264 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocCommand += "-x c++ \"" + step1File + "\" > \"" + preprocOutputFile + "\"" ; 
#line 265 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( system ( preprocCommand . c_str ( ) ) != 0 ) { 
#line 266 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Preprocessing failed.\n" ; 
#line 267 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 268 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 270 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: ifstream preprocFile ( preprocOutputFile ) ; 
#line 271 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! preprocFile ) { 
#line 272 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Failed to open preprocessed file: " << preprocOutputFile << "\n" ; 
#line 273 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 274 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 275 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string line ; 
#line 276 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: ostringstream cleanedOutput ; 
#line 277 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
while ( std :: getline ( preprocFile , line ) ) { 
#line 278 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( line . empty ( ) || line [ 0 ] != '#' ) { 
#line 279 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
cleanedOutput << line << "\n" ; 
#line 280 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 281 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 282 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
preprocFile . close ( ) ; 
#line 283 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: ofstream cleanedFile ( preprocOutputFile ) ; 
#line 284 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! cleanedFile ) { 
#line 285 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Failed to write cleaned preprocessed file: " << preprocOutputFile << "\n" ; 
#line 286 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 287 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 288 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
cleanedFile << cleanedOutput . str ( ) ; 
#line 289 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
cleanedFile . close ( ) ; 
#line 291 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
CXIndex index = clang_createIndex ( 0 , 0 ) ; 
#line 292 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
const char * args [ ] = { 
#line 293 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
"-x" , "c++-cpp-output" , 
#line 294 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
"-std=c++20" , 
#line 295 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
"-Dpub=__attribute__((annotate(\"pub\")))" , 
#line 296 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
"-Dpriv=__attribute__((annotate(\"priv\")))" , 
#line 297 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
"-P" 
#line 298 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} ; 
#line 300 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
GLOBAL_SOURCE_FILE = argv [ 1 ] ; 
#line 301 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
GLOBAL_INPUT_FILE = preprocOutputFile . c_str ( ) ; 
#line 303 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
CXTranslationUnit tu = clang_parseTranslationUnit ( 
#line 304 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
index , preprocOutputFile . c_str ( ) , args , sizeof ( args ) / sizeof ( args [ 0 ] ) , nullptr , 0 , CXTranslationUnit_Incomplete ) ; 
#line 305 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! tu ) { 
#line 306 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( unsigned numErrors = clang_getNumDiagnostics ( tu ) ) { 
#line 307 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
unsigned displayOptions = clang_defaultDiagnosticDisplayOptions ( ) ; 
#line 308 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
for ( unsigned i = 0 ; i < numErrors ; ++ i ) { 
#line 309 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
CXDiagnostic diag = clang_getDiagnostic ( tu , i ) ; 
#line 310 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
CXString str = clang_formatDiagnostic ( diag , displayOptions ) ; 
#line 311 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << clang_getCString ( str ) << "\n" ; 
#line 312 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
clang_disposeString ( str ) ; 
#line 313 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
clang_disposeDiagnostic ( diag ) ; 
#line 314 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 315 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 2 ; 
#line 316 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 317 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Failed to parse input file.\n" ; 
#line 318 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 319 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 321 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
CXCursor root = clang_getTranslationUnitCursor ( tu ) ; 
#line 322 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
clang_visitChildren ( root , visitor , & tu ) ; 
#line 324 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
writeFiles ( filename , outputDir ) ; 
#line 325 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
clang_disposeTranslationUnit ( tu ) ; 
#line 326 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
clang_disposeIndex ( index ) ; 
std::string headerFile = std::filesystem::path(outputDir) / (filename + ".yapp.h");
    postProcess(headerFile);
#line 327 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( compileGenerated ) { 
#line 328 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cout << "WARNING: Auto compiling generated files is not recommended. Use with caution." << std :: endl ; 
#line 329 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string outdirfilename = std :: filesystem :: path ( outputDir ) / ( filename + ".yapp.cpp" ) ; 
#line 330 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string compileCommand = "clang++ \"" + outdirfilename + "\" " ; 
#line 331 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
for ( const auto & arg : compileArgs ) { 
#line 332 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
compileCommand += "\"" + arg + "\" " ; 
#line 333 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 334 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( system ( compileCommand . c_str ( ) ) != 0 ) { 
#line 335 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: cerr << "Compilation failed.\n" ; 
#line 336 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 1 ; 
#line 337 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 338 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 340 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ! debugMode ) { 
#line 342 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: remove ( preprocOutputFile . c_str ( ) ) ; 
#line 343 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: remove ( step1File . c_str ( ) ) ; 
#line 344 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: remove ( step0File . c_str ( ) ) ; 
#line 346 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( ( ! compileGenerated && sourceToggle ) || ( compileGenerated && ! sourceToggle ) ) { 
#line 347 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: remove ( ( std :: filesystem :: path ( outputDir ) / ( filename + ".yapp.cpp" ) ) . c_str ( ) ) ; 
#line 348 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 350 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
if ( removeHeader ) { 
#line 351 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: remove ( ( std :: filesystem :: path ( outputDir ) / ( filename + ".yapp.h" ) ) . c_str ( ) ) ; 
#line 352 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 353 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} 
#line 355 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
return 0 ; 
#line 356 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
} ;

#undef pub
#undef priv
