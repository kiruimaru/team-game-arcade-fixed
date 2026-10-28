#define main arcadeMain
#include "../game.cpp"
#undef main

#include <cassert>

void resetGame(int health = 100, int caps = 50) {
  hp = health;
  resources = caps;
  score = 0;
  turn = 1;
}

void testLoop() {
  resetGame();
  finishTurn(false);
  assert(score == 0 && turn == 1);
  finishTurn(true);
  assert(score == 10 && turn == 2);
  hp = 0;
  finishTurn(true);
  assert(score == 10 && turn == 2);
  int value = std::numeric_limits<int>::max() - 5;
  addCapped(value, 10);
  assert(value == std::numeric_limits<int>::max());
}

int main() {
  std::ostringstream output;
  auto *previousOutput = std::cout.rdbuf(output.rdbuf());
  testLoop();
  std::cout.rdbuf(previousOutput);
  std::cout << "All game checks passed.\n";
}
