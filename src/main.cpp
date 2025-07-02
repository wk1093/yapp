#include <algorithm>
#include <clang-c/CXString.h>
#include <clang-c/Index.h>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <unordered_set>

struct DeclInfo {
    std::string name;
    std::string usr;
    std::string code;
    std::string annotation; // "pub" or "priv"
    bool isDefinition = false;
    bool isInline = false;
    bool isExternC = false;
    CXCursorKind kind;
    int sourceOrderIndex = 0;
    std::vector<std::string> namespaces;
};

bool isExternC(CXCursor cursor) {
    if (clang_getCursorKind(cursor) != CXCursor_FunctionDecl)
        return false;

    if (clang_getCursorLinkage(cursor) != CXLinkage_External)
        return false;

    CXCursor parent = clang_getCursorSemanticParent(cursor);
    if (clang_getCursorKind(parent) == CXCursor_LinkageSpec) {
        // Check the source text at the parent's location
        CXSourceRange range = clang_getCursorExtent(parent);
        CXTranslationUnit tu = clang_Cursor_getTranslationUnit(parent);
        CXToken* tokens = nullptr;
        unsigned numTokens = 0;
        clang_tokenize(tu, range, &tokens, &numTokens);

        for (unsigned i = 0; i < numTokens; ++i) {
            CXString spelling = clang_getTokenSpelling(tu, tokens[i]);
            const char* token = clang_getCString(spelling);
            if (strcmp(token, "\"C\"") == 0) {
                clang_disposeString(spelling);
                clang_disposeTokens(tu, tokens, numTokens);
                return true;
            }
            clang_disposeString(spelling);
        }
        clang_disposeTokens(tu, tokens, numTokens);
    }
    return false;
}

bool isAnonymousStruct(const DeclInfo& d) {
    // The cursor kind must be StructDecl and name empty
    return (d.kind == CXCursor_StructDecl) && d.name.empty();
}


std::string toStdString(CXString cxStr) {
    std::string str = clang_getCString(cxStr);
    clang_disposeString(cxStr);
    return str;
}

std::string getSourceText_old(CXSourceRange range, CXTranslationUnit tu) {
    CXSourceLocation startLoc = clang_getRangeStart(range);
    CXSourceLocation endLoc = clang_getRangeEnd(range);

    CXFile file;
    unsigned startOffset, endOffset;
    clang_getFileLocation(startLoc, &file, nullptr, nullptr, &startOffset);
    clang_getFileLocation(endLoc, &file, nullptr, nullptr, &endOffset);

    size_t fileSize = 0;
    const char* fileContents = clang_getFileContents(tu, file, &fileSize);

    if (startOffset < endOffset && endOffset <= fileSize)
        return std::string(fileContents + startOffset, (endOffset + 1) - startOffset);
    return "";
}

std::string getSourceText(CXCursor cursor, CXTranslationUnit tu) {
    CXSourceRange range = clang_getCursorExtent(cursor);
    CXToken* tokens = nullptr;
    unsigned numTokens = 0;
    clang_tokenize(tu, range, &tokens, &numTokens);

    std::string result;
    for (unsigned i = 0; i < numTokens; ++i) {
        result += toStdString(clang_getTokenSpelling(tu, tokens[i]));
        CXTokenKind kind = clang_getTokenKind(tokens[i]);
        if (kind == CXToken_Punctuation || kind == CXToken_Keyword)
            result += " ";
        else
            result += " ";
    }

    clang_disposeTokens(tu, tokens, numTokens);
    return result;
}

std::string getAnnotate(CXCursor cursor) {
    std::string annotation = "";
    clang_visitChildren(cursor, [](CXCursor c, CXCursor, CXClientData data) {
        if (clang_getCursorKind(c) == CXCursor_AnnotateAttr) {
            auto str = toStdString(clang_getCursorSpelling(c));
            *static_cast<std::string*>(data) = str;
            return CXChildVisit_Break;
        }
        return CXChildVisit_Continue;
    }, &annotation);
    return annotation;
}

std::vector<std::string> getNamespaceChain(CXCursor cursor) {
    std::vector<std::string> chain;

    CXCursor parent = clang_getCursorSemanticParent(cursor);
    while (!clang_Cursor_isNull(parent)) {
        if (clang_getCursorKind(parent) == CXCursor_Namespace) {
            std::string ns = toStdString(clang_getCursorSpelling(parent));
            chain.push_back(ns);
        }
        parent = clang_getCursorSemanticParent(parent);
    }

    std::reverse(chain.begin(), chain.end());
    return chain;
}

