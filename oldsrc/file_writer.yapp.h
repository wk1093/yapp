#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 12 declarations


;

#include <clang-c/Index.h>
;

#include <cstring>
;

#include <filesystem>
;

#include <fstream>
;

#include <iostream>
;

#include <unordered_map>
;

#include <algorithm>
;

#include <string>
;

#include "visitor.yapp.h"
;

#include "decl_utils.yapp.h"
;


#line 293 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void writeFiles ( const std :: string & base , const std :: string & dir ) ;;

#undef pub
#undef priv
