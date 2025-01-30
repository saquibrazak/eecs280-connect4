# Makefile
# Build rules for EECS 280 project 3

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

# Run a regression test
test: Game_tests.exe
	./Game_tests.exe

Game_tests.exe: Game_tests.cpp Game.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

connect4.exe: connect4.cpp CommandUI.cpp Game.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.SUFFIXES:

.PHONY: clean

clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump