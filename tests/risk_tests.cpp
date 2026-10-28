#define main arcadeMain
#include "../game.cpp"
#undef main

#include <cassert>

int main() {
  std::ostringstream output;
  auto *previous = std::cout.rdbuf(output.rdbuf());
  bool sawWin = false;
  bool sawLoss = false;
  bool sawDeath = false;
  for (unsigned int seed = 0; seed < 1000; ++seed) {
    std::srand(seed);
    hp = 100;
    resources = 0;
    score = 0;
    turn = 1;
    assert(riskOperation());
    if (hp == 100) {
      sawWin = true;
      assert(score >= 200 && score <= 500);
      assert(resources == score);
    } else {
      sawLoss = true;
      assert(hp >= 50 && hp <= 70);
      assert(score == 0 && resources == 0);
    }
    const int reward = score;
    finishTurn(true);
    assert(score == reward + 10 && turn == 2);

    std::srand(seed);
    hp = 1;
    resources = 0;
    score = 0;
    turn = 1;
    assert(riskOperation());
    if (hp == 0) {
      sawDeath = true;
      finishTurn(true);
      assert(score == 0 && turn == 1);
    }

    std::srand(seed);
    hp = 100;
    resources = std::numeric_limits<int>::max();
    score = std::numeric_limits<int>::max();
    assert(riskOperation());
    assert(resources == std::numeric_limits<int>::max());
    assert(score == std::numeric_limits<int>::max());
  }
  assert(sawWin && sawLoss && sawDeath);
  hp = 0;
  score = 0;
  resources = 50;
  assert(!riskOperation());
  assert(score == 0 && resources == 50 && hp == 0);
  std::cout.rdbuf(previous);
  std::cout << "Risk checks passed (1000 seeds).\n";
}
