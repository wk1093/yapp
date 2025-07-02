#include "file_writer.h"
#include "visitor.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <regex>

std::vector<std::string> preprocStored;

std::string prePreprocess(const std::string& inputFile) {
    std::ifstream in(inputFile);
    if (!in) {
        std::cerr << "Failed to open input file for pre-preprocessing: " << inputFile << "\n";
        exit(1);
    }
    std::ostringstream out;
    std::string line;

    std::regex pubPreproc(R"(^\s*#pub\s+(.*?)$)");
    while (std::getline(in, line)) {
        std::smatch m;
        if (std::regex_search(line, m, pubPreproc)) {
            preprocStored.push_back(m[1].str());
            out << "pub __attribute__((annotate(\"__pub_preproc__\"))) void __pub_preproc__" << preprocStored.size() - 1 << "();\n";
        }else {
            out << line << "\n";
        }
    }
    std::string outFile = inputFile + ".pubpp";
    std::ofstream pubpp(outFile);
    if (!pubpp) {
        std::cerr << "Failed to write pre-preprocessed file: " << outFile << "\n";
        exit(1);
    }
    pubpp << out.str();
    pubpp.close();
    return outFile;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./yappc <source.yapp> [OPTIONS] -- [Preprocessor Args] -- [Compiler Args]\n";
        return 1;
    }

    std::vector<std::string> preprocArgs;
    std::vector<std::string> compileArgs;
    std::vector<std::string> myArgs;
    // bool isPreprocArgs = true;
    // for (int i = 2; i < argc; ++i) {
    //     if (strcmp(argv[i], "--") == 0) {
    //         isPreprocArgs = false;
    //         continue;
    //     }
    //     if (isPreprocArgs) {
    //         preprocArgs.push_back(argv[i]);
    //     } else {
    //         compileArgs.push_back(argv[i]);
    //     }
    // }

    int argState = 0; // 0: myargs, 1: preprocArgs, 2: compileArgs
    for (int i = 2; i < argc; ++i) {
        if (strcmp(argv[i], "--") == 0) {
            argState++;
            continue;
        }
        if (argState == 0) {
            myArgs.push_back(argv[i]);
        } else if (argState == 1) {
            preprocArgs.push_back(argv[i]);
        } else if (argState == 2) {
            compileArgs.push_back(argv[i]);
        }
    }
    // Check for -d option in myArgs
    bool debugMode = false;
    bool showGenerated = false;
    for (const auto& arg : myArgs) {
        if (arg == "-d") {
            debugMode = true;
            break;
        }
        if (arg == "-g") {
            showGenerated = true;
            break;
        }
    }


    // pre-preprocessor step
    std::string pubppFile = prePreprocess(argv[1]);
    // preprocessor step
    std::string preprocOutputFile = pubppFile;
    if (preprocOutputFile.find(".yapp") == std::string::npos) {
        std::cerr << "Input file must have .yapp extension.\n";
        return 1;
    }
    preprocOutputFile = preprocOutputFile.substr(0, preprocOutputFile.size() - 6) + ".pyapp";
    std::string preprocCommand = "clang -E ";
    for (const auto& arg : preprocArgs) {
        preprocCommand += "\"" + arg + "\" ";
    }
    preprocCommand += "\"-Dpub=__attribute__((annotate(\\\"pub\\\")))\" ";
    preprocCommand += "\"-Dpriv=__attribute__((annotate(\\\"priv\\\")))\" ";
    preprocCommand += "-D__yaplusplus ";
    preprocCommand += "-x c++ \"" + pubppFile + "\" > \"" + preprocOutputFile + "\"";
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
    std::string compileCommand = "clang++ \"" + dir + filename + ".yapp.cpp\" ";
    for (const auto& arg : compileArgs) {
        compileCommand += "\"" + arg + "\" ";
    }
    if (system(compileCommand.c_str()) != 0) {
        std::cerr << "Compilation failed.\n";
        return 1;
    }

    if (!debugMode) {
        // remove intermediate files
        std::remove(preprocOutputFile.c_str());
        std::remove(pubppFile.c_str());
        if (!showGenerated) {   
            std::remove((dir + filename + ".yapp.cpp").c_str());
            std::remove((dir + filename + ".yapp.h").c_str());
        }
    }

    return 0;
}