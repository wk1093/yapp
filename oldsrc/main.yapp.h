#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 20 declarations

#include "std.main.yapp.h"
#include "std.str.yapp.h"
#include "std.vec.yapp.h"
#include "std.result.yapp.h"
#include "std.stream.yapp.h"

;

#include "std.io.yapp.h"
;

#include <filesystem>
;

#include <vector>
;

#include <string>
;

#include <iostream>
;

#include <fstream>
;

#include <sstream>
;

#include <cstring>
;

#include <regex>
;

#include "file_writer.yapp.h"
;

#include "visitor.yapp.h"
;

extern 
#line 15 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) vec < str > preprocStored;

extern 
#line 16 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) vec < str > usingStored;


#line 18 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str prePreprocess ( const str & inputFile , const str & outputDir , bool stdlib ) ;;


#line 86 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) str preprocessStep2 ( const str & p0File , const str & outputDir ) ;;


#line 139 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void postProcess ( const str & headerFile ) ;;

extern 
#line 192 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str GLOBAL_SOURCE_FILE;

extern 
#line 193 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
str GLOBAL_INPUT_FILE;


#line 195 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) int main ( vec < str > argv ) ;;

#undef pub
#undef priv
