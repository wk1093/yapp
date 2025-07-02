import sys
import os
import subprocess
import shutil
import time

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

for test_file in TEST_FILES:
    with open(test_file, 'r') as f:
        # Find all line numbers where @test appears at the start of the line
        test_lines = [i+1 for i, line in enumerate(f) if line.lstrip().startswith("@test")]
        if test_lines:
            TESTS.append((test_file, len(test_lines), test_lines))

def run_test(test, test_dir):
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
    test_line_info = f"{CYAN}{test[0]}:{test[2]} ({test_index}){RESET}"
    if "compile" in test_code[0]:
        with open(os.path.join(test_dir, "compile.log"), 'w') as log_file:
            print(f"{test_line_info} compile... ", end='')
            log_file.write(f"Starting compilation...\nTest source: {test[0]} line {test[2]}\n")
            try:
                subprocess.run(["./build/yappc", os.path.join(test_dir, "test.yapp"), "--", "-c", "-o", os.path.join(test_dir, "test.o")], check=True, stdout=log_file, stderr=subprocess.STDOUT)
                log_file.write("Compilation successful.\n")
                print(f"{GREEN}[OK]{RESET}", flush=True)
            except Exception as e:
                log_file.write("An error occurred during compilation.\n")
                log_file.write(str(e))
                print(f"{RED}[FAILED]{RESET} {test_dir}", flush=True)
    elif "check" in test_code[0]:
        with open(os.path.join(test_dir, "check.log"), 'w') as log_file:
            print(f"{test_line_info} check... ", end='')
            log_file.write(f"Starting compilation for check...\nTest source: {test[0]} line {test[2]}\n")
            try:
                subprocess.run(["./build/yappc", os.path.join(test_dir, "test.yapp"), "--", "-c", "-o", os.path.join(test_dir, "test.o")], check=True, stdout=log_file, stderr=subprocess.STDOUT)
                log_file.write("Compilation successful for check.\n")
            except subprocess.CalledProcessError as e:
                log_file.write("An error occurred during compilation for check.\n")
                log_file.write(str(e))
            # Prepare conditions and file contents before error handling
            conditions = []
            for line in test_code:
                if line.lstrip().startswith("@c "):
                    condition = line.split(" ", 1)[1].strip()
                    conditions.append(condition)
            header_file_path = os.path.join(test_dir, "test.gen.h")
            source_file_path = os.path.join(test_dir, "test.gen.cpp")
            header_content = None
            source_content = None
            try:
                with open(header_file_path, 'r') as header_file:
                    header_content = header_file.read()
            except FileNotFoundError:
                log_file.write(f"Header file {header_file_path} not found.\n")
                print(f"{RED}[FAILED: Header not found]{RESET} {test_dir}", flush=True)
                return
            try:
                with open(source_file_path, 'r') as source_file:
                    source_content = source_file.read()
            except FileNotFoundError:
                log_file.write(f"Source file {source_file_path} not found.\n")
                print(f"{RED}[FAILED: Source not found]{RESET} {test_dir}", flush=True)
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
                print(f"{GREEN}[OK]{RESET}", flush=True)
            else:
                log_file.write("Not all conditions were met.\n")
                print(f"{RED}[FAILED: Conditions not met]{RESET} {test_dir}", flush=True)
    else:
        print(f"{YELLOW}{BOLD}{test[0]}:{test[2]} ({test_index}){RESET} has an unrecognized test directive. Please use @test compile or @test check.", flush=True)
        return

def run_tests(test):
    for i in range(test[1]):
        os.makedirs(os.path.join("test_output", os.path.splitext(os.path.basename(test[0]))[0], str(i)), exist_ok=True)
        # Pass the line number for this test
        run_test((test[0], i+1, test[2][i]), os.path.join("test_output", os.path.splitext(os.path.basename(test[0]))[0], str(i)))

shutil.rmtree("test_output", ignore_errors=True)  # Clean up previous test outputs 
time.sleep(1)

for test in TESTS:
    run_tests(test)
