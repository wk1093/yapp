cmake_minimum_required(VERSION 3.10)
project(yapp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(RUN_YAPP_TESTS OFF)
set(RUN_YAPP_EXAMPLE_FLUIDSIM ON)

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
set_target_properties(yappc PROPERTIES OUTPUT_NAME "yappc_old")

add_definitions(${LLVM_DEFINITIONS})

find_package(Threads REQUIRED)
target_link_libraries(yappc PRIVATE Threads::Threads)



set(YAPP_OLD_COMPILER "${CMAKE_CURRENT_BINARY_DIR}/yappc_old")

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

function(yapp_add_sources out_var sources output_dir)
    set(output_files "")
    set(transpile_commands "")
    set(yapp_compile_sources "")
    set(depend_files "")
    foreach(source ${sources})
        get_filename_component(source_name ${source} NAME)
        set(output_file "${output_dir}/${source_name}.cpp")
        list(APPEND output_files OUTPUT ${output_file})
        get_filename_component(output_file_dir ${output_file} DIRECTORY)
        list(APPEND transpile_commands COMMAND ${CMAKE_COMMAND} -E make_directory ${output_file_dir})
        list(APPEND transpile_commands COMMAND ${YAPP_COMPILER} ${source} -o ${output_file_dir} ${YAPP_TRANSPILER_FLAGS})
        list(APPEND yapp_compile_sources ${output_file})
        list(APPEND depend_files DEPENDS ${source})
    endforeach()
    set(dependencies)
    foreach(dep ${YAPP_DEPENDENCIES})
        list(APPEND dependencies DEPENDS ${dep})
    endforeach()
    add_custom_command(
        ${output_files}
        ${depend_files}
        ${transpile_commands}
        ${dependencies}

    )
    set(${out_var} ${yapp_compile_sources} PARENT_SCOPE)
endfunction()

set(YAPP_COMPILER "${YAPP_OLD_COMPILER}")
set(YAPP_DEPENDENCIES yappc)
set(YAPP_TRANSPILER_FLAGS "--no-std")
yapp_add_sources(YAPP_COMPILE_SOURCES "${YAPP_STD_SOURCES}" "${CMAKE_CURRENT_BINARY_DIR}/stdlib")
add_library(yapp_stdlib SHARED ${YAPP_COMPILE_SOURCES})
target_compile_options(yapp_stdlib PUBLIC -Wno-attributes)
set_target_properties(yapp_stdlib PROPERTIES OUTPUT_NAME "yapp")
set_target_properties(yapp_stdlib PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/stdlib)
target_include_directories(yapp_stdlib PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/stdlib)
target_link_libraries(yapp_stdlib PRIVATE ${LLVM_LIBRARIES} libclang)
add_dependencies(yapp_stdlib yappc)

set(YAPP_TRANSPILER_FLAGS "")
set(YAPP_TRANSPILER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/visitor.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/file_writer.yapp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decl_utils.yapp
)
yapp_add_sources(YAPP_COMPILE_SOURCES "${YAPP_TRANSPILER_SOURCES}" "${CMAKE_CURRENT_BINARY_DIR}/custom")
add_executable(yappc_compile ${YAPP_COMPILE_SOURCES})
target_compile_options(yappc_compile PRIVATE -Wno-attributes)
target_include_directories(yappc_compile PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/custom)
target_link_libraries(yappc_compile PRIVATE yapp_stdlib ${LLVM_LIBRARIES} libclang)
set_target_properties(yappc_compile PROPERTIES OUTPUT_NAME "yappc")
set_target_properties(yappc_compile PROPERTIES EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/custom)

set(YAPP_NEW_COMPILER "${CMAKE_CURRENT_BINARY_DIR}/yappc")
set(YAPP_COMPILER "${YAPP_NEW_COMPILER}")
set(YAPP_DEPENDENCIES yappc_compile)

if (RUN_YAPP_TESTS)
    add_custom_target(yappc_test
        DEPENDS yappc_compile
        DEPENDS yapp_stdlib
        COMMENT "Testing YAPP"
        # Run the new yapp compiler on test files
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/runner.py
    )
endif()

if (RUN_YAPP_EXAMPLE_FLUIDSIM)
    file(GLOB_RECURSE FLUIDSIM_SOURCES "examples/fluidsim/*.yapp")
    yapp_add_sources(FLUIDSIM_COMPILE_SOURCES "${FLUIDSIM_SOURCES}" "${CMAKE_CURRENT_BINARY_DIR}/examples/fluidsim")
    add_executable(yappc_example_fluidsim ${FLUIDSIM_COMPILE_SOURCES})
    target_link_libraries(yappc_example_fluidsim PUBLIC yapp_stdlib)
    target_include_directories(yappc_example_fluidsim PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/examples/fluidsim)
    add_dependencies(yappc_example_fluidsim yappc_compile)
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