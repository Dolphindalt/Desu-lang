CC=g++
FLAGS=-std=c++17

make:
	$(CC) $(FLAGS) $(wildcard *.cpp) -o desu