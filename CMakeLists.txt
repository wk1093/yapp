cmake_minimum_required(VERSION 3.10)
project(AnnotateDetect)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# LLVM provides imported targets including Clang libraries
find_package(Clang REQUIRED CONFIG)

# You can use Clang::clang-c for libclang C API
add_executable(annotate_detect src/main.cpp)

target_include_directories(annotate_detect PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(annotate_detect PRIVATE
    libclang
)

# Required to compile with LLVM headers properly
add_definitions(${LLVM_DEFINITIONS})

# On some systems, you may need to link to pthread and dl
find_package(Threads REQUIRED)
target_link_libraries(annotate_detect PRIVATE Threads::Threads)