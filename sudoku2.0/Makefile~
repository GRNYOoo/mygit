CXXFLAGS+=-O2 -ggdb -DDEBUG
CXXFLAGS+=-Wall -Wextra

all: sudoku1-1

sudoku1-1: main.cc neighbor.cc sudoku_basic.cc 
	g++ -O2 -o $@ $^ -lpthread
