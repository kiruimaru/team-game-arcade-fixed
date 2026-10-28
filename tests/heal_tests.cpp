#define main arcadeMain
#include "../game.cpp"
#undef main

#include <cassert>

void checkHeal(int health, int caps, const std::string &input,
               bool expected, int expectedHealth, int expectedCaps) {
  hp = health;
  resources = caps;
  score = 0;
  turn = 1;
  std::istringstream commands(input);
  auto *previous = std::cin.rdbuf(commands.rdbuf());
  std::cin.clear();
  const bool completed = recovery();
  std::cin.rdbuf(previous);
  std::cin.clear();
  assert(completed == expected);
  assert(hp == expectedHealth && resources == expectedCaps);
  finishTurn(completed);
  assert(score == (expected ? 10 : 0));
  assert(turn == (expected ? 2 : 1));
}

int main() {
  std::ostringstream output;
  auto *previous = std::cout.rdbuf(output.rdbuf());
  checkHeal(50, 50, "1\n", true, 60, 40);
  checkHeal(50, 50, "2\n", true, 80, 25);
  checkHeal(95, 10, "1\n", true, 100, 0);
  assert(output.str().find("Восстановлено HP: 5") != std::string::npos);
  checkHeal(99, 25, "2\n", true, 100, 0);
  checkHeal(100, 50, "1\n", false, 100, 50);
  checkHeal(0, 50, "1\n", false, 0, 50);
  checkHeal(50, 0, "1\n", false, 50, 0);
  checkHeal(50, 9, "1\n", false, 50, 9);
  checkHeal(50, 24, "2\n", false, 50, 24);
  checkHeal(50, 50, "0\n", false, 50, 50);
  checkHeal(50, 50, "99\n", false, 50, 50);
  checkHeal(50, 50, "abc\n", false, 50, 50);
  checkHeal(50, 50, "1abc\n", false, 50, 50);
  checkHeal(50, 50, "999999999999999999999\n", false, 50, 50);
  checkHeal(50, 50, "", false, 50, 50);
  std::cout.rdbuf(previous);
  std::cout << "Healing checks passed (15 scenarios).\n";
}
