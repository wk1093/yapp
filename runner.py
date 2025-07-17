import sys
import os
import subprocess
import shutil
import time

debug = True

yappc_path = "./build/custom/yappc"

if len(sys.argv) > 1 and sys.argv[1] == "nodbg":
    debug = False

# ANSI escape codes for formatting
RESET = "\033[0m"
BOLD = "\033[1m"
DIM = "\033[2m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
CYAN = "\033[36m"
GRAY = "\033[90m"

TEST_FILES = []

for root, dirs, files in os.walk("test"):
    for file in files:
        if file.endswith(".tapp"):
            TEST_FILES.append(os.path.join(root, file))

TESTS = []

any_failed = False

for test_file in TEST_FILES:
    with open(test_file, 'r') as f:
        # Find all line numbers where @test appears at the start of the line
        test_lines = [i+1 for i, line in enumerate(f) if line.lstrip().startswith("@test")]
        if test_lines:
            TESTS.append((test_file, len(test_lines), test_lines))

verbose = False
endbuffer = ""

def print_test_result(file, line, index, type, result, testdir):
    if verbose:
        if result.startswith("OK"):
            print(f"{BOLD}{file}:{line} ({index}) {type}... {GREEN}{result}{RESET}", flush=True)
        elif result.startswith("WARN"):
            print(f"{testdir} {BOLD}{file}:{line} ({index}) {type}... {YELLOW}{result}{RESET}", flush=True)
        else:
            print(f"{testdir} {BOLD}{file}:{line} ({index}) {type}... {RED}{result}{RESET}", flush=True)
    else:
        global endbuffer
        if result.startswith("OK"):
            print(".", end='', flush=True)
        elif result.startswith("WARN"):
            print("w", end='', flush=True)
            endbuffer += f"{testdir} {file}:{line} ({index}) {type}: {result}\n"
        else:
            print("F", end='', flush=True)
            endbuffer += f"{testdir} {file}:{line} ({index}) {type}: {result}\n"


