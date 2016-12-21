CC = g++
CFLAG = -g -Wall -std=c++11

all: main

main: main.cpp STMap.o
	$(CC) $(CFLAG) $^ -o $@

test: test.cpp SplayTree.h bst.h
	$(CC) $(CFLAG) $< -o $@

STMap.o: STMap.cpp SplayTree.h bst.h
	$(CC) $(CFLAG) -c $< -o $@

.PHONY:

clean:
	rm -f *.o main test
