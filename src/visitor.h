#pragma once
#include <clang-c/Index.h>
#include <vector>
#include <string>
#include <unordered_set>
#include "decl_utils.h"

extern std::vector<DeclInfo> decls;
extern int orderCounter;
extern std::unordered_set<std::string> typedefBackedTags;

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data);
