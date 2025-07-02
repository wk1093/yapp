#include "file_writer.h"
#include "visitor.h"
#include "decl_utils.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>

// Helper: emit decls with namespace handling
static void emitWithNamespaces(std::ostream& out, const std::vector<DeclInfo>& decls) {
    std::vector<std::string> currentNS;
    for (const auto& d : decls) {
        size_t common = 0;
        while (common < currentNS.size() && common < d.namespaces.size() &&
               currentNS[common] == d.namespaces[common]) {
            ++common;
        }
        for (size_t i = currentNS.size(); i-- > common;) {
            out << "}\n";
        }
        for (size_t i = common; i < d.namespaces.size(); ++i) {
            out << "namespace " << d.namespaces[i] << " {\n";
        }
        currentNS = d.namespaces;
        if (d.isExternC) {
            out << "#ifdef __cplusplus\nextern \"C\" {\n#endif\n";
            out << d.code << ";\n";
            out << "#ifdef __cplusplus\n}\n#endif\n\n";
        } else {
            out << d.code << ";\n\n";
        }
    }
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
        if (d.annotation == "pub") {
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
            if (d.isDefinition && !d.isInline &&
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
            d.kind == CXCursor_UnionDecl) {
            continue;
        }
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
