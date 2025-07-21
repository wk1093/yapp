#pragma once
#define pub
#define priv

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

extern __attribute__ ( ( annotate ( "pub" ) ) ) std :: vector < std :: string > preprocStored;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string prePreprocess ( const std :: string & inputFile , const std :: string & outputDir , bool stdlib ) ;;

__attribute__ ( ( annotate ( "pub" ) ) ) std :: string preprocessStep2 ( const std :: string & p0File , const std :: string & outputDir ) ;;

extern std :: string GLOBAL_SOURCE_FILE;

extern std :: string GLOBAL_INPUT_FILE;

__attribute__ ( ( annotate ( "pub" ) ) ) int main ( int argc , char * * argv ) ;;

#undef pub
#undef priv
