import sys
import os
import subprocess
import shutil
import time

# TODO: recurse for this
TEST_FILES = [
    "test/test1.xppt"
]

TESTS = []

for test_file in TEST_FILES:
    with open(test_file, 'r') as f:
        # cout how many times "@test" appears in the file (beginning of line only)
        numtests = sum(1 for line in f if line.lstrip().startswith("@test"))
        if numtests > 0:
            TESTS.append((test_file, numtests))

def run_test(test, test_dir):
    # get all code after (but including) the nth "@test" in the file until the next "@test" or end of file
    with open(test[0], 'r') as f:
        lines = f.readlines()
        test_code = []
        test_count = 0
        for line in lines:
            if line.lstrip().startswith("@test"):
                if test_count == test[1]:
                    break
                test_count += 1
                if test_count == test[1]:
                    test_code.append(line)
            elif test_count == test[1]:
                test_code.append(line)
    # write the test to a file
    with open(os.path.join(test_dir, "test.xppt"), 'w') as f:
        f.writelines(test_code)

    # write the code to a file (remove all test directives which are lines that start with @)
    with open(os.path.join(test_dir, "test.xpp"), 'w') as f:
        for line in test_code:
            if not line.lstrip().startswith("@"):
                f.write(line)

    
    
    # two supported types of tests: compile and check
    # compile we just run the compiler on the test code
    # check we run the compiler and check the intermediate output for a given condition
    # the first line should be @test compile or @test check
    if "compile" in test_code[0]:
        # compile the test code
        # subprocess.run(["./build/xppc", os.path.join(test_dir, "test.xpp"), "--", "-c", "-o", os.path.join(test_dir, "test.o")], check=True)
        # capture output and errors
        # write to a log file
        with open(os.path.join(test_dir, "compile.log"), 'w') as log_file:
            print(f"{test[0]} (test {test[1]}) compile... ", end='')
            log_file.write("Starting compilation...\n")
            try:
                subprocess.run(["./build/xppc", os.path.join(test_dir, "test.xpp"), "--", "-c", "-o", os.path.join(test_dir, "test.o")], check=True, stdout=log_file, stderr=subprocess.STDOUT)
                log_file.write("Compilation successful.\n")
                print("[OK]", flush=True)
            except Exception as e:
                log_file.write("An error occurred during compilation.\n")
                log_file.write(str(e))
                print(f"[FAILED]", flush=True)
    elif "check" in test_code[0]:
        # compie (but we ignore if the compilation fails) we only care about the intermediate output
        with open(os.path.join(test_dir, "check.log"), 'w') as log_file:
            print(f"{test[0]} (test {test[1]}) check... ", end='')
            log_file.write("Starting compilation for check...\n")
            try:
                # run the compiler with the test code
                subprocess.run(["./build/xppc", os.path.join(test_dir, "test.xpp"), "--", "-c", "-o", os.path.join(test_dir, "test.o")], check=True, stdout=log_file, stderr=subprocess.STDOUT)
                log_file.write("Compilation successful for check.\n")

            except subprocess.CalledProcessError as e:
                log_file.write("An error occurred during compilation for check.\n")
                log_file.write(str(e))
            
            # Now we need to check the intermediate output
            if not os.path.exists(os.path.join(test_dir, "test.gen.h")):
                log_file.write("No intermediate output file found (test.gen.h).\n")
                print("[FAILED: No header]", flush=True)
                return
            if not os.path.exists(os.path.join(test_dir, "test.gen.cpp")):
                log_file.write("No intermediate output file found (test.gen.cpp).\n")
                print("[FAILED: No source]", flush=True)
                return
            
            # The check test should have something like this at the top of the xppt:
            # @test check
            # @c !h.contains("testfunction")
            # @c c.contains("testfunction")

            # we will just get the conditions and use eval to evaluate them
            conditions = []
            for line in test_code:
                if line.lstrip().startswith("@c "):
                    # get the condition after the space
                    condition = line.split(" ", 1)[1].strip()
                    conditions.append(condition)
            # Now we need to check the conditions
            # We will read the generated header and source files and check for the conditions
            header_file_path = os.path.join(test_dir, "test.gen.h")
            source_file_path = os.path.join(test_dir, "test.gen.cpp")
            try:
                with open(header_file_path, 'r') as header_file:
                    header_content = header_file.read()
            except FileNotFoundError:
                log_file.write(f"Header file {header_file_path} not found.\n")
                print("[FAILED: Header not found]", flush=True)
                return
            try:
                with open(source_file_path, 'r') as source_file:
                    source_content = source_file.read()
            except FileNotFoundError:
                log_file.write(f"Source file {source_file_path} not found.\n")
                print("[FAILED: Source not found]", flush=True)
                return
            
            # Now we will evaluate the conditions
            all_conditions_met = True
            for condition in conditions:
                # just use eval with h=header_content and c=source_content
                try:
                    # Prepare the environment for eval
                    eval_env = {
                        'h': header_content,
                        'c': source_content
                    }
                    # Evaluate the condition
                    if not eval(condition, {}, eval_env):
                        log_file.write(f"Condition failed: {condition}\n")
                        all_conditions_met = False
                except Exception as e:
                    log_file.write(f"Error evaluating condition '{condition}': {str(e)}\n")
                    all_conditions_met = False
            if all_conditions_met:
                log_file.write("All conditions met.\n")
                print("[OK]", flush=True)
            else:
                log_file.write("Not all conditions were met.\n")
                print("[FAILED: Conditions not met]", flush=True)
    else:
        # If we reach here, it means the test directive was not recognized
        print(f"{test[0]} (test {test[1]}) has an unrecognized test directive. Please use @test compile or @test check.", flush=True)
        return



def run_tests(test):
    for i in range(test[1]):
        os.makedirs(os.path.join("test_output", os.path.splitext(os.path.basename(test[0]))[0], str(i)), exist_ok=True)
        run_test((test[0], i+1), os.path.join("test_output", os.path.splitext(os.path.basename(test[0]))[0], str(i)))
    

shutil.rmtree("test_output", ignore_errors=True)  # Clean up previous test outputs 
time.sleep(1)

run_tests(TESTS[0])  # For now, just run the first test
