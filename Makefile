CC = g++
CFLAG = -g -Wall -std=c++11

all: main

main: main.cpp SplayTree.h bst.h
	$(CC) $(CFLAG) $< -o $@

.PHONY:

clean:
	rm -f *.o main
