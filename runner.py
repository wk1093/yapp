import sys
import os
import subprocess

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



def run_test(test):
    os.mkdir("test_output")
    os.mkdir(os.path.join("test_output", os.path.splitext(os.path.basename(test[0]))[0]))
    for i in range(test[1]):
        os.mkdir(os.path.join("test_output", os.path.splitext(os.path.basename(test[0]))[0], str(i)))

run_test(TESTS[0])  # For now, just run the first test
    


