#include "file_writer.h"
#include "visitor.h"
#include "decl_utils.h"
#include <clang-c/Index.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>

// Helper: check if a DeclInfo is a template (function or class)
static bool isTemplateDecl(const DeclInfo& d) {
    return d.isTemplate;
}

// Helper: emit decls with namespace and extern "C" grouping, with strict nesting
static void emitWithNamespaces(std::ostream& out, const std::vector<DeclInfo>& decls) {
    std::vector<std::string> currentNS;
    bool inExternC = false;
    for (size_t idx = 0; idx < decls.size(); ++idx) {
        const auto& d = decls[idx];
        size_t common = 0;
        while (common < currentNS.size() && common < d.namespaces.size() &&
               currentNS[common] == d.namespaces[common]) {
            ++common;
        }
        // Always close extern "C" before closing/opening namespaces
        if (inExternC && (currentNS.size() != common || d.namespaces.size() != common)) {
            out << "#ifdef __cplusplus\n}\n#endif\n";
            inExternC = false;
        }
        // Close namespaces
        for (size_t i = currentNS.size(); i-- > common;) {
            out << "}\n";
        }
        // Open namespaces
        for (size_t i = common; i < d.namespaces.size(); ++i) {
            out << "namespace " << d.namespaces[i] << " {\n";
        }
        currentNS = d.namespaces;
        // Open extern "C" if needed (always after namespace is open)
        if (d.isExternC && !inExternC) {
            out << "#ifdef __cplusplus\nextern \"C\" {\n#endif\n";
            inExternC = true;
        }
        // Output the declaration
        out << d.code << ";\n\n";
        // If the next decl is in a different namespace or extern "C" state, close extern "C" now
        bool nextNeedsExtern = false;
        size_t nextCommon = common;
        if (idx + 1 < decls.size()) {
            const auto& next = decls[idx + 1];
            nextCommon = 0;
            while (nextCommon < currentNS.size() && nextCommon < next.namespaces.size() &&
                   currentNS[nextCommon] == next.namespaces[nextCommon]) {
                ++nextCommon;
            }
            nextNeedsExtern = next.isExternC;
        }
        if (inExternC && (idx + 1 == decls.size() || currentNS.size() != nextCommon || !nextNeedsExtern)) {
            out << "#ifdef __cplusplus\n}\n#endif\n";
            inExternC = false;
        }
    }
    // Close any open namespaces
    for (size_t i = currentNS.size(); i-- > 0;) {
        out << "}\n";
    }
}

// Helper: collect unique decls by USR
static std::vector<DeclInfo> collectUniqueDecls() {
    std::vector<DeclInfo> seen;
    std::unordered_map<std::string, size_t> usrToIndex;
    for (auto& d : decls) {
        if (d.annotation.empty()) {
            std::cout << "Warning: Declaration without annotation for " << d.name << "\n";
            d.annotation = "priv";
        }
        auto it = usrToIndex.find(d.usr);
        if (it == usrToIndex.end()) {
            usrToIndex[d.usr] = seen.size();
            seen.push_back(d);
        } else {
            auto& existing = seen[it->second];
            if (existing.annotation == "priv" && d.annotation == "pub") {
                existing = d;
            } else if (!existing.isDefinition && d.isDefinition) {
                // keep existing
            }
        }
    }
    std::sort(seen.begin(), seen.end(), [](const DeclInfo& a, const DeclInfo& b) {
        return a.sourceOrderIndex < b.sourceOrderIndex;
    });
    return seen;
}

// Helper: collect public decls for header
static std::vector<DeclInfo> collectHeaderDecls(const std::vector<DeclInfo>& seen) {
    std::vector<DeclInfo> pubDecls;
    for (const auto& d : seen) {
        if (d.annotation == "pub" || isTemplateDecl(d)) {
            if (isAnonymousStruct(d)) {
                continue;
            }
            if ((d.kind == CXCursor_StructDecl ||
                d.kind == CXCursor_UnionDecl ||
                d.kind == CXCursor_EnumDecl) &&
                typedefBackedTags.count(d.usr))
            {
                continue;
            }
            DeclInfo copy = d;
            // For templates, always emit the full definition
            if (!isTemplateDecl(d) && d.isDefinition && !d.isInline &&
                (d.kind == CXCursor_FunctionDecl || d.kind == CXCursor_CXXMethod)) {
                copy.code = makeDeclaration(d.code);
            }
            pubDecls.push_back(copy);
        }
    }
    std::sort(pubDecls.begin(), pubDecls.end(), [](const DeclInfo& a, const DeclInfo& b) {
        return a.sourceOrderIndex < b.sourceOrderIndex;
    });
    return pubDecls;
}

// Helper: collect source decls for cpp file
static std::vector<DeclInfo> collectSourceDecls(const std::vector<DeclInfo>& seen) {
    std::unordered_map<std::string, bool> pubHasDefinition;
    for (const auto& d : seen) {
        if (d.annotation == "pub" && d.isDefinition) {
            pubHasDefinition[d.name] = true;
        }
    }
    std::vector<DeclInfo> sourceDecls;
    for (const auto& d : decls) {
        if (d.annotation.empty()) {
            const_cast<DeclInfo&>(d).annotation = "priv";
        }
        if (d.kind == CXCursor_TypedefDecl || d.kind == CXCursor_TypeAliasDecl ||
            d.kind == CXCursor_StructDecl || d.kind == CXCursor_EnumDecl ||
            d.kind == CXCursor_UnionDecl || d.kind == CXCursor_ClassDecl) {
            continue;
        }
        // Do not emit template definitions in the source file
        if (isTemplateDecl(d)) continue;
        if (d.annotation == "pub") {
            if (!d.isDefinition && pubHasDefinition[d.name]) continue;
            if (d.isInline) continue;
            if (!d.isDefinition) continue;
        }
        sourceDecls.push_back(d);
    }
    std::sort(sourceDecls.begin(), sourceDecls.end(), [](const DeclInfo& a, const DeclInfo& b) {
        return a.sourceOrderIndex < b.sourceOrderIndex;
    });
    return sourceDecls;
}

void writeFiles(const std::string& base, const std::string& dir) {
    std::ofstream hfile(dir + base + ".gen.h");
    std::ofstream cppfile(dir + base + ".gen.cpp");
    hfile << "#pragma once\n";
    hfile << "#define pub\n#define priv\n\n";
    cppfile << "#include \"" << base << ".gen.h\"\n\n";
    cppfile << "#define pub\n#define priv\n\n";
    auto seen = collectUniqueDecls();
    auto pubDecls = collectHeaderDecls(seen);
    emitWithNamespaces(hfile, pubDecls);
    hfile << "#undef pub\n#undef priv\n";
    auto sourceDecls = collectSourceDecls(seen);
    emitWithNamespaces(cppfile, sourceDecls);
    cppfile << "#undef pub\n#undef priv\n";
}
