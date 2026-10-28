CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -Werror

.PHONY: all test clean
all: game

game: game.cpp
	$(CXX) $(CXXFLAGS) game.cpp -o game

build/game-tests: tests/game_tests.cpp game.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) tests/game_tests.cpp -o $@

test: game build/game-tests
	./build/game-tests
	printf 'abc\n999\n0\n' | ./game | tail -n 1 | grep -F 'рекорд: 0 очков!'
	$(CXX) $(CXXFLAGS) -fsyntax-only main.cpp

clean:
	$(RM) game
	$(RM) -r build
