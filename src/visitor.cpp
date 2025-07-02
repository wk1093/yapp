#include "visitor.h"
#include "decl_utils.h"
#include <cstring>
#include <clang-c/Index.h>
#include <string>
#include <vector>
#include <unordered_set>

std::vector<DeclInfo> decls;
int orderCounter = 0;
std::unordered_set<std::string> typedefBackedTags;

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data) {
    CXCursorKind kind = clang_getCursorKind(cursor);
    if (!clang_isDeclaration(kind)) return CXChildVisit_Recurse;
    if (kind == CXCursor_LinkageSpec || kind == CXCursor_Namespace) {
        return CXChildVisit_Recurse;
    }
    std::string annotation = getAnnotate(cursor);
    if (annotation.empty()) {
        if (kind == CXCursor_TypedefDecl || kind == CXCursor_TypeAliasDecl || kind == CXCursor_StructDecl || CXCursor_UnionDecl || kind == CXCursor_ClassDecl) {
            annotation = "pub";
        }
        else if (clang_isCursorDefinition(cursor)) {
            annotation = "priv";
        } else {
            annotation = "pub";
        }
    }
    DeclInfo info;
    info.name = toStdString(clang_getCursorSpelling(cursor));
    info.usr = toStdString(clang_getCursorUSR(cursor));
    info.annotation = annotation;
    info.isDefinition = clang_isCursorDefinition(cursor);
    info.isInline = clang_Cursor_isFunctionInlined(cursor);
    info.isExternC = isExternC(cursor);
    info.kind = kind;
    info.namespaces = getNamespaceChain(cursor);
    if (kind == CXCursor_StructDecl || kind == CXCursor_UnionDecl || kind == CXCursor_EnumDecl) {
        auto range = clang_Cursor_getSpellingNameRange(cursor, 0, 0);
        CXTranslationUnit tu = *(CXTranslationUnit*)client_data;
        CXToken* tokens = nullptr;
        unsigned numTokens = 0;
        clang_tokenize(tu, range, &tokens, &numTokens);
        for (unsigned i = 0; i < numTokens; ++i) {
            CXString spelling = clang_getTokenSpelling(tu, tokens[i]);
            if (clang_getTokenKind(tokens[i]) == CXToken_Keyword &&
                (strcmp(clang_getCString(spelling), "struct") == 0)) {
                info.name = "";
            }
            if (clang_getTokenKind(tokens[i]) == CXToken_Keyword &&
                (strcmp(clang_getCString(spelling), "union") == 0)) {
                info.name = "";
            }
            if (clang_getTokenKind(tokens[i]) == CXToken_Keyword &&
                (strcmp(clang_getCString(spelling), "enum") == 0)) {
                info.name = "";
            }
            clang_disposeString(spelling);
        }
        clang_disposeTokens(tu, tokens, numTokens);
    }
    CXTranslationUnit tu = *(CXTranslationUnit*)client_data;
    info.code = getSourceText(cursor, tu);
    info.sourceOrderIndex = orderCounter++;
    if (clang_getCursorKind(cursor) == CXCursor_TypedefDecl) {
        clang_visitChildren(cursor, [](CXCursor c, CXCursor, CXClientData client_data) {
            auto kind = clang_getCursorKind(c);
            if (kind == CXCursor_StructDecl || kind == CXCursor_UnionDecl || kind == CXCursor_EnumDecl) {
                std::string structName = toStdString(clang_getCursorUSR(c));
                if (!structName.empty()) {
                    static_cast<std::unordered_set<std::string>*>(client_data)->insert(structName);
                }
            }
            return CXChildVisit_Continue;
        }, &typedefBackedTags);
    }
    decls.push_back(info);
    return CXChildVisit_Continue;
}