std::vector<DeclInfo> decls;
int orderCounter = 0;
std::unordered_set<std::string> typedefBackedTags;

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data) {
    CXCursorKind kind = clang_getCursorKind(cursor);
    if (!clang_isDeclaration(kind)) return CXChildVisit_Recurse;

    // if this is an extern "c" declaration, we need to handle it specially
    if (kind == CXCursor_LinkageSpec || kind == CXCursor_Namespace) {
        // Recurse inside this cursor's children
        return CXChildVisit_Recurse;
    }


    std::string annotation = getAnnotate(cursor);
    if (annotation.empty()) {

        // Always treat type declarations and aliases as public
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
    // ANONYMOUS DETECTION
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

std::string makeDeclaration(const std::string& code) {
    std::string trimmed = code;
    trimmed.erase(trimmed.find_last_not_of(" \\t\n\r") + 1);
    size_t brace = trimmed.find('{');
    if (brace != std::string::npos) {
        trimmed = trimmed.substr(0, brace);
    }
    if (trimmed.back() != ';') {
        trimmed += ";";
    }
    return trimmed;
}

void writeFiles(const std::string& base, const std::string& dir) {
    std::ofstream hfile(dir + base + ".gen.h");
    std::ofstream cppfile(dir + base + ".gen.cpp");

    hfile << "#pragma once\n";
    hfile << "#define pub\n#define priv\n\n";
    cppfile << "#include \"" << base << ".gen.h\"\n\n";
    cppfile << "#define pub\n#define priv\n\n";

    // Map: name -> best pub DeclInfo
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

    auto emitWithNamespaces = [](std::ostream& out, const std::vector<DeclInfo>& decls) {
        std::vector<std::string> currentNS;

        for (const auto& d : decls) {
            // Compare namespace vector
            size_t common = 0;
            while (common < currentNS.size() && common < d.namespaces.size() &&
                   currentNS[common] == d.namespaces[common]) {
                ++common;
            }

            // Close old namespaces
            for (size_t i = currentNS.size(); i-- > common;) {
                out << "}\n";
            }

            // Open new namespaces
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

        // Close remaining namespaces
        for (size_t i = currentNS.size(); i-- > 0;) {
            out << "}\n";
        }
    };

    // --- Collect header declarations ---
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
                continue; // This struct/union/enum is already included in a typedef
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

    emitWithNamespaces(hfile, pubDecls);

    hfile << "#undef pub\n#undef priv\n";

    // --- Emit source ---

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
            if (!d.isDefinition) continue; // maybe remove this?
        }

        sourceDecls.push_back(d);
    }

    std::sort(sourceDecls.begin(), sourceDecls.end(), [](const DeclInfo& a, const DeclInfo& b) {
        return a.sourceOrderIndex < b.sourceOrderIndex;
    });

    emitWithNamespaces(cppfile, sourceDecls);

    cppfile << "#undef pub\n#undef priv\n";
}


// Instead of running 3 commands like this:
// clang -E PREPROC_ARGS "-Dpub=__attribute__((annotate(\"pub\")))" "-Dpriv=__attribute__((annotate(\"priv\")))" -x c++ test.xpp > test.p.xpp
// ./this_program test.p.xpp
// clang++ test.gen.cpp COMPILE_ARGS
// We can run a single command:
// ./this_program test.xpp PREPROC_ARGS -- COMPILE_ARGS
// where PREPROC_ARGS are the arguments for the preprocessor, and COMPILE_ARGS are the
// arguments for the compiler. The preprocessor will run first, and then this program


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./header_generator <source.xpp> [Preprocessor Args] -- [Compiler Args]\n";
        return 1;
    }

    std::vector<std::string> preprocArgs;
    std::vector<std::string> compileArgs;
    bool isPreprocArgs = true;
    for (int i = 2; i < argc; ++i) {
        if (strcmp(argv[i], "--") == 0) {
            isPreprocArgs = false;
            continue;
        }
        if (isPreprocArgs) {
            preprocArgs.push_back(argv[i]);
        } else {
            compileArgs.push_back(argv[i]);
        }
    }

    // preprocessor step
    std::string preprocOutputFile = argv[1];
    if (preprocOutputFile.find(".xpp") == std::string::npos) {
        std::cerr << "Input file must have .xpp extension.\n";
        return 1;
    }
    preprocOutputFile = preprocOutputFile.substr(0, preprocOutputFile.size() - 4) + ".p.xpp";
    std::string preprocCommand = "clang -E ";
    for (const auto& arg : preprocArgs) {
        preprocCommand += "\"" + arg + "\" ";
    }
    preprocCommand += "\"-Dpub=__attribute__((annotate(\\\"pub\\\")))\" ";
    preprocCommand += "\"-Dpriv=__attribute__((annotate(\\\"priv\\\")))\" ";
    preprocCommand += "-x c++ \"" + std::string(argv[1]) + "\" > \"" + preprocOutputFile + "\"";
    // std::cout << "+ " << preprocCommand << "\n";
    if (system(preprocCommand.c_str()) != 0) {
        std::cerr << "Preprocessing failed.\n";
        return 1;
    }

    // remove the # line directives from the preprocessed output
    std::ifstream preprocFile(preprocOutputFile);
    if (!preprocFile) {
        std::cerr << "Failed to open preprocessed file: " << preprocOutputFile << "\n";
        return 1;
    }
    std::string line;
    std::ostringstream cleanedOutput;
    while (std::getline(preprocFile, line)) {
        // Remove lines starting with # (line directives)
        if (line.empty() || line[0] != '#') {
            cleanedOutput << line << "\n";
        } else {
            cleanedOutput << "\n"; // Comment out the line directive for clarity
        }
    }
    preprocFile.close();
    // Write cleaned output back to the file
    std::ofstream cleanedFile(preprocOutputFile);
    if (!cleanedFile) {
        std::cerr << "Failed to write cleaned preprocessed file: " << preprocOutputFile << "\n";
        return 1;
    }
    cleanedFile << cleanedOutput.str();
    cleanedFile.close();

    CXIndex index = clang_createIndex(0, 0);
    const char* args[] = {
        "-x", "c++-cpp-output",
        "-std=c++20",
        "-Dpub=__attribute__((annotate(\"pub\")))",
        "-Dpriv=__attribute__((annotate(\"priv\")))"
    };
    CXTranslationUnit tu = clang_parseTranslationUnit(
        index, preprocOutputFile.c_str(), args, sizeof(args)/sizeof(args[0]), nullptr, 0, CXTranslationUnit_None);
    if (!tu) {
        if (unsigned numErrors = clang_getNumDiagnostics(tu)) {
            unsigned displayOptions = clang_defaultDiagnosticDisplayOptions();

            for (unsigned i=0; i < numErrors; ++i) {
                CXDiagnostic diag = clang_getDiagnostic(tu, i);
                CXString str = clang_formatDiagnostic(diag, displayOptions);

                std::cerr << clang_getCString(str) << "\n";

                clang_disposeString(str);
                clang_disposeDiagnostic(diag);
            }

            // Stop if there are errors.
            return 2;
        }


        std::cerr << "Failed to parse input file.\n";
        return 1;
    }

    CXCursor root = clang_getTranslationUnitCursor(tu);
    clang_visitChildren(root, visitor, &tu);

    std::string base = argv[1];
    size_t slash = base.find_last_of("/\\");
    size_t dot = base.find_last_of('.');
    std::string filename = base.substr(slash == std::string::npos ? 0 : slash + 1, dot - (slash == std::string::npos ? 0 : slash + 1));

    // get directory of the input file
    std::string dir = (slash == std::string::npos) ? "./" :
                        base.substr(0, slash + 1);

    writeFiles(filename, dir);

    clang_disposeTranslationUnit(tu);
    clang_disposeIndex(index);

    // Compile the generated files
    std::string compileCommand = "clang++ \"" + dir + filename + ".gen.cpp\" ";
    for (const auto& arg : compileArgs) {
        compileCommand += "\"" + arg + "\" ";
    }
    // std::cout << "+ " << compileCommand << "\n";
    if (system(compileCommand.c_str()) != 0) {
        std::cerr << "Compilation failed.\n";
        return 1;
    }

    return 0;
}