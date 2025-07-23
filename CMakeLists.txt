cmake_minimum_required(VERSION 3.10)
project(yapp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(RUN_YAPP_TESTS ON)
set(RUN_YAPP_EXAMPLE_FLUIDSIM OFF)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# LLVM provides imported targets including Clang libraries
find_package(Clang REQUIRED CONFIG)

file(GLOB_RECURSE YAPP_SOURCES "oldsrc/*.cpp")

add_executable(yappc ${YAPP_SOURCES})

target_compile_options(yappc PRIVATE -Wno-attributes)
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

set(YAPP_STD_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.io.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.result.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.str.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.main.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.main.function.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.vec.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.stream.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.set.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.map.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.regex.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.alg.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/std.fs.yapp
)

# auto generate the commands to compile the standard library
set(YAPP_STD_PREPROC_COMMANDS "")
set(YAPP_STD_COMPILE_COMMANDS "")
set(YAPP_STD_OBJECTS "")
foreach(source ${YAPP_STD_SOURCES})
    get_filename_component(source_name ${source} NAME)
    set(output_file "${CMAKE_CURRENT_BINARY_DIR}/stdlib/${source_name}.cpp")
    get_filename_component(output_file_dir ${output_file} DIRECTORY)
    list(APPEND YAPP_STD_PREPROC_COMMANDS COMMAND ${YAPP_OLD_COMPILER} ${source} -o ${output_file_dir} --no-std)
    list(APPEND YAPP_STD_COMPILE_COMMANDS COMMAND ${CMAKE_CXX_COMPILER} -c -o ${CMAKE_CURRENT_BINARY_DIR}/stdlib/${source_name}.o ${output_file} -Wno-attributes -I${CMAKE_CURRENT_BINARY_DIR}/stdlib -fPIC)
    list(APPEND YAPP_STD_OBJECTS ${CMAKE_CURRENT_BINARY_DIR}/stdlib/${source_name}.o)
endforeach()

add_custom_target(yapp_stdlib
    DEPENDS yappc
    COMMENT "Compiling YAPP standard library"
    
    # make dir
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/stdlib
    # compile the standard library yapp sources into c++
    ${YAPP_STD_PREPROC_COMMANDS}
    # compile the generated c++ files
    ${YAPP_STD_COMPILE_COMMANDS}
    # link the generated c++ files into a shared library
    COMMAND ${CMAKE_CXX_COMPILER} -shared -o ${CMAKE_CURRENT_BINARY_DIR}/stdlib/libyapp.so ${YAPP_STD_OBJECTS} -Wl,-soname,libyapp.so -Wl,--no-undefined -fPIC
)

set(YAPP_COMPILE_FLAGS
    -I${CMAKE_CURRENT_BINARY_DIR}/stdlib
    -Wno-attributes
)

set(YAPP_LINK_FLAGS
    -L${CMAKE_CURRENT_BINARY_DIR}/stdlib
    -Wl,-rpath,${CMAKE_CURRENT_BINARY_DIR}/stdlib
    -lyapp
    -lclang
)

add_custom_target(yappc_compile
    DEPENDS yappc
    DEPENDS yapp_stdlib
    COMMENT "Compiling YAPP"
    # make dir
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/custom
    # compile the yapp sources into c++
    COMMAND ${YAPP_OLD_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.yapp -o ${CMAKE_CURRENT_BINARY_DIR}/custom
    COMMAND ${YAPP_OLD_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/src/visitor.yapp -o ${CMAKE_CURRENT_BINARY_DIR}/custom
    COMMAND ${YAPP_OLD_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/src/file_writer.yapp -o ${CMAKE_CURRENT_BINARY_DIR}/custom
    COMMAND ${YAPP_OLD_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/src/decl_utils.yapp -o ${CMAKE_CURRENT_BINARY_DIR}/custom

    # compile the generated c++ files
    COMMAND ${CMAKE_CXX_COMPILER} -c -o ${CMAKE_CURRENT_BINARY_DIR}/custom/visitor.o ${YAPP_COMPILE_FLAGS} ${CMAKE_CURRENT_BINARY_DIR}/custom/visitor.yapp.cpp
    COMMAND ${CMAKE_CXX_COMPILER} -c -o ${CMAKE_CURRENT_BINARY_DIR}/custom/file_writer.o ${YAPP_COMPILE_FLAGS} ${CMAKE_CURRENT_BINARY_DIR}/custom/file_writer.yapp.cpp
    COMMAND ${CMAKE_CXX_COMPILER} -c -o ${CMAKE_CURRENT_BINARY_DIR}/custom/decl_utils.o ${YAPP_COMPILE_FLAGS} ${CMAKE_CURRENT_BINARY_DIR}/custom/decl_utils.yapp.cpp
    COMMAND ${CMAKE_CXX_COMPILER} -c -o ${CMAKE_CURRENT_BINARY_DIR}/custom/main.o ${YAPP_COMPILE_FLAGS} ${CMAKE_CURRENT_BINARY_DIR}/custom/main.yapp.cpp
    # link the generated c++ files into a new yapp compiler
    COMMAND ${CMAKE_CXX_COMPILER} -o ${CMAKE_CURRENT_BINARY_DIR}/custom/yappc ${YAPP_LINK_FLAGS} ${CMAKE_CURRENT_BINARY_DIR}/custom/decl_utils.o ${CMAKE_CURRENT_BINARY_DIR}/custom/visitor.o ${CMAKE_CURRENT_BINARY_DIR}/custom/file_writer.o ${CMAKE_CURRENT_BINARY_DIR}/custom/main.o
)

set(YAPP_NEW_COMPILER "${CMAKE_CURRENT_BINARY_DIR}/custom/yappc")

if (RUN_YAPP_TESTS)
    add_custom_target(yappc_test
        DEPENDS yappc_compile
        DEPENDS yapp_stdlib
        COMMENT "Testing YAPP"
        # Run the new yapp compiler on test files
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/runner.py
    )
else()
    add_custom_target(yappc_test
        DEPENDS yappc_compile
        DEPENDS yapp_stdlib
        COMMENT "YAPP tests are disabled. Set RUN_YAPP_TESTS to ON to enable."
    )
endif()

if (RUN_YAPP_EXAMPLE_FLUIDSIM)
    file(GLOB_RECURSE FLUIDSIM_SOURCES "examples/fluidsim/*.yapp")
    set(YAPP_EX_FLUID_PREPROC_COMMANDS "")
    set(YAPP_EX_FLUID_COMPILE_COMMANDS "")
    set(YAPP_EX_FLUID_OBJECTS "")
    foreach(source ${FLUIDSIM_SOURCES})
        get_filename_component(source_name ${source} NAME)
        set(output_file "${CMAKE_CURRENT_BINARY_DIR}/examples/fluidsim/${source_name}.cpp")
        get_filename_component(output_file_dir ${output_file} DIRECTORY)
        list(APPEND YAPP_EX_FLUID_PREPROC_COMMANDS COMMAND ${YAPP_NEW_COMPILER} ${source} -o ${output_file_dir})
        list(APPEND YAPP_EX_FLUID_COMPILE_COMMANDS COMMAND ${CMAKE_CXX_COMPILER} -c -o ${CMAKE_CURRENT_BINARY_DIR}/examples/fluidsim/${source_name}.o ${output_file} -Wno-attributes -I${CMAKE_CURRENT_BINARY_DIR}/stdlib -fPIC)
        list(APPEND YAPP_EX_FLUID_OBJECTS ${CMAKE_CURRENT_BINARY_DIR}/examples/fluidsim/${source_name}.o)
    endforeach()
    add_custom_target(yappc_example_fluidsim
        DEPENDS yappc_compile
        DEPENDS yapp_stdlib
        COMMENT "Compiling YAPP example: Fluid Simulation"
        
        # make dir
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/examples/fluidsim
        # compile the example yapp sources into c++
        ${YAPP_EX_FLUID_PREPROC_COMMANDS}
        # compile the generated c++ files
        ${YAPP_EX_FLUID_COMPILE_COMMANDS}
        # link the generated c++ files into an executable
        COMMAND ${CMAKE_CXX_COMPILER} -o ${CMAKE_CURRENT_BINARY_DIR}/examples/fluidsim/fluidsim ${YAPP_LINK_FLAGS} ${YAPP_EX_FLUID_OBJECTS}
    )
else()
    add_custom_target(yappc_example_fluidsim
        DEPENDS yappc_compile
        DEPENDS yapp_stdlib
        COMMENT "YAPP example: Fluid Simulation is disabled. Set RUN_YAPP_EXAMPLE_FLUIDSIM to ON to enable."
    )
endif()

add_custom_target(yappc_all)
if (RUN_YAPP_TESTS)
    add_dependencies(yappc_all yappc_test)
else()
    add_dependencies(yappc_all yappc_compile)
endif()
if (RUN_YAPP_EXAMPLE_FLUIDSIM)
    add_dependencies(yappc_all yappc_example_fluidsim)
else()
    add_dependencies(yappc_all yappc_compile)
endif()
add_dependencies(yappc_all yapp_stdlib)