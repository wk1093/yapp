#pragma once
#include <clang-c/Index.h>
#include <string>
#include <vector>

struct DeclInfo {
    std::string name;
    std::string usr;
    std::string code;
    std::string annotation;
    bool isDefinition = false;
    bool isInline = false;
    bool isExternC = false;
    bool isTemplate = false;
    bool isStatic = false;
    bool isExtern = false;
    CXCursorKind kind;
    int sourceOrderIndex = 0;
    std::vector<std::string> namespaces;
    std::string typeUsr;
};

bool isExternC(CXCursor cursor);
bool isAnonymousStruct(const DeclInfo& d);
std::string toStdString(CXString cxStr);
std::string getSourceText(CXCursor cursor, CXTranslationUnit tu);
std::string getAnnotate(CXCursor cursor);
std::vector<std::string> getNamespaceChain(CXCursor cursor);
std::string makeDeclaration(const std::string& code);
