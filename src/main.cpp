#include "file_writer.h"
#include "visitor.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./header_generator <source.yapp> [Preprocessor Args] -- [Compiler Args]\n";
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
    if (preprocOutputFile.find(".yapp") == std::string::npos) {
        std::cerr << "Input file must have .yapp extension.\n";
        return 1;
    }
    preprocOutputFile = preprocOutputFile.substr(0, preprocOutputFile.size() - 4) + ".p.yapp";
    std::string preprocCommand = "clang -E ";
    for (const auto& arg : preprocArgs) {
        preprocCommand += "\"" + arg + "\" ";
    }
    preprocCommand += "\"-Dpub=__attribute__((annotate(\\\"pub\\\")))\" ";
    preprocCommand += "\"-Dpriv=__attribute__((annotate(\\\"priv\\\")))\" ";
    preprocCommand += "-x c++ \"" + std::string(argv[1]) + "\" > \"" + preprocOutputFile + "\"";
    if (system(preprocCommand.c_str()) != 0) {
        std::cerr << "Preprocessing failed.\n";
        return 1;
    }

    std::ifstream preprocFile(preprocOutputFile);
    if (!preprocFile) {
        std::cerr << "Failed to open preprocessed file: " << preprocOutputFile << "\n";
        return 1;
    }
    std::string line;
    std::ostringstream cleanedOutput;
    while (std::getline(preprocFile, line)) {
        if (line.empty() || line[0] != '#') {
            cleanedOutput << line << "\n";
        } else {
            cleanedOutput << "\n";
        }
    }
    preprocFile.close();
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
    std::string dir = (slash == std::string::npos) ? "./" : base.substr(0, slash + 1);
    writeFiles(filename, dir);
    clang_disposeTranslationUnit(tu);
    clang_disposeIndex(index);
    std::string compileCommand = "clang++ \"" + dir + filename + ".gen.cpp\" ";
    for (const auto& arg : compileArgs) {
        compileCommand += "\"" + arg + "\" ";
    }
    if (system(compileCommand.c_str()) != 0) {
        std::cerr << "Compilation failed.\n";
        return 1;
    }
    return 0;
}