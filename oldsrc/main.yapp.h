#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 18 declarations


;

#include "file_writer.yapp.h"
;

#include "visitor.yapp.h"
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

extern 
#line 12 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: vector < std :: string > preprocStored;

extern 
#line 13 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: vector < std :: string > usingStored;


#line 15 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: string prePreprocess ( const std :: string & inputFile , const std :: string & outputDir , bool stdlib ) ;;


#line 75 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) std :: string preprocessStep2 ( const std :: string & p0File , const std :: string & outputDir ) ;;

extern 
#line 145 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string GLOBAL_SOURCE_FILE;

extern 
#line 146 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
std :: string GLOBAL_INPUT_FILE;


#line 148 "/home/wyatt/dev/cpp/pubprivattr/src/main.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) int main ( int argc, char ** argv ) ;;

#undef pub
#undef priv
