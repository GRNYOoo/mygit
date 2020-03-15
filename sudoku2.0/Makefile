CXXFLAGS+=-O2 -ggdb -DDEBUG
CXXFLAGS+=-Wall -Wextra

all: sudoku2

sudoku2: main.cc neighbor.cc sudoku_basic.cc 
	g++ -O2 -o $@ $^ -lpthread