def run_test(test, test_dir):
    global any_failed
    # get all code after (but including) the nth "@test" in the file until the next "@test" or end of file
    with open(test[0], 'r') as f:
        lines = f.readlines()
        test_code = []
        test_count = 0
        test_line = None
        for idx, line in enumerate(lines):
            if line.lstrip().startswith("@test"):
                if test_count == test[1]:
                    break
                test_count += 1
                if test_count == test[1]:
                    test_code.append(line)
                    test_line = idx + 1
            elif test_count == test[1]:
                test_code.append(line)
    # write the test to a file
    with open(os.path.join(test_dir, "test.tapp"), 'w') as f:
        f.writelines(test_code)

    # write the code to a file (remove all test directives which are lines that start with @)
    with open(os.path.join(test_dir, "test.yapp"), 'w') as f:
        for line in test_code:
            if not line.lstrip().startswith("@"):
                f.write(line)

    # two supported types of tests: compile and check
    # compile we just run the compiler on the test code
    # check we run the compiler and check the intermediate output for a given condition
    # the first line should be @test compile or @test check
    # test[1] is 1-based, test[2] is the line number
    test_index = test[1] - 1
    if "compile" in test_code[0]:
        with open(os.path.join(test_dir, "compile.log"), 'w') as log_file:
            log_file.write(f"Starting compilation...\nTest source: {test[0]} line {test[2]}\n")
            try:
                args1 = [yappc_path, os.path.join(test_dir, "test.yapp"), "-c"]
                if debug:
                    args1.append("-g")
                else:
                    args1.append("-s")
                args = args1 + ["--", "--", "-c", "-o", os.path.join(test_dir, "test.o"), "-I", "./build/stdlib/", "-L", "./build/stdlib/", "-lyapp"]
                log_file.write(f"Running command: {' '.join(args)}\n")
                subprocess.run(args, check=True, stdout=log_file, stderr=subprocess.STDOUT)
                log_file.write("Compilation successful.\n")
                print_test_result(test[0], test[2], test_index, "compile", "OK", test_dir)
            except Exception as e:
                log_file.write("An error occurred during compilation.\n")
                log_file.write(str(e))
                print_test_result(test[0], test[2], test_index, "compile", "FAILED: Compilation error", test_dir)
                any_failed = True
    elif "link" in test_code[0]:
        with open(os.path.join(test_dir, "compile.log"), 'w') as log_file:
            log_file.write(f"Starting compilation...\nTest source: {test[0]} line {test[2]}\n")
            try:
                args1 = [yappc_path, os.path.join(test_dir, "test.yapp"), "-c"]
                if debug:
                    args1.append("-g")
                else:
                    args1.append("-s")
                args = args1 + ["--", "--",  "-o", os.path.join(test_dir, "test.elf"), "-I", "./build/stdlib/", "-L", "./build/stdlib/", "-lyapp"]
                log_file.write(f"Running command: {' '.join(args)}\n")
                subprocess.run(args, check=True, stdout=log_file, stderr=subprocess.STDOUT)
                log_file.write("Compilation successful.\n")
                print_test_result(test[0], test[2], test_index, "compile", "OK", test_dir)
            except Exception as e:
                log_file.write("An error occurred during compilation.\n")
                log_file.write(str(e))
                print_test_result(test[0], test[2], test_index, "compile", "FAILED: Compilation error", test_dir)
                any_failed = True
    elif "run" in test_code[0]:
        # same as link but we run it and ensure it runs without errors (i.e. exit code 0)
        with open(os.path.join(test_dir, "run.log"), 'w') as log_file:
            log_file.write(f"Starting compilation and execution...\nTest source: {test[0]} line {test[2]}\n")
            try:
                args1 = [yappc_path, os.path.join(test_dir, "test.yapp"), "-c"]
                if debug:
                    args1.append("-g")
                else:
                    args1.append("-s")
                args = args1 + ["--", "--", "-o", os.path.join(test_dir, "test.elf"), "-I", "./build/stdlib/", "-L", "./build/stdlib/", "-lyapp"]
                log_file.write(f"Running command: {' '.join(args)}\n")
                subprocess.run(args, check=True, stdout=log_file, stderr=subprocess.STDOUT)
                log_file.write("Compilation successful.\n")
                
                # Now run the compiled program
                run_args = [os.path.join(test_dir, "test.elf")]
                log_file.write(f"Running program: {' '.join(run_args)}\n")
                subprocess.run(run_args, check=True, stdout=log_file, stderr=subprocess.STDOUT)
                log_file.write("Program executed successfully.\n")
                print_test_result(test[0], test[2], test_index, "run", "OK", test_dir)
            except subprocess.CalledProcessError as e:
                log_file.write("An error occurred during compilation or execution.\n")
                log_file.write(str(e))
                print_test_result(test[0], test[2], test_index, "run", "FAILED: Compilation or execution error", test_dir)
                any_failed = True
    elif "check" in test_code[0]:
        nocompile = any(line.lstrip().startswith("@nocompile") for line in test_code)
        nocompile_nowarn = any(line.lstrip().startswith("@nocompile nowarn") for line in test_code)
        with open(os.path.join(test_dir, "check.log"), 'w') as log_file:
            log_file.write(f"Starting compilation for check...\nTest source: {test[0]} line {test[2]}\n")
            compile_failed = False
            try:
                args1 = [yappc_path, os.path.join(test_dir, "test.yapp"), "-c"]
                if debug:
                    args1.append("-g")
                else:
                    args1.append("-s")
                args = args1 + ["--", "--", "-c", "-o", os.path.join(test_dir, "test.o"), "-I", "./build/stdlib/", "-L", "./build/stdlib/", "-lyapp"]
                log_file.write(f"Running command: {' '.join(args)}\n")
                subprocess.run(args, check=True, stdout=log_file, stderr=subprocess.STDOUT)
                log_file.write("Compilation successful for check.\n")
            except subprocess.CalledProcessError as e:
                log_file.write("An error occurred during compilation for check.\n")
                log_file.write(str(e))
                compile_failed = True
            if compile_failed and not nocompile:
                print_test_result(test[0], test[2], test_index, "check", "FAILED: Compilation error", test_dir)
                any_failed = True
                return
            # Prepare conditions and file contents before error handling
            conditions = []
            for line in test_code:
                if line.lstrip().startswith("@c "):
                    condition = line.split(" ", 1)[1].strip()
                    conditions.append(condition)
            header_file_path = os.path.join(test_dir, "test.yapp.h")
            source_file_path = os.path.join(test_dir, "test.yapp.cpp")
            header_content = None
            source_content = None
            try:
                with open(header_file_path, 'r') as header_file:
                    header_content = header_file.read()
            except FileNotFoundError:
                log_file.write(f"Header file {header_file_path} not found.\n")
                print_test_result(test[0], test[2], test_index, "check", "FAILED: Header not found", test_dir)
                any_failed = True
                return
            try:
                with open(source_file_path, 'r') as source_file:
                    source_content = source_file.read()
            except FileNotFoundError:
                log_file.write(f"Source file {source_file_path} not found.\n")
                print_test_result(test[0], test[2], test_index, "check", "FAILED: Source not found", test_dir)
                any_failed = True
                return
            all_conditions_met = True
            for condition in conditions:
                try:
                    eval_env = {
                        'h': header_content,
                        'c': source_content
                    }
                    if not eval(condition, {}, eval_env):
                        log_file.write(f"Condition failed: {condition}\n")
                        all_conditions_met = False
                except Exception as e:
                    log_file.write(f"Error evaluating condition '{condition}': {str(e)}\n")
                    all_conditions_met = False
            if all_conditions_met:
                log_file.write("All conditions met.\n")
                if compile_failed and not nocompile_nowarn:
                    print_test_result(test[0], test[2], test_index, "check", "WARN: Compile failed", test_dir)
                else:
                    print_test_result(test[0], test[2], test_index, "check", "OK", test_dir)
            else:
                log_file.write("Not all conditions were met.\n")
                print_test_result(test[0], test[2], test_index, "check", "FAILED: Conditions not met", test_dir)
                any_failed = True
    else:
        print(f"{YELLOW}{BOLD}{test[0]}:{test[2]} ({test_index}){RESET} has an unrecognized test directive. Please use @test compile or @test check.", flush=True)
        return

def run_tests(test):
    for i in range(test[1]):
        test_dir = os.path.join("test_output", os.path.dirname(test[0]).replace(os.path.sep, ".") + "." + os.path.splitext(os.path.basename(test[0]))[0], str(i))

        os.makedirs(test_dir, exist_ok=True)
        # Pass the line number for this test
        run_test((test[0], i+1, test[2][i]), test_dir)

shutil.rmtree("test_output", ignore_errors=True)  # Clean up previous test outputs 
time.sleep(1)

for test in TESTS:
    run_tests(test)
print()

if endbuffer:
    print(endbuffer, flush=True)

if any_failed:
    print(f"{RED}{BOLD}Some tests failed. Please check the logs for details.{RESET}", flush=True)
    sys.exit(1)
print(f"{GREEN}{BOLD}All tests passed successfully!{RESET}", flush=True)