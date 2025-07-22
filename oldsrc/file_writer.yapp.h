#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 13 declarations

#include "std.main.yapp.h"
#include "std.str.yapp.h"
#include "std.vec.yapp.h"
#include "std.result.yapp.h"
#include "std.stream.yapp.h"

;

#include "std.io.yapp.h"
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


#line 294 "/home/wyatt/dev/cpp/pubprivattr/src/file_writer.yapp"
__attribute__ ( ( annotate ( "pub" ) ) ) void writeFiles ( const str & base , const str & dir ) ;;

#undef pub
#undef priv
