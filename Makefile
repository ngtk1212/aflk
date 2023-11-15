CC := gcc
CFLAGS := -W -Wall
TEST_CFLAGS := $(CFLAGS) -DDEBUG -Dmain=_main_for_cunit -fprofile-arcs -ftest-coverage

all: aflk

aflk: make_output
	$(CC) $(CFLAGS) ./src/c/aflk.c  -I ./src/h -o ./output/aflk

test: make_test_output
	$(CC) tests/test_aflk.c $(TEST_CFLAGS) -g -L/usr/lib -lcunit -I ./src/h -o ./test_output/test_aflk

make_output:
	-mkdir ./output

make_test_output:
	-mkdir ./test_output

.PHONY: clean
clean:
	-rm ./output/* 
	-rmdir ./output 
	-rm ./test_output/* 
	-rmdir ./test_output
 
.DEFAULT_GOAL=aflk
