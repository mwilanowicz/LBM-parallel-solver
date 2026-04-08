.PHONY: main test clean
FLAGS = -std=c++20 -pthread -Wall -Iinclude
CC = g++

main:
	@$(CC) src/Lattice.cpp src/main.cpp -o main $(FLAGS) && ./main

test:
	@$(CC) src/Lattice.cpp test/test_lattice.cpp -o test_bin $(FLAGS) && ./test_bin

clean:
	@rm -f main test_bin