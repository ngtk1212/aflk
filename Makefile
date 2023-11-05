CC := gcc
CFLAGS := -W -Wall

all: aflk

aflk: make_output
	$(CC) $(CFLAGS) ./src/c/aflk.c  -I ./src/h -o ./output/aflk

make_output:
	-mkdir ./output

.PHONY: clean
clean:
	-rm ./output/* 
	-rmdir ./output 

.DEFAULT_GOAL=aflk
