#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

make

run_test() {
    local test_name=$1
    local input=$2
    local expected_output=$3

    echo -n "Running test: $test_name... "

    echo "$input" > test_input.txt

    ./bsq test_input.txt > test_output.txt 2>&1

    if diff -q test_output.txt <(echo "$expected_output") >/dev/null; then
        echo -e "${GREEN}PASSED${NC}"
    else
        echo -e "${RED}FAILED${NC}"
        echo "Expected:"
        echo "$expected_output"
        echo "Got:"
        cat test_output.txt
    fi

    rm test_input.txt test_output.txt
}

run_test "Basic 3x3 map" \
"3.ox
...
...
..." \
"xxx
xxx
xxx"

run_test "5x5 map with obstacles" \
"5.ox
.....
.o...
.....
....o
....." \
"xxxx.
xoxx.
xxxx.
xxxo.
xxxx."

run_test "1x1 map" \
"1.ox
." \
"x"

run_test "Map with only obstacles" \
"3.ox
ooo
ooo
ooo" \
"ooo
ooo
ooo"

run_test "Invalid map (wrong number of rows)" \
"4.ox
...
...
..." \
"map error"

run_test "Invalid map (inconsistent row length)" \
"3.ox
....
...
...." \
"map error"

run_test "Large map (10x10)" \
"10.ox
..........
.o........
..........
...o......
....o.....
..........
......o...
..........
.........o
.........." \
"xxxxxxx...
xoxxxxxx...
xxxxxxxx...
xxxoxxxx...
xxxxoxxx...
xxxxxxxx...
xxxxxxoxxx.
xxxxxxxxxx.
xxxxxxxo...
xxxxxxxx..."

run_test "Map with different characters" \
"5abc
aabaa
baaaa
aaaaa
aaaba
aaaaa" \
"cccaa
cccaa
cccaa
aaaba
aaaaa"

make fclean

echo "All tests completed."
