cmake_minimum_required(VERSION 3.10)
project(yapp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# LLVM provides imported targets including Clang libraries
find_package(Clang REQUIRED CONFIG)

add_executable(yappc oldsrc/main.cpp oldsrc/decl_utils.cpp oldsrc/file_writer.cpp oldsrc/visitor.cpp)

target_include_directories(yappc PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(yappc PRIVATE
    libclang
)

# Required to compile with LLVM headers properly
add_definitions(${LLVM_DEFINITIONS})

# On some systems, you may need to link to pthread and dl
find_package(Threads REQUIRED)
target_link_libraries(yappc PRIVATE Threads::Threads)


# define custom programming language (YAPP) to compile yapp source files
# this is meant to replace the old shell script and add "suopport" for yapp in CMake

set(YAPP_OLD_COMPILER "${CMAKE_CURRENT_BINARY_DIR}/yappc")
add_custom_target(yappc_compile
    DEPENDS yappc
    COMMENT "Compiling YAPP"
    # make dir
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/custom
    # compile the yapp sources into c++
    COMMAND ${YAPP_OLD_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.yapp -o ${CMAKE_CURRENT_BINARY_DIR}/custom
    COMMAND ${YAPP_OLD_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/src/visitor.yapp -o ${CMAKE_CURRENT_BINARY_DIR}/custom
    COMMAND ${YAPP_OLD_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/src/file_writer.yapp -o ${CMAKE_CURRENT_BINARY_DIR}/custom
    COMMAND ${YAPP_OLD_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/src/decl_utils.yapp -o ${CMAKE_CURRENT_BINARY_DIR}/custom
    # compile the generated c++ files
    COMMAND ${CMAKE_CXX_COMPILER} -c -o ${CMAKE_CURRENT_BINARY_DIR}/custom/visitor.o ${CMAKE_CURRENT_BINARY_DIR}/custom/visitor.yapp.cpp -lclang -Wno-attributes
    COMMAND ${CMAKE_CXX_COMPILER} -c -o ${CMAKE_CURRENT_BINARY_DIR}/custom/file_writer.o ${CMAKE_CURRENT_BINARY_DIR}/custom/file_writer.yapp.cpp -lclang -Wno-attributes
    COMMAND ${CMAKE_CXX_COMPILER} -c -o ${CMAKE_CURRENT_BINARY_DIR}/custom/decl_utils.o ${CMAKE_CURRENT_BINARY_DIR}/custom/decl_utils.yapp.cpp -lclang -Wno-attributes
    COMMAND ${CMAKE_CXX_COMPILER} -c -o ${CMAKE_CURRENT_BINARY_DIR}/custom/main.o ${CMAKE_CURRENT_BINARY_DIR}/custom/main.yapp.cpp -lclang -Wno-attributes
    # link the generated c++ files into a new yapp compiler
    COMMAND ${CMAKE_CXX_COMPILER} -o ${CMAKE_CURRENT_BINARY_DIR}/custom/yappc ${CMAKE_CURRENT_BINARY_DIR}/custom/decl_utils.o ${CMAKE_CURRENT_BINARY_DIR}/custom/visitor.o ${CMAKE_CURRENT_BINARY_DIR}/custom/file_writer.o ${CMAKE_CURRENT_BINARY_DIR}/custom/main.o -lclang
)

add_custom_target(yappc_test
    DEPENDS yappc_compile
    COMMENT "Testing YAPP"
    # Run the new yapp compiler on test files
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/runner.py
    )