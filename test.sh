#!/bin/bash

# build
echo ================================
echo build
echo ================================
make test
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# run test
echo ================================
echo run test
echo ================================

echo dummy > ./test_output/dummy.txt
./test_output/test_aflk

# check coverage
echo ================================
echo check coverage
echo ================================
gcov  -o ./test_output ./test_output/test_aflk.gcda
mv ./*.gcov ./test_output

exit 0
